


#!/bin/sh

set -m # Enable Job Control

for i in `seq 500`; do # start 30 jobs in parallel
  sleep 0.2
  node app.js &
done