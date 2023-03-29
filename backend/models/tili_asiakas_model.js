const db = require('../database');

const tili_asiakas = {
  getAll: function(callback) {
    return db.query('select * from tili_asiakas', callback);
  },

  getByAsiakas: function(idAsiakas, callback) {
    return db.query('select * from tili_asiakas where idAsiakas=?', [idAsiakas], callback);
  },
  getByTili: function(idTili, callback) {
    return db.query('select * from tili_asiakas where idTili=?', [idTili], callback);
  },
  add: function(tili_asiakas, callback) {
    return db.query(
      'insert into tili_asiakas (idTili,idAsiakas) values(?,?)',
      [tili_asiakas.idTili, tili_asiakas.idAsiakas],
      callback
    );
  },
  deleteByTiliAndAsiakas: function(idTili, callback) {
    return db.query('delete from tili_asiakas where idTili=? and idAsiakas=?', [idTili], callback);
  },
  update: function(id, tili_asiakas, callback) {
    return db.query(
      'update tili_asiakas set idTili=?,idAsiakas=? where id_tili_asiakas=?',
      [tili_asiakas.idTili, tili_asiakas.idAsiakas],
      callback
    );
  }
};
module.exports = tili_asiakas;