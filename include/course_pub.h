/*************************************************************************
*File Name: course.h
*Author: lbavsc
*471242574@qq.com
*Created Time: 2020年11月12日 星期四 11时19分34秒
 ************************************************************************/
#pragma once

#define COURSE_ALL 0

#define COURSE_ID 1

#define COURSE_NAME 2

#define COURSE_PEOPLE_SELECTED 3

#define COURSE_ADD 6

#define COURSE_DELETE 7

void addCourse();

void deleteCourse();

void viewCourse(int type);

void modifyCourse(int type);

void studentCourse(int type);

