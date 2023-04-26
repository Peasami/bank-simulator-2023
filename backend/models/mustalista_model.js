const db = require('../database');

const mustattu =
{
    getAll: function(callback)
    {
        return db.query('select * from lukitut_kortit', callback);
    },
    add: function(lukitut_kortit, callback) {
      return db.query('insert into lukitut_kortit values(?)', [lukitut_kortit.idKortti], callback);
        
    },
    delete: function(id, callback) {
      return db.query('delete from lukitut_kortit where idKortti=?', [id], callback);
    },

    check_if_card_locked: function(isLocked, callback) {
        return db.query(
          'call check_if_card_locked(?);',
          [isLocked.idKortti],
          callback
        );
      }
};

module.exports = mustattu;
