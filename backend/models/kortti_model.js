const db = require('../database');

const bcrypt = require('bcryptjs');

const saltRounds=10;

const kortti = {
  getAll: function(callback) {
    return db.query('select * from Kortti', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from kortti where idKortti=?', [id], callback);
  },
  add: function(Kortti, callback) {
    
      bcrypt.hash(Kortti.PIN, saltRounds, function(err, hashed_PIN) {
        return db.query('insert into Kortti (idKortti,PIN,idAsiakas,idTili,Debit,Credit) values(?,?,?,?,?,?)',
      [Kortti.idKortti, hashed_PIN, Kortti.idAsiakas, Kortti.idTili,Kortti.Debit, Kortti.Credit],
      callback);
      });
  },
  delete: function(id, callback) {
    return db.query('delete from Kortti where idKortti=?', [id], callback);
  },
  update: function(id, Kortti, callback) {
    bcrypt.hash(Kortti.PIN, saltRounds, function(err, hashed_PIN) {
    return db.query('update Kortti set PIN=?,Debit=?, Credit=? where idKortti=?',
      [hashed_PIN, Kortti.Debit, Kortti.Credit, id],
      callback);
  });
},
};
module.exports = kortti;