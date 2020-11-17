/*************************************************************************
*File Name: student.h
*Author: lbavsc
*471242574@qq.com
*Created Time: 2020年11月12日 星期四 18时27分25秒
 ************************************************************************/
#pragma once
#include "../include/sql_pub.h"

#define STUDENT_ID_MIN 1000000000
#define STUDENT_ID_MAX 9999999999
#define COURSE_NAME 0
#define COURSE_CREDIT 1
#define RESULT_NULL "0"

//sql语句
#define QUERY_STUDENT_TYPE_ID "select count(*) from student_information where student_id = %d "
#define QUERY_STUDENT_TYPE_NAME "select count(*) from student_information where student_name = '%s'"
#define INSERT_STUDENT "insert into student_information(student_id, student_name) values (%d, '%s')"
#define DELETE_STUDENT "delete from student_information where student_id = %d"
#define DELETE_STUDENT_SELECTED "delete from selected_course_student where student_id = %d"
#define UPDATE_STUDENT_TYPE_ID "update student_information set student_id = %d, student_name = '%s'  where student_id = %d"
#define UPDATE_STUDENT_TYPE_NAME "update student_information set student_id = %d, student_name = '%s'  where student_name = '%s'"
#define SELECT_STUDENT_TYPE_ID "select * from student_information where student_id = %d"
#define SELECT_STUDENT_TYPE_NAME "select * from student_information where student_name = '%s'"
#define SELECT_STUDENT_TYPE_ALL "select * from student_information"
#define SELECT_COURSR_NAME "select course_name, course_credit from course_information where course_number = %s"
#define SELECT_COURSR_LIST "select course_id from selected_course_student where student_id = %s"
#define UPDATE_COURSR_CREDIT "update student_information set student_course = %lf where student_id = %s"

//数据库返回错误
#define ERROR_PRIMARY_KEY_ONLY "for key 'PRIMARY'"
#define ERROR_OUT_OF_BOUNDS "for key 'PRIMARY'"
#define ERROR_UPDATA_STUDENT "update data error:%d from %s\n"