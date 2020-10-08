#!/bin/bash

fuser -k 1337/tcp
fuser -k 1338/tcp
fuser -k 1339/tcp
fuser -k 1340/tcp
fuser -k 1341/tcp
fuser -k 1342/tcp

exec bash