#!/bin/bash
echo 'Content-Type: text/plain'
echo
Logfile=/var/www/html/logs/scriptlog

declare -A param
while IFS='=' read -r -d '&' key value && [[ -n "$key" ]]; do
    param["$key"]=$value
done <<<"${QUERY_STRING:+"${QUERY_STRING}&"}"

file=${param[FILE]}
args=${param[Args]}

if [ -z "$file" ]; then
    echo "YOU DIDN'T GIVE ME A FILE"
    echo "HERE ARE SOME OPTIONS, PICK ONE:"
    echo $(ls)
    echo
    echo "Command options: h,r,d,L,H"
    echo
    echo "Query String should be:"
    echo "IP/cgi-bin/Homework-Wrapper/FILE=???&Args=???"
    exit
fi

/usr/lib/cgi-bin/Homework.out -${param[Args]} ${param[FILE]}
err=$?
#-L $Logfile ${param[FILE]}
echo "$QUERY_STRING"
echo ${param[FILE]}
echo ${param[Args]}
echo
echo $err
