#!/bin/bash


# first run
$@ >stdout.txt

for (( i = 1; i < 100; i++ )); do
	$@ >stdout.txt.2
	if ! diff stdout.txt stdout.txt.2; then
		#statements
		echo "Fisierele difera"
		exit 1
	fi
done
echo "OK"
