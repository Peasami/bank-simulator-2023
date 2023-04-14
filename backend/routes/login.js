const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.idKortti && request.body.PINkoodi){
      const kortti = request.body.idKortti;
      const pinni = request.body.PINkoodi;
      
        login.checkPIN(kortti, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError.errno);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pinni,dbResult[0].pin, function(err,compareResult) {
                if(compareResult) {
                  console.log("onnistui!");
                  const token = generateAccessToken({ idKortti: kortti });
                  response.send(token);
                }
                else {
                    console.log("väärä PINkoodi");
                    //console.log(dbResult[0].pin);
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("korttia ei löydy");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("idKortti tai PINkoodi puuttuu");
      response.send(false);
    }
  }
);

function generateAccessToken(idKortti) {
  dotenv.config();
  return jwt.sign(idKortti, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;