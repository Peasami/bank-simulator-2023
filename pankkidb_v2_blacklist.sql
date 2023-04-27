CREATE DATABASE  IF NOT EXISTS `pankkidb` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `pankkidb`;
-- MySQL dump 10.13  Distrib 8.0.31, for Win64 (x86_64)
--
-- Host: db4free.net    Database: pankkidb
-- ------------------------------------------------------
-- Server version	8.0.33

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Asiakas`
--

DROP TABLE IF EXISTS `Asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Asiakas` (
  `idAsiakas` int NOT NULL AUTO_INCREMENT,
  `Etunimi` varchar(45) NOT NULL,
  `Sukunimi` varchar(45) NOT NULL,
  `Osoite` varchar(45) NOT NULL,
  PRIMARY KEY (`idAsiakas`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Asiakas`
--

LOCK TABLES `Asiakas` WRITE;
/*!40000 ALTER TABLE `Asiakas` DISABLE KEYS */;
INSERT INTO `Asiakas` VALUES (1,'Aku','Ankka','Paratiisitie 13'),(2,'Hessu','Hopo','Koulukuja 5'),(3,'Mikki','Hiiri','Juustokuja 6');
/*!40000 ALTER TABLE `Asiakas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Kortti`
--

DROP TABLE IF EXISTS `Kortti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Kortti` (
  `idKortti` varchar(20) NOT NULL,
  `PIN` varchar(255) NOT NULL,
  `idAsiakas` int NOT NULL,
  `idTili` int NOT NULL,
  `Debit` tinyint(1) DEFAULT NULL,
  `Credit` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`idKortti`),
  KEY `Asiakas2_idx` (`idAsiakas`),
  KEY `Tili1_idx` (`idTili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Kortti`
--

LOCK TABLES `Kortti` WRITE;
/*!40000 ALTER TABLE `Kortti` DISABLE KEYS */;
INSERT INTO `Kortti` VALUES ('06000626a5','$2a$10$wKftUu.Lcf/KPRS1XrCHe.6J5gY2DMrhI3mWaGf7yLkM/gSn66FRu',1,1,1,0),('06000d8977','$2a$10$YE8iX6UaMVFtlWy0abyN.eRa2wMSpUcxPhW0LTVgc2nYxRt9I79bu',3,3,1,1),('0b0032a677','$2a$10$N14CwoUeiYNaE3U.3Zq9a.xCN7H5SRowdkdbICRBTGDXAF7Q51MFy',2,2,0,1);
/*!40000 ALTER TABLE `Kortti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tili`
--

DROP TABLE IF EXISTS `Tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Tili` (
  `idTili` int NOT NULL AUTO_INCREMENT,
  `TilinroDebit` varchar(45) DEFAULT NULL,
  `SaldoDebit` float DEFAULT NULL,
  `TilinroCredit` varchar(45) DEFAULT NULL,
  `SaldoCredit` float DEFAULT NULL,
  PRIMARY KEY (`idTili`),
  UNIQUE KEY `Tilinumero_UNIQUE` (`TilinroDebit`),
  UNIQUE KEY `TilinroCredit_UNIQUE` (`TilinroCredit`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tili`
--

LOCK TABLES `Tili` WRITE;
/*!40000 ALTER TABLE `Tili` DISABLE KEYS */;
INSERT INTO `Tili` VALUES (1,'1111-2222',110,NULL,NULL),(2,'3333-4444',5000,'4444-3333',1210),(3,'5555-6666',48543,'6666-5555',198968);
/*!40000 ALTER TABLE `Tili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tilitapahtumat`
--

DROP TABLE IF EXISTS `Tilitapahtumat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Tilitapahtumat` (
  `idTilitapahtumat` int NOT NULL AUTO_INCREMENT,
  `idTili` int NOT NULL,
  `pvm` datetime DEFAULT NULL,
  `TapahtumaNimi` varchar(45) DEFAULT NULL,
  `SummaDebit` float DEFAULT NULL,
  `SummaCredit` float DEFAULT NULL,
  PRIMARY KEY (`idTilitapahtumat`,`idTili`),
  UNIQUE KEY `idTilitapahtumat_UNIQUE` (`idTilitapahtumat`),
  KEY `Tili2_idx` (`idTili`)
) ENGINE=InnoDB AUTO_INCREMENT=48 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tilitapahtumat`
--

LOCK TABLES `Tilitapahtumat` WRITE;
/*!40000 ALTER TABLE `Tilitapahtumat` DISABLE KEYS */;
INSERT INTO `Tilitapahtumat` VALUES (1,1,'2023-03-28 10:33:16','Alkutalletus',130,NULL),(2,2,'2023-03-28 10:34:57','Alkutalletus',5000,NULL),(3,2,'2023-03-28 10:35:39','Alkuluotto',NULL,2000),(4,3,'2023-03-28 10:36:00','Alkutalletus',50000,NULL),(5,3,'2023-03-28 10:36:05','Alkuluotto',NULL,200000),(6,1,'2023-04-17 12:23:12','Nosto',20,NULL),(7,3,'2023-04-24 13:33:55','nosto',20,NULL),(8,3,'2023-04-24 13:34:31','nosto',NULL,20),(9,3,'2023-04-25 16:51:20','lahjoitus, Punainen Risti',40,NULL),(10,3,'2023-04-25 16:51:27','nosto',100,NULL),(11,3,'2023-04-25 16:51:30','nosto',60,NULL),(12,3,'2023-04-25 16:51:36','nosto',20,NULL),(13,3,'2023-04-25 16:51:38','nosto',100,NULL),(14,3,'2023-04-25 16:51:43','nosto',50,NULL),(15,3,'2023-04-25 16:51:50','lahjoitus, Syöpäsäätiö',100,NULL),(16,3,'2023-04-25 16:51:53','nosto',40,NULL),(17,3,'2023-04-25 16:51:55','nosto',20,NULL),(18,3,'2023-04-25 16:52:06','nosto',NULL,200),(19,3,'2023-04-25 16:52:08','nosto',NULL,40),(20,3,'2023-04-25 16:52:12','nosto',NULL,100),(21,3,'2023-04-25 16:52:13','nosto',NULL,20),(22,3,'2023-04-25 16:52:15','nosto',NULL,60),(23,3,'2023-04-25 16:52:19','nosto',NULL,80),(24,3,'2023-04-27 06:38:29','lahjoitus, Pelastakaa Lapset',20,NULL),(25,3,'2023-04-27 06:38:51','nosto',20,NULL),(26,3,'2023-04-27 06:46:36','lahjoitus, Punainen Risti',NULL,20),(27,3,'2023-04-27 06:46:46','nosto',NULL,20),(28,3,'2023-04-27 06:47:05','nosto',NULL,2),(29,3,'2023-04-27 06:47:30','nosto',NULL,0),(30,3,'2023-04-27 07:09:35','nosto',20,NULL),(31,3,'2023-04-27 07:09:43','nosto',NULL,200),(32,3,'2023-04-27 07:11:15','nosto',20,NULL),(33,3,'2023-04-27 07:11:43','nosto',NULL,200),(34,2,'2023-04-27 10:53:10','nosto',NULL,200),(35,2,'2023-04-27 10:53:29','nosto',NULL,200),(36,2,'2023-04-27 10:53:43','nosto',NULL,200),(37,3,'2023-04-27 12:35:59','lahjoitus, Mieli RY',NULL,20),(38,2,'2023-04-27 13:00:55','lahjoitus, Syöpäsäätiö',NULL,40),(39,2,'2023-04-27 13:01:37','lahjoitus, Punainen Risti',NULL,20),(40,3,'2023-04-27 14:22:54','nosto',NULL,0),(41,3,'2023-04-27 14:23:53','nosto',0,NULL),(42,3,'2023-04-27 14:32:49','nosto',50,NULL),(43,2,'2023-04-27 15:09:59','nosto',NULL,20),(44,2,'2023-04-27 15:12:47','nosto',NULL,100),(45,2,'2023-04-27 15:13:40','nosto',NULL,10),(46,3,'2023-04-27 16:41:22','lahjoitus, Mieli RY',777,NULL),(47,3,'2023-04-27 16:43:04','nosto',NULL,50);
/*!40000 ALTER TABLE `Tilitapahtumat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `lukitut_kortit`
--

DROP TABLE IF EXISTS `lukitut_kortit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lukitut_kortit` (
  `idKortti` varchar(20) NOT NULL,
  PRIMARY KEY (`idKortti`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `lukitut_kortit`
--

LOCK TABLES `lukitut_kortit` WRITE;
/*!40000 ALTER TABLE `lukitut_kortit` DISABLE KEYS */;
INSERT INTO `lukitut_kortit` VALUES ('06000626a5');
/*!40000 ALTER TABLE `lukitut_kortit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tili_asiakas`
--

DROP TABLE IF EXISTS `tili_asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili_asiakas` (
  `idTili_Asiakas` int NOT NULL AUTO_INCREMENT,
  `idAsiakas` int NOT NULL,
  `idTili` int NOT NULL,
  PRIMARY KEY (`idTili_Asiakas`,`idAsiakas`,`idTili`),
  KEY `Asiakas1_idx` (`idAsiakas`),
  KEY `Tili3_idx` (`idTili`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili_asiakas`
--

LOCK TABLES `tili_asiakas` WRITE;
/*!40000 ALTER TABLE `tili_asiakas` DISABLE KEYS */;
INSERT INTO `tili_asiakas` VALUES (1,1,1),(2,2,2),(3,3,2),(4,3,3);
/*!40000 ALTER TABLE `tili_asiakas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'pankkidb'
--
/*!50003 DROP PROCEDURE IF EXISTS `check_if_card_locked` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`bankuzer`@`%` PROCEDURE `check_if_card_locked`(IN first_id VARCHAR(45))
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
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `credit_transfer` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`bankuzer`@`%` PROCEDURE `credit_transfer`(IN first_id VARCHAR(45), IN action VARCHAR(45), IN amount FLOAT )
BEGIN
    DECLARE test1 INT DEFAULT 0;
    START TRANSACTION;
    UPDATE Tili JOIN Kortti ON Tili.idTili = Kortti.idTili SET SaldoCredit=SaldoCredit-amount WHERE idKortti=first_id AND SaldoCredit>=amount;
    SET test1=ROW_COUNT(); #testi muuttujaan tallennetaan row_countin arvo. Jos ylempi rivi onnistui row_count=1 tai jos ei onnistunut row_count=0
    IF (test1 > 0) THEN #Ainoastaan silloin kun ylempi saldon update-komento onnistui lisätään tilitapahtuma
      COMMIT;
      INSERT INTO Tilitapahtumat(idTili,pvm,TapahtumaNimi,SummaCredit) SELECT idTili, NOW(), action, amount FROM Kortti WHERE idKortti = first_id;
    ELSE
      ROLLBACK;
    END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `debit_transfer` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`bankuzer`@`%` PROCEDURE `debit_transfer`(IN `first_id` VARCHAR(45), IN `action` VARCHAR(45), IN `amount` FLOAT)
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
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-04-27 20:50:27
