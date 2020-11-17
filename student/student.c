/*************************************************************************
*File Name: student.c
*Author: lbavsc
*471242574@qq.com
*Created Time: 2020年11月12日 星期四 12时35分12秒
 ************************************************************************/
#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>
#include "student_pub.h"
#include "menu_pub.h"
#include "student.h"
#include "log_pub.h"

MYSQL *studentConn;
int studentId;
char studentName[20];
char studentTempStr[80];


void initStudentDB() {

    studentConn = mysql_init(NULL);

    if (studentConn == NULL) {
        printf("mysql_init failed\n");
        exit(0);
    }

    studentConn = mysql_real_connect(studentConn, HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0);

    if (!studentConn) {
        printf("数据库连接成功\n");
    }

}

char *studentQuery(char *recordName, int recordType) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    const char *sql = NULL;
    int flag = -1;

    if (recordType == STUDENT_ID) {
        sprintf(studentTempStr, QUERY_STUDENT_TYPE_ID, studentId);
    } else if (recordType == STUDENT_NAME) {
        sprintf(studentTempStr, QUERY_STUDENT_TYPE_NAME, studentName);
    }
    sql = studentTempStr;

    mysql_real_query(studentConn, sql, strlen(sql));
    res = mysql_store_result(studentConn);
    row = mysql_fetch_row(res);

    return row[0];
}

char *courseNameSelection(char *courseId, int type) {
    initStudentDB();
    int flag;
    const char *sql = NULL;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL_FIELD *fields = NULL;

    sprintf(studentTempStr, SELECT_COURSR_NAME,
            courseId);
    sql = studentTempStr;
    flag = mysql_real_query(studentConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(studentConn));
        return NULL;
    }

    res = mysql_store_result(studentConn);
    row = mysql_fetch_row(res);

    if (type == COURSE_NAME) {
        return row[0];
    } else if (type == COURSE_CREDIT) {
        return row[1];
    }

}

void courseSelectionList(char *studentId) {
    int flag, i;
    const char *sql = NULL;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL_FIELD *fields = NULL;

    sprintf(studentTempStr, SELECT_COURSR_LIST, studentId);

    sql = studentTempStr;
    flag = mysql_real_query(studentConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(studentConn));
        return;
    }

    res = mysql_store_result(studentConn);

    // 遍历结果集
    while ((row = mysql_fetch_row(res))) {
        printf("%s", courseNameSelection(row[0], COURSE_NAME));
        //printf("%s",row[0]);
        printf("\n\t\t\t\t");
    }

    // 释放结果集
    mysql_free_result(res);
}

void courseCreditSelection(char *studentId) {

    int flag, i;
    const char *sql = NULL;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL_FIELD *fields = NULL;
    double courseCredit = 0;

    sprintf(studentTempStr, SELECT_COURSR_LIST, studentId);

    sql = studentTempStr;
    flag = mysql_real_query(studentConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(studentConn));
        return;
    }

    res = mysql_store_result(studentConn);

    // 遍历结果集
    while ((row = mysql_fetch_row(res))) {
        courseCredit += atof(courseNameSelection(row[0], COURSE_CREDIT));
    }
    sprintf(studentTempStr, UPDATE_COURSR_CREDIT, courseCredit,
            studentId);

    sql = studentTempStr;
    flag = mysql_real_query(studentConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(studentConn));
        return;
    }

    // 释放结果集
    mysql_free_result(res);
}

void updateCredit() {
    int flag;
    const char *sql = NULL;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL_FIELD *fields = NULL;

    sprintf(studentTempStr, SELECT_STUDENT_TYPE_ALL);

    sql = studentTempStr;
    flag = mysql_real_query(studentConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(studentConn));
        return;
    }

    // 将查询结果读取到内存当中，如果数据很多的情况会比较耗内存
    res = mysql_store_result(studentConn);
    // 遍历结果集
    while ((row = mysql_fetch_row(res))) {
        courseCreditSelection(row[0]);
    }

    // 释放结果集
    mysql_free_result(res);
}

void addStudent() {

    initStudentDB();
    const char *sql = NULL;
    int flag = -1;
    char logInfoStudent[1024];

    printf("学号：");
    scanf("%d", &studentId);
    printf("姓名：");
    scanf("%s", &studentName);


    if (studentId < STUDENT_ID_MIN || studentId > STUDENT_ID_MAX) {
        printf("\n\n学号长度不在范围内，添加失败\n");
        return;
    }

    sprintf(studentTempStr, INSERT_STUDENT, studentId, studentName);
    sql = studentTempStr;

    flag = mysql_real_query(studentConn, sql, strlen(sql));

    if (flag) {
        if (strstr(mysql_error(studentConn), ERROR_PRIMARY_KEY_ONLY)) {
            printf("\n\n数据库存在相同学号的学生，添加失败\n");
        } else if (strstr(mysql_error(studentConn), ERROR_OUT_OF_BOUNDS)) {
            printf("\n\n姓名长度超出范围，添加失败\n");
        }
        printf("\n\n%s\n", mysql_error(studentConn));

    } else {
        printf("\n\n学号为：%d，姓名为：%s，添加成功\n", studentId, studentName);
    }

    sprintf(logInfoStudent, "添加了学号为 %d 的学生信息: %s ", studentId, sql);
    addLog(logInfoStudent);

    mysql_close(studentConn);

}

void deleteStudent() {

    initStudentDB();
    const char *sql = NULL;
    int flag = -1;
    char logInfoStudent[1024];

    printf("请输入需要删除学生的学号：");
    scanf("%d", &studentId);

    sprintf(studentTempStr, "%d", studentId);

    if (!strcmp(studentQuery(studentTempStr, STUDENT_ID), RESULT_NULL)) {
        printf("数据库无此学生信息");
        return;
    }

    sprintf(studentTempStr, DELETE_STUDENT, studentId);
    sql = studentTempStr;
    flag = mysql_real_query(studentConn, sql, strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(studentConn));
    } else {
        printf("删除成功");
    }

    sprintf(studentTempStr, DELETE_STUDENT_SELECTED, studentId);
    sql = studentTempStr;
    flag = mysql_real_query(studentConn, sql, strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(studentConn));
    }
    sprintf(logInfoStudent, "删除了学号为 %d 的学生信息: %s ", studentId, sql);
    addLog(logInfoStudent);

    mysql_close(studentConn);
}

void modifyStudent(int type) {

    initStudentDB();
    const char *sql = NULL;
    int flag = -1;
    char logInfoStudent[1024];

    if (type == STUDENT_ID) {

        printf("请输入需要修改信息学生的学号：");
        scanf("%d", &studentId);

        sprintf(studentTempStr, "%d", studentId);
        if (!strcmp(studentQuery(studentTempStr, STUDENT_ID), RESULT_NULL)) {
            printf("数据库无此学生信息");
            return;
        }

        int newStudentId;
        printf("请输入修改后学生的学号：");
        scanf("%d", &newStudentId);
        printf("请输入修改后学生的姓名：");
        scanf("%s", &studentName);

        sprintf(studentTempStr, UPDATE_STUDENT_TYPE_ID, newStudentId, studentName, studentId);

    } else if (type == STUDENT_NAME) {

        printf("请输入需要修改信息学生的姓名：");
        scanf("%s", &studentName);

        if (!strcmp(studentQuery(studentName, STUDENT_NAME), RESULT_NULL)) {
            printf("数据库无此学生信息");
            return;
        }

        char newStudentName[20];
        printf("请输入修改后学生的学号：");
        scanf("%d", &studentId);
        printf("请输入修改后学生的姓名：");
        scanf("%s", &newStudentName);

        sprintf(studentTempStr, UPDATE_STUDENT_TYPE_NAME, studentId, newStudentName, studentName);


    }
    sql = studentTempStr;

    flag = mysql_real_query(studentConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf(ERROR_UPDATA_STUDENT, mysql_errno(studentConn), mysql_error(studentConn));
        return;
    }

    sprintf(logInfoStudent, "修改了学号为 %d 的学生信息: %s ", studentId, sql);
    addLog(logInfoStudent);
    printf("修改成功\n");
    mysql_close(studentConn);

}

void viewStudent(int type) {

    initStudentDB();
    int flag, i;
    const char *sql = NULL;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL_FIELD *fields = NULL;
    updateCredit();
    if (type == STUDENT_ID) {

        printf("请输入学生的学号：");
        scanf("%d", &studentId);
        sprintf(studentTempStr, "%d", studentId);

        if (!strcmp(studentQuery(studentTempStr, STUDENT_ID), RESULT_NULL)) {
            printf("\n\n数据库无此学生信息");
            return;
        }
        sprintf(studentTempStr, SELECT_STUDENT_TYPE_ID, studentId);

    } else if (type == STUDENT_NAME) {

        printf("请输入学生的姓名：");
        scanf("%s", &studentName);

        if (!strcmp(studentQuery(studentName, STUDENT_NAME), RESULT_NULL)) {
            printf("\n\n数据库无此学生信息");
            return;
        }
        sprintf(studentTempStr, SELECT_STUDENT_TYPE_NAME, studentName);

    } else if (type == STUDENT_ALL) {
        sprintf(studentTempStr, SELECT_STUDENT_TYPE_ALL);
    }


    sql = studentTempStr;
    flag = mysql_real_query(studentConn, sql, (unsigned int) strlen(sql));

    if (flag) {
        printf("发生错误： %s\n", mysql_error(studentConn));
        return;
    }

    // 将查询结果读取到内存当中，如果数据很多的情况会比较耗内存
    res = mysql_store_result(studentConn);

    printf("\n\n\n学号\t\t姓名\t学分\t选课列表\n");

    // 遍历结果集
    while ((row = mysql_fetch_row(res))) {
        //刷新学分，因为查询结果已经写入内存中了，所以选取课程改变后需刷新一次才能显示出正确的学分
        //   courseCreditSelection(row[0]);
        //输出学生信息
        for (i = 0; i < mysql_num_fields(res); i++) {
            printf("%s\t", row[i]);
        }
        //输出选课列表
        courseSelectionList(row[0]);
        printf("\n");
    }

    // 释放结果集
    mysql_free_result(res);
    mysql_close(studentConn);
}
