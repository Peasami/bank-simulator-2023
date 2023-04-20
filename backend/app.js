var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const dotenv=require('dotenv');
const jwt = require('jsonwebtoken');

const indexRouter = require('./routes/index');
const loginRouter = require('./routes/login');
var tilitapahtumatRouter = require('./routes/tilitapahtumat');
var tiliRouter = require('./routes/tili');
var asiakasRouter = require('./routes/asiakas');
const tili_asiakasRouter = require('./routes/tili_asiakas');
var korttiRouter = require('./routes/kortti');
var transferRouter = require('./routes/transfer');
var app = express();
dotenv.config();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/login', loginRouter);
//app.use(authenticateToken);
app.use('/tilitapahtumat', tilitapahtumatRouter);
app.use('/tili', tiliRouter);
app.use('/asiakas', asiakasRouter);
app.use('/tili_asiakas', tili_asiakasRouter);
app.use('/kortti', korttiRouter);
app.use('/transfer', transferRouter);


function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

  module.exports = app;