var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

const indexRouter = require('./routes/index');
<<<<<<< HEAD
const usersRouter = require('./routes/users');
<<<<<<< HEAD
var tilitapahtumatRouter = require('./routes/tilitapahtumat');
=======
=======
var tiliRouter = require('./routes/tili');
>>>>>>> c1f018e24f91c3d99e7f8d872291354c63a5c25f
var asiakasRouter = require('./routes/asiakas');
>>>>>>> main

const tili_asiakasRouter = require('./routes/tili_asiakas');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
<<<<<<< HEAD
app.use('/users', usersRouter);
<<<<<<< HEAD
app.use('/tilitapahtumat', tilitapahtumatRouter);
=======
=======
app.use('/tili', tiliRouter);
>>>>>>> c1f018e24f91c3d99e7f8d872291354c63a5c25f
app.use('/asiakas', asiakasRouter);
>>>>>>> main
app.use('/tili_asiakas', tili_asiakasRouter);

module.exports = app;
