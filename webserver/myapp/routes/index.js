var express = require('express');
var router = express.Router();

//set up forecast to get weather info////
var Forecast = require("forecast");
var forecast = new Forecast({
		service:'forecast.io',
		key:"56deaa420d921c98244bcf39f670f19e",
		units:'celcius',
		cache:true,
		ttl:{
			minutes:27,
			seconds:45
		}
		});
////////////////////////////////////////


/* GET home page. */
router.get('/', function(req, res) {
  res.render('index', { title: 'hoang pham' });
//	res.render('simple');
});

module.exports = router;
