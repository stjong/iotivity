package org.iotivity.cloud.testrdserver;

import java.util.ArrayList;
import java.util.HashMap;
import org.iotivity.cloud.base.protocols.IRequest;
import org.iotivity.cloud.base.protocols.MessageBuilder;
import org.iotivity.cloud.base.protocols.enums.ContentFormat;
import org.iotivity.cloud.base.protocols.enums.RequestMethod;
import org.iotivity.cloud.rdserver.Constants;
import org.iotivity.cloud.rdserver.db.MongoDB;
import org.iotivity.cloud.util.Cbor;

public class RDServerTestUtils {
    public static final String DI                 = "98f7483c-5a31-4161-ba7e-9c13e0d";
    public static final String RD_REQ_URI         = "/oic/rd";
    public static final String DISCOVERY_REQ_URI  = "/oic/res";
    public static final String DEVICE_PRS_REQ_URI = "/.well-known/ocf/prs";
    public static final String RES_PRS_URI        = "/oic/ad";

    public static IRequest makePublishRequest() throws Exception {
        HashMap<Object, Object> payload = new HashMap<>();
        payload.put(Constants.DEVICE_ID, DI);
        ArrayList<HashMap<Object, Object>> publishLinks = new ArrayList<>();
        HashMap<Object, Object> link = new HashMap<>();
        link.put(Constants.HREF, "/a/light");
        ArrayList<String> rt = new ArrayList<String>();
        rt.add("core.light");
        ArrayList<String> itf = new ArrayList<String>();
        itf.add("oic.if.baseline");
        HashMap<String, Object> policy = new HashMap<>();
        policy.put(Constants.BITMAP, 5);
        link.put(Constants.RESOURCE_TYPE, rt);
        link.put(Constants.INTERFACE, itf);
        link.put(Constants.POLICY, policy);
        publishLinks.add(link);
        payload.put(Constants.LINKS, publishLinks);
        Cbor<HashMap<Object, Object>> cbor = new Cbor<>();
        IRequest request = MessageBuilder.createRequest(RequestMethod.POST,
                Constants.RD_URI,
                Constants.RESOURCE_TYPE + "="
                        + Constants.RESOURCE_TYPE_RDPUBLISH,
                ContentFormat.APPLICATION_CBOR,
                cbor.encodingPayloadToCbor(payload));
        return request;
    }

    public static void resetRDDatabase() throws Exception {
        MongoDB mongoDB = new MongoDB(Constants.RD_DB_NAME);
        mongoDB.createTable(Constants.RD_TABLE);
        mongoDB.createTable(Constants.PRESENCE_TABLE);
    }
}