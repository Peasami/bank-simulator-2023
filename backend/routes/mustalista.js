const express = require('express');
const router = express.Router();
const mustattu = require('../models/mustalista_model');

router.get('/',
    function(request, response){
        mustattu.getAll(function(err, dbResult){
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
});

router.post('/', 
function(request, response) {
  mustattu.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  mustattu.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.post('/check', 
function(request, response) {
    mustattu.check_if_card_locked(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
        response.json(dbResult.affectedRows);
    }
  });
});

module.exports = router;