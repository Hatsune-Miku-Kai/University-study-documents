-- MySQL dump 10.13  Distrib 8.0.29, for Win64 (x86_64)
--
-- Host: localhost    Database: thmonitoring
-- ------------------------------------------------------
-- Server version	8.0.29

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
-- Table structure for table `threcords`
--

DROP TABLE IF EXISTS `threcords`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `threcords` (
  `recordid` int NOT NULL AUTO_INCREMENT,
  `temperature` float DEFAULT NULL,
  `humidity` int DEFAULT NULL,
  `recordtime` datetime DEFAULT NULL,
  PRIMARY KEY (`recordid`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `threcords`
--

LOCK TABLES `threcords` WRITE;
/*!40000 ALTER TABLE `threcords` DISABLE KEYS */;
INSERT INTO `threcords` VALUES (1,10.2,56,'2022-06-05 12:36:25'),(2,10.2,56,'2022-06-05 12:36:30'),(3,10.2,56,'2022-06-05 12:36:31'),(4,10.2,56,'2022-06-05 12:36:32'),(5,10.2,56,'2022-06-05 12:36:33'),(6,10.2,56,'2022-06-05 12:36:34'),(7,10.2,56,'2022-06-05 12:36:35'),(8,10.2,56,'2022-06-05 12:36:36'),(9,10.2,56,'2022-06-05 12:36:37'),(10,10.2,56,'2022-06-05 12:36:38'),(11,10.2,56,'2022-06-05 12:36:39'),(12,10.2,56,'2022-06-05 12:36:40'),(13,10.1,56,'2022-06-05 12:36:41'),(14,10.1,56,'2022-06-05 12:36:42'),(15,10.1,54,'2022-06-05 12:36:43'),(16,10.1,54,'2022-06-05 12:36:44'),(17,10.1,54,'2022-06-05 12:36:45'),(18,10.1,54,'2022-06-05 12:36:46'),(19,10.1,54,'2022-06-05 12:36:47'),(20,10.1,54,'2022-06-05 12:36:48'),(21,10.6,54,'2022-06-05 12:36:49'),(22,10.6,54,'2022-06-05 12:36:50'),(23,10.6,53,'2022-06-05 12:36:51'),(24,10.6,53,'2022-06-05 12:36:52'),(25,10.6,53,'2022-06-05 12:36:53'),(26,10.6,53,'2022-06-05 12:36:54'),(27,10.6,53,'2022-06-05 12:36:55'),(28,10.6,53,'2022-06-05 12:36:56'),(29,10.6,53,'2022-06-05 12:36:57'),(30,10.6,53,'2022-06-05 12:36:59'),(31,10.6,53,'2022-06-05 12:37:00'),(32,10.6,53,'2022-06-05 12:37:01'),(33,10.6,53,'2022-06-05 12:37:02'),(34,25.1,60,'2022-06-06 06:33:12');
/*!40000 ALTER TABLE `threcords` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `account` varchar(20) NOT NULL,
  `password` varchar(45) DEFAULT NULL,
  `name` varchar(10) DEFAULT NULL,
  `sex` varchar(2) DEFAULT NULL,
  `phone` varchar(15) DEFAULT NULL,
  `email` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES ('admin','123456','李四','男','135678234**','zhang**@126.com');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-06-06 11:13:28
