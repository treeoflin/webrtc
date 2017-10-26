/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef MODULES_AUDIO_CODING_NETEQ_DECODER_DATABASE_H_
#define MODULES_AUDIO_CODING_NETEQ_DECODER_DATABASE_H_

#include <map>
#include <memory>
#include <string>

#include "api/audio_codecs/audio_decoder_factory.h"
#include "api/audio_codecs/audio_format.h"
#include "common_types.h"  // NOLINT(build/include)  // NULL
#include "modules/audio_coding/codecs/cng/webrtc_cng.h"
#include "modules/audio_coding/neteq/neteq_decoder_enum.h"
#include "modules/audio_coding/neteq/packet.h"
#include "rtc_base/constructormagic.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "typedefs.h"  // NOLINT(build/include)

namespace webrtc {

class DecoderDatabase {
 public:
  enum DatabaseReturnCodes {
    kOK = 0,
    kInvalidRtpPayloadType = -1,
    kCodecNotSupported = -2,
    kInvalidSampleRate = -3,
    kDecoderExists = -4,
    kDecoderNotFound = -5,
    kInvalidPointer = -6
  };

  // Class that stores decoder info in the database.
  class DecoderInfo {
   public:
    DecoderInfo(const SdpAudioFormat& audio_format,
                AudioDecoderFactory* factory,
                const std::string& codec_name);
    explicit DecoderInfo(const SdpAudioFormat& audio_format,
                         AudioDecoderFactory* factory = nullptr);
    explicit DecoderInfo(NetEqDecoder ct,
                         AudioDecoderFactory* factory = nullptr);
    DecoderInfo(const SdpAudioFormat& audio_format,
                AudioDecoder* ext_dec,
                const std::string& codec_name);
    DecoderInfo(DecoderInfo&&);
    ~DecoderInfo();

    // Was this info object created with a specification that allows us to
    // actually produce a decoder?
    bool CanGetDecoder() const;

    // Get the AudioDecoder object, creating it first if necessary.
    AudioDecoder* GetDecoder() const;

    // Delete the AudioDecoder object, unless it's external. (This means we can
    // always recreate it later if we need it.)
    void DropDecoder() const { decoder_.reset(); }

    int SampleRateHz() const {
      if (IsDtmf()) {
        // DTMF has a 1:1 mapping between clock rate and sample rate.
        return audio_format_.clockrate_hz;
      }
      const AudioDecoder* decoder = GetDecoder();
      RTC_DCHECK_EQ(1, !!decoder + !!cng_decoder_);
      return decoder ? decoder->SampleRateHz() : cng_decoder_->sample_rate_hz;
    }

    const SdpAudioFormat& GetFormat() const { return audio_format_; }

    // Returns true if the decoder's format is comfort noise.
    bool IsComfortNoise() const {
      RTC_DCHECK_EQ(!!cng_decoder_, subtype_ == Subtype::kComfortNoise);
      return subtype_ == Subtype::kComfortNoise;
    }

    // Returns true if the decoder's format is DTMF.
    bool IsDtmf() const {
      return subtype_ == Subtype::kDtmf;
    }

    // Returns true if the decoder's format is RED.
    bool IsRed() const {
      return subtype_ == Subtype::kRed;
    }

    // Returns true if the decoder's format is named |name|.
    bool IsType(const char* name) const;
    // Returns true if the decoder's format is named |name|.
    bool IsType(const std::string& name) const;

    const std::string& get_name() const { return name_; }

   private:
    // TODO(ossu): |name_| is kept here while we retain the old external
    //             decoder interface. Remove this once using an
    //             AudioDecoderFactory has supplanted the old functionality.
    const std::string name_;

    const SdpAudioFormat audio_format_;
    AudioDecoderFactory* const factory_;
    mutable std::unique_ptr<AudioDecoder> decoder_;

    // Set iff this is an external decoder.
    AudioDecoder* const external_decoder_;

    // Set iff this is a comfort noise decoder.
    struct CngDecoder {
      static rtc::Optional<CngDecoder> Create(const SdpAudioFormat& format);
      int sample_rate_hz;
    };
    const rtc::Optional<CngDecoder> cng_decoder_;

    enum class Subtype : int8_t {
      kNormal,
      kComfortNoise,
      kDtmf,
      kRed
    };

    static Subtype SubtypeFromFormat(const SdpAudioFormat& format);

    const Subtype subtype_;
  };

  // Maximum value for 8 bits, and an invalid RTP payload type (since it is
  // only 7 bits).
  static const uint8_t kRtpPayloadTypeError = 0xFF;

  DecoderDatabase(
      const rtc::scoped_refptr<AudioDecoderFactory>& decoder_factory);

  virtual ~DecoderDatabase();

  // Returns true if the database is empty.
  virtual bool Empty() const;

  // Returns the number of decoders registered in the database.
  virtual int Size() const;

  // Resets the database, erasing all registered payload types, and deleting
  // any AudioDecoder objects that were not externally created and inserted
  // using InsertExternal().
  virtual void Reset();

  // Replaces the existing set of decoders with the given set. Returns the
  // payload types that were reassigned or removed while doing so.
  virtual std::vector<int> SetCodecs(
      const std::map<int, SdpAudioFormat>& codecs);

  // Registers |rtp_payload_type| as a decoder of type |codec_type|. The |name|
  // is only used to populate the name field in the DecoderInfo struct in the
  // database, and can be arbitrary (including empty). Returns kOK on success;
  // otherwise an error code.
  virtual int RegisterPayload(uint8_t rtp_payload_type,
                              NetEqDecoder codec_type,
                              const std::string& name);

  // Registers a decoder for the given payload type. Returns kOK on success;
  // otherwise an error code.
  virtual int RegisterPayload(int rtp_payload_type,
                              const SdpAudioFormat& audio_format);

  // Registers an externally created AudioDecoder object, and associates it
  // as a decoder of type |codec_type| with |rtp_payload_type|.
  virtual int InsertExternal(uint8_t rtp_payload_type,
                             NetEqDecoder codec_type,
                             const std::string& codec_name,
                             AudioDecoder* decoder);

  // Removes the entry for |rtp_payload_type| from the database.
  // Returns kDecoderNotFound or kOK depending on the outcome of the operation.
  virtual int Remove(uint8_t rtp_payload_type);

  // Remove all entries.
  virtual void RemoveAll();

  // Returns a pointer to the DecoderInfo struct for |rtp_payload_type|. If
  // no decoder is registered with that |rtp_payload_type|, NULL is returned.
  virtual const DecoderInfo* GetDecoderInfo(uint8_t rtp_payload_type) const;

  // Sets the active decoder to be |rtp_payload_type|. If this call results in a
  // change of active decoder, |new_decoder| is set to true. The previous active
  // decoder's AudioDecoder object is deleted.
  virtual int SetActiveDecoder(uint8_t rtp_payload_type, bool* new_decoder);

  // Returns the current active decoder, or NULL if no active decoder exists.
  virtual AudioDecoder* GetActiveDecoder() const;

  // Sets the active comfort noise decoder to be |rtp_payload_type|. If this
  // call results in a change of active comfort noise decoder, the previous
  // active decoder's AudioDecoder object is deleted.
  virtual int SetActiveCngDecoder(uint8_t rtp_payload_type);

  // Returns the current active comfort noise decoder, or NULL if no active
  // comfort noise decoder exists.
  virtual ComfortNoiseDecoder* GetActiveCngDecoder() const;

  // The following are utility methods: they will look up DecoderInfo through
  // GetDecoderInfo and call the respective method on that info object, if it
  // exists.

  // Returns a pointer to the AudioDecoder object associated with
  // |rtp_payload_type|, or NULL if none is registered. If the AudioDecoder
  // object does not exist for that decoder, the object is created.
  AudioDecoder* GetDecoder(uint8_t rtp_payload_type) const;

  // Returns if |rtp_payload_type| is registered with a format named |name|.
  bool IsType(uint8_t rtp_payload_type, const char* name) const;

  // Returns if |rtp_payload_type| is registered with a format named |name|.
  bool IsType(uint8_t rtp_payload_type, const std::string& name) const;

  // Returns true if |rtp_payload_type| is registered as comfort noise.
  bool IsComfortNoise(uint8_t rtp_payload_type) const;

  // Returns true if |rtp_payload_type| is registered as DTMF.
  bool IsDtmf(uint8_t rtp_payload_type) const;

  // Returns true if |rtp_payload_type| is registered as RED.
  bool IsRed(uint8_t rtp_payload_type) const;

  // Returns kOK if all packets in |packet_list| carry payload types that are
  // registered in the database. Otherwise, returns kDecoderNotFound.
  int CheckPayloadTypes(const PacketList& packet_list) const;

 private:
  typedef std::map<uint8_t, DecoderInfo> DecoderMap;

  DecoderMap decoders_;
  int active_decoder_type_;
  int active_cng_decoder_type_;
  mutable std::unique_ptr<ComfortNoiseDecoder> active_cng_decoder_;
  rtc::scoped_refptr<AudioDecoderFactory> decoder_factory_;

  RTC_DISALLOW_COPY_AND_ASSIGN(DecoderDatabase);
};

}  // namespace webrtc
#endif  // MODULES_AUDIO_CODING_NETEQ_DECODER_DATABASE_H_
