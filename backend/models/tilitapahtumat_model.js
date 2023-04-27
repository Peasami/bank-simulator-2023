const db = require('../database');

const tapahtuma =
{
    getAll: function(callback)
    {
        return db.query('select * from Tilitapahtumat', callback);
    },
    getById: function(id, callback)
    {
        return db.query('SELECT pvm, TapahtumaNimi, SummaDebit, SummaCredit FROM Tilitapahtumat JOIN Tili ON Tilitapahtumat.idTili=Tili.idTili JOIN Kortti ON Tili.idTili=Kortti.idTili WHERE Kortti.idKortti=? ORDER BY pvm DESC;', [id], callback);
    },
    add: function(tilitapahtumat, callback)
    {
        return db.query('insert into Tilitapahtumat (idTili,pvm,TapahtumaNimi,SummaDebit,SummaCredit) values(?,?,?,?,?)',
        [tilitapahtumat.idTili, tilitapahtumat.pvm, tilitapahtumat.TapahtumaNimi, tilitapahtumat.SummaDebit, tilitapahtumat.SummaCredit],
        callback
      );
    },
    delete: function(id, callback) {
      return db.query('delete from Tilitapahtumat where idTilitapahtumat=?', [id], callback);
    },
    update: function(id, tilitapahtumat, callback) {
      return db.query(
        'update Tilitapahtumat set idTili=?, pvm=?, TapahtumaNimi=?, SummaDebit=?, SummaCredit=? where idTilitapahtumat=?',
        [tilitapahtumat.idTili, tilitapahtumat.pvm, tilitapahtumat.TapahtumaNimi, tilitapahtumat.SummaDebit, tilitapahtumat.SummaCredit, id],
        callback
      );
    }
};

module.exports = tapahtuma;
