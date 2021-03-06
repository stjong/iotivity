//******************************************************************
//
// Copyright 2015 Samsung Electronics All Rights Reserved.
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

#ifndef ES_COMMON_H_
#define ES_COMMON_H_

#include "ocstack.h"
#include "octypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Defines
#define OIC_STRING_MAX_VALUE    64
#define MAX_WEBLINKLEN          3
#define NUM_WIFIMODE            5

/**
 * Attributes used to form a proper easysetup conforming JSON message.
 */
#define OC_RSRVD_ES_PROVSTATUS             "ps"
#define OC_RSRVD_ES_LAST_ERRORCODE         "lec"
#define OC_RSRVD_ES_LINKS                  "links"
#define OC_RSRVD_ES_SUPPORTEDWIFIMODE      "swmt"
#define OC_RSRVD_ES_SUPPORTEDWIFIFREQ      "swf"
#define OC_RSRVD_ES_SSID                   "tnn"
#define OC_RSRVD_ES_CRED                   "cd"
#define OC_RSRVD_ES_AUTHTYPE               "wat"
#define OC_RSRVD_ES_ENCTYPE                "wet"
#define OC_RSRVD_ES_AUTHCODE               "ac"
#define OC_RSRVD_ES_AUTHPROVIDER           "apn"
#define OC_RSRVD_ES_CISERVER               "cis"
#define OC_RSRVD_ES_SERVERID               "sid"
#define OC_RSRVD_ES_DEVNAME                "dn"
#define OC_RSRVD_ES_LANGUAGE               "lang"
#define OC_RSRVD_ES_COUNTRY                "ctry"
#define OC_RSRVD_ES_MODELNUMBER            "mnmo"
#define OC_RSRVD_ES_LOCATION               "loc"

/**
 * Easysetup defined resoruce types and uris.
 */
#define OC_RSRVD_ES_RES_TYPE_PROV         "ocf.wk.prov"
#define OC_RSRVD_ES_URI_PROV              "/ProvisioningResURI"
#define OC_RSRVD_ES_RES_TYPE_WIFI         "ocf.wk.wifi"
#define OC_RSRVD_ES_URI_WIFI              "/WiFiProvisioningResURI"
#define OC_RSRVD_ES_RES_TYPE_CLOUDSERVER  "ocf.wk.cloudserver"
#define OC_RSRVD_ES_URI_CLOUDSERVER       "/CloudServerProvisioningResURI"
#define OC_RSRVD_ES_RES_TYPE_DEVCONF      "ocf.wk.devconf"
#define OC_RSRVD_ES_URI_DEVCONF           "/DevConfProvisioningResURI"


/**
 * @brief  Supported WIFI frequency like 2.4G and 5G
 */
typedef enum
{
    WIFI_24G = 0,       /**< 2.4G **/
    WIFI_5G,            /**< 5G **/
    WIFI_BOTH,          /**< 2.4G and 5G **/
    WIFI_FREQ_NONE      /**< EOF **/
} WIFI_FREQ;

/**
 * @brief  Supported WIFI mode like 802.11g and 802.11n
 */
typedef enum
{
    WIFI_11A = 0,       /**< 802.11a **/
    WIFI_11B,           /**< 802.11b **/
    WIFI_11G,           /**< 802.11g **/
    WIFI_11N,           /**< 802.11n **/
    WIFI_11AC,          /**< 802.11ac **/
    WiFi_EOF = 999
} WIFI_MODE;


/**
 * @brief  WIFI Authentication tlype of the Enroller
 */
typedef enum
{
    NONE_AUTH = 0,      /**< NO authentication **/
    WEP,                /**< WEP **/
    WPA_PSK,            /**< WPA-PSK **/
    WPA2_PSK            /**< WPA2-PSK **/
} WIFI_AUTHTYPE;

/**
 * @brief  WIFI encryption type of the Enroller
 */
typedef enum
{
    NONE_ENC = 0,       /**< NO encryption **/
    WEP_64,             /**< WEP-64 **/
    WEP_128,            /**< WEP-128**/
    TKIP,               /**< TKIP **/
    AES,                /**< AES **/
    TKIP_AES            /**< TKIP-AES **/
} WIFI_ENCTYPE;

typedef enum
{
    ES_ERROR = -1,
    ES_OK = 0,
    ES_NETWORKFOUND = 1,
    ES_NETWORKCONNECTED,
    ES_NETWORKNOTCONNECTED,
    ES_RESOURCECREATED = 11,
    ES_RECVREQOFPROVRES = 21,
    ES_RECVREQOFNETRES,
    ES_RECVUPDATEOFPROVRES,
    ES_RECVTRIGGEROFPROVRES,
    ES_UNAUTHORIZED = 31,
    ES_UNSUPPORTED_OPERATION = 41
} ESResult;

/**
 * @brief Indicate which resource is created in Enrollee
 */
typedef enum
{
    ES_WIFI_RESOURCE = 0x01,
    ES_CLOUD_RESOURCE = 0x02,
    ES_DEVCONF_RESOURCE = 0x04
} ESResourceMask;

/**
 * @brief Indicate enrollee and provisioning status. Provisioning status is shown in "provisioning
 *        status" property in provisioning resource.
 */
typedef enum
{
    /**
     * Default state of the device
     */
    ES_STATE_INIT = 0,

    /**
    * Status indicating being cnnecting to target network
    */
    ES_STATE_CONNECTING_TO_ENROLLER,

    /**
    * Status indicating successful conection to target network
    */
    ES_STATE_CONNECTED_TO_ENROLLER,

    /**
    * Status indicating failure connection to target network
    */
    ES_STATE_CONNECTED_FAIL_TO_ENROLLER,

    /**
    * Status indicating successful registration to cloud
    */
    ES_STATE_REGISTERED_TO_CLOUD,

    /**
    * Status indicating failure registeration to cloud
    */
    ES_STATE_REGISTRRED_FAIL_TO_CLOUD
} ESEnrolleeState, ProvStatus;

/**
 * @brief Indicate last error code to describe a reason of error during easy setup.
 */
typedef enum
{
    /**
     * Init Error Code
     */
    ES_ERRCODE_NO_ERROR = 0,

    /**
    * Error Code that given WiFi's SSID is not found
    */
    ES_ERRCODE_SSID_NOT_FOUND,

    /**
    * Error Code that given WiFi's Password is wrong
    */
    ES_ERRCODE_PW_WRONG,

    /**
    * Error Code that IP address is not allocated
    */
    ES_ERRCODE_IP_NOT_ALLOCATED,

    /**
    * Error Code that there is no Internet connection
    */
    ES_ERRCODE_NO_INTERNETCONNECTION,

    /**
    * Error Code that Timeout occured
    */
    ES_ERRCODE_TIMEOUT,

    /**
    * Error Code that Unknown error occured
    */
    ES_ERRCODE_UNKNOWN
} ESErrorCode;

#ifdef __cplusplus
}
#endif

#endif //ES_COMMON_H_
