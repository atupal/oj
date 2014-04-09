#/bin/bash

a=1000
while [ $a -lt 3048 ]
do
    curl --cookie 'PHPSESSID=gjejmh06200ihqpsdr9jm50k10; CNZZDATA2982771=cnzz_eid=10560400-1360068043-https%253A%252F%252Fwww.google.com.hk%252F&ntime=1360068043&cnzz_a=13&retime=1360069326932&sin=none&ltime=1360069326932&rtime=0' "http://www.lydsy.com/JudgeOnline/problem.php?id=$a" >>$a.html
    let a++
done
