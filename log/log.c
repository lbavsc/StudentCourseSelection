/*************************************************************************
*File Name: log.c
*Author: lbavsc
*471242574@qq.com
*Created Time: 2020年11月16日 星期一 20时09分06秒
 ************************************************************************/
#include <stdio.h>
#include <time.h>
#include "log_pub.h"
char date[100];

void get_local_time() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(date, "%04d-%02d-%02d %02d:%02d:%02d",
            (timeinfo->tm_year + 1900), timeinfo->tm_mon, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

}

void addLog(char* log) {
    FILE *fp;
    get_local_time();
    fp = fopen("./log/log.log", "a");
    fprintf(fp, "[%s] %s\n",date, log);
    fclose(fp);
}

