/*
 * //******************************************************************
 * //
 * // Copyright 2016 Samsung Electronics All Rights Reserved.
 * //
 * //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 * //
 * // Licensed under the Apache License, Version 2.0 (the "License");
 * // you may not use this file except in compliance with the License.
 * // You may obtain a copy of the License at
 * //
 * //      http://www.apache.org/licenses/LICENSE-2.0
 * //
 * // Unless required by applicable law or agreed to in writing, software
 * // distributed under the License is distributed on an "AS IS" BASIS,
 * // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * // See the License for the specific language governing permissions and
 * // limitations under the License.
 * //
 * //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 */
package org.iotivity.cloud.ciserver;

import org.iotivity.cloud.base.OCFConstants;

public class Constants extends OCFConstants {

    public static final int    MIN_TO_LIVE         = 10;

    public static final String USER_ID             = "uid";
    public static final String DEVICE_ID           = "di";
    public static final String PRESENCE_STATE      = "state";

    public static final String REQ_LOGIN           = "login";

    public static final String ACCESS_TOKEN        = "accesstoken";
    public static final Object REFRESH_TOKEN       = "refreshtoken";
    public static final Object EXPIRES_IN          = "expiresin";

    public static final String REQ_GROUP_MASTER_ID = "gmid";
    public static final String REQ_MEMBER_ID       = "mid";
    public static final String REQ_MEMBER_LIST     = "midlist";
    public static final String REQ_DEVICE_ID       = "di";
    public static final String REQ_DEVICE_LIST     = "dilist";

}
