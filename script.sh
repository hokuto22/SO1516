killall -9 -q ligarServidor
killall -9 -q servidor
killall -9 -q cliente
make

clear
./ligarServidor
sleep 1

./cliente << EOF
2
Rui
123
1
Rui
123
plafond
ls -l
ls | wc
firefox
exit
3
Rui
20
1
Rui
123
plafond
firefox
ls -l -a | wc > teste.txt
ls -l | tail -n +2 | sed 's/\s\s*/ /g' | cut -d ' ' -f 3 | sort | uniq -c
plafond
exit
9
EOF

killall -9 -q ligarServidor
killall -9 -q servidor