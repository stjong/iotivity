var request = require('request');
var ocfdevices = [];
var rviuri = "http://localhost:8080/wsi/cap/org.genivi.rvi";
var ocfuri = "http://localhost:8080/wsi/cap/org.openinterconnect";
var smstatus, chstatus;
var smcount = 0, chcount = 0;

var FSM = {
	NOTREADY : 0,
	RVICONNECT: 1,
	REGHOMECONTROL: 2,
	REGCALLBACK: 3,
	GETRVISERVICES: 4,
	GET_VEHICLE_HVAC : 5,
	GET_VEHICLE_LOCATION : 6,
	FINDOCFDEVICES: 7,
	MAKEOCFRVIDEVICE: 8,
	COMINGHOME : 9,
	SMARTHOMESTATUS : 10,
	SETHVAC : 11,
	UNREGHOMECONTROL: 12,
	UNREGCALLBACK: 13,
	READY: 14
};
var state = FSM.NOTREADY;

var rvimsg = [
      {
          "cid": "org.genivi.rvi.connect",
          "isauthrequired": "false",
          "description": "Connect to RVI.",
          "endpoint": "ws://localhost:9008/",
          "endpointtype": "rvi",
          "chain" : "http://localhost:8081/callback",
          "operation": "RVICONNECT",
          "params" : {}
      },
      {
          "cid": "org.genivi.rvi.send",
          "isauthrequired": "false",
          "description": "Send to RVI.",
          "endpoint": "ws://localhost:9008/",
          "endpointtype": "rvi",
          "operation": "RVISEND",
          "params" : {}
      }
];

var rvibody = [
	{//0
		"jsonrpc":"2.0",
		"id":"1",
		"method": "register_service",
		"params": {
			"timeout":1459388884,
			"service_name": "servicename"
		}
	},
 	{//1
		"jsonrpc":"2.0",
		"id":"1",
		"method": "get_available_services",
		"params" : {}
    },
	{//2
		"jsonrpc":"2.0",
		"id":"1",
		"method": "message",
		"params": {
			"timeout":1459388884,
			"service_name": "genivi.org/node/vehicle_id/rvi/vehiclecontrol",
	        "parameters": {
                "target" : "GETHVAC"
	        }
		}
	},
	{//3
		"jsonrpc":"2.0",
		"id":"1",
		"method": "message",
		"params": {
			"timeout":1459388884,
			"service_name": "genivi.org/node/vehicle_id/rvi/vehiclecontrol",
			"parameters":{
				"target" : "GETLOCATION"
			}
		}
	},
	{//4
		"jsonrpc":"2.0",
		"id":"1",
		"method": "message",
		"params": {
			"timeout":1459388884,
			"service_name": "genivi.org/node/vehicle_id/rvi/vehiclecontrol",
			"parameters":{
				"target" : "SETHVAC",
				"function": "function",
				"newValue": "value"
			}
		}
	},
	{//5
		"jsonrpc":"2.0",
		"id":"1",
		"method": "message",
		"params": {
			"timeout":1459388884,
			"service_name": "genivi.org/node/vehicle_id/rvi/callback",
			"parameters":{
				"target" : "SMARTHOMESCENARIO",
				"text": "scenario name",
				"result": "Success/Failure",
				"status" : {}
			}
		}
	},	
	{//6
		"jsonrpc":"2.0",
		"id":"1",
		"method": "unregister_service",
		"params": {
			"timeout":1459388884,
			"service_name": "servicename"
		}
	}
];

var ocfbody = [
   	{//0
   	    "cid": "org.openinterconnect.findresource",                    
   	    "endpointtype": "OCF",
   	    "operation": "GET",
   	    "resourceType" : "all"
   	},
    {//1
        "cid": "org.openinterconnect.createresource",
        "endpointtype": "OCF",
        "operation": "CREATE",
        "chain" : "notification URI",
        "params":
        {
            "uri": "/a/rvi",
            "type" : "core.rvi",
        },
        "payload": {},        
        "tags": [
            "create an OCF server with RVI resource"
        ]
    },
   	{//2
   	    "cid": "org.openinterconnect.getresource",
   	    "endpoint": "oic://{{address}}:{{port}}/{{uri}}",
   	    "endpointtype": "OCF",
   	    "operation": "GET",
   	    "resourceID" : "",
   	    "params": 
   	    {
   	        "address": "server ip address",
   	        "port": "server port",
   	        "uri": "server's uri"
   	    }
   	},
   	{//3
   	    "cid": "org.openinterconnect.putresource",
   	    "endpoint": "oic://{{address}}:{{port}}/{{uri}}",
   	    "endpointtype": "OCF",
   	    "operation": "POST",
   	    "resourceID" : "",
   	    "params": {
   	          "address": "server ip address",
   	          "port": "server port",
   	          "uri": "server's uri"
   	     },
   	    "payload": {},
   	    "tags": [
   	      "put reosurce properties and value"
   	    ]
   	},
    {//4
        "cid": "org.openinterconnect.ocfupdate",
        "endpointtype": "OCF",
        "operation": "UPDATE",
        "payload": {},        
        "tags": [
            "RVI Resource updated by OCF"
        ]
    },    
    {//5
        "cid": "org.openinterconnect.rviupdate",
        "endpointtype": "OCF",
        "operation": "UPDATE",
        "params":
        {
            "uri": "/a/rvi",
            "type" : "core.rvi",
        },
        "payload": {},        
        "tags": [
            "RVI Resource updated by RVI"
        ]
    }    
];

var wsiFSM = function(error, response, body) {
	if(!body || response.statusCode > 399){
        console.log("Failed Response = " + body);
        state = FSM.READY;
		return;
	}
	var res;
	console.log("State " + state + " Response = " + JSON.stringify(body));
	switch(state)
    {
    	case FSM.RVICONNECT:{
    		console.log("RVI Connected.");
    		state = FSM.REGHOMECONTROL;
    		rvibody[0].params.service_name = "homecontrol";
    		rvimsg[1].params = rvibody[0];
    		res = post(rviuri, rvimsg[1]);
    		break;
    	}
    	case FSM.REGHOMECONTROL:{
    		console.log("RVI HomeControl Service Registered.");
    		state = FSM.REGCALLBACK;
    		rvibody[0].params.service_name = "callback";
    		rvimsg[1].params = rvibody[0];
    		res = post(rviuri, rvimsg[1]);
    		break;
    	}
    	case FSM.REGCALLBACK:{
    		console.log("RVI Callback Service Registered.");
    		state = FSM.GETRVISERVICES;
    		rvimsg[1].params = rvibody[1];
    		res = post(rviuri, rvimsg[1]);
    		break;
    	}
    	case FSM.GETRVISERVICES:{
    		console.log("RVI Service List Received.");
    		state = FSM.GET_VEHICLE_LOCATION;
    		rvimsg[1].params = rvibody[3];
    		res = post(rviuri, rvimsg[1]);
    		break;
    	}
    	case FSM.FINDOCFDEVICES:{
            var rcvbody = body.utf8Data;
            var params = rcvbody.params.parameters;
            ocfdevices = params.status;
    		console.log("OCF Device List Received." + ocfdevices);
            state = FSM.MAKEOCFRVIDEVICE;
            console.log("Making RVI device with " + JSON.stringify(ocfbody[1].payload));
    		var res = post(ocfuri, ocfbody[1]);
    		break;
    	}
    	case FSM.SMARTHOMESTATUS : {
    		smstatus += body;
    		smcount = smcount - 1;
    		if(smcount==0){
        		rvibody[5].params.parameters.text = "SmartHome Status";
        		rvibody[5].params.parameters.result = "Success";
        		rvibody[5].params.parameters.status = smstatus;
        		rvimsg[1].params = rvibody[5];
        		res = post(rviuri, rvimsg[1]);
        		state = FSM.READY;
			}
    		break;
    	}
    	case FSM.COMINGHOME : {
    		chstatus += body;
    		chcount = chcount - 1;
    		console.log("CHCOUNT = " + chcount);
    		if(chcount==0){
        		rvimsg[1].params = rvibody[5];
        		rvibody[5].params.parameters.text = "Coming Home";
        		rvibody[5].params.parameters.result = "Success";
        		rvimsg[1].params = rvibody[5];
        		res = post(rviuri, rvimsg[1]);
        		state = FSM.READY;
    		}
    		break;
    	}
    	case FSM.GET_VEHICLE_HVAC:{
    		console.log("HVAC Response Received.");
    		break;
    	}
    	case FSM.GET_VEHICLE_LOCATION:{
    		console.log("Location Response Received.");
    		break;
    	}
    	case FSM.MAKEOCFRVIDEVICE:
    	case FSM.SETHVAC:
    	case FSM.READY:{
    		console.log(".....................................Gateway Ready");
    		state = FSM.READY;
    		break;
    	}
    }
};

var post = function(uri, b){
    console.log("Posting " + JSON.stringify(b) + "to " + uri + " in state = " + state);
    var options = {
        url: uri ,
        json : true,
        method: 'POST',
        body: b
    };
    request(options, wsiFSM);        
};

var start = function(){
	state = FSM.RVICONNECT;//connect to rvi
	console.log("Callback Initialization");
	post(rviuri, rvimsg[0]);
};


module.exports = {
    init: function(app) {
        var template = {
                "sid":"org.wsidemo.callback",
                "handler" : "callback",
                "description":"The app to handle responses from WSI.",
                "platforms":[
                    {
                        "name":"Linux",
                        "minPlatformVersion":"3.0",
                        "minApiVersion":"0.1",
                        "appURL":"http://wsidemoapp.com",
                        "minAppVersion":"1.0"
                    }
                ],
                "capability":[
                    {
                        "cid":"org.wsi.ocfcallback",
                        "platform" : "linux",
                        "isauthrequired":"false",
                        "description":"Gets the current status of a resource and its properties.",
                        "endpoint":"http://localhost:8081/callback",
                        "endpointtype":"REST",
                        "operation":"OCFRVIUPDATE",
                        "params":{}
                    },
                    {
                        "cid":"/callback",
                        "platform" : "linux",
                        "isauthrequired":"false",
                        "description":"Callback invocations from OCF-RVI.",
                        "endpoint":"http://localhost:8081/callback",
                        "endpointtype":"REST",
                        "operation":"RVICALLBACK",
                        "params":{},
                    }
                ]
        };
        return template;
    },
    request: function (req, res) {
        console.log("Received RVI Callback : "+ JSON.stringify(req.body));
        res.sendStatus(200);
        
        console.log("Content Type = " + JSON.stringify(req.headers));
        
        var rcvbody;
        if(req.body.utf8Data instanceof Object)
        	rcvbody = req.body.utf8Data;
        else
        	rcvbody = JSON.parse(req.body.utf8Data);
        
    	var params = rcvbody.params.parameters;
    	console.log("-------------------------------------------------------------------");
        if(params)
        	console.log("WSI Request Processing " + params.target);
        else
        	console.log("WHY AM I EVEN HERE");
        
        if(params && params.target == "GETLOCATION"){
    		state = FSM.GET_VEHICLE_HVAC;
        	for(var key in params){
    			ocfbody[1].payload[key] = params[key];
    			console.log(key + " = " +  params[key]);
    		}
    		rvimsg[1].params = rvibody[2];
    		res = post(rviuri, rvimsg[1]);
        }
        if(params && params.target == "GETHVAC"){
    		for(var key in params.status){
    			ocfbody[1].payload[key] = params.status[key];
    			console.log(key + " = " +  params.status[key]);
    		}
    		state = FSM.FINDOCFDEVICES;
        	var res = post(ocfuri, ocfbody[0]);
        }
        if(params && params.target == "HVACSTATUS"){
        	//Send an update to hosted resource
    		console.log("RVI OCF Device Update Received." + params.function + " = " + params.value + " by RVI.")
    		ocfbody[5].payload = {};
			ocfbody[5].payload[params.function] = params.value;
        	var res = post(ocfuri, ocfbody[5]);
        }
        if(params && params.target == "OCF_HVAC_UPDATE"){
        	//send to RVI
        	console.log("Send Update to RVI." + params.status.function);
    		state = FSM.SETHVAC;
    		rvibody[4].params.parameters.function = params.status.function;
    		rvibody[4].params.parameters.newValue = params.status.newValue;
    		rvimsg[1].params = rvibody[4];
    		res = post(rviuri, rvimsg[1]);
        }
        if(params && params.target == "SMARTHOMESCENARIO"){
        	if(params.text == "SmartHome Status"){
        		console.log("Scenario Name : " + params.text)
            	//series of OCF GET requests - SmartHome Status
        		state = FSM.SMARTHOMESTATUS;
        	}
        	if(params.text == "Coming Home"){
        		console.log("Scenario Name : " + params.text)
            	//series of OCF POST requests - Coming Home
        		state = FSM.COMINGHOME;
        		var len = ocfdevices.length;
        		for (var i = 0; i < len; i++) {
        			console.log("Checking " + ocfdevices[i]);
        			var device = JSON.parse(ocfdevices[i]);
        			var sample;
        			if(device.uri == "/a/light"){
            			sample = {
        					"state" : 1,
        					"param" : 0,
        					"color" : 1
    					};
        			}
        			if(device.uri == "/a/thermostat"){
        				sample = {
    						"state" : 1,
    						"param" : 20,
    						"temp" : 20
        				};
        			}
        			if(device.uri == "/a/washer"){
        				sample = {
    						"state" : 1,
    						"param" : 20,
    						"time" 	 : 0
						};
        			}
        			if(device.uri == "/a/tv"){
        				sample = {
    						"state" : 1,
    						"source" : 0
						};
        			}
        			if(device.uri == "/a/aircon"){
        				sample = {
    						"state"    : 1,
    						"temp" 	   : 17,
    						"fanspeed" : 40,
						};
        			}
        			if(device.uri == "/a/door"){
            			sample = {
        					"state" : 1,
        					"doorbell" : 3
    					};
        			}
					ocfbody[3].params.address = device.address;	
					ocfbody[3].params.port = device.port;
					ocfbody[3].params.uri = device.uri;
					ocfbody[3].payload = sample;
					chcount = chcount + 1;
					var res = post(ocfuri, ocfbody[3]);
					break;
        		}        		
        	}
        }
    	console.log("-------------------------------------------------------------------");
    },
    start: start,
}
console.log("App initialized");