// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/base/Callback

#ifndef org_chromium_base_Callback_JNI
#define org_chromium_base_Callback_JNI

#include <jni.h>

#include "../../../../../../../../../base/android/jni_generator/jni_generator_helper.h"

// Step 1: forward declarations.
JNI_REGISTRATION_EXPORT extern const char
    kClassPath_org_chromium_base_Callback[];
const char kClassPath_org_chromium_base_Callback[] =
    "org/chromium/base/Callback";

JNI_REGISTRATION_EXPORT extern const char
    kClassPath_org_chromium_base_Callback_00024Helper[];
const char kClassPath_org_chromium_base_Callback_00024Helper[] =
    "org/chromium/base/Callback$Helper";

// Leaking this jclass as we cannot use LazyInstance from some threads.
JNI_REGISTRATION_EXPORT base::subtle::AtomicWord
    g_org_chromium_base_Callback_clazz = 0;
#ifndef org_chromium_base_Callback_clazz_defined
#define org_chromium_base_Callback_clazz_defined
inline jclass org_chromium_base_Callback_clazz(JNIEnv* env) {
  return base::android::LazyGetClass(env, kClassPath_org_chromium_base_Callback,
      &g_org_chromium_base_Callback_clazz);
}
#endif

// Leaking this jclass as we cannot use LazyInstance from some threads.
JNI_REGISTRATION_EXPORT base::subtle::AtomicWord
    g_org_chromium_base_Callback_00024Helper_clazz = 0;
#ifndef org_chromium_base_Callback_00024Helper_clazz_defined
#define org_chromium_base_Callback_00024Helper_clazz_defined
inline jclass org_chromium_base_Callback_00024Helper_clazz(JNIEnv* env) {
  return base::android::LazyGetClass(env,
      kClassPath_org_chromium_base_Callback_00024Helper,
      &g_org_chromium_base_Callback_00024Helper_clazz);
}
#endif

// Step 2: method stubs.

static base::subtle::AtomicWord
    g_org_chromium_base_Callback_00024Helper_onObjectResultFromNative = 0;
static void Java_Helper_onObjectResultFromNative(JNIEnv* env, const
    base::android::JavaRef<jobject>& callback,
    const base::android::JavaRef<jobject>& result) {
  CHECK_CLAZZ(env, org_chromium_base_Callback_00024Helper_clazz(env),
      org_chromium_base_Callback_00024Helper_clazz(env));
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, org_chromium_base_Callback_00024Helper_clazz(env),
      "onObjectResultFromNative",
"("
"Lorg/chromium/base/Callback;"
"Ljava/lang/Object;"
")"
"V",
      &g_org_chromium_base_Callback_00024Helper_onObjectResultFromNative);

env->CallStaticVoidMethod(org_chromium_base_Callback_00024Helper_clazz(env),
          method_id, callback.obj(), result.obj());
  jni_generator::CheckException(env);
}

static base::subtle::AtomicWord
    g_org_chromium_base_Callback_00024Helper_onBooleanResultFromNative = 0;
static void Java_Helper_onBooleanResultFromNative(JNIEnv* env, const
    base::android::JavaRef<jobject>& callback,
    jboolean result) {
  CHECK_CLAZZ(env, org_chromium_base_Callback_00024Helper_clazz(env),
      org_chromium_base_Callback_00024Helper_clazz(env));
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, org_chromium_base_Callback_00024Helper_clazz(env),
      "onBooleanResultFromNative",
"("
"Lorg/chromium/base/Callback;"
"Z"
")"
"V",
      &g_org_chromium_base_Callback_00024Helper_onBooleanResultFromNative);

env->CallStaticVoidMethod(org_chromium_base_Callback_00024Helper_clazz(env),
          method_id, callback.obj(), result);
  jni_generator::CheckException(env);
}

static base::subtle::AtomicWord
    g_org_chromium_base_Callback_00024Helper_onIntResultFromNative = 0;
static void Java_Helper_onIntResultFromNative(JNIEnv* env, const
    base::android::JavaRef<jobject>& callback,
    JniIntWrapper result) {
  CHECK_CLAZZ(env, org_chromium_base_Callback_00024Helper_clazz(env),
      org_chromium_base_Callback_00024Helper_clazz(env));
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, org_chromium_base_Callback_00024Helper_clazz(env),
      "onIntResultFromNative",
"("
"Lorg/chromium/base/Callback;"
"I"
")"
"V",
      &g_org_chromium_base_Callback_00024Helper_onIntResultFromNative);

env->CallStaticVoidMethod(org_chromium_base_Callback_00024Helper_clazz(env),
          method_id, callback.obj(), as_jint(result));
  jni_generator::CheckException(env);
}

#endif  // org_chromium_base_Callback_JNI
