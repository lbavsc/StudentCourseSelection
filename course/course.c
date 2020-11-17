/*************************************************************************
*File Name: course.c
*Author: lbavsc
*471242574@qq.com
*Created Time: 2020年11月12日 星期四 17时32分17秒
 ************************************************************************/
#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>
#include "menu_pub.h"
#include "course_pub.h"
#include "course.h"
#include "log_pub.h"

MYSQL *courseConn;
int courseNumber;
char courseName[20];
char courseNature[20];
int courseHours;
int coursePeople;
char courseTempStr[80];


/**
 * 数据库初始化及连接函数
 */
void initCourse() {

    courseConn = mysql_init(NULL);

    if (courseConn == NULL) {
        printf("mysql_init failed\n");
        exit(0);
    }


    if (courseConn == NULL) {
        printf("mysql_init failed\n");
        exit(0);
    }

    courseConn = mysql_real_connect(courseConn, HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0);

    if (!courseConn) {
        printf("数据库连接失败\n");
    }
}

/**
 * 查询函数
 * @param recordName
 * @param recordType
 * @return
 */
char *courseQuery(char *recordName, int recordType) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    const char *sql = NULL;
    int flag = -1;

    if (recordType == COURSE_ID) {  //查询是否存在课程ID
        sprintf(courseTempStr, QUERY_COURSE_TYPE_ID, atoi(recordName));
    } else if (recordType == COURSE_NAME) { //查询是否存在课程名
        sprintf(courseTempStr, QUERY_COURSE_TYPE_NAME, recordName);
    } else if (recordType == COURSE_PEOPLE_SELECTED) {  //查询课程有多少人选取
        sprintf(courseTempStr, QUERY_PEOPLE_SELECTED, recordName);
    } else if (recordType == STUDENT_ID) {  //查询是否存在学号
        sprintf(courseTempStr, QUERY_STUDENT_TYPE_ID, atoi(recordName));
    } else if (recordType == COURSE_NUMBER) {   //查询课程号
        sprintf(courseTempStr, QUERY_COURSE_NUMBER, recordName);
    }

    sql = courseTempStr;
    mysql_real_query(courseConn, sql, strlen(sql));
    res = mysql_store_result(courseConn);
    row = mysql_fetch_row(res);

    return row[0];
}

/**
 * 课程性质定义函数
 * @param courseNatureNumber
 * @return
 */
char *getCourseNature(int courseNatureNumber) {
    if (courseNatureNumber == 1) {
        return "必修课";
    } else if (courseNatureNumber == 2) {
        return "选修课";
    } else if (courseNatureNumber == 3) {
        return "公选课";
    } else {
        return "输入错误";
    }
}


/**
 * 刷新课程选取人数函数
 * @param courseNumber
 */
void courseSelected(char *courseNumber) {
    const char *sql = NULL;
    int flag = -1;
    int coursePeople = 0;
    coursePeople = atoi(courseQuery(courseNumber, COURSE_PEOPLE_SELECTED));
    sprintf(courseTempStr, REFRESH_COURSE_SELECTED, coursePeople,
            atoi(courseNumber));
    sql = courseTempStr;

    flag = mysql_real_query(courseConn, sql, strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(courseConn));
    }
}

/**
 * 遍历并刷新数据库中每门课的学分
 */
void updateCourseSelected() {
    initCourse();
    int flag, i;
    const char *sql = NULL;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL_FIELD *fields = NULL;

    sprintf(courseTempStr, SELECT_COURSE_TYPE_ALL);

    sql = courseTempStr;
    flag = mysql_real_query(courseConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(courseConn));
        return;
    }

    // 将查询结果读取到内存当中，如果数据很多的情况会比较耗内存
    res = mysql_store_result(courseConn);


    // 遍历结果集
    while ((row = mysql_fetch_row(res))) {
        courseSelected(row[0]);
    }

    // 释放结果集
    mysql_free_result(res);

}

/**
 * 增加或减少课程选取学生
 * @param type
 */
void studentCourse(int type) {
    initCourse();
    const char *sql = NULL;
    int flag = -1;
    char logInfoCourse[1024];

    int studentId;
    printf("请输入课程号：");
    scanf("%d", &courseNumber);
    printf("请输入学生学号：");
    scanf("%d", &studentId);
    sprintf(courseTempStr, "%d", studentId);
    if (!strcmp(courseQuery(courseTempStr, STUDENT_ID), RESULT_NULL)) {
        printf("数据库无此学生信息");
        return;
    }
    sprintf(courseTempStr, "%d", courseNumber);
    if (!strcmp(courseQuery(courseTempStr, COURSE_ID), RESULT_NULL)) {
        printf("数据库无此课程信息");
        return;
    }


    if (type == COURSE_ADD) {
        sprintf(courseTempStr, COURSE_ADD_SELECTED,
                studentId, courseNumber);
        sprintf(logInfoCourse, "给 %d 增加了编号为 %d 课程: %s ",studentId, courseNumber, courseTempStr);
        addLog(logInfoCourse);
    } else if (type == COURSE_DELETE) {
        sprintf(courseTempStr, COURSE_DETELETE_SELECTED,
                studentId, courseNumber);
        sprintf(logInfoCourse, "给 %d 删除了编号为 %d 课程: %s ",studentId, courseNumber, courseTempStr);
        addLog(logInfoCourse);
    }
    sql = courseTempStr;
    flag = mysql_real_query(courseConn, sql, strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(courseConn));
        return;
    }

    printf("执行成功");
}

/**
 * 增加课程函数
 */
void addCourse() {
    initCourse();
    const char *sql = NULL;
    int flag = -1;
    int courseNatureNumber;
    double courseCredit;
    char logInfoCourse[1024];

    printf("课程名称：");
    scanf("%s", &courseName);
    printf("课程性质（1. 必修课/2. 选修课/3. 公选课，输入数字选择）：");
    scanf("%d", &courseNatureNumber);
    sprintf(courseNature, "%s", getCourseNature(courseNatureNumber));

    printf("学时（10-120 课时）：");
    scanf("%d", &courseHours);
    printf("课程人数上限（1-300）：");
    scanf("%d", &coursePeople);
    printf("学分：");
    scanf("%lf", &courseCredit);

    if (!strcmp(courseNature, "输入错误")) {
        printf("课程性质输入错误");
        return;
    }

    if (courseHours < COURSE_HOURS_MIN || courseHours > COURSE_HOURS_MAX) {
        printf("\n\n学时不符合规则（10-120），添加失败\n");
        return;
    }
    if (coursePeople < COURSE_PEOPLE_MIN || coursePeople > COURSE_PEOPLE_MAX) {
        printf("\n\n人数不符合规则（1-300），添加失败\n");
        return;
    }
    if (courseCredit < 0) {
        printf("\n\n学分不符合规则，添加失败\n");
        return;
    }


    sprintf(courseTempStr, INSERT_COURSE, courseName, courseNature, courseHours, courseCredit, coursePeople);
    //printf("%s", courseTempStr);
    sql = courseTempStr;

    flag = mysql_real_query(courseConn, sql, strlen(sql));

    if (flag) {
        if (strstr(mysql_error(courseConn), ERROR_PRIMARY_KEY_ONLY)) {
            printf("\n\n数据库存在相同编号的课程，添加失败\n");
        } else if (strstr(mysql_error(courseConn), ERROR_OUT_OF_BOUNDS)) {
            printf("\n\n课程名长度超出范围，添加失败\n");
        }
        printf("\n\n%s\n", mysql_error(courseConn));

    } else {
        printf("\n\n课程名：%s，添加成功\n", courseName);
    }
    sprintf(logInfoCourse, "增加了课程信息: %s ", courseTempStr);
    addLog(logInfoCourse);

    mysql_close(courseConn);
}

/**
 * 删除课程函数
 */
void deleteCourse() {
    initCourse();
    const char *sql = NULL;
    int flag = -1;
    char logInfoCourse[1024];

    printf("请输入需要删除课程的课程号：");
    scanf("%d", &courseNumber);

    sprintf(courseTempStr, "%d", courseNumber);

    if (!strcmp(courseQuery(courseTempStr, COURSE_ID), RESULT_NULL)) {
        printf("数据库无此课程信息");
        return;
    }

    sprintf(courseTempStr, DELETE_COURSE, courseNumber);
    sql = courseTempStr;

    flag = mysql_real_query(courseConn, sql, strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(courseConn));
    } else {
        printf("删除成功");
    }

    sprintf(courseTempStr, DELETE_COURSE_SELECTED, courseNumber);
    sql = courseTempStr;
    flag = mysql_real_query(courseConn, sql, strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(courseConn));
    }

    sprintf(logInfoCourse, "删除了编号为 %d 课程信息: %s ", courseNumber, courseTempStr);
    addLog(logInfoCourse);

    mysql_close(courseConn);
}

/**
 * 查看课程详情函数
 * @param type
 */
void viewCourse(int type) {
    initCourse();
    int flag, i;
    const char *sql = NULL;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL_FIELD *fields = NULL;
    updateCourseSelected();

    if (type == COURSE_ID) {

        printf("请输入课程编号：");
        scanf("%d", &courseNumber);
        sprintf(courseTempStr, "%d", courseNumber);
        if (!strcmp(courseQuery(courseTempStr, COURSE_ID), RESULT_NULL)) {
            printf("\n\n数据库无此课程信息");
            return;
        }

        sprintf(courseTempStr, SELECT_COURSE_TYPE_ID, courseNumber);

    } else if (type == COURSE_NAME) {

        printf("请输入课程名：");
        scanf("%s", &courseName);

        if (!strcmp(courseQuery(courseName, COURSE_NAME), RESULT_NULL)) {
            printf("\n\n数据库无此课程信息");
            return;
        }

        sprintf(courseTempStr, SELECT_COURSE_TYPE_NAME, courseName);

    } else if (type == COURSE_ALL) {
        sprintf(courseTempStr, SELECT_COURSE_TYPE_ALL);
    }


    sql = courseTempStr;
    flag = mysql_real_query(courseConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(courseConn));
        return;
    }

    // 将查询结果读取到内存当中，如果数据很多的情况会比较耗内存
    res = mysql_store_result(courseConn);

    printf("\n\n\n课程号\t\t课程名\t\t\t课程性质\t课程学时\t课时学分\t课程已选人数\t课程人数上限\n");

    // 遍历结果集
    while ((row = mysql_fetch_row(res))) {
        courseSelected(row[0]);
        for (i = 0; i < mysql_num_fields(res); i++) {
            printf("%-4s\t\t", row[i]);
        }

        printf("\n");
    }

    // 释放结果集
    mysql_free_result(res);
    mysql_close(courseConn);
}

/**
 * 修改课程信息函数
 * @param type
 */
void modifyCourse(int type) {

    initCourse();
    const char *sql = NULL;
    int flag = -1;


    char newCourseName[20];
    char newCourseNature[20];
    int newCourseHours;
    int newCoursPeople;
    double newCourseCredit;
    int courseNatureNumber;
    char logInfoCourse[1024];

    if (type == COURSE_ID) {

        printf("请输入需要修改课程的课程号：");
        scanf("%d", &courseNumber);

        sprintf(courseTempStr, "%d", courseNumber);
        if (!strcmp(courseQuery(courseTempStr, COURSE_ID), RESULT_NULL)) {
            printf("数据库无此课程信息");
            return;
        }


        printf("请输入修改后课程的名字：");
        scanf("%s", &newCourseName);
        printf("课程性质（1. 必修课/2. 选修课/3. 公选课，输入数字选择）：");
        scanf("%d", &courseNatureNumber);
        sprintf(newCourseNature, "%s", getCourseNature(courseNatureNumber));

        printf("学时（10-120 课时）：");
        scanf("%d", &newCourseHours);
        printf("课程人数上限（1-300）：");
        scanf("%d", &newCoursPeople);
        printf("学分：");
        scanf("%lf", &newCourseCredit);

        sprintf(courseTempStr, UPDATE_COURSE_TYPE_ID, newCourseName, newCourseNature, newCourseHours, newCourseCredit,
                newCoursPeople,
                courseNumber);
        sprintf(logInfoCourse, "修改了编号为 %d 课程信息: %s ", courseNumber, courseTempStr);
        addLog(logInfoCourse);

    } else if (type == COURSE_NAME) {

        printf("请输入需要修改的课程名字：");
        scanf("%s", &courseName);

        if (!strcmp(courseQuery(courseName, COURSE_NAME), RESULT_NULL)) {
            printf("数据库无此课程信息");
            return;
        }


        printf("请输入修改后课程的名字：");
        scanf("%s", &newCourseName);
        printf("课程性质（1. 必修课/2. 选修课/3. 公选课，输入数字选择）：");
        scanf("%d", &courseNatureNumber);
        sprintf(newCourseNature, "%s", getCourseNature(courseNatureNumber));

        printf("学时（10-120 课时）：");
        scanf("%d", &newCourseHours);
        printf("课程人数上限（1-300）：");
        scanf("%d", &newCoursPeople);
        printf("学分：");
        scanf("%lf", &newCourseCredit);

        int temp;
        temp = atoi(courseQuery(courseName, COURSE_NUMBER));

        sprintf(courseTempStr, UPDATE_COURSE_TYPE_NAME, newCourseName, newCourseNature, newCourseHours, newCourseCredit,
                newCoursPeople,
                courseName);

        sprintf(logInfoCourse, "修改了编号为 %d 课程信息: %s ", temp, courseTempStr);
        addLog(logInfoCourse);
    }
    sql = courseTempStr;

    flag = mysql_real_query(courseConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf(ERROR_UPDATA_STUDENT, mysql_errno(courseConn), mysql_error(courseConn));
        return;
    }



    printf("修改成功\n");
    mysql_close(courseConn);

}




