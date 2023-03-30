const db = require('../database');

const tili_asiakas = {
  getAll: function(callback) {
    return db.query('select * from tili_asiakas', callback);
  },

  getById: function(id, callback) {
    return db.query('select * from tili_asiakas where idTili_Asiakas=?', [id], callback);
  },
  getByAsiakas: function(id, callback) {
    return db.query('select * from tili_asiakas where idAsiakas=?', [id], callback);
  },
  getByTili: function(id, callback) {
    return db.query('select * from tili_asiakas where idTili=?', [id], callback);
  },
  add: function(tili_asiakas, callback) {
    return db.query(
      'insert into tili_asiakas (idTili,idAsiakas) values(?,?)',
      [tili_asiakas.idTili, tili_asiakas.idAsiakas],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from tili_asiakas where idTili_Asiakas=?', [id], callback);
  },
  update: function(id, tili_asiakas, callback) {
    return db.query(
      'update tili_asiakas set idTili=?,idAsiakas=? where idTili_Asiakas=?',
      [tili_asiakas.idTili, tili_asiakas.idAsiakas, id],
      callback
    );
  }
};
module.exports = tili_asiakas;