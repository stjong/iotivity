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

#include <gtest/gtest.h>
#include <HippoMocks/hippomocks.h>
#include <atomic>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <chrono>

#include "ESMediatorSimulator.h"
#include "easysetup.h"

using namespace OC;

namespace
{
    std::atomic_bool g_isStartedStack(false);

    std::chrono::milliseconds g_waitForResponse(1000);

    std::condition_variable responseCon;
    std::mutex mutexForCondition;

    ESMediatorSimulator g_mediatorSimul;
}

class TestWithMock: public testing::Test
{
public:
    MockRepository mocks;

protected:
    virtual ~TestWithMock() noexcept(noexcept(std::declval<Test>().~Test()))
    {
    }

    virtual void TearDown()
    {
        try
        {
            mocks.VerifyAll();
        }
        catch (...)
        {
            mocks.reset();
            throw;
        }
    }
};

class EasysetupEnrolleeTest : public TestWithMock
{
public:
    EasysetupEnrolleeTest() = default;
    ~EasysetupEnrolleeTest() = default;

    static void discoveredResource(std::shared_ptr<OC::OCResource>)
    {
        std::cout << __func__ << std::endl;
    }

    static void onGetStatus(std::shared_ptr< GetEnrolleeStatus >)
    {
        std::cout << __func__ << std::endl;
    }

    static void onGetConfiguration(std::shared_ptr< GetConfigurationStatus >)
    {
        std::cout << __func__ << std::endl;
    }

    static void deviceProvisioningStatusCallback(std::shared_ptr< DevicePropProvisioningStatus >)
    {
        std::cout << __func__ << std::endl;
    }

    static void cloudProvisioningStatusCallback(std::shared_ptr< CloudPropProvisioningStatus >)
    {
        std::cout << __func__ << std::endl;
    }

    static void WiFiProvCbInApp(ESWiFiProvData *)
    {
        std::cout << __func__ << std::endl;
    }

    static void DevConfProvCbInApp(ESDevConfProvData *)
    {
        std::cout << __func__ << std::endl;
    }

    static void CloudDataCbInApp(ESCloudProvData *)
    {
        std::cout << __func__ << std::endl;
    }

    ESResult startEnrollee()
    {
        ESResourceMask resourcemMask = (ESResourceMask)(ES_WIFI_RESOURCE |
                                                    ES_CLOUD_RESOURCE |
                                                    ES_DEVCONF_RESOURCE);
        ESProvisioningCallbacks callbacks;
        callbacks.WiFiProvCb = &EasysetupEnrolleeTest::WiFiProvCbInApp;
        callbacks.DevConfProvCb = &EasysetupEnrolleeTest::DevConfProvCbInApp;
        callbacks.CloudDataProvCb = &EasysetupEnrolleeTest::CloudDataCbInApp;

        return ESInitEnrollee(false, resourcemMask, callbacks);
    }

    ESResult setDeviceProperty()
    {
        ESDeviceProperty deviceProperty = {
            {{WIFI_11G, WiFi_EOF}, WIFI_5G}, {"Test Device"}
        };

        return ESSetDeviceProperty(&deviceProperty);
    }

protected:

    void SetUp()
    {
        TestWithMock::SetUp();

        if (g_isStartedStack == false)
        {
            if (OCInit(NULL, 0, OC_SERVER) != OC_STACK_OK)
            {
                printf("OCStack init error!!\n");
                return;
            }

            g_isStartedStack = true;
        }
    }

    void TearDown()
    {
        TestWithMock::TearDown();
    }

};

TEST_F(EasysetupEnrolleeTest, ESInitEnrolleeSuccess)
{
    ESResult ret = startEnrollee();
    EXPECT_EQ(ret, ES_OK);
    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, ESInitEnrolleeFailedByWiFiCbIsNull)
{
    ESResourceMask resourcemMask = (ESResourceMask)(ES_WIFI_RESOURCE |
                                                    ES_CLOUD_RESOURCE |
                                                    ES_DEVCONF_RESOURCE);
    ESProvisioningCallbacks callbacks;
    callbacks.WiFiProvCb = NULL;
    callbacks.DevConfProvCb = &EasysetupEnrolleeTest::DevConfProvCbInApp;
    callbacks.CloudDataProvCb = &EasysetupEnrolleeTest::CloudDataCbInApp;

    ESResult ret = ESInitEnrollee(false, resourcemMask, callbacks);
    EXPECT_EQ(ret, ES_ERROR);
    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, ESInitEnrolleeFailedByDevConfCbIsNull)
{
    ESResourceMask resourcemMask = (ESResourceMask)(ES_WIFI_RESOURCE |
                                                    ES_CLOUD_RESOURCE |
                                                    ES_DEVCONF_RESOURCE);
    ESProvisioningCallbacks callbacks;
    callbacks.WiFiProvCb = &EasysetupEnrolleeTest::WiFiProvCbInApp;
    callbacks.DevConfProvCb = NULL;
    callbacks.CloudDataProvCb = &EasysetupEnrolleeTest::CloudDataCbInApp;

    ESResult ret = ESInitEnrollee(false, resourcemMask, callbacks);
    EXPECT_EQ(ret, ES_ERROR);
    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, ESInitEnrolleeFailedByCloudCbIsNull)
{
    ESResourceMask resourcemMask = (ESResourceMask)(ES_WIFI_RESOURCE |
                                                    ES_CLOUD_RESOURCE |
                                                    ES_DEVCONF_RESOURCE);
    ESProvisioningCallbacks callbacks;
    callbacks.WiFiProvCb = &EasysetupEnrolleeTest::WiFiProvCbInApp;
    callbacks.DevConfProvCb = &EasysetupEnrolleeTest::DevConfProvCbInApp;
    callbacks.CloudDataProvCb = NULL;

    ESResult ret = ESInitEnrollee(false, resourcemMask, callbacks);
    EXPECT_EQ(ret, ES_ERROR);
    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, FindProvisioningResourceAtEnrolleeWithSuccess)
{
    mocks.ExpectCallFunc(discoveredResource).Do(
        [](std::shared_ptr<OC::OCResource> resource)
        {
            try
            {
                std::cout<<"DISCOVERED Resource:"<<std::endl;
                // Get the resource host address
                std::string uri = resource->uri();
                std::cout << "\tURI of the resource: " << uri << std::endl;
            } catch (OCException &e)
            {
                std::cout << e.reason() << std::endl;
            }

        });

    ESResult ret = startEnrollee();

    g_mediatorSimul.discoverRemoteEnrollee(discoveredResource);

    std::unique_lock< std::mutex > lock{ mutexForCondition };
    responseCon.wait_for(lock, g_waitForResponse);

    EXPECT_EQ(ret, ES_OK);

    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, SetDevicePropertyWithSuccess)
{
    ESResult ret = startEnrollee();
    ret = setDeviceProperty();
    EXPECT_EQ(ret, ES_OK);
    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, SetProvStatusWithSuccess)
{
    ESResult ret = startEnrollee();
    ret = ESSetState(ES_STATE_CONNECTED_TO_ENROLLER);
    EXPECT_EQ(ret, ES_OK);
    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, SetErrorCodeWithSuccess)
{
    ESResult ret = startEnrollee();
    ret = ESSetErrorCode(ES_ERRCODE_PW_WRONG);
    EXPECT_EQ(ret, ES_OK);
    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, DevicePropertyIsWellConstructedInResponsePayload)
{
    bool isWellConstructed = false;
    mocks.ExpectCallFunc(onGetConfiguration).Do(
        [& isWellConstructed](std::shared_ptr< GetConfigurationStatus > status)
        {
            if(status->getESResult() == ES_OK)
            {
                EnrolleeConf conf = status->getEnrolleeConf();
                if(conf.getWiFiModes().at(0) == WIFI_11G &&
                    conf.getWiFiFreq() == WIFI_5G &&
                    !strcmp(conf.getDeviceName().c_str(), "Test Device"))
                {
                    isWellConstructed = true;
                }
            }
        });
    ESResult ret = startEnrollee();
    ret = setDeviceProperty();

    g_mediatorSimul.getConfiguration(onGetConfiguration);

    std::unique_lock< std::mutex > lock{ mutexForCondition };
    responseCon.wait_for(lock, g_waitForResponse);

    EXPECT_EQ(ret, ES_OK);

    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, ProvisioningPropertiesIsWellConstructedInResponsePayload)
{
    bool isWellConstructed = false;
    mocks.ExpectCallFunc(onGetStatus).Do(
        [& isWellConstructed](std::shared_ptr< GetEnrolleeStatus > status)
        {
            if(status->getESResult() == ES_OK)
            {
                EnrolleeStatus enrolleeStatus = status->getEnrolleeStatus();


                if(enrolleeStatus.getProvStatus() == ES_STATE_CONNECTED_TO_ENROLLER &&
                   enrolleeStatus.getLastErrCode() == ES_ERRCODE_NO_INTERNETCONNECTION)
                {
                    isWellConstructed = true;
                }
            }
        });
    ESResult ret = startEnrollee();
    ret = setDeviceProperty();
    ret = ESSetState(ES_STATE_CONNECTED_TO_ENROLLER);
    ret = ESSetErrorCode(ES_ERRCODE_NO_INTERNETCONNECTION);

    g_mediatorSimul.getStatus(onGetStatus);

    std::unique_lock< std::mutex > lock{ mutexForCondition };
    responseCon.wait_for(lock, g_waitForResponse);

    EXPECT_EQ(ret, ES_OK);

    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, WiFiAndDevConfProperiesProvisionedWithSuccess)
{
    int cntForReceivedCallbackWithSuccess = 0;

    mocks.OnCallFunc(deviceProvisioningStatusCallback).Do(
        [& cntForReceivedCallbackWithSuccess](std::shared_ptr< DevicePropProvisioningStatus > status)
        {
            if(status->getESResult() == ES_OK)
               cntForReceivedCallbackWithSuccess++;
        });

    mocks.OnCallFunc(WiFiProvCbInApp).Do(
        [& cntForReceivedCallbackWithSuccess](ESWiFiProvData *data)
        {
            if(!strcmp(data->ssid, "Iotivity_SSID") &&
                !strcmp(data->pwd, "Iotivity_PWD") &&
                data->authtype == WPA2_PSK &&
                data->enctype == TKIP_AES)
            {
                cntForReceivedCallbackWithSuccess++;
            }
        });
    mocks.OnCallFunc(DevConfProvCbInApp).Do(
        [& cntForReceivedCallbackWithSuccess](ESDevConfProvData *data)
        {
            if(!strcmp(data->language, "korean") &&
                !strcmp(data->country, "Korea"))
            {
                cntForReceivedCallbackWithSuccess++;
            }
        });

    startEnrollee();

    g_mediatorSimul.provisionDeviceProperties(deviceProvisioningStatusCallback);

    std::unique_lock< std::mutex > lock{ mutexForCondition };
    responseCon.wait_for(lock, g_waitForResponse);

    EXPECT_EQ(cntForReceivedCallbackWithSuccess, 3);

    ESTerminateEnrollee();
}

TEST_F(EasysetupEnrolleeTest, CloudServerProperiesProvisionedWithSuccess)
{
    int cntForReceivedCallbackWithSuccess = 0;

    mocks.OnCallFunc(cloudProvisioningStatusCallback).Do(
        [& cntForReceivedCallbackWithSuccess](std::shared_ptr< CloudPropProvisioningStatus > status)
        {
            // Will called twice
            if(status->getESResult() == ES_OK)
            {
               cntForReceivedCallbackWithSuccess++;
            }
        });

    mocks.OnCallFunc(CloudDataCbInApp).Do(
        [& cntForReceivedCallbackWithSuccess](ESCloudProvData *data)
        {
            if(!strcmp(data->authCode, "authCode") &&
                !strcmp(data->authProvider, "authProvider") &&
                !strcmp(data->ciServer, "ciServer"))
            {
                cntForReceivedCallbackWithSuccess++;
            }
        });

    startEnrollee();

    g_mediatorSimul.provisionCloudProperties(cloudProvisioningStatusCallback);

    std::unique_lock< std::mutex > lock{ mutexForCondition };
    responseCon.wait_for(lock, g_waitForResponse);

    EXPECT_EQ(cntForReceivedCallbackWithSuccess, 3);

    ESTerminateEnrollee();
}


