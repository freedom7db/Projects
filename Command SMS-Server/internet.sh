#!/bin/bash

ping -w 3 google.com | grep "transmitted" > /dev/nul

if [ $? = "0" ]: 
then
	echo "1" > .connection.txt
else
	echo "0" > .connection.txt
fi

