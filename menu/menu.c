/*************************************************************************
*File Name: menu.c
*Author: lbavsc
*471242574@qq.com
*Created Time: 2020年11月12日 星期四 13时35分53秒
 ************************************************************************/
#include <stdio.h>
#include "menu_pub.h"

void showMainMenu() {
    printf("\n-------------------欢迎来到学生选课管理系统-------------------\n");
    printf("\n\t\t1. 课程信息管理\n");
    printf("\n\t\t2. 学生信息管理\n");
    printf("\n\t\t0. 退出系统\n");
    printf("\n请输入选择的菜单项：");
}

void showStudentMenu() {
    printf("\n\n\n\n-------------------学生信息管理-------------------\n");
    printf("\n\t\t1. 新增学生信息\n");
    printf("\n\t\t2. 删除学生信息\n");
    printf("\n\t\t3. 修改学生信息（按学号）\n");
    printf("\n\t\t4. 修改学生信息（按姓名）\n");
    printf("\n\t\t5. 查看学生信息（按学号）\n");
    printf("\n\t\t6. 查看学生信息（按姓名）\n");
    printf("\n\t\t7. 查看所有学生信息\n");
    printf("\n\t\t8. 返回上级\n");
    printf("\n\t\t0. 退出系统\n");
    printf("\n请输入选择的菜单项：");
}

void studentIdPrompt() {
    printf("\n\n请输入学号：");
}

void studentNamePrompt() {
    printf("\n\n请输入姓名");
}

void showCourseMenu() {
    printf("\n\n\n\n-------------------课程信息管理-------------------\n");
    printf("\n\t\t1. 新增课程\n");
    printf("\n\t\t2. 删除课程\n");
    printf("\n\t\t3. 查看课程（以课程号）\n");
    printf("\n\t\t4. 查看课程（以课程名）\n");
    printf("\n\t\t5. 修改课程（以课程号）\n");
    printf("\n\t\t6. 修改课程（以课程名）\n");
    printf("\n\t\t7. 课程增加学生\n");
    printf("\n\t\t8. 课程减少学生\n");
    printf("\n\t\t9. 查看所有课程\n");
    printf("\n\t\t10. 返回上级\n");
    printf("\n\t\t0. 退出系统\n");
    printf("\n请输入选择的菜单项：");
}

void courseManager() {
    printf("\n\t\t1. 给该课程添加学生\n");
    printf("\n\t\t2. 给该课程删除学生\n");
    printf("\n\t\t0. 不修改学生列表\n");
    printf("\n请输入选择的菜单项：");
}

void courseIdPrompt() {
    printf("\n\n请输入学号：");
}

void courseNamePrompt() {
    printf("\n\n请输入姓名：");
}


