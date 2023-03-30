var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
<<<<<<< HEAD
var tilitapahtumatRouter = require('./routes/tilitapahtumat');
=======
var asiakasRouter = require('./routes/asiakas');
>>>>>>> main

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
<<<<<<< HEAD
app.use('/tilitapahtumat', tilitapahtumatRouter);
=======
app.use('/asiakas', asiakasRouter);
>>>>>>> main

module.exports = app;
