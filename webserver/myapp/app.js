var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var routes = require('./routes/index');
var users = require('./routes/users');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

// uncomment after placing your favicon in /public
//app.use(favicon(__dirname + '/public/favicon.ico'));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', routes);
app.use('/users', users);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});

// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
    app.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});


var request = require("request");


//setup plotly////
var plotly = require('plotly')('hoang.pham','fxyuq3d36u');
var apikey = "fxyuq3d36u"
var username="hoang.pham"
var token1 = "u1n5rq6t8n"
var token2 = "nneutplqhv"
var token3 = "jkzn4pzo6z"
//////////////////////

////gps coordinate/////
var gpscoordinate=[47.6097,-122.3331];
//////////////////////

var sparktoken='a2351163aa2217b904f08964cad63325ad944df8';

var strftime=require('fast-strftime');

var voltage=0;
var amp=0;
var temperature=0;
var vin=0;


////////spark comm//////////////////////////////
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
					console.log(now.toString()+'voltage:'+json.return_value);
				}

			});
		request.post(
			'https://api.spark.io/v1/devices/'+'badger_penguin'+'/'+'queryTemp',
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
					temperature=json.return_value;
					console.log(now.toString()+'temp:'+json.return_value);
				}

			});
		request.post(
			'https://api.spark.io/v1/devices/'+'badger_penguin'+'/'+'queryVin',
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
					vin=json.return_value;
					console.log(now.toString()+'vin:'+json.return_value);
				}

			});
	},
	1500);

setInterval(
	function(){
		request.post(
			'https://api.spark.io/v1/devices/'+'badger_penguin'+'/'+'queryAmp',
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
					amp=json.return_value;
					console.log(now.toString()+'amperage:'+json.return_value);
				}

			});
	},
	1000);




///////////////////////////////////////////////////

var mdata = [{
	x:[strftime('%Y-%m-%d %H:%M:%S')],
	y:[voltage],
	name:'output voltage',
	stream:{
		token:token1,
		maxpoints : 200
	}},
	{
	x:[strftime('%Y-%m-%d %H:%M:%S')],
	y:[vin],
	name:'input voltage',
	stream:{
		token:token3,
		maxpoints : 200
	}},
	{
	x:[strftime('%Y-%m-%d %H:%M:%S')],
	y:[amp],
	name:'rms current',
	yaxis: 'y2',
	stream:{
		token:token2,
		maxpoints : 200
	}}];

var layout = {
	title:"output",
	xaxis:{
		title:"UTC time stamps"
	},
	yaxis:{
		title:"volts (V)"
	},
	yaxis2:{
		title:"amps (A)",
		overlaying:"y",
		side:"right"
	}
};

var initGraphOptions={fileopt:"overwrite",filename:"nodenodenode",layout:layout};

plotly.plot(mdata, initGraphOptions,function(err,msg){
	if(err) return console.log(err)
	//console.log(msg);
	var url = msg['url'];
	var stream1 = plotly.stream(token1,function(err,res){
		//console.log(err,res);
		clearInterval(loop);//once stream is closed stop writing
	});
	var stream2=plotly.stream(token2,function(err,res){
		//console.log(err,res);
		clearInterval(loop);
	});

	var stream3=plotly.stream(token3,function(err,res){
		clearInterval(loop);
	});
	//var i=0;
	var loop = setInterval(function(){
		var streamObject1 = JSON.stringify({x:strftime('%Y-%m-%d %H:%M:%S'),y:vin});
		var streamObject2=JSON.stringify({x:strftime('%Y-%m-%d %H:%M:%S'),y:amp});
		var streamObject3=JSON.stringify({x:strftime('%Y-%m-%d %H:%M:%S'),y:voltage});
		
		stream1.write(streamObject1+'\n');
		stream2.write(streamObject2+'\n');
		stream3.write(streamObject3+'\n');
		//i+=0.1;
	},1000);



	var server = app.listen(8080,function(){

		var host = server.address().address
		var port = server.address().port
		console.log('app up');


	});
});


function converttemp(x){
	var foo=x*3.3/4095;
	var bar=(foo/(3/5)-1.375)/0.0225;
	return bar;
}


module.exports = app;
