#!/bin/bash

ps -u`whoami` -o cmd,pcpu,time|head -n1
i=0
while [ $i -le 5 ]
do
	ps -u`whoami` -o cmd,pcpu,time |egrep "(^$1|^$2)"
	sleep 2
	i=`expr $i + 1`
done
