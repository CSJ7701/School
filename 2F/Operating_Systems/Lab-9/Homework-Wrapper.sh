#!/bin/bash

Logfile=/var/www/html/logs/scriptlog

/usr/lib/cgi-bin/Homework.out -H -r -L $Logfile MD.txt
