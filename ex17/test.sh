#!/bin/bash

set -e

make

static="ex17pre ex17 ex17e ex17e2 ex17e4 ex17b"

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

echo "====ex17e1===="
./ex17e1 test.db c 10 20
./ex17e1 test.db s 0 name email
./ex17e1 test.db s 1 one 1mail 
# testing for failure
if OUTPUT="$(./ex17e1 test.db s 101 toomuch mail)"; then
	echo "shouldn't work"
else
	echo failed properly: $OUTPUT
fi
# better way for testing for failure
# the || means OR first command then (if it fails) second command
OUTPUT=$(./ex17e1 test.db s 101 toomuch mail) || echo failed properly: $OUTPUT
./ex17e1 test.db g 1
./ex17e1 test.db l
./ex17e1 test.db d 1
OUTPUT=$(./ex17e1 test.db g 1) || echo failed properly: $OUTPUT
OUTPUT=$(./ex17e1 test.db s 0 name email) || echo failed properly: $OUTPUT
./ex17e1 test.db l
echo "-----------"

echo "====ex17e3===="
OUTPUT=$(./ex17e3 test.db) || echo failed properly $OUTPUT
OUTPUT=$(./ex17e3 test.db c) || echo failed properly: $OUTPUT
OUTPUT=$(./ex17e3 test.db c 2001 20) || echo failed properly: $OUTPUT
OUTPUT=$(./ex17e3 test.db c 20 1000001) || echo failed properly: $OUTPUT
./ex17e3 test.db c 10 20
./ex17e3 test.db s 0 name 1 email location 
./ex17e3 test.db s 1 one 11 1mail 1location
./ex17e3 test.db g 1
./ex17e3 test.db l
./ex17e3 test.db f name one
./ex17e3 test.db f age 11
./ex17e3 test.db f email 1mail
./ex17e3 test.db f location 1location
OUTPUT=$(./ex17e3 test.db f NAME one) || echo failed properly: $OUTPUT
OUTPUT=$(./ex17e3 test.db f name two)
echo failed properly: $OUTPUT
./ex17e3 test.db d 1
./ex17e3 test.db l
echo "-----------"


make clean

