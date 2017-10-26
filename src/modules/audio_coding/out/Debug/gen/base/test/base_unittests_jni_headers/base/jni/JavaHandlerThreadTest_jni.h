// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/base/JavaHandlerThreadTest

#ifndef org_chromium_base_JavaHandlerThreadTest_JNI
#define org_chromium_base_JavaHandlerThreadTest_JNI

#include <jni.h>

#include "../../../../../../../../../../base/android/jni_generator/jni_generator_helper.h"

// Step 1: forward declarations.
JNI_REGISTRATION_EXPORT extern const char
    kClassPath_org_chromium_base_JavaHandlerThreadTest[];
const char kClassPath_org_chromium_base_JavaHandlerThreadTest[] =
    "org/chromium/base/JavaHandlerThreadTest";

// Leaking this jclass as we cannot use LazyInstance from some threads.
JNI_REGISTRATION_EXPORT base::subtle::AtomicWord
    g_org_chromium_base_JavaHandlerThreadTest_clazz = 0;
#ifndef org_chromium_base_JavaHandlerThreadTest_clazz_defined
#define org_chromium_base_JavaHandlerThreadTest_clazz_defined
inline jclass org_chromium_base_JavaHandlerThreadTest_clazz(JNIEnv* env) {
  return base::android::LazyGetClass(env,
      kClassPath_org_chromium_base_JavaHandlerThreadTest,
      &g_org_chromium_base_JavaHandlerThreadTest_clazz);
}
#endif

namespace base {

// Step 2: method stubs.

static base::subtle::AtomicWord
    g_org_chromium_base_JavaHandlerThreadTest_testAndGetJavaHandlerThread = 0;
static base::android::ScopedJavaLocalRef<jobject>
    Java_JavaHandlerThreadTest_testAndGetJavaHandlerThread(JNIEnv* env) {
  CHECK_CLAZZ(env, org_chromium_base_JavaHandlerThreadTest_clazz(env),
      org_chromium_base_JavaHandlerThreadTest_clazz(env), NULL);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, org_chromium_base_JavaHandlerThreadTest_clazz(env),
      "testAndGetJavaHandlerThread",
"("
")"
"Lorg/chromium/base/JavaHandlerThread;",
      &g_org_chromium_base_JavaHandlerThreadTest_testAndGetJavaHandlerThread);

  jobject ret =
env->CallStaticObjectMethod(org_chromium_base_JavaHandlerThreadTest_clazz(env),
          method_id);
  jni_generator::CheckException(env);
  return base::android::ScopedJavaLocalRef<jobject>(env, ret);
}

}  // namespace base

#endif  // org_chromium_base_JavaHandlerThreadTest_JNI
