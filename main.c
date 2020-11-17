/*************************************************************************
*File Name: main.c
*Author: lbavsc
*471242574@qq.com
*Created Time: 2020年11月12日 星期四 13时44分30秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "menu_pub.h"
#include "student_pub.h"
#include "course_pub.h"

void openMainMenu();

void openStudentMenu();

void openCourseMenu();


int main() {
    openMainMenu();
    return 0;
}

void openMainMenu() {

    showMainMenu();
    int temp;
    scanf("%d", &temp);
    switch (temp) {
        case 1 :
            openCourseMenu();
            break;
        case 2 :
            openStudentMenu();
            break;
        case 0 :
            exit(0);
            break;
        default:
            printf("\n输入错误，请重新输入\n\n");
            openMainMenu();
            break;
    }

}

void openStudentMenu() {

    showStudentMenu();
    int temp;
    scanf("%d", &temp);
    switch (temp) {
        case 1 :
            addStudent();
            openStudentMenu();
            break;
        case 2 :
            deleteStudent();
            openStudentMenu();
            break;
        case 3 :
            modifyStudent(STUDENT_ID);
            openStudentMenu();
            break;
        case 4 :
            modifyStudent(STUDENT_NAME);
            openStudentMenu();
            break;
        case 5 :
            viewStudent(STUDENT_ID);
            openStudentMenu();
            break;
        case 6 :
            viewStudent(STUDENT_NAME);
            openStudentMenu();
            break;
        case 7 :
            viewStudent(STUDENT_ALL);
            openStudentMenu();
            break;
        case 8 :
            openMainMenu();
            break;
        case 0 :
            exit(0);
            break;
        default:
            printf("\n输入错误，请重新输入\n\n");
            openStudentMenu();
            break;

    }

}

void openCourseMenu() {

    showCourseMenu();
    int temp;
    scanf("%d", &temp);

    switch (temp) {
        case 1 :
            addCourse();
            openCourseMenu();
            break;
        case 2 :
            deleteCourse();
            openCourseMenu();
            break;
        case 3 :
            viewCourse(COURSE_ID);
            openCourseMenu();
            break;
        case 4 :
            viewCourse(COURSE_NAME);
            openCourseMenu();
            break;
        case 5 :
            modifyCourse(COURSE_ID);
            openCourseMenu();
            break;
        case 6 :
            modifyCourse(COURSE_NAME);
            openCourseMenu();
            break;
        case 7 :
            studentCourse(COURSE_ADD);
            openCourseMenu();
            break;
        case 8:
            studentCourse(COURSE_DELETE);
            openCourseMenu();
            break;
        case 9 :
            viewCourse(COURSE_ALL);
            openCourseMenu();
            break;
        case 10 :
            openMainMenu();
            break;
        case 0 :
            exit(0);
        default:
            printf("\n输入错误，请重新输入\n\n");
            openCourseMenu();
            break;
    }

}
