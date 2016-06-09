#!/bin/sh
# 
# File:   runSh.sh
# Author: fordem
#
# Created on Aug 21, 2015, 12:35:50 PM
#

ulimit -s 512000
#make CONF=Release QMAKE=/usr/bin/qmake clean
#make CONF=Release QMAKE=/usr/bin/qmake 
#/home/fordem/Dropbox/HC/RandomFwkGUI/dist/Release/GNU-Linux/RandomFwkGUI tamanho disc minbox maxbox seed tempo(ms)
/home/fordem/Dropbox/HC/RandomFwkGUI/dist/Release/GNU-Linux/RandomFwkGUI 100000 8 3 10000 232123 360000000>disc8_232123.dat&
/home/fordem/Dropbox/HC/RandomFwkGUI/dist/Release/GNU-Linux/RandomFwkGUI 100000 8 3 10000 90987665 360000000>disc8_90987665.dat&
/home/fordem/Dropbox/HC/RandomFwkGUI/dist/Release/GNU-Linux/RandomFwkGUI 100000 8 3 10000 19283747 360000000>disc8_19283747.dat&
/home/fordem/Dropbox/HC/RandomFwkGUI/dist/Release/GNU-Linux/RandomFwkGUI 100000 8 3 10000 877463525 360000000>disc8_877463525.dat&
/home/fordem/Dropbox/HC/RandomFwkGUI/dist/Release/GNU-Linux/RandomFwkGUI 100000 8 3 10000 929847378 360000000>disc8_929847378.dat&
/home/fordem/Dropbox/HC/RandomFwkGUI/dist/Release/GNU-Linux/RandomFwkGUI 100000 8 3 10000 746627687 360000000>disc8_746627687.dat&
#/home/fordem/Dropbox/HC/RandomFwkGUI/dist/Release/GNU-Linux/RandomFwkGUI 100000 8 3 10000 454323 36000000>>disc8.dat&

