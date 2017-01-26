#!/bin/bash


today=$(date +%Y-%m-%d_%H:%M:%S)
u='_'
n=`basename $1`
mkdir subm/u5780642/backups/$n$u$today
cp -r $1/. subm/u5780677/backups/$n$u$today
echo Backup $1 completed sucessfully.