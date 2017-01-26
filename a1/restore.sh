#/bin/bash

bdir="/subm/u57805642/backups/"
re="./recovered/"

if [ -d "$re$1" ]
	then
		rm -rf $re$1

cd subm/u5780642/backups

late= $(ls $bdir | grep $1 | sort | tail -n1)
cp -r subm/u5780642/backups/$late ./recovered/$1
echo "$1 has been restored to ./recovered/$1"