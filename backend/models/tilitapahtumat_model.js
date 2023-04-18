const db = require('../database');

const tapahtuma =
{
    getAll: function(callback)
    {
        return db.query('select * from tilitapahtumat', callback);
    },
    getById: function(id, callback)
    {
        return db.query('SELECT pvm, TapahtumaNimi, SummaDebit, SummaCredit FROM tilitapahtumat JOIN Tili ON tilitapahtumat.idTili=Tili.idTili JOIN Kortti ON Tili.idTili=Kortti.idTili WHERE Kortti.idKortti=?', [id], callback);
    },
    add: function(tilitapahtumat, callback)
    {
        return db.query('insert into tilitapahtumat (idTili,pvm,TapahtumaNimi,SummaDebit,SummaCredit) values(?,?,?,?,?)',
        [tilitapahtumat.idTili, tilitapahtumat.pvm, tilitapahtumat.TapahtumaNimi, tilitapahtumat.SummaDebit, tilitapahtumat.SummaCredit],
        callback
      );
    },
    delete: function(id, callback) {
      return db.query('delete from tilitapahtumat where idtilitapahtumat=?', [id], callback);
    },
    update: function(id, tilitapahtumat, callback) {
      return db.query(
        'update tilitapahtumat set idTili=?, pvm=?, TapahtumaNimi=?, SummaDebit=?, SummaCredit=? where idtilitapahtumat=?',
        [tilitapahtumat.idTili, tilitapahtumat.pvm, tilitapahtumat.TapahtumaNimi, tilitapahtumat.SummaDebit, tilitapahtumat.SummaCredit, id],
        callback
      );
    }
};

module.exports = tapahtuma;
