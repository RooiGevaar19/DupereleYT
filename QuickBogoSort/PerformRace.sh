#!/bin/bash

i=$1

green='\e[1;32m'
red='\e[1;31m'
cyan='\e[1;36m'
yellow='\e[1;33m'
yellowb='\e[5;33m'
endColor='\e[0m'

echo -e "${cyan}`date +"%Y"` SORTING ALGORITHMS TOURNAMENT!${endColor}"
echo "Powered by `whoami`"
echo -e "${green}Round 1${endColor}: ${i} Numbers of `hostname`"
echo
sleep 1

echo -e "${yellow}Starting grid${endColor}:"
echo -e "\tQuickSort"
echo -e "\tBubbleSort"
echo -e "\tQuick BogoSort"
echo
sleep 1

echo -ne "${yellowb}Players are preparing their machines for the race...${endColor}"
g++ racers/BubbleSortRacer.cpp -o b500racer
g++ racers/QuickSortRacer.cpp -o q500racer
g++ racers/QuickBogoSortRacer.cpp -o f500racer
sleep 1

echo -e "${yellow}\rPlayers are ready. Press ENTER to start the race!          ${endColor}"
read -n 1 -s

echo
echo -e "${green}IT'S LIGHTS OUT AND AWAY WE GO!${endColor}"
./f500racer $i &
pids[0]=$! 
./b500racer $i & 
pids[1]=$!
./q500racer $i &
pids[2]=$!

for pid in ${pids[*]}; do
    wait $pid
done

echo -e "${red}Race is over.${endColor}"

rm b500racer
rm q500racer
rm f500racer