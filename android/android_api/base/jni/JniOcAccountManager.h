/*
 *******************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 *-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 */

#ifndef _Included_org_iotivity_base_OcAccountManager
#define _Included_org_iotivity_base_OcAccountManager

#include "JniOcStack.h"
#include "OCAccountManager.h"
#include "JniListenerManager.h"
#include "JniOnGetListener.h"
#include "JniOnPostListener.h"
#include "JniOnDeleteListener.h"

using namespace OC;

class JniOcAccountManager
{
public:
    JniOcAccountManager(std::shared_ptr<OCAccountManager> accountManager);
    ~JniOcAccountManager();

    std::string host();
    OCConnectivityType connectivityType() const;

    static JniOcAccountManager* getJniOcAccountManagerPtr(JNIEnv *env, jobject thiz);

    OCStackResult signUp(JNIEnv* env, const std::string& authProvider, const std::string& authCode,
                         jobject jListener);
    OCStackResult signUp(JNIEnv* env, const std::string& authProvider, const std::string& authCode,
                         const QueryParamsMap& options, jobject jListener);
    OCStackResult signIn(JNIEnv* env, const std::string& userUuid, const std::string& accessToken,
                         jobject jListener);
    OCStackResult signOut(JNIEnv* env, jobject jListener);
    OCStackResult refreshAccessToken(JNIEnv* env, const std::string& userUuid,
                                     const std::string& refreshToken, jobject jListener);
    OCStackResult searchUser(JNIEnv* env, const std::string& userUuid, jobject jListener);
    OCStackResult searchUser(JNIEnv* env, const QueryParamsMap& queryMap, jobject jListener);
    OCStackResult deleteDevice(JNIEnv* env, const std::string& deviceId, jobject jListener);

    JniOnGetListener* addOnGetListener(JNIEnv* env, jobject jListener);
    JniOnPostListener* addOnPostListener(JNIEnv* env, jobject jListener);
    JniOnDeleteListener* addOnDeleteListener(JNIEnv* env, jobject jListener);

    void removeOnGetListener(JNIEnv* env, jobject jListener);
    void removeOnPostListener(JNIEnv* env, jobject jListener);
    void removeOnDeleteListener(JNIEnv* env, jobject jListener);

private:
    JniListenerManager<JniOnGetListener> m_onGetManager;
    JniListenerManager<JniOnPostListener> m_onPostManager;
    JniListenerManager<JniOnDeleteListener> m_onDeleteManager;

    std::shared_ptr<OCAccountManager> m_sharedAccountManager;
};

/* DO NOT EDIT THIS FILE BEYOND THIS LINE - it is machine generated */

#ifdef __cplusplus
extern "C" {
#endif

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    getHost
    * Signature: ()Ljava/lang/String;
    */
    JNIEXPORT jstring JNICALL Java_org_iotivity_base_OcAccountManager_getHost
        (JNIEnv *, jobject);

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    getConnectivityTypeN
    * Signature: ()I
    */
    JNIEXPORT jint JNICALL Java_org_iotivity_base_OcAccountManager_getConnectivityTypeN
        (JNIEnv *, jobject);

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    signUp0
    * Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/iotivity/base/OcAccountManager/OnPostListener;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcAccountManager_signUp0
        (JNIEnv *, jobject, jstring, jstring, jobject);

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    signUp1
    * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;Lorg/iotivity/base/OcAccountManager/OnPostListener;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcAccountManager_signUp1
        (JNIEnv *, jobject, jstring, jstring, jobject, jobject);

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    signIn0
    * Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/iotivity/base/OcAccountManager/OnPostListener;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcAccountManager_signIn0
        (JNIEnv *, jobject, jstring, jstring, jobject);

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    signOut0
    * Signature: (Lorg/iotivity/base/OcAccountManager/OnPostListener;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcAccountManager_signOut0
        (JNIEnv *, jobject, jobject);

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    refreshAccessToken0
    * Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/iotivity/base/OcAccountManager/OnPostListener;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcAccountManager_refreshAccessToken0
        (JNIEnv *, jobject, jstring, jstring, jobject);

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    searchUser0
    * Signature: (Ljava/lang/String;Lorg/iotivity/base/OcAccountManager/OnGetListener;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcAccountManager_searchUser0
        (JNIEnv *env, jobject thiz, jstring juserUuid, jobject jListener);

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    searchUser1
    * Signature: (Ljava/util/Map;Lorg/iotivity/base/OcAccountManager/OnGetListener;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcAccountManager_searchUser1
        (JNIEnv *env, jobject thiz, jobject jQueryMap, jobject jListener);

    /*
    * Class:     org_iotivity_base_OcAccountManager
    * Method:    deleteDevice0
    * Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/iotivity/base/OcAccountManager/onDeleteListener;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcAccountManager_deleteDevice0
        (JNIEnv *env, jobject thiz, jstring jDeviceId, jobject jListener);

#ifdef __cplusplus
}
#endif
#endif
