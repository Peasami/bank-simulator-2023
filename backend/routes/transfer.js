const express = require('express');
const router = express.Router();
const tili = require('../models/tili_model');

router.put('/debit', 
function(request, response) {
    tili.debit_transfer(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
        response.json(dbResult.affectedRows);
    }
  });
});

router.put('/credit', 
function(request, response) {
    tili.credit_transfer(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
        response.json(dbResult.affectedRows);
    }
  });
});

module.exports=router;