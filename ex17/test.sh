#!/bin/bash

set -e

make

static="ex17pre ex17 ex17e ex17e1 ex17e2 ex17b"

for i in $static; do
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
done

./ex17e3 test.db c 10 20
./ex17e3 test.db s 0 name 1 email location 
./ex17e3 test.db s 1 one 11 1mail 1location
./ex17e3 test.db g 1
./ex17e3 test.db l
./ex17e3 test.db f name one
./ex17e3 test.db f age 11
./ex17e3 test.db f email 1mail
./ex17e3 test.db f location 1location
./ex17e3 test.db d 1
./ex17e3 test.db l


make clean

