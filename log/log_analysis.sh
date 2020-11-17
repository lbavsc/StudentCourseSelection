##########################################################################
# File Name: log_analysis.sh
# Author: lbavsc
# mail: 471242574@qq.com
# Created Time: 2020年11月17日 星期二 09时14分18秒
#########################################################################
#!/bin/bash
course=0
student=0
while read line
do
    if [[ $line =~ "课程" ]]
    then
        ((course++))
    elif [[ $line =~ "学生信息" ]]
    then
        ((student++))
    fi
done < log.log
echo "修改了$course次课程信息" 
echo "修改了$student次学生信息"

function get_student(){
    student_temp=0
    read -p "请输入学号:" STU_NUM

    while read line
    do
        student_temp_str=$(echo $line | awk '{printf $4}')
        if [ "$student_temp_str" = $STU_NUM ]
        then
            ((student_temp++))
        fi
    done < log.log
    echo "$1被修改了$student_temp次"
}

function get_course(){
    course_temp=0
    read -p "请输入课程号:" COU_NUM
    
    while read line
    do
        course_temp_str=$(echo $line | awk '{printf $4}')
        if [ "$course_temp_str" = $COU_NUM ]
        then
            ((course_temp++))
        fi
    done < log.log
    echo "$1被修改了$course_temp次"
}

while :
do
    echo "1. 查询学生信息是否被修改"
    echo "2. 查询课程信息是否被修改"
    echo "0. 退出"
    read -p "请输入：" TEMP
    case $TEMP in 
        1)
            get_student
            ;;
        2)
            get_course
            ;;
        0)
            exit
            ;;
        *)
            echo "输入错误"
            ;;
    esac
done

