#Aliohjelman mallipohja https://peatutor.com/, joka muokattu toimivaksi meidän tietokantaan
#Aliohjelnma ottaa parametreinä kortin id:n, tapahtuman ninmen sekä summan. 
CREATE PROCEDURE `debit_transfer`(IN `first_id` VARCHAR(45), IN `action` VARCHAR(45), IN `amount` FLOAT)
BEGIN
    DECLARE test1 INT DEFAULT 0;
    START TRANSACTION;
    UPDATE Tili JOIN Kortti ON Tili.idTili = Kortti.idTili SET SaldoDebit=SaldoDebit-amount WHERE idKortti=first_id AND SaldoDebit>=amount;
    SET test1=ROW_COUNT(); #testi muuttujaan tallennetaan row_countin arvo. Jos ylempi rivi onnistui row_count=1 tai jos ei onnistunut row_count=0
    IF (test1 > 0) THEN #Ainoastaan silloin kun ylempi saldon update-komento onnistui lisätään tilitapahtuma
      COMMIT;
      INSERT INTO Tilitapahtumat(idTili,pvm,TapahtumaNimi,SummaDebit) SELECT idTili, NOW(), action, amount FROM Kortti WHERE idKortti = first_id;
    ELSE
      ROLLBACK;
    END IF;
END