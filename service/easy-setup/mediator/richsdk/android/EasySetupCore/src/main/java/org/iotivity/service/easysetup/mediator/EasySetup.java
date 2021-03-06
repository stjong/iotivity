/**
 * ***************************************************************
 *
 * Copyright 2017 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ****************************************************************
 */

package org.iotivity.service.easysetup.mediator;

import android.content.Context;
import android.util.Log;

import org.iotivity.base.OcConnectivityType;
import org.iotivity.base.OcResource;
import org.iotivity.base.OcPlatform;

import java.util.ArrayList;
import java.util.EnumSet;
import java.util.List;

/**
 * This provides an API to instanciate a new RemoteEnrollee object correspondent to Enrollee
 * Device to be setup.
 */
public class EasySetup {

    private static final String TAG = EasySetup.class.getName();
    public static final String PROV_RESOURCE_TYPE = "ocf.wk.prov";
    private static EasySetup sInstance;

    private static Context mContext;

    private ArrayList<RemoteEnrollee> mRemoteEnrolleeList;

    protected RemoteEnrollee mRemoteEnrollee;

    // function to call the native nativeCreateRemoteEnrollee
    private native RemoteEnrollee nativeCreateRemoteEnrollee(OcResource enrolleeResource);
    static {
        // Load Easy Setup JNI interface
        try
        {
            System.loadLibrary("ocprovision");
        } catch (UnsatisfiedLinkError e) {
            Log.i(TAG, "ocprovision library does not exist. (Unsecure mode)");
        }

        System.loadLibrary("ocstack-jni");
        System.loadLibrary("ESMediatorRich");
        System.loadLibrary("easysetup-jni");
    }

    private EasySetup() {
        mRemoteEnrolleeList = new ArrayList<RemoteEnrollee>();
        mContext = null;
    }

    /**
     * Gives a singleton instance of Easy setup and initialize the easy setup
     */
    public synchronized static EasySetup getInstance(Context context) {
        if (sInstance == null) {
            sInstance = new EasySetup();
            mContext = context;
        }
        return sInstance;
    }

     /**
     * This API is used for creating a remote Enrollee instance
     *
     * @param enrolleeResource an OCResource object corresponding to enrollee resource
     *        discovered in a network. The OcResource object can be obtained by calling
     *        OcPlatform.findResource() API. What resource you have to discover with
     *        the OcPlatform.findResource() API is a "provisioning" resource with a certain
     *        resource type, i.e. ocf.wk.prov
     *
     * @return Pointer to RemoteEnrollee instance
     */
    public synchronized RemoteEnrollee createRemoteEnrollee(OcResource enrolleeResource)
    {
        // native call
        if(!enrolleeResource.getResourceTypes().contains(PROV_RESOURCE_TYPE)
                || !enrolleeResource.getResourceInterfaces().contains(OcPlatform.BATCH_INTERFACE))
        {
            Log.e(TAG, "Validation check for OcResource is failed.");
            return null;
        }
        mRemoteEnrollee = nativeCreateRemoteEnrollee(enrolleeResource);
        mRemoteEnrolleeList.add(mRemoteEnrollee);
        return mRemoteEnrollee;
    }
}
