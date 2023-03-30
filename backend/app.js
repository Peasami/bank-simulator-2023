var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const dotenv=require('dotenv');


const indexRouter = require('./routes/index');
const usersRouter = require('./routes/users');
var tilitapahtumatRouter = require('./routes/tilitapahtumat');
var tiliRouter = require('./routes/tili');
var asiakasRouter = require('./routes/asiakas');
const tili_asiakasRouter = require('./routes/tili_asiakas');
var korttiRouter = require('./routes/kortti');
var app = express();
dotenv.config();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/tilitapahtumat', tilitapahtumatRouter);
app.use('/tili', tiliRouter);
app.use('/asiakas', asiakasRouter);
app.use('/tili_asiakas', tili_asiakasRouter);
app.use('/kortti', korttiRouter)
module.exports = app;
