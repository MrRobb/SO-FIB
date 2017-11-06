#!/bin/bash

i=0
while [ $i -lt $1 ]
do
	/usr/bin/time nice ./fib 45&
	i=`expr $i + 1` #incrementa en 1 la variable i
done
