-- MySQL dump 10.13  Distrib 8.0.34, for Win64 (x86_64)
--
-- Host: localhost    Database: jwxt
-- ------------------------------------------------------
-- Server version	8.0.34

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
-- Table structure for table `c`
--

DROP TABLE IF EXISTS `c`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `c` (
  `cno` varchar(45) COLLATE utf8mb3_bin NOT NULL,
  `cn` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `ct` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  PRIMARY KEY (`cno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `c`
--

LOCK TABLES `c` WRITE;
/*!40000 ALTER TABLE `c` DISABLE KEYS */;
INSERT INTO `c` VALUES ('c1','数据库','32'),('c2','高等数学','64'),('c3','操作系统','48'),('c36','程序设计','48'),('c4','数字通信','48'),('c5','信息系统','48');
/*!40000 ALTER TABLE `c` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `s`
--

DROP TABLE IF EXISTS `s`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `s` (
  `sno` varchar(45) COLLATE utf8mb3_bin NOT NULL,
  `password` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `sn` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `sex` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `age` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `dept` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  PRIMARY KEY (`sno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `s`
--

LOCK TABLES `s` WRITE;
/*!40000 ALTER TABLE `s` DISABLE KEYS */;
INSERT INTO `s` VALUES ('S6','123456','刘明远','男','19','自动化'),('s1','123456','赵国庆','男','20','机电'),('s2','123456','张三','男','20','机电'),('s3','123456','王平','女','18','信科'),('s4','123456','张勇','男','19','信科'),('s5','123456','黎明','女','18','自动化');
/*!40000 ALTER TABLE `s` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sc`
--

DROP TABLE IF EXISTS `sc`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `sc` (
  `sno` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `cno` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `score` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sc`
--

LOCK TABLES `sc` WRITE;
/*!40000 ALTER TABLE `sc` DISABLE KEYS */;
INSERT INTO `sc` VALUES ('s1','c1','84'),('s1','c2','84'),('s2','c1','93'),('s2','c2','84'),('s2','c3','84'),('s3','c2','83'),('s3','c3','93'),('s3','c7','0'),('s4','c1','60'),('s4','c2','0'),('s4','c3','58'),('s4','c4','87'),('s4','c5','75'),('s4','c6','92'),('s4','c7','93');
/*!40000 ALTER TABLE `sc` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t`
--

DROP TABLE IF EXISTS `t`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `t` (
  `tno` varchar(45) COLLATE utf8mb3_bin NOT NULL,
  `password` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `tn` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `sex` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `age` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `prof` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `sal` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `comm` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `dept` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  PRIMARY KEY (`tno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t`
--

LOCK TABLES `t` WRITE;
/*!40000 ALTER TABLE `t` DISABLE KEYS */;
INSERT INTO `t` VALUES ('t1','123456','李力','男','47','教授','1500','3000','信科'),('t2','123456','王平','女','28','讲师','800','1200','信科'),('t3','123456','刘伟','男','30','讲师','900','1200','自动化'),('t4','123456','张雪','女','51','教授','1600','3000','自动化'),('t5','123456','张兰','女','39','副教授','1300','2000','机电');
/*!40000 ALTER TABLE `t` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tc`
--

DROP TABLE IF EXISTS `tc`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tc` (
  `tno` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL,
  `cno` varchar(45) COLLATE utf8mb3_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tc`
--

LOCK TABLES `tc` WRITE;
/*!40000 ALTER TABLE `tc` DISABLE KEYS */;
INSERT INTO `tc` VALUES ('t1','c1'),('t1','c4'),('t2','c5'),('t3','c1'),('t3','c5'),('t4','c2'),('t4','c3'),('t5','c5'),('t5','c7');
/*!40000 ALTER TABLE `tc` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-11-05 21:48:56
