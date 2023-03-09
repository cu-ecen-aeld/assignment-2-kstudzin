#!/bin/bash

if [ $# -ne 2 ]
then
	echo "Usage: ./writer.sh <write file> <write string>"
	exit 1
fi

writefile=$1
writestr=$2

mkdir -p `dirname $writefile`
echo $writestr > $writefile
