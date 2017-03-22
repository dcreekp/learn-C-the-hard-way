#!/bin/bash

set -e

make

static="ex17pre ex17 ex17e ex17e1 ex17e2 ex17e4 ex17b"

for i in $static; do
	echo "====$i===="
	if [ $i == "ex17e1" ]; then
		./$i test.db c 10 20
	else
		./$i test.db c
	fi
	./$i test.db s 0 name email
	./$i test.db s 1 one 1mail
	./$i test.db g 1
	./$i test.db l
	./$i test.db d 1
	./$i test.db l
	if [ $i == "ex17e2" ]; then
		./$i test.db f name
	fi
	echo "-----------"
done

more="ex17e3"
for i in $more ; do
	echo "====$i===="
	./$i test.db c 10 20
	./$i test.db s 0 name 1 email location 
	./$i test.db s 1 one 11 1mail 1location
	./$i test.db g 1
	./$i test.db l
	./$i test.db f name one
	./$i test.db f age 11
	./$i test.db f email 1mail
	./$i test.db f location 1location
	./$i test.db d 1
	./$i test.db l
	echo "-----------"
done

make clean

