# Aliohjelma ottaa parametriksi tarkistettavan kortin numeron,
# ja vertailee sitä lukitut_kortit -taulussa oleviin numeroihin.
# Jos kortti löytyy listalta, palautetaan 1, muuten palautetaan 0.

CREATE PROCEDURE check_if_card_locked(IN first_id VARCHAR(45))
BEGIN
    SET @i = 0;
    SET @isLocked = 0;
    SET @numberOfRows = (
        SELECT count(*) FROM lukitut_kortit);

    WHILE @i < @numberOfRows
    DO
        SET @cardIdNum = '';
        SET @sql = concat('SELECT idKortti into @cardIdNum FROM lukitut_kortit LIMIT 1 OFFSET ', @i);
        PREPARE stmt1 FROM @sql;
        EXECUTE stmt1;
        IF (@cardIdNum = first_id) THEN
            SET @isLocked = 1;
        END IF;
        SET @i = @i+1;
    END WHILE;
    SELECT @isLocked AS 'locked';
END