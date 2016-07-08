CREATE DATABASE  IF NOT EXISTS `BDBIVKM` /*!40100 DEFAULT CHARACTER SET cp1251 */;
USE `BDBIVKM`;
-- MySQL dump 10.13  Distrib 5.6.13, for Win32 (x86)
--
-- Host: sql.module.ru    Database: BDBIVKM
-- ------------------------------------------------------
-- Server version	5.6.16-enterprise-commercial-advanced

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `TabAccessRights`
--

DROP TABLE IF EXISTS `TabAccessRights`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabAccessRights` (
  `idTabAccessRights` int(11) NOT NULL AUTO_INCREMENT,
  `TabLoginPassword_idTabLoginPassword` int(11) NOT NULL,
  `TabTestKinds_idTabTestKinds` int(11) NOT NULL,
  `TabTypeProducts_idTabTypeProducts` int(11) NOT NULL,
  `TabUsers_idTabUsers` int(11) NOT NULL,
  `TabAuthorityKinds_idTabAuthorityKinds` int(11) NOT NULL,
  PRIMARY KEY (`idTabAccessRights`),
  KEY `fk_TabAccessRights_TabLoginPassword1_idx` (`TabLoginPassword_idTabLoginPassword`),
  KEY `fk_TabAccessRights_TabTestKinds1_idx` (`TabTestKinds_idTabTestKinds`),
  KEY `fk_TabAccessRights_TabTypeProducts1_idx` (`TabTypeProducts_idTabTypeProducts`),
  KEY `fk_TabAccessRights_TabUsers1_idx` (`TabUsers_idTabUsers`),
  KEY `fk_TabAccessRights_TabAuthorityKinds1_idx` (`TabAuthorityKinds_idTabAuthorityKinds`),
  CONSTRAINT `fk_TabAccessRights_TabAuthorityKinds1` FOREIGN KEY (`TabAuthorityKinds_idTabAuthorityKinds`) REFERENCES `TabAuthorityKinds` (`idTabAuthorityKinds`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabAccessRights_TabLoginPassword1` FOREIGN KEY (`TabLoginPassword_idTabLoginPassword`) REFERENCES `TabLoginPassword` (`idTabLoginPassword`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabAccessRights_TabTestKinds1` FOREIGN KEY (`TabTestKinds_idTabTestKinds`) REFERENCES `TabTestKinds` (`idTabTestKinds`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabAccessRights_TabTypeProducts1` FOREIGN KEY (`TabTypeProducts_idTabTypeProducts`) REFERENCES `TabTypeProducts` (`idTabTypeProducts`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabAccessRights_TabUsers1` FOREIGN KEY (`TabUsers_idTabUsers`) REFERENCES `TabUsers` (`idTabUsers`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabAccessRights`
--

LOCK TABLES `TabAccessRights` WRITE;
/*!40000 ALTER TABLE `TabAccessRights` DISABLE KEYS */;
INSERT INTO `TabAccessRights` VALUES (1,3,1,2,1,3),(2,4,1,2,2,2),(3,4,2,2,2,2);
/*!40000 ALTER TABLE `TabAccessRights` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabAuthorityKinds`
--

DROP TABLE IF EXISTS `TabAuthorityKinds`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabAuthorityKinds` (
  `idTabAuthorityKinds` int(11) NOT NULL AUTO_INCREMENT,
  `AuthorityKind` varchar(45) NOT NULL,
  PRIMARY KEY (`idTabAuthorityKinds`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabAuthorityKinds`
--

LOCK TABLES `TabAuthorityKinds` WRITE;
/*!40000 ALTER TABLE `TabAuthorityKinds` DISABLE KEYS */;
INSERT INTO `TabAuthorityKinds` VALUES (1,'Оператор'),(2,'Аппаратчик'),(3,'Программист'),(4,'Администратор БД');
/*!40000 ALTER TABLE `TabAuthorityKinds` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabLoginPassword`
--

DROP TABLE IF EXISTS `TabLoginPassword`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabLoginPassword` (
  `idTabLoginPassword` int(11) NOT NULL AUTO_INCREMENT,
  `login` varchar(45) NOT NULL,
  `password` varchar(45) NOT NULL,
  PRIMARY KEY (`idTabLoginPassword`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabLoginPassword`
--

LOCK TABLES `TabLoginPassword` WRITE;
/*!40000 ALTER TABLE `TabLoginPassword` DISABLE KEYS */;
INSERT INTO `TabLoginPassword` VALUES (1,'User1','101'),(2,'Prog','456'),(3,'Op','789'),(4,'Ap','321'),(5,'AdminBD','202');
/*!40000 ALTER TABLE `TabLoginPassword` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabProducts`
--

DROP TABLE IF EXISTS `TabProducts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabProducts` (
  `idTabProducts` int(11) NOT NULL AUTO_INCREMENT,
  `TabTypeProducts_idTabTypeProducts` int(11) NOT NULL,
  `nameProduct` tinytext NOT NULL,
  PRIMARY KEY (`idTabProducts`),
  KEY `fk_TabProducts_TabTypeProducts_idx` (`TabTypeProducts_idTabTypeProducts`),
  CONSTRAINT `fk_TabProducts_TabTypeProducts` FOREIGN KEY (`TabTypeProducts_idTabTypeProducts`) REFERENCES `TabTypeProducts` (`idTabTypeProducts`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabProducts`
--

LOCK TABLES `TabProducts` WRITE;
/*!40000 ALTER TABLE `TabProducts` DISABLE KEYS */;
INSERT INTO `TabProducts` VALUES (1,2,'Зав. № 14'),(2,2,'Зав. № 15');
/*!40000 ALTER TABLE `TabProducts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabScripts`
--

DROP TABLE IF EXISTS `TabScripts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabScripts` (
  `idTabScripts` int(11) NOT NULL AUTO_INCREMENT,
  `TabUsers_idTabUsers` int(11) NOT NULL,
  `contentScript` text,
  `commentaryScript` text NOT NULL,
  PRIMARY KEY (`idTabScripts`),
  KEY `fk_TabScripts_TabUsers1_idx` (`TabUsers_idTabUsers`),
  CONSTRAINT `fk_TabScripts_TabUsers1` FOREIGN KEY (`TabUsers_idTabUsers`) REFERENCES `TabUsers` (`idTabUsers`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=573 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabScripts`
--

LOCK TABLES `TabScripts` WRITE;
/*!40000 ALTER TABLE `TabScripts` DISABLE KEYS */;
INSERT INTO `TabScripts` VALUES (1,3,'когда то здесь будет текст скрипта1','Проверка МКО БИВК 008 Зав. № 1-14. Скрипт1'),(2,3,'когда то здесь будет текст скрипта2','Проверка МКО БИВК 008 Зав. № 15. Скрипт1'),(3,3,'когда то здесь будет текст скрипта3','Проверка МКО БИВК 008. Скрипт2'),(4,3,'когда то здесь будет текст скрипта4','Проверка интерфейса сигналов прерываний'),(570,3,'c:\\Тест_повторяемости_МАД.py','Тест проверки модулей КПА используемых для имитации аналоговых датчиков'),(572,3,'c:\\Ponomarenko\\selftest-kpavm.py','Тест проверки модулей КПА ВМ-БИВК');
/*!40000 ALTER TABLE `TabScripts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabTestCycles`
--

DROP TABLE IF EXISTS `TabTestCycles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabTestCycles` (
  `idTabTestCycles` int(11) NOT NULL AUTO_INCREMENT,
  `TabUsers_idTabUsers` int(11) NOT NULL,
  `nameTestCycle` tinytext NOT NULL,
  PRIMARY KEY (`idTabTestCycles`),
  KEY `fk_TabTestCycles_TabUsers1_idx` (`TabUsers_idTabUsers`),
  CONSTRAINT `fk_TabTestCycles_TabUsers1` FOREIGN KEY (`TabUsers_idTabUsers`) REFERENCES `TabUsers` (`idTabUsers`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabTestCycles`
--

LOCK TABLES `TabTestCycles` WRITE;
/*!40000 ALTER TABLE `TabTestCycles` DISABLE KEYS */;
INSERT INTO `TabTestCycles` VALUES (1,2,'Пример Проверка интерфейсов СВ БИВК 008'),(2,2,'Пример Проверка интерфейсов МКО БИВК 008 Зав. № 1-14'),(3,2,'Пример Проверка интерфейсов МКО БИВК 008 Зав. № 15'),(4,2,'Проверка КПА ТМС-БИВК'),(5,2,'Проверка КПА ВМ-БИВК');
/*!40000 ALTER TABLE `TabTestCycles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabTestCycles_Scripts`
--

DROP TABLE IF EXISTS `TabTestCycles_Scripts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabTestCycles_Scripts` (
  `idTabTestCycles_Scripts` int(11) NOT NULL AUTO_INCREMENT,
  `TabTestCycles_idTabTestCycles` int(11) NOT NULL,
  `TabScripts_idTabScripts` int(11) NOT NULL,
  `TabUsers_idTabUsers` int(11) NOT NULL,
  `execOrder` int(11) NOT NULL,
  PRIMARY KEY (`idTabTestCycles_Scripts`),
  KEY `fk_TabTestCycles_Scripts_TabTestCycles1_idx` (`TabTestCycles_idTabTestCycles`),
  KEY `fk_TabTestCycles_Scripts_TabScripts1_idx` (`TabScripts_idTabScripts`),
  KEY `fk_TabTestCycles_Scripts_TabUsers1_idx` (`TabUsers_idTabUsers`),
  CONSTRAINT `fk_TabTestCycles_Scripts_TabScripts1` FOREIGN KEY (`TabScripts_idTabScripts`) REFERENCES `TabScripts` (`idTabScripts`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabTestCycles_Scripts_TabTestCycles1` FOREIGN KEY (`TabTestCycles_idTabTestCycles`) REFERENCES `TabTestCycles` (`idTabTestCycles`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabTestCycles_Scripts_TabUsers1` FOREIGN KEY (`TabUsers_idTabUsers`) REFERENCES `TabUsers` (`idTabUsers`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabTestCycles_Scripts`
--

LOCK TABLES `TabTestCycles_Scripts` WRITE;
/*!40000 ALTER TABLE `TabTestCycles_Scripts` DISABLE KEYS */;
INSERT INTO `TabTestCycles_Scripts` VALUES (1,1,1,2,3),(2,1,2,2,1),(3,1,3,2,2),(4,1,4,2,4),(7,4,570,2,1),(8,5,572,2,1);
/*!40000 ALTER TABLE `TabTestCycles_Scripts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabTestCyclograms`
--

DROP TABLE IF EXISTS `TabTestCyclograms`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabTestCyclograms` (
  `idTabTestCyclograms` int(11) NOT NULL AUTO_INCREMENT,
  `TabProducts_idTabProducts` int(11) NOT NULL,
  `TabTestKinds_idTabTestKinds` int(11) NOT NULL,
  `TabTestCycles_idTabTestCycles` int(11) NOT NULL,
  PRIMARY KEY (`idTabTestCyclograms`),
  KEY `fk_TabTestCyclograms_TabProducts1_idx` (`TabProducts_idTabProducts`),
  KEY `fk_TabTestCyclograms_TabTestKinds1_idx` (`TabTestKinds_idTabTestKinds`),
  KEY `fk_TabTestCyclograms_TabTestCycles1_idx` (`TabTestCycles_idTabTestCycles`),
  CONSTRAINT `fk_TabTestCyclograms_TabProducts1` FOREIGN KEY (`TabProducts_idTabProducts`) REFERENCES `TabProducts` (`idTabProducts`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabTestCyclograms_TabTestCycles1` FOREIGN KEY (`TabTestCycles_idTabTestCycles`) REFERENCES `TabTestCycles` (`idTabTestCycles`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabTestCyclograms_TabTestKinds1` FOREIGN KEY (`TabTestKinds_idTabTestKinds`) REFERENCES `TabTestKinds` (`idTabTestKinds`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabTestCyclograms`
--

LOCK TABLES `TabTestCyclograms` WRITE;
/*!40000 ALTER TABLE `TabTestCyclograms` DISABLE KEYS */;
INSERT INTO `TabTestCyclograms` VALUES (1,1,2,1),(2,1,2,2),(3,2,1,1),(4,2,3,3);
/*!40000 ALTER TABLE `TabTestCyclograms` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabTestKinds`
--

DROP TABLE IF EXISTS `TabTestKinds`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabTestKinds` (
  `idTabTestKinds` int(11) NOT NULL AUTO_INCREMENT,
  `nameTestKind` tinytext NOT NULL,
  PRIMARY KEY (`idTabTestKinds`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabTestKinds`
--

LOCK TABLES `TabTestKinds` WRITE;
/*!40000 ALTER TABLE `TabTestKinds` DISABLE KEYS */;
INSERT INTO `TabTestKinds` VALUES (1,'Отладка'),(2,'ПСИ'),(3,'Входной контроль');
/*!40000 ALTER TABLE `TabTestKinds` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabTestSessions`
--

DROP TABLE IF EXISTS `TabTestSessions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabTestSessions` (
  `idTabTestSessions` int(11) NOT NULL AUTO_INCREMENT,
  `TabProducts_idTabProducts` int(11) NOT NULL,
  `TabUsers_idTabUsers` int(11) NOT NULL,
  `TabTestKinds_idTabTestKinds` int(11) NOT NULL,
  `TabTestCycles_idTabTestCycles` int(11) NOT NULL,
  `commentarySession` text NOT NULL,
  `beginDateTime` datetime NOT NULL,
  `endDateTime` datetime NOT NULL,
  `textProtocol` longtext NOT NULL,
  PRIMARY KEY (`idTabTestSessions`),
  KEY `fk_TabTestSessions_TabProducts1_idx` (`TabProducts_idTabProducts`),
  KEY `fk_TabTestSessions_TabUsers1_idx` (`TabUsers_idTabUsers`),
  KEY `fk_TabTestSessions_TabTestKinds1_idx` (`TabTestKinds_idTabTestKinds`),
  KEY `fk_TabTestSessions_TabTestCycles1_idx` (`TabTestCycles_idTabTestCycles`),
  CONSTRAINT `fk_TabTestSessions_TabProducts1` FOREIGN KEY (`TabProducts_idTabProducts`) REFERENCES `TabProducts` (`idTabProducts`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabTestSessions_TabTestCycles1` FOREIGN KEY (`TabTestCycles_idTabTestCycles`) REFERENCES `TabTestCycles` (`idTabTestCycles`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabTestSessions_TabTestKinds1` FOREIGN KEY (`TabTestKinds_idTabTestKinds`) REFERENCES `TabTestKinds` (`idTabTestKinds`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TabTestSessions_TabUsers1` FOREIGN KEY (`TabUsers_idTabUsers`) REFERENCES `TabUsers` (`idTabUsers`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabTestSessions`
--

LOCK TABLES `TabTestSessions` WRITE;
/*!40000 ALTER TABLE `TabTestSessions` DISABLE KEYS */;
INSERT INTO `TabTestSessions` VALUES (1,2,2,2,1,'Пример комментария сеанса испытаний','2009-12-31 22:58:59','2009-12-31 23:59:59','Пример текста протокола'),(2,2,2,2,3,'Пример комментария сеанса испытаний','2010-04-15 10:10:08','2010-05-15 09:12:18','Пример текста протокола'),(3,1,2,1,1,'Пример комментария сеанса испытаний','2014-09-25 15:20:11','2014-09-25 15:25:12','Пример текста протокола'),(4,1,2,3,2,'Пример комментария сеанса испытаний','2015-03-24 18:18:18','2015-03-26 08:08:08','Пример текста протокола');
/*!40000 ALTER TABLE `TabTestSessions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabTests`
--

DROP TABLE IF EXISTS `TabTests`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabTests` (
  `idTabTests` int(11) NOT NULL AUTO_INCREMENT,
  `TabUsers_idTabUsers` int(11) NOT NULL,
  `nameTest` tinytext NOT NULL,
  `version` int(11) NOT NULL,
  `createdDateTime` datetime NOT NULL,
  `pathSourceText` text NOT NULL,
  `pathExecCode` text NOT NULL,
  `commentaryTest` text NOT NULL,
  PRIMARY KEY (`idTabTests`),
  KEY `fk_TabTests_TabUsers1_idx` (`TabUsers_idTabUsers`),
  CONSTRAINT `fk_TabTests_TabUsers1` FOREIGN KEY (`TabUsers_idTabUsers`) REFERENCES `TabUsers` (`idTabUsers`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabTests`
--

LOCK TABLES `TabTests` WRITE;
/*!40000 ALTER TABLE `TabTests` DISABLE KEYS */;
INSERT INTO `TabTests` VALUES (1,4,'Тест1',1,'2013-04-15 07:16:15','d:\\KPA\\Sou\\t1.c','d:\\KPA\\rez\\t1.abs','Пример комментария к тесту 1'),(2,3,'Тест2',3,'2014-08-24 18:10:18','d:\\KPA\\Sou\\t2.c','d:\\KPA\\rez\\t2.abs','Пример комментария к тесту 2'),(3,3,'Тест3',1,'2015-02-14 10:18:10','d:\\KPA\\Sou\\t3.c','d:\\KPA\\rez\\t3.abs','Пример комментария к тесту 3');
/*!40000 ALTER TABLE `TabTests` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabTypeProducts`
--

DROP TABLE IF EXISTS `TabTypeProducts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabTypeProducts` (
  `idTabTypeProducts` int(11) NOT NULL AUTO_INCREMENT,
  `nameTypeProduct` tinytext NOT NULL,
  PRIMARY KEY (`idTabTypeProducts`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabTypeProducts`
--

LOCK TABLES `TabTypeProducts` WRITE;
/*!40000 ALTER TABLE `TabTypeProducts` DISABLE KEYS */;
INSERT INTO `TabTypeProducts` VALUES (1,'БИВК 006'),(2,'БИВК 008');
/*!40000 ALTER TABLE `TabTypeProducts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TabUsers`
--

DROP TABLE IF EXISTS `TabUsers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TabUsers` (
  `idTabUsers` int(11) NOT NULL AUTO_INCREMENT,
  `lastName` varchar(45) NOT NULL,
  `firstName` varchar(45) NOT NULL,
  `patronymic` varchar(45) NOT NULL,
  `phone` varchar(20) NOT NULL,
  `email` varchar(45) NOT NULL,
  `nameDept` tinytext NOT NULL,
  `post` tinytext NOT NULL,
  `numberOffice` int(11) NOT NULL,
  PRIMARY KEY (`idTabUsers`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TabUsers`
--

LOCK TABLES `TabUsers` WRITE;
/*!40000 ALTER TABLE `TabUsers` DISABLE KEYS */;
INSERT INTO `TabUsers` VALUES (1,'Солина','Нелли','Игоревна','246','solina@module.ru','Сектор П-133','Старший научный сотрудник',446),(2,'Левин','Олег','Анатольевич','218','olev@module.ru','Сектор Р-114','Руководитель группы',320),(3,'Бочкарев','Дмитрий','Александрович','246','d.bochkarev@module.ru','Сектор П-133','Старший инженер-программист',446),(4,'Телешов','Александр','Вячеславович','321','a.teleshov@module.ru','Сектор П-133','Инженер-программист',359);
/*!40000 ALTER TABLE `TabUsers` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-10-23 14:48:51
