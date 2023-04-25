const db = require('../database');

const Tili = {
  getAll: function(callback) {
    return db.query('select * from Tili', callback);
  },
  getById: function(id, callback) {
    return db.query('SELECT t.TilinroDebit, t.SaldoDebit, t.TilinroCredit, t.SaldoCredit FROM Tili t INNER JOIN kortti k ON t.idTili = k.idTili WHERE k.idKortti =?', [id], callback);
  },
  add: function(Tili, callback) {
    return db.query(
      'insert into Tili (TilinroDebit, SaldoDebit, TilinroCredit, SaldoCredit) values(?,?,?,?)',
      [Tili.TilinroDebit, Tili.SaldoDebit, Tili.TilinroCredit, Tili.SaldoCredit],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from Tili where idTili=?', [id], callback);
  },
  update: function(id, Tili, callback) {
    return db.query(
      'update Tili set TilinroDebit=?, SaldoDebit=?, TilinroCredit=?, SaldoCredit=? where idTili=?',
      [Tili.TilinroDebit, Tili.SaldoDebit, Tili.TilinroCredit, Tili.SaldoCredit, id],
      callback
    );
  },

  debit_transfer: function(debitTransfer, callback) {
    return db.query(
      'call debit_transfer(?, ?, ?);',
      [debitTransfer.idKortti, debitTransfer.tapahtumaNimi, debitTransfer.maara],
      callback
    );
  },

  credit_transfer: function(creditTransfer, callback) {
    return db.query(
      'call credit_transfer(?, ?, ?);',
      [creditTransfer.idKortti, creditTransfer.tapahtumaNimi, creditTransfer.maara],
      callback
    );
  }
};
module.exports = Tili;