//******************************************************************
//
// Copyright 2016 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jniNSCommon.h"

#include "NSConsumerInterface.h"
//#include "NSConsumerCommon.h"
/* Header for class org_iotivity_service_ns_consumer */

#ifndef NOTIFICATION_CONSUMER_JNI_H
#define NOTIFICATION_CONSUMER_JNI_H
#ifdef __cplusplus
extern "C" {
#endif

/*
* Class:     org_iotivity_service_ns_consumer_ConsumerService
* Method:    Start
* Signature:
*/
JNIEXPORT void JNICALL Java_org_iotivity_service_ns_consumer_ConsumerService_Start
(JNIEnv *, jobject, jobject, jobject);

/*
* Class:     org_iotivity_service_ns_consumer_ConsumerService
* Method:    Stop
* Signature: (V)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_service_ns_consumer_ConsumerService_Stop
(JNIEnv *, jobject);

/*
* Class:     org_iotivity_service_ns_consumer_ConsumerService
* Method:    GetProvider
* Signature: (Ljava/lang/String;)Lorg/iotivity/service/ns/consumer/NSProvider;
*/
JNIEXPORT jobject JNICALL Java_org_iotivity_service_ns_consumer_ConsumerService_GetProvider
(JNIEnv *, jobject, jobject);

/*
* Class:     org_iotivity_service_ns_consumer_NSProvider
* Method:    Subscribe
* Signature: (J)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_service_ns_consumer_NSProvider_Subscribe
(JNIEnv *, jobject, jlong);

/*
* Class:     org_iotivity_service_ns_consumer_NSProvider
* Method:    Unsubscribe
* Signature: (J)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_service_ns_consumer_NSProvider_Unsubscribe
(JNIEnv *, jobject, jlong);

/*
* Class:     org_iotivity_service_ns_consumer_NSProvider
* Method:    SendSyncInfo
* Signature: (Ljava/lang/String;JI)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_service_ns_consumer_NSProvider_SendSyncInfo
(JNIEnv *, jobject, jobject, jlong, jint);

/*
* Class:     org_iotivity_service_ns_consumer_NSProvider
* Method:    SetListener
* Signature: 
*/
JNIEXPORT void JNICALL Java_org_iotivity_service_ns_consumer_NSProvider_SetListener
(JNIEnv *, jobject, jobject, jobject);

/*
* Class:     org_iotivity_service_ns_consumer_ConsumerService
* Method:    NSRescanProvider
* Signature: (V)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_service_ns_consumer_ConsumerService_NSRescanProvider
(JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif