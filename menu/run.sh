##########################################################################
# File Name: run.sh
# Author: lbavsc
# mail: 471242574@qq.com
# Created Time: 2020年11月12日 星期四 19时31分55秒
#########################################################################
#!/bin/bash
gcc -c menu.c
ar crv libmenu.a  menu.o
cp ./libmenu.a ../
rm -rf menu.o libmenu.a