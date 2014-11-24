var http=require('http');
var fs = require("fs");

var request = require("request");

var voltage = 0;


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
					voltage=json.return_value;
					//console.log(now.toString()+':'+json.return_value);
				}

			});
	},
	1000);



var plotly = require('plotly')('hoang.pham','fxyuq3d36u');
var Signal = require('random-signal')
var config = require("./config.json") // put your user credentials in config.json
var apikey = "fxyuq3d36u"
var username = "hoang.pham"
var token = "u1n5rq6t8n"
// , username = ''
// , apikey = ''
// build a data object - see https://plot.ly/api/rest/docs for information

var voltdata = [{x:[], y:[], stream:{token:'u1n5rq6t8n', maxpoints:200}}];
var tempdata = [{x:[], y:[], stream:{token:'nneutplqhv', maxpoints:200}}];

var mdata = [{
	x:[],
	y:[],
	stream:{
		token : 'u1n5rq6t8n',
		maxpoints : 200
	}},
	{
	x:[],
	y:[],
	stream:{
		token : 'nneutplqhv',
		maxpoints :200
	}}];

var initGraphOptions = {fileopt : "overwrite", filename : "nodenodenode"};

plotly.plot(mdata, initGraphOptions, function (err, msg) {
  if (err) return console.log(err)
  console.log(msg);
  var url=msg['url'];

  var stream1 = plotly.stream('u1n5rq6t8n', function (err, res) {
    console.log(err, res);
    clearInterval(loop); // once stream is closed, stop writing
  });

  var stream2 = plotly.stream('nneutplqhv', function (err, res){
    console.log(err, res);
	clearInterval(loop);
	});


  var i = 0;
  var loop = setInterval(function () {
      
      var streamObject = JSON.stringify({ x : i, y : voltage});
      var streamObject2 = JSON.stringify({ x : i, y :sine(i)});

      stream1.write(streamObject+'\n');
	stream2.write(streamObject2+'\n');
      i+=0.1;
  }, 1000);

  http.createServer(function (req, res){


	res.writeHead(200, {'Content-Type':'text/html'});
	res.write('<div align="left">\n');
	res.write('<iframe id="igraph"  src="'+url+'/550/550"'+" width='550' height='550' style='border:none'></iframe>\n");
	res.write('dsfaoiwjfwoifawfaweijfewa\n');

	res.write('</div>\n');

	
	
	res.end();

	}).listen(8124,"127.0.0.1");
});


function sine (x) {

return 100*Math.sin(x)

}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////




console.log('Server running at http://127.0.0.1:8124/');

