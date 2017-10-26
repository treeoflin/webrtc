// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/base/BuildInfo

#ifndef org_chromium_base_BuildInfo_JNI
#define org_chromium_base_BuildInfo_JNI

#include <jni.h>

#include "../../../../../../../../../base/android/jni_generator/jni_generator_helper.h"

// Step 1: forward declarations.
JNI_REGISTRATION_EXPORT extern const char
    kClassPath_org_chromium_base_BuildInfo[];
const char kClassPath_org_chromium_base_BuildInfo[] =
    "org/chromium/base/BuildInfo";

// Leaking this jclass as we cannot use LazyInstance from some threads.
JNI_REGISTRATION_EXPORT base::subtle::AtomicWord
    g_org_chromium_base_BuildInfo_clazz = 0;
#ifndef org_chromium_base_BuildInfo_clazz_defined
#define org_chromium_base_BuildInfo_clazz_defined
inline jclass org_chromium_base_BuildInfo_clazz(JNIEnv* env) {
  return base::android::LazyGetClass(env,
      kClassPath_org_chromium_base_BuildInfo,
      &g_org_chromium_base_BuildInfo_clazz);
}
#endif

// Step 2: method stubs.

static base::subtle::AtomicWord g_org_chromium_base_BuildInfo_getAll = 0;
static base::android::ScopedJavaLocalRef<jobjectArray>
    Java_BuildInfo_getAll(JNIEnv* env) {
  CHECK_CLAZZ(env, org_chromium_base_BuildInfo_clazz(env),
      org_chromium_base_BuildInfo_clazz(env), NULL);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, org_chromium_base_BuildInfo_clazz(env),
      "getAll",
"("
")"
"[Ljava/lang/String;",
      &g_org_chromium_base_BuildInfo_getAll);

  jobjectArray ret =
static_cast<jobjectArray>(env->CallStaticObjectMethod(org_chromium_base_BuildInfo_clazz(env),
          method_id));
  jni_generator::CheckException(env);
  return base::android::ScopedJavaLocalRef<jobjectArray>(env, ret);
}

#endif  // org_chromium_base_BuildInfo_JNI
