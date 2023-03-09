#!/bin/bash

if [ $# -ne 2 ]
then
	echo "Usage: ./finder.sh <directory> <search string>"
	exit 1
elif [ ! -d $1 ]
then
	echo "$1 is not a valid directory"
	exit 1
fi

filesdir=$1
searchstr=$2

grep -r -c $searchstr $filesdir | awk -F":" '$2!=0 {numFiles++} {numLines=numLines+$2} END {print "The number of files are " numFiles " and the number of matching lines are " numLines}'

