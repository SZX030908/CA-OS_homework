#!/bin/sh

[ -d lmbench-3.0-a9 ] || tar xf lmbench-3.0-a9.tgz

[ -d results ] || mkdir results

cp config.guess lmbench-3.0-a9/scripts/gnu-os

cd lmbench-3.0-a9
for i in `seq 1 3`
do
(echo "1"
sleep 1
echo "1"
sleep 1
echo "16384"
sleep 1
echo "\n"
sleep 1
echo "\n"
sleep 1
echo "\n"
sleep 1
echo "\n"
sleep 1
echo "\n"
sleep 1
echo "\n"
sleep 1
echo "\n"
sleep 1
echo "\n"
sleep 1
echo "no"
sleep 1
)|make results
make see
done
