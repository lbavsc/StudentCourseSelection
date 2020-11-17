# 学生选课管理系统（C语言）

Linux应用编程复习周小项目，分为学生信息管理模块和课程信息管理模块


## 内容列表
- [目录结构](#目录结构)
- [环境](#环境)
- [使用](#使用)
- [模块功能](#模块功能)


### 目录结构

```
.
├── build
├── course
│   ├── course.c
│   ├── course.h
│   └── makefile
├── include
│   ├── course_pub.h
│   ├── log_pub.h
│   ├── menu_pub.h
│   ├── sql_pub.h
│   └── student_pub.h
├── log
│   ├── log_analysis.sh
│   ├── log.c
│   ├── log.log
│   └── makefile
├── main.c
├── makefile
├── menu
│   ├── makefile
│   ├── menu.c
│   └── run.sh
├── myenv.sh
├── release
└── student
    ├── makefile
    ├── student.c
    └── student.h

```

### 环境
```
操作系统：manjaro 或其他 Linux 发行版

数据库：mysql / mariadb

```
### 使用
```
$ git clone https://github.com/lbavsc/StudentCourseSelection.git
```

连接数据库，创建一个名为“elective-course_system”的数据库（数据库相关配置存放在 ```/include/sql_pub.h``` ），将sql文件导入

修改```myenv.sh```里```ROOT```的地址为当前目录地址

```
$ source myenv.sh
$ make clean
$ make all
$ ./main
```


### 模块功能
1. 学生信息管理模块
    
    1.1 添加学生
    
    1.2 删除学生

    1.3 按学号修改学生信息

    1.4 按姓名修改学生信息

    1.5 按学号查看学生信息

    1.6 按姓名查看学生信息

    1.7 查看所有学生信息

    学生信息主要包括：学号，姓名，学分，选课列表

2. 课程信息管理模块
    
    2.1 新增课程

    2.2 删除课程

    2.3 按课程号查看课程信息

    2.4 按课程名查看课程信息

    2.5 按课程号修改课程信息

    2.6 按课程名修改课程信息

    2.7 课程增添学生

    2.8 课程删除学生
    
    课程信息主要包括：课程编号，课程名称，课程性质，授课学时，学分，课程已选人数，课程人数上限

3. 菜单模块

    该模块主要负责菜单的显示样式

4. 日志模块

    日志主要存放操作记录信息，其中 ``` log_analysis.sh ``` 为日志分析脚本，可以统计修改学生信息和课程信息的次数，同时，给定学号（课程号）可以查找是否有该学号（课程）的修改记录


