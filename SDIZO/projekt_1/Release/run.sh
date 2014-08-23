#!/bin/sh
# usage:
# ./run.sh [input file path] [storage_type] [algorithm]
#
# storage_type = matrix/list
# algorithm    = dijkstra/ford
#
# example:
# ./run.sh ../input/default.wiki.jjd matrix dijkstra

rm output.txt

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
do
./proj_struktury ../input/$i.jjd $1 $2 >> output.txt
done

cat output.txt
