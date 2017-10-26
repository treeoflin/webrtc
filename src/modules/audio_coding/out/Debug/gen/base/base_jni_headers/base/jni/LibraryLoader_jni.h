// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/base/library_loader/LibraryLoader

#ifndef org_chromium_base_library_loader_LibraryLoader_JNI
#define org_chromium_base_library_loader_LibraryLoader_JNI

#include <jni.h>

#include "../../../../../../../../../base/android/jni_generator/jni_generator_helper.h"

// Step 1: forward declarations.
JNI_REGISTRATION_EXPORT extern const char
    kClassPath_org_chromium_base_library_1loader_LibraryLoader[];
const char kClassPath_org_chromium_base_library_1loader_LibraryLoader[] =
    "org/chromium/base/library_loader/LibraryLoader";

// Leaking this jclass as we cannot use LazyInstance from some threads.
JNI_REGISTRATION_EXPORT base::subtle::AtomicWord
    g_org_chromium_base_library_1loader_LibraryLoader_clazz = 0;
#ifndef org_chromium_base_library_1loader_LibraryLoader_clazz_defined
#define org_chromium_base_library_1loader_LibraryLoader_clazz_defined
inline jclass org_chromium_base_library_1loader_LibraryLoader_clazz(JNIEnv* env)
    {
  return base::android::LazyGetClass(env,
      kClassPath_org_chromium_base_library_1loader_LibraryLoader,
      &g_org_chromium_base_library_1loader_LibraryLoader_clazz);
}
#endif

namespace base {
namespace android {

// Step 2: method stubs.

static jboolean LibraryLoaded(JNIEnv* env, const
    base::android::JavaParamRef<jobject>& jcaller);

JNI_GENERATOR_EXPORT jboolean
    Java_org_chromium_base_library_1loader_LibraryLoader_nativeLibraryLoaded(JNIEnv*
    env, jobject jcaller) {
  return LibraryLoaded(env, base::android::JavaParamRef<jobject>(env, jcaller));
}

static void RecordChromiumAndroidLinkerBrowserHistogram(JNIEnv* env, const
    base::android::JavaParamRef<jobject>& jcaller,
    jboolean isUsingBrowserSharedRelros,
    jboolean loadAtFixedAddressFailed,
    jint libraryLoadFromApkStatus,
    jlong libraryLoadTime);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_library_1loader_LibraryLoader_nativeRecordChromiumAndroidLinkerBrowserHistogram(JNIEnv*
    env, jobject jcaller,
    jboolean isUsingBrowserSharedRelros,
    jboolean loadAtFixedAddressFailed,
    jint libraryLoadFromApkStatus,
    jlong libraryLoadTime) {
  return RecordChromiumAndroidLinkerBrowserHistogram(env,
      base::android::JavaParamRef<jobject>(env, jcaller),
      isUsingBrowserSharedRelros, loadAtFixedAddressFailed,
      libraryLoadFromApkStatus, libraryLoadTime);
}

static void RecordLibraryPreloaderBrowserHistogram(JNIEnv* env, const
    base::android::JavaParamRef<jobject>& jcaller,
    jint status);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_library_1loader_LibraryLoader_nativeRecordLibraryPreloaderBrowserHistogram(JNIEnv*
    env, jobject jcaller,
    jint status) {
  return RecordLibraryPreloaderBrowserHistogram(env,
      base::android::JavaParamRef<jobject>(env, jcaller), status);
}

static void RegisterChromiumAndroidLinkerRendererHistogram(JNIEnv* env, const
    base::android::JavaParamRef<jobject>& jcaller,
    jboolean requestedSharedRelro,
    jboolean loadAtFixedAddressFailed,
    jlong libraryLoadTime);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_library_1loader_LibraryLoader_nativeRegisterChromiumAndroidLinkerRendererHistogram(JNIEnv*
    env, jobject jcaller,
    jboolean requestedSharedRelro,
    jboolean loadAtFixedAddressFailed,
    jlong libraryLoadTime) {
  return RegisterChromiumAndroidLinkerRendererHistogram(env,
      base::android::JavaParamRef<jobject>(env, jcaller), requestedSharedRelro,
      loadAtFixedAddressFailed, libraryLoadTime);
}

static void RegisterLibraryPreloaderRendererHistogram(JNIEnv* env, const
    base::android::JavaParamRef<jobject>& jcaller,
    jint status);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_library_1loader_LibraryLoader_nativeRegisterLibraryPreloaderRendererHistogram(JNIEnv*
    env, jobject jcaller,
    jint status) {
  return RegisterLibraryPreloaderRendererHistogram(env,
      base::android::JavaParamRef<jobject>(env, jcaller), status);
}

static base::android::ScopedJavaLocalRef<jstring> GetVersionNumber(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller);

JNI_GENERATOR_EXPORT jstring
    Java_org_chromium_base_library_1loader_LibraryLoader_nativeGetVersionNumber(JNIEnv*
    env, jobject jcaller) {
  return GetVersionNumber(env, base::android::JavaParamRef<jobject>(env,
      jcaller)).Release();
}

static jboolean ForkAndPrefetchNativeLibrary(JNIEnv* env, const
    base::android::JavaParamRef<jclass>& jcaller);

JNI_GENERATOR_EXPORT jboolean
    Java_org_chromium_base_library_1loader_LibraryLoader_nativeForkAndPrefetchNativeLibrary(JNIEnv*
    env, jclass jcaller) {
  return ForkAndPrefetchNativeLibrary(env,
      base::android::JavaParamRef<jclass>(env, jcaller));
}

static jint PercentageOfResidentNativeLibraryCode(JNIEnv* env, const
    base::android::JavaParamRef<jclass>& jcaller);

JNI_GENERATOR_EXPORT jint
    Java_org_chromium_base_library_1loader_LibraryLoader_nativePercentageOfResidentNativeLibraryCode(JNIEnv*
    env, jclass jcaller) {
  return PercentageOfResidentNativeLibraryCode(env,
      base::android::JavaParamRef<jclass>(env, jcaller));
}

static base::subtle::AtomicWord
    g_org_chromium_base_library_1loader_LibraryLoader_getLibraryProcessType = 0;
static jint Java_LibraryLoader_getLibraryProcessType(JNIEnv* env) {
  CHECK_CLAZZ(env, org_chromium_base_library_1loader_LibraryLoader_clazz(env),
      org_chromium_base_library_1loader_LibraryLoader_clazz(env), 0);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, org_chromium_base_library_1loader_LibraryLoader_clazz(env),
      "getLibraryProcessType",
"("
")"
"I",
      &g_org_chromium_base_library_1loader_LibraryLoader_getLibraryProcessType);

  jint ret =
env->CallStaticIntMethod(org_chromium_base_library_1loader_LibraryLoader_clazz(env),
          method_id);
  jni_generator::CheckException(env);
  return ret;
}

}  // namespace android
}  // namespace base

#endif  // org_chromium_base_library_loader_LibraryLoader_JNI
