const express = require('express');
const router = express.Router();
const tili_asiakas = require('../models/tili_asiakas_model');

router.get('/tili_asiakas',
  function (request, response) {
    tili_asiakas.getAll(function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        console.log(dbResult);
        response.json(dbResult);
      }
    })
  });

router.get('/tili_asiakas/tili/:idTili',
  function (request, response) {
    tili_asiakas.getById(request.params.idTili, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
  });

router.get('/tili_asiakas/asiakas/:idAsiakas',
  function (request, response) {
    tili_asiakas.getById(request.params.idAsiakas, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
  });

router.post('/',
  function (request, response) {
    tili_asiakas.add(request.body, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(request.body);
      }
    });
  });


router.delete('/:id',
  function (request, response) {
    tili_asiakas.delete(request.params.id, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  });


router.put('/:id',
  function (request, response) {
    tili_asiakas.update(request.params.id, request.body, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  });

module.exports = router;