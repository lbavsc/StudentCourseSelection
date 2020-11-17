-- MariaDB dump 10.17  Distrib 10.5.6-MariaDB, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: elective_course_system
-- ------------------------------------------------------
-- Server version	10.5.6-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `course_information`
--

DROP TABLE IF EXISTS `course_information`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `course_information` (
  `course_number` int(4) NOT NULL AUTO_INCREMENT,
  `course_name` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `course_nature` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `course_hours` int(3) NOT NULL,
  `course_credit` double NOT NULL DEFAULT 2,
  `course_selected` int(11) DEFAULT 0,
  `course_max_people` int(3) NOT NULL DEFAULT 0,
  PRIMARY KEY (`course_number`),
  UNIQUE KEY `course_information_course_number_uindex` (`course_number`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `course_information`
--

LOCK TABLES `course_information` WRITE;
/*!40000 ALTER TABLE `course_information` DISABLE KEYS */;
INSERT INTO `course_information` (`course_number`, `course_name`, `course_nature`, `course_hours`, `course_credit`, `course_selected`, `course_max_people`) VALUES (15,'JavaWeb  ','公选课',48,2.5,1,40),(16,'线性代数','必修课',100,5,1,100),(19,'UI设计  ','公选课',30,2,0,100),(21,'c语言编程','必修课',60,4.5,1,100),(22,'Java编程','必修课',84,4.5,1,100);
/*!40000 ALTER TABLE `course_information` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `selected_course_student`
--

DROP TABLE IF EXISTS `selected_course_student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `selected_course_student` (
  `student_id` int(10) NOT NULL,
  `course_id` int(4) NOT NULL,
  PRIMARY KEY (`student_id`,`course_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `selected_course_student`
--

LOCK TABLES `selected_course_student` WRITE;
/*!40000 ALTER TABLE `selected_course_student` DISABLE KEYS */;
INSERT INTO `selected_course_student` (`student_id`, `course_id`) VALUES (1000000001,15),(1000000001,16),(1000000001,21),(1812001029,22);
/*!40000 ALTER TABLE `selected_course_student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student_information`
--

DROP TABLE IF EXISTS `student_information`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `student_information` (
  `student_id` int(10) NOT NULL AUTO_INCREMENT,
  `student_name` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `student_course` double NOT NULL DEFAULT 0,
  PRIMARY KEY (`student_id`),
  UNIQUE KEY `student_information_student_id_uindex` (`student_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2000000003 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student_information`
--

LOCK TABLES `student_information` WRITE;
/*!40000 ALTER TABLE `student_information` DISABLE KEYS */;
INSERT INTO `student_information` (`student_id`, `student_name`, `student_course`) VALUES (1000000000,'dir',0),(1000000001,'lip',12),(1000000003,'spq',0),(1812001029,'罗兴旭',4.5);
/*!40000 ALTER TABLE `student_information` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-11-17 14:55:36
