// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/base/TraceEvent

#ifndef org_chromium_base_TraceEvent_JNI
#define org_chromium_base_TraceEvent_JNI

#include <jni.h>

#include "../../../../../../../../../base/android/jni_generator/jni_generator_helper.h"

// Step 1: forward declarations.
JNI_REGISTRATION_EXPORT extern const char
    kClassPath_org_chromium_base_TraceEvent[];
const char kClassPath_org_chromium_base_TraceEvent[] =
    "org/chromium/base/TraceEvent";

// Leaking this jclass as we cannot use LazyInstance from some threads.
JNI_REGISTRATION_EXPORT base::subtle::AtomicWord
    g_org_chromium_base_TraceEvent_clazz = 0;
#ifndef org_chromium_base_TraceEvent_clazz_defined
#define org_chromium_base_TraceEvent_clazz_defined
inline jclass org_chromium_base_TraceEvent_clazz(JNIEnv* env) {
  return base::android::LazyGetClass(env,
      kClassPath_org_chromium_base_TraceEvent,
      &g_org_chromium_base_TraceEvent_clazz);
}
#endif

namespace base {
namespace android {

// Step 2: method stubs.

static void RegisterEnabledObserver(JNIEnv* env, const
    base::android::JavaParamRef<jclass>& jcaller);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_TraceEvent_nativeRegisterEnabledObserver(JNIEnv* env,
    jclass jcaller) {
  return RegisterEnabledObserver(env, base::android::JavaParamRef<jclass>(env,
      jcaller));
}

static void StartATrace(JNIEnv* env, const base::android::JavaParamRef<jclass>&
    jcaller);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_TraceEvent_nativeStartATrace(JNIEnv* env, jclass
    jcaller) {
  return StartATrace(env, base::android::JavaParamRef<jclass>(env, jcaller));
}

static void StopATrace(JNIEnv* env, const base::android::JavaParamRef<jclass>&
    jcaller);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_TraceEvent_nativeStopATrace(JNIEnv* env, jclass
    jcaller) {
  return StopATrace(env, base::android::JavaParamRef<jclass>(env, jcaller));
}

static void Instant(JNIEnv* env, const base::android::JavaParamRef<jclass>&
    jcaller,
    const base::android::JavaParamRef<jstring>& name,
    const base::android::JavaParamRef<jstring>& arg);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_TraceEvent_nativeInstant(JNIEnv* env, jclass jcaller,
    jstring name,
    jstring arg) {
  return Instant(env, base::android::JavaParamRef<jclass>(env, jcaller),
      base::android::JavaParamRef<jstring>(env, name),
      base::android::JavaParamRef<jstring>(env, arg));
}

static void Begin(JNIEnv* env, const base::android::JavaParamRef<jclass>&
    jcaller,
    const base::android::JavaParamRef<jstring>& name,
    const base::android::JavaParamRef<jstring>& arg);

JNI_GENERATOR_EXPORT void Java_org_chromium_base_TraceEvent_nativeBegin(JNIEnv*
    env, jclass jcaller,
    jstring name,
    jstring arg) {
  return Begin(env, base::android::JavaParamRef<jclass>(env, jcaller),
      base::android::JavaParamRef<jstring>(env, name),
      base::android::JavaParamRef<jstring>(env, arg));
}

static void End(JNIEnv* env, const base::android::JavaParamRef<jclass>& jcaller,
    const base::android::JavaParamRef<jstring>& name,
    const base::android::JavaParamRef<jstring>& arg);

JNI_GENERATOR_EXPORT void Java_org_chromium_base_TraceEvent_nativeEnd(JNIEnv*
    env, jclass jcaller,
    jstring name,
    jstring arg) {
  return End(env, base::android::JavaParamRef<jclass>(env, jcaller),
      base::android::JavaParamRef<jstring>(env, name),
      base::android::JavaParamRef<jstring>(env, arg));
}

static void BeginToplevel(JNIEnv* env, const
    base::android::JavaParamRef<jclass>& jcaller,
    const base::android::JavaParamRef<jstring>& target);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_TraceEvent_nativeBeginToplevel(JNIEnv* env, jclass
    jcaller,
    jstring target) {
  return BeginToplevel(env, base::android::JavaParamRef<jclass>(env, jcaller),
      base::android::JavaParamRef<jstring>(env, target));
}

static void EndToplevel(JNIEnv* env, const base::android::JavaParamRef<jclass>&
    jcaller);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_TraceEvent_nativeEndToplevel(JNIEnv* env, jclass
    jcaller) {
  return EndToplevel(env, base::android::JavaParamRef<jclass>(env, jcaller));
}

static void StartAsync(JNIEnv* env, const base::android::JavaParamRef<jclass>&
    jcaller,
    const base::android::JavaParamRef<jstring>& name,
    jlong id);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_TraceEvent_nativeStartAsync(JNIEnv* env, jclass
    jcaller,
    jstring name,
    jlong id) {
  return StartAsync(env, base::android::JavaParamRef<jclass>(env, jcaller),
      base::android::JavaParamRef<jstring>(env, name), id);
}

static void FinishAsync(JNIEnv* env, const base::android::JavaParamRef<jclass>&
    jcaller,
    const base::android::JavaParamRef<jstring>& name,
    jlong id);

JNI_GENERATOR_EXPORT void
    Java_org_chromium_base_TraceEvent_nativeFinishAsync(JNIEnv* env, jclass
    jcaller,
    jstring name,
    jlong id) {
  return FinishAsync(env, base::android::JavaParamRef<jclass>(env, jcaller),
      base::android::JavaParamRef<jstring>(env, name), id);
}

static base::subtle::AtomicWord g_org_chromium_base_TraceEvent_setEnabled = 0;
static void Java_TraceEvent_setEnabled(JNIEnv* env, jboolean enabled) {
  CHECK_CLAZZ(env, org_chromium_base_TraceEvent_clazz(env),
      org_chromium_base_TraceEvent_clazz(env));
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, org_chromium_base_TraceEvent_clazz(env),
      "setEnabled",
"("
"Z"
")"
"V",
      &g_org_chromium_base_TraceEvent_setEnabled);

     env->CallStaticVoidMethod(org_chromium_base_TraceEvent_clazz(env),
          method_id, enabled);
  jni_generator::CheckException(env);
}

}  // namespace android
}  // namespace base

#endif  // org_chromium_base_TraceEvent_JNI
