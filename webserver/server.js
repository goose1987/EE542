var http=require('http');

var request = require("request");

var scratchtxt="";


var spark = require('spark');

var device;

spark.on('login',function(){
	var devicesPr = spark.listDevices();

	devicesPr.then(
	
		
			function(devices){
				device=devices[0];
				console.log('devices:',devices);
				//console.log('device:',device);
				device.callFunction('queryVolts','',function(err,data){
					console.log('result:',data.return_value);
				});

			}



	);
	

	setInterval(function(){
		device.callFunction('queryVolts','',function(err,data){
					console.log('result:',data.return_value);
					scratchtxt=JSON.stringify(data);
				});
	},1000);

	
	
	

});


spark.login({username:'phamh1987@gmail.com',password:'Swellpt1'});


/*

var fs = require("fs");
var myJson={

	key:"myvalue"

};

fs.writeFile("filename.json",JSON.stringify(myJson),"utf8",yourcallback);

myJson=require("./filename.json");

*/

/*
setInterval(function(){

	request("http://api.spark.io/v1/devices/badger_penguin/result?access_token=a2351163aa2217b904f08964cad63325ad944df8",function(error,response,body){

	scratchtxt=body;

});


},1000);

*/


http.createServer(function (req, res){
	/*
	request.post("http://api.spark.io/v1/devices/badger_penguin/queryVolts?access_token=a2351163aa2217b904f08964cad63325ad944df8",function(response,body){
	scratchtxt=body;

});
	*/

	
		res.writeHead(200, {'Content-Type':'text/plain'});
		res.write(scratchtxt);
		res.end('Hello World and proton is a mark\n');
	}).listen(8124,"127.0.0.1");







console.log('Server running at http://127.0.0.1:8124/');



