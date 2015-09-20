/******************************************************************
 *
 * Copyright 2015 Samsung Electronics All Rights Reserved.
 *
 *
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
 ******************************************************************/
package com.re.sampleclient;

import java.util.ArrayList;

import org.iotivity.base.ModeType;
import org.iotivity.base.OcPlatform;
import org.iotivity.base.PlatformConfig;
import org.iotivity.base.QualityOfService;
import org.iotivity.base.ServiceType;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;

/**
 * Starting Activity of the application responsible for configuring the
 * OcPlatform and redirecting to ResourceClient activity or Container Activity
 * as per user's selection.
 */
public class MainActivity extends Activity {

    private static MainActivity  activityObj;
    private ArrayAdapter<String> apis;
    private ArrayList<String>    apisList;
    private ListView             list;
    private final String         LOG_TAG = "[ReSample] "
                                                 + this.getClass()
                                                         .getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        activityObj = this;

        list = (ListView) findViewById(R.id.list);
        apisList = new ArrayList<String>();

        // adding the item to list that will be displayed on the UI.
        apisList.add("Resource Client");
        apisList.add("Discover Container Resource");
        apis = new ArrayAdapter<String>(activityObj,
                android.R.layout.simple_list_item_1, apisList);
        list.setAdapter(apis);

        // handling user's selection on the UI
        list.setOnItemClickListener(new OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view,
                    int position, long id) {

                if (position == 0) {
                    Intent intent = new Intent(activityObj,
                            ResourceClientActivity.class);
                    startActivity(intent);
                }
                if (position == 1) {

                    Intent intent = new Intent(activityObj,
                            ContainerClientActivity.class);
                    startActivity(intent);
                }
            }
        });

        // calling the method to check the Wi-fi connectivity and configuring
        // the OcPlatform
        configurePlatform();
    }

    @Override
    public void onBackPressed() {
        apisList.clear();
        super.onBackPressed();
    }

    private void configurePlatform() {
        // local Variables
        ConnectivityManager connManager;
        NetworkInfo wifi;
        AlertDialog dialog;
        PlatformConfig platformConfigObj;

        // Check the wifi connectivity
        connManager = (ConnectivityManager) getSystemService(CONNECTIVITY_SERVICE);
        wifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
        if (false == wifi.isConnected()) {
            // WiFi is not connected close the application
            AlertDialog.Builder dialogBuilder = new AlertDialog.Builder(this);
            dialogBuilder.setTitle("Error");
            dialogBuilder
                    .setMessage("WiFi is not enabled/connected! Please connect the WiFi and start application again...");
            dialogBuilder.setCancelable(false);
            dialogBuilder.setPositiveButton("OK", new OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    // Closing the application
                    activityObj.finish();
                }
            });

            dialog = dialogBuilder.create();
            dialog.show();
            Log.i(LOG_TAG,
                    "WiFi is not enabled/connected! Please connect the WiFi and start application again...");
            return;
        }
        // If wifi is connected calling the configure method for configuring the
        // OcPlatform
        platformConfigObj = new PlatformConfig(getApplicationContext(),
                ServiceType.IN_PROC, ModeType.CLIENT_SERVER, "0.0.0.0", 0,
                QualityOfService.LOW);

        OcPlatform.Configure(platformConfigObj);
        Log.i(LOG_TAG, "Configuration done Successfully");
    }
}
