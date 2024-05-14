#!/bin/bash
#STREAM
#DESCRIPTION:
#The STREAM benchmark is a simple synthetic benchmark program that measures sustainable memory bandwidth (in MB/s) and the corresponding computation rate for simple vector kernels.  
#DATE:2012/06/07

mkdir -p results

CMD=./stream
CMD1=./stream_O3
MUCMD=./stream_mu
MUCMD1=./stream_mu_O3
#unset OMP_NUM_THREADS
CPUNO=`cat /proc/cpuinfo|grep processor|wc -l`
times=`date +%H%M%S`

usage()
{
echo "usage: run   [-n #]
      "
}

while getopts "n:" arg
do
if ( [ $arg == n ] )
then
  if [ $OPTARG -eq 1 ]
  then
  	$CMD >./results/O2_$OPTARG-$times.result
  	$CMD1 >./results/O3_$OPTARG-$times.result
	continue
  else
  	export OMP_NUM_THREADS=$OPTARG
  	if [   -f $MUCMD ] 
  	then
 		 $MUCMD >./results/O2_$OPTARG-$times.result
 		 $MUCMD1 >./results/O3_$OPTARG-$times.result
  	fi
  fi
elif [ $arg==-h ]
then
    usage
else
    usage

fi
done 

if [ $# -lt 1 ]
then 
  if [  -f $CMD ]
  then
      $CMD >./results/O2_Single-$times.result
      $CMD1 >./results/O3_Single-$times.result
  fi
  if [  -f $MUCMD ]
  then
      $MUCMD >./results/O2_$CPUNO-$times.result
      $MUCMD1 >./results/O3_$CPUNO-$times.result
  fi
fi
