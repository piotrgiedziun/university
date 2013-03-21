#!/bin/bash

find . -type f -perm +111 -path "./lab*" -print | while read file; do
	rm $file
	echo $file removed
done
