#!/bin/bash

delay=0.1
if [[ $# == 1 ]]
then
    delay=$1
fi

symbol_map=""
rows=0
cols=0
while IFS= read -r line
do
    for ((cols=0; cols<${#line}; ++cols))
    do
        c=${line:${cols}:1}
        if [[ ${c} != " " ]]
        then
            symbol_map="${symbol_map}${rows} ${cols} ${c}\n"
        fi
    done
    rows=$((rows+1))
done

tput clear

symbol_map=$(printf "${symbol_map}" | shuf)

printf "${symbol_map}" | while read row col c
do
    tput cup ${row} ${col}
    printf ${c}
    sleep ${delay}
done

tput cup ${rows} 0

