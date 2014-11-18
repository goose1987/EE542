var http=require('http');
var fs = require("fs");

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

			}

	);
	
	
	

});


spark.login({username:'phamh1987@gmail.com',password:'Swellpt1'});

setInterval(
		function(){
			request.post(
				'https://api.spark.io/v1/devices/'+'badger_penguin'+'/'+'queryVolts',
				{
					form:{
						access_token:'a2351163aa2217b904f08964cad63325ad944df8',
						args: ''
					}
				},
				function (error,response, body){
					if(!error&&response.statusCode==200){
						var now = new Date();
						var json = JSON.parse(body);
						console.log(now.toString()+':'+json.return_value);
					}

				});
		},1000);









var plotly = require('plotly')('hoang.pham','fxyuq3d36u');



http.createServer(function (req, res){
	
		var url='';

		var plotly = require('plotly')('hoang.pham','fxyuq3d36u');

		var trace1 = {
		  x: [1, 2, 3, 4], 
		  y: [10, 15, 13, 17], 
		  type: "scatter"
		};
		var trace2 = {
		  x: [1, 2, 3, 4], 
		  y: [16, 5, 11, 9], 
		  type: "scatter"
		};
		var data = [trace1, trace2];
		var graph_options = {filename: "basic-line", world_readable: true, fileopt: "overwrite"}
		plotly.plot(data, graph_options, function (err, msg) {
		    console.log(msg.url);
		    url=msg.url;
		res.writeHead(200, {'Content-Type':'text/html'});
		//res.write('<body>');
		res.write('<iframe id="igraph" style="border:none" src="'+url+'"'+" width='100%' height='80%' </iframe>");
		//res.write('</body>');
		res.end();
		//res.end('Hello World and proton is a mark\n');
		});
		

	}).listen(8124,"127.0.0.1");



		





console.log('Server running at http://127.0.0.1:8124/');



