/*************************************************************************
*File Name: course.h
*Author: lbavsc
*471242574@qq.com
*Created Time: 2020年11月13日 星期五 14时19分43秒
 ************************************************************************/
#pragma once
#include "../include/sql_pub.h"

#define COURSE_ID_MIN 1000
#define COURSE_ID_MAX 9999
#define COURSE_HOURS_MIN 10
#define COURSE_HOURS_MAX 120
#define COURSE_PEOPLE_MIN 1
#define COURSE_PEOPLE_MAX 300
#define RESULT_NULL "0"
#define STUDENT_ID 4
#define COURSE_NUMBER 5

//sql语句
#define QUERY_STUDENT_TYPE_ID "select count(*) from student_information where student_id = %d "
#define QUERY_COURSE_NUMBER "select course_number from course_information where course_name = '%s'"
#define QUERY_COURSE_TYPE_ID "select count(*) from course_information where course_number = %d "
#define QUERY_PEOPLE_SELECTED "select count(*) from selected_course_student where course_id = %s"
#define QUERY_COURSE_TYPE_NAME "select count(*) from course_information where course_name = '%s'"
#define COURSE_ADD_SELECTED "insert ignore into selected_course_student(student_id, course_id) values (%d, %d)"
#define COURSE_DETELETE_SELECTED "delete from selected_course_student where student_id = %d and course_id = %d"
#define INSERT_COURSE "insert into course_information(course_name, course_nature, course_hours, course_credit, course_max_people) values ('%s', '%s', %d, %lf, %d)"
#define DELETE_COURSE "delete from course_information where course_number = %d"
#define DELETE_COURSE_SELECTED "delete from selected_course_student where course_id = %d"
#define UPDATE_COURSE_TYPE_ID "update course_information set course_name = '%s', course_nature = '%s', course_hours = %d, course_credit = %lf, course_max_people = %d where course_number = %d"
#define UPDATE_COURSE_TYPE_NAME "update course_information set course_name = '%s', course_nature = '%s', course_hours = %d, course_credit = %lf, course_max_people = %d where course_name = '%s'"
#define SELECT_COURSE_TYPE_ID "select * from course_information where course_number = %d"
#define SELECT_COURSE_TYPE_NAME "select * from course_information where course_name = '%s'"
#define SELECT_COURSE_TYPE_ALL "select * from course_information"
#define REFRESH_COURSE_SELECTED "update course_information set course_selected = %d where course_number = %d"

//数据库返回错误
#define ERROR_PRIMARY_KEY_ONLY "for key 'PRIMARY'"
#define ERROR_OUT_OF_BOUNDS "for key 'PRIMARY'"
#define ERROR_UPDATA_STUDENT "update data error:%d from %s\n"