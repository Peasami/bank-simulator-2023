const db = require('../database');

const Asiakas = {
  getAll: function(callback) {
    return db.query('select * from Asiakas', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from Asiakas where idAsiakas=?', [id], callback);
  },
  add: function(Asiakas, callback) {
    return db.query(
      'insert into Asiakas (Etunimi,Sukunimi,Osoite) values(?,?,?)',
      [Asiakas.Etunimi, Asiakas.Sukunimi, Asiakas.Osoite],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from Asiakas where idAsiakas=?', [id], callback);
  },
  update: function(id, Asiakas, callback) {
    return db.query(
      'update Asiakas set Etunimi=?,Sukunimi=?,Osoite=? where idAsiakas=?',
      [Asiakas.Etunimi, Asiakas.Sukunimi, Asiakas.Osoite, id],
      callback
    );
  }
};
module.exports = Asiakas;