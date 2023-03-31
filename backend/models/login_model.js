const db = require('../database');

const login={
  checkPIN: function(login_kortti, callback) {
      return db.query('SELECT pin FROM kortti WHERE idKortti=?',login_kortti, callback); 
    }
};
          
module.exports = login;