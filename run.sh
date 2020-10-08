#!/bin/bash
cd ~/work/Mix-Network/  
xterm -hold -e "node ppsn-server-array/app.js 1339 ppsn-server-array/mix3-privkey.pem" &
xterm -hold -e "node ppsn-server-array/app.js 1338 ppsn-server-array/mix2-privkey.pem" &
xterm -hold -e "node ppsn-server-array/app.js 1337 ppsn-server-array/mix1-privkey.pem" &
xterm -hold -e "node ppsn-server-array/app.js 1341 ppsn-server-array/mix4-privkey.pem" &
xterm -hold -e "node ppsn-server-array/app.js 1342 ppsn-server-array/mix5-privkey.pem" &
gnome-terminal --window-with-profile=holdWindow -e "node sn-backend/app.js 1340 sn-backend/sn-backend-privkey.pem" 

exec bash