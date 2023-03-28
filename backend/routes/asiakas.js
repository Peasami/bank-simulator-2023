const express = require('express');
const router = express.Router();
const asiakas = require('../models/asiakas_model');

router.get('/',function(request,response){
    //getAll metodi ottaa callback funktion parametrina
    asiakas.getAll(function(err,dbResult){ //db.query tarvitsee 2 parametria.
                                          //eka on virheilmoitus ja toinen on tietokannasta tulevia tuloksia varten
        if(err){ //jos tietokanta antaa virheen
            response.json(err); //lähettää virheilmoituksen json muodossa frontendille sellaisenaan kuin se on
        }
        else{
            response.json(dbResult); //muussa tapauksessa lähetetään saadut tulokset
            //console.log(dbResult);
        }
    })
});

router.get('/:id',
    function (request, response) {
        asiakas.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
            }
        })
    });


router.post('/', 
function(request, response) {
  asiakas.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      //response.json(dbResult);
      response.json(dbResult.affectedRows);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  asiakas.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});


router.put('/:id', 
function(request, response) {
  asiakas.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});


module.exports=router;