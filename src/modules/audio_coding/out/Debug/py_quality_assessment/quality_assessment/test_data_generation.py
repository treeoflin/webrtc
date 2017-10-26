# Copyright (c) 2017 The WebRTC project authors. All Rights Reserved.
#
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file in the root of the source
# tree. An additional intellectual property rights grant can be found
# in the file PATENTS.  All contributing project authors may
# be found in the AUTHORS file in the root of the source tree.

"""Test data generators producing signals pairs intended to be used to
test the APM module. Each pair consists of a noisy input and a reference signal.
The former is used as APM input and it is generated by adding noise to a
clean audio track. The reference is the expected APM output.

Throughout this file, the following naming convention is used:
  - input signal: the clean signal (e.g., speech),
  - noise signal: the noise to be summed up to the input signal (e.g., white
    noise, Gaussian noise),
  - noisy signal: input + noise.
The noise signal may or may not be a function of the clean signal. For
instance, white noise is independently generated, whereas reverberation is
obtained by convolving the input signal with an impulse response.
"""

import logging
import os
import sys

try:
  import scipy.io
except ImportError:
  logging.critical('Cannot import the third-party Python package scipy')
  sys.exit(1)

from . import data_access
from . import exceptions
from . import signal_processing


class TestDataGenerator(object):
  """Abstract class responsible for the generation of noisy signals.

  Given a clean signal, it generates two streams named noisy signal and
  reference. The former is the clean signal deteriorated by the noise source,
  the latter goes through the same deterioration process, but more "gently".
  Noisy signal and reference are produced so that the reference is the signal
  expected at the output of the APM module when the latter is fed with the noisy
  signal.

  An test data generator generates one or more pairs.
  """

  NAME = None
  REGISTERED_CLASSES = {}

  def __init__(self, output_directory_prefix):
    self._output_directory_prefix = output_directory_prefix
    # Init dictionaries with one entry for each test data generator
    # configuration (e.g., different SNRs).
    # Noisy audio track files (stored separately in a cache folder).
    self._noisy_signal_filepaths = None
    # Path to be used for the APM simulation output files.
    self._apm_output_paths = None
    # Reference audio track files (stored separately in a cache folder).
    self._reference_signal_filepaths = None
    self.Clear()

  @classmethod
  def RegisterClass(cls, class_to_register):
    """Registers a TestDataGenerator implementation.

    Decorator to automatically register the classes that extend
    TestDataGenerator.
    Example usage:

    @TestDataGenerator.RegisterClass
    class IdentityGenerator(TestDataGenerator):
      pass
    """
    cls.REGISTERED_CLASSES[class_to_register.NAME] = class_to_register
    return class_to_register

  @property
  def config_names(self):
    return self._noisy_signal_filepaths.keys()

  @property
  def noisy_signal_filepaths(self):
    return self._noisy_signal_filepaths

  @property
  def apm_output_paths(self):
    return self._apm_output_paths

  @property
  def reference_signal_filepaths(self):
    return self._reference_signal_filepaths

  def Generate(
      self, input_signal_filepath, test_data_cache_path, base_output_path):
    """Generates a set of noisy input and reference audiotrack file pairs.

    This method initializes an empty set of pairs and calls the _Generate()
    method implemented in a concrete class.

    Args:
      input_signal_filepath: path to the clean input audio track file.
      test_data_cache_path: path to the cache of the generated audio track
                            files.
      base_output_path: base path where output is written.
    """
    self.Clear()
    self._Generate(
        input_signal_filepath, test_data_cache_path, base_output_path)

  def Clear(self):
    """Clears the generated output path dictionaries.
    """
    self._noisy_signal_filepaths = {}
    self._apm_output_paths = {}
    self._reference_signal_filepaths = {}

  def _Generate(
      self, input_signal_filepath, test_data_cache_path, base_output_path):
    """Abstract method to be implemented in each concrete class.
    """
    raise NotImplementedError()

  def _AddNoiseSnrPairs(self, base_output_path, noisy_mix_filepaths,
                        snr_value_pairs):
    """Adds noisy-reference signal pairs.

    Args:
      base_output_path: noisy tracks base output path.
      noisy_mix_filepaths: nested dictionary of noisy signal paths organized
                           by noisy track name and SNR level.
      snr_value_pairs: list of SNR pairs.
    """
    for noise_track_name in noisy_mix_filepaths:
      for snr_noisy, snr_refence in snr_value_pairs:
        config_name = '{0}_{1:d}_{2:d}_SNR'.format(
            noise_track_name, snr_noisy, snr_refence)
        output_path = self._MakeDir(base_output_path, config_name)
        self._AddNoiseReferenceFilesPair(
            config_name=config_name,
            noisy_signal_filepath=noisy_mix_filepaths[
                noise_track_name][snr_noisy],
            reference_signal_filepath=noisy_mix_filepaths[
                noise_track_name][snr_refence],
            output_path=output_path)

  def _AddNoiseReferenceFilesPair(self, config_name, noisy_signal_filepath,
                                  reference_signal_filepath, output_path):
    """Adds one noisy-reference signal pair.

    Args:
      config_name: name of the APM configuration.
      noisy_signal_filepath: path to noisy audio track file.
      reference_signal_filepath: path to reference audio track file.
      output_path: APM output path.
    """
    assert config_name not in self._noisy_signal_filepaths
    self._noisy_signal_filepaths[config_name] = os.path.abspath(
        noisy_signal_filepath)
    self._apm_output_paths[config_name] = os.path.abspath(output_path)
    self._reference_signal_filepaths[config_name] = os.path.abspath(
        reference_signal_filepath)

  def _MakeDir(self, base_output_path, test_data_generator_config_name):
    output_path = os.path.join(
        base_output_path,
        self._output_directory_prefix + test_data_generator_config_name)
    data_access.MakeDirectory(output_path)
    return output_path


@TestDataGenerator.RegisterClass
class IdentityTestDataGenerator(TestDataGenerator):
  """Generator that adds no noise.

  Both the noisy and the reference signals are the input signal.
  """

  NAME = 'identity'

  def __init__(self, output_directory_prefix):
    TestDataGenerator.__init__(self, output_directory_prefix)

  def _Generate(
      self, input_signal_filepath, test_data_cache_path, base_output_path):
    config_name = 'default'
    output_path = self._MakeDir(base_output_path, config_name)
    self._AddNoiseReferenceFilesPair(
        config_name=config_name,
        noisy_signal_filepath=input_signal_filepath,
        reference_signal_filepath=input_signal_filepath,
        output_path=output_path)


@TestDataGenerator.RegisterClass
class WhiteNoiseTestDataGenerator(TestDataGenerator):
  """Generator that adds white noise.
  """

  NAME = 'white_noise'

  # Each pair indicates the clean vs. noisy and reference vs. noisy SNRs.
  # The reference (second value of each pair) always has a lower amount of noise
  # - i.e., the SNR is 10 dB higher.
  _SNR_VALUE_PAIRS = [
      [20, 30],  # Smallest noise.
      [10, 20],
      [5, 15],
      [0, 10],  # Largest noise.
  ]

  _NOISY_SIGNAL_FILENAME_TEMPLATE = 'noise_{0:d}_SNR.wav'

  def __init__(self, output_directory_prefix):
    TestDataGenerator.__init__(self, output_directory_prefix)

  def _Generate(
      self, input_signal_filepath, test_data_cache_path, base_output_path):
    # Load the input signal.
    input_signal = signal_processing.SignalProcessingUtils.LoadWav(
        input_signal_filepath)

    # Create the noise track.
    noise_signal = signal_processing.SignalProcessingUtils.GenerateWhiteNoise(
        input_signal)

    # Create the noisy mixes (once for each unique SNR value).
    noisy_mix_filepaths = {}
    snr_values = set([snr for pair in self._SNR_VALUE_PAIRS for snr in pair])
    for snr in snr_values:
      noisy_signal_filepath = os.path.join(
          test_data_cache_path,
          self._NOISY_SIGNAL_FILENAME_TEMPLATE.format(snr))

      # Create and save if not done.
      if not os.path.exists(noisy_signal_filepath):
        # Create noisy signal.
        noisy_signal = signal_processing.SignalProcessingUtils.MixSignals(
            input_signal, noise_signal, snr)

        # Save.
        signal_processing.SignalProcessingUtils.SaveWav(
            noisy_signal_filepath, noisy_signal)

      # Add file to the collection of mixes.
      noisy_mix_filepaths[snr] = noisy_signal_filepath

    # Add all the noisy-reference signal pairs.
    for snr_noisy, snr_refence in self._SNR_VALUE_PAIRS:
      config_name = '{0:d}_{1:d}_SNR'.format(snr_noisy, snr_refence)
      output_path = self._MakeDir(base_output_path, config_name)
      self._AddNoiseReferenceFilesPair(
          config_name=config_name,
          noisy_signal_filepath=noisy_mix_filepaths[snr_noisy],
          reference_signal_filepath=noisy_mix_filepaths[snr_refence],
          output_path=output_path)


# TODO(alessiob): remove comment when class implemented.
# @TestDataGenerator.RegisterClass
class NarrowBandNoiseTestDataGenerator(TestDataGenerator):
  """Generator that adds narrow-band noise.
  """

  NAME = 'narrow_band_noise'

  def __init__(self, output_directory_prefix):
    TestDataGenerator.__init__(self, output_directory_prefix)

  def _Generate(
      self, input_signal_filepath, test_data_cache_path, base_output_path):
    # TODO(alessiob): implement.
    pass


@TestDataGenerator.RegisterClass
class AdditiveNoiseTestDataGenerator(TestDataGenerator):
  """Generator that adds noise loops.

  This generator uses all the wav files in a given path (default: noise_tracks/)
  and mixes them to the clean speech with different target SNRs (hard-coded).
  """

  NAME = 'additive_noise'
  _NOISY_SIGNAL_FILENAME_TEMPLATE = '{0}_{1:d}_SNR.wav'

  DEFAULT_NOISE_TRACKS_PATH = os.path.join(
      os.path.dirname(__file__), os.pardir, 'noise_tracks')

  # TODO(alessiob): Make the list of SNR pairs customizable.
  # Each pair indicates the clean vs. noisy and reference vs. noisy SNRs.
  # The reference (second value of each pair) always has a lower amount of noise
  # - i.e., the SNR is 10 dB higher.
  _SNR_VALUE_PAIRS = [
      [20, 30],  # Smallest noise.
      [10, 20],
      [5, 15],
      [0, 10],  # Largest noise.
  ]

  def __init__(self, output_directory_prefix, noise_tracks_path):
    TestDataGenerator.__init__(self, output_directory_prefix)
    self._noise_tracks_path = noise_tracks_path
    self._noise_tracks_file_names = [n for n in os.listdir(
        self._noise_tracks_path) if n.lower().endswith('.wav')]
    if len(self._noise_tracks_file_names) == 0:
      raise exceptions.InitializationException(
          'No wav files found in the noise tracks path %s' % (
              self._noise_tracks_path))

  def _Generate(
      self, input_signal_filepath, test_data_cache_path, base_output_path):
    """Generates test data pairs using environmental noise.

    For each noise track and pair of SNR values, the following two audio tracks
    are created: the noisy signal and the reference signal. The former is
    obtained by mixing the (clean) input signal to the corresponding noise
    track enforcing the target SNR.
    """
    # Init.
    snr_values = set([snr for pair in self._SNR_VALUE_PAIRS for snr in pair])

    # Load the input signal.
    input_signal = signal_processing.SignalProcessingUtils.LoadWav(
        input_signal_filepath)

    noisy_mix_filepaths = {}
    for noise_track_filename in self._noise_tracks_file_names:
      # Load the noise track.
      noise_track_name, _ = os.path.splitext(noise_track_filename)
      noise_track_filepath = os.path.join(
          self._noise_tracks_path, noise_track_filename)
      if not os.path.exists(noise_track_filepath):
        logging.error('cannot find the <%s> noise track', noise_track_filename)
        raise exceptions.FileNotFoundError()

      noise_signal = signal_processing.SignalProcessingUtils.LoadWav(
          noise_track_filepath)

      # Create the noisy mixes (once for each unique SNR value).
      noisy_mix_filepaths[noise_track_name] = {}
      for snr in snr_values:
        noisy_signal_filepath = os.path.join(
            test_data_cache_path,
            self._NOISY_SIGNAL_FILENAME_TEMPLATE.format(noise_track_name, snr))

        # Create and save if not done.
        if not os.path.exists(noisy_signal_filepath):
          # Create noisy signal.
          noisy_signal = signal_processing.SignalProcessingUtils.MixSignals(
              input_signal, noise_signal, snr,
              pad_noise=signal_processing.SignalProcessingUtils.MixPadding.LOOP)

          # Save.
          signal_processing.SignalProcessingUtils.SaveWav(
              noisy_signal_filepath, noisy_signal)

        # Add file to the collection of mixes.
        noisy_mix_filepaths[noise_track_name][snr] = noisy_signal_filepath

    # Add all the noise-SNR pairs.
    self._AddNoiseSnrPairs(
        base_output_path, noisy_mix_filepaths, self._SNR_VALUE_PAIRS)


@TestDataGenerator.RegisterClass
class ReverberationTestDataGenerator(TestDataGenerator):
  """Generator that adds reverberation noise.

  TODO(alessiob): Make this class more generic since the impulse response can be
  anything (not just reverberation); call it e.g.,
  ConvolutionalNoiseTestDataGenerator.
  """

  NAME = 'reverberation'

  _IMPULSE_RESPONSES = {
      'lecture': 'air_binaural_lecture_0_0_1.mat',  # Long echo.
      'booth': 'air_binaural_booth_0_0_1.mat',  # Short echo.
  }
  _MAX_IMPULSE_RESPONSE_LENGTH = None

  # Each pair indicates the clean vs. noisy and reference vs. noisy SNRs.
  # The reference (second value of each pair) always has a lower amount of noise
  # - i.e., the SNR is 5 dB higher.
  _SNR_VALUE_PAIRS = [
      [3, 8],  # Smallest noise.
      [-3, 2],  # Largest noise.
  ]

  _NOISE_TRACK_FILENAME_TEMPLATE = '{0}.wav'
  _NOISY_SIGNAL_FILENAME_TEMPLATE = '{0}_{1:d}_SNR.wav'

  def __init__(self, output_directory_prefix, aechen_ir_database_path):
    TestDataGenerator.__init__(self, output_directory_prefix)
    self._aechen_ir_database_path = aechen_ir_database_path

  def _Generate(
      self, input_signal_filepath, test_data_cache_path, base_output_path):
    """Generates test data pairs using reverberation noise.

    For each impulse response, one noise track is created. For each impulse
    response and pair of SNR values, the following 2 audio tracks are
    created: the noisy signal and the reference signal. The former is
    obtained by mixing the (clean) input signal to the corresponding noise
    track enforcing the target SNR.
    """
    # Init.
    snr_values = set([snr for pair in self._SNR_VALUE_PAIRS for snr in pair])

    # Load the input signal.
    input_signal = signal_processing.SignalProcessingUtils.LoadWav(
        input_signal_filepath)

    noisy_mix_filepaths = {}
    for impulse_response_name in self._IMPULSE_RESPONSES:
      noise_track_filename = self._NOISE_TRACK_FILENAME_TEMPLATE.format(
          impulse_response_name)
      noise_track_filepath = os.path.join(
          test_data_cache_path, noise_track_filename)
      noise_signal = None
      try:
        # Load noise track.
        noise_signal = signal_processing.SignalProcessingUtils.LoadWav(
            noise_track_filepath)
      except exceptions.FileNotFoundError:
        # Generate noise track by applying the impulse response.
        impulse_response_filepath = os.path.join(
            self._aechen_ir_database_path,
            self._IMPULSE_RESPONSES[impulse_response_name])
        noise_signal = self._GenerateNoiseTrack(
            noise_track_filepath, input_signal, impulse_response_filepath)
      assert noise_signal is not None

      # Create the noisy mixes (once for each unique SNR value).
      noisy_mix_filepaths[impulse_response_name] = {}
      for snr in snr_values:
        noisy_signal_filepath = os.path.join(
            test_data_cache_path,
            self._NOISY_SIGNAL_FILENAME_TEMPLATE.format(
                impulse_response_name, snr))

        # Create and save if not done.
        if not os.path.exists(noisy_signal_filepath):
          # Create noisy signal.
          noisy_signal = signal_processing.SignalProcessingUtils.MixSignals(
              input_signal, noise_signal, snr)

          # Save.
          signal_processing.SignalProcessingUtils.SaveWav(
              noisy_signal_filepath, noisy_signal)

        # Add file to the collection of mixes.
        noisy_mix_filepaths[impulse_response_name][snr] = noisy_signal_filepath

    # Add all the noise-SNR pairs.
    self._AddNoiseSnrPairs(base_output_path, noisy_mix_filepaths,
                           self._SNR_VALUE_PAIRS)

  def _GenerateNoiseTrack(self, noise_track_filepath, input_signal,
                            impulse_response_filepath):
    """Generates noise track.

    Generate a signal by convolving input_signal with the impulse response in
    impulse_response_filepath; then save to noise_track_filepath.

    Args:
      noise_track_filepath: output file path for the noise track.
      input_signal: (clean) input signal samples.
      impulse_response_filepath: impulse response file path.

    Returns:
      AudioSegment instance.
    """
    # Load impulse response.
    data = scipy.io.loadmat(impulse_response_filepath)
    impulse_response = data['h_air'].flatten()
    if self._MAX_IMPULSE_RESPONSE_LENGTH is not None:
      logging.info('truncating impulse response from %d to %d samples',
                   len(impulse_response), self._MAX_IMPULSE_RESPONSE_LENGTH)
      impulse_response = impulse_response[:self._MAX_IMPULSE_RESPONSE_LENGTH]

    # Apply impulse response.
    processed_signal = (
        signal_processing.SignalProcessingUtils.ApplyImpulseResponse(
            input_signal, impulse_response))

    # Save.
    signal_processing.SignalProcessingUtils.SaveWav(
        noise_track_filepath, processed_signal)

    return processed_signal
