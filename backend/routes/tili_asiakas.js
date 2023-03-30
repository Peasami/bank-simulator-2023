const express = require('express');
const router = express.Router();
const tili_asiakas = require('../models/tili_asiakas_model');

router.get('/',
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

router.get('/:id',
  function (request, response) {
    tili_asiakas.getById(request.params.id, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
  });

/*router.get('/:id',
  function (request, response) {
    tili_asiakas.getByAsiakas(request.params.idAsiakas, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
  });*/

router.post('/',
  function (request, response) {
    tili_asiakas.add(request.body, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult.affectedRows);
      }
    });
  });


router.delete('/:id',
  function (request, response) {
    tili_asiakas.delete(request.params.id, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult.affectedRows);
      }
    });
  });


router.put('/:id',
  function (request, response) {
    tili_asiakas.update(request.params.id, request.body, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult.affectedRows);
      }
    });
  });

module.exports = router;