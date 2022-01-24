#!/bin/bash

### This script prints system info ###

echo "Welcome to automatic config and Unit test bash script."
echo

sleep 2

echo "#####################################"
echo "Erasing old files and updating"
rm -rf mpbComponents
rm -rf *.xml
rm -rf *.txt
echo "##### done #########################"

sleep 2
echo "#########################################################"
echo "fetching the last code from repository "
git clone git@github.com:Juan-Andres-Castano/MpbComponents.git

sleep 2
echo "#########################################################"
echo "test the library time"
cd mpbComponents
cd mpbTime
cd UnitTestFramework
ceedling test:all


echo "##########################################################"
echo "test the library math"
cd ..
cd ..
cd mpbMath
cd UnitTestFramework
ceedling test:all


echo "########## ----- tests done ----- ##############"
cd ..
cd ..
cd ..



mv /c/mpbComponents/configurationManagement/mpbComponents/mpbTime/unitTestFramework/build/artifacts/test/report.xml /c/mpbComponents/configurationManagement/report_time_library.xml

mv /c/mpbComponents/configurationManagement/mpbComponents/mpbMath/unitTestFramework/build/artifacts/test/report.xml /c/mpbComponents/configurationManagement/report_math_library.xml



touch softReleaseDocument.txt

logInfo="$(git log)"
echo "$logInfo">softReleaseDocument.txt


echo "#####################################"
echo "cleaning files "
rm -rf mpbComponents
sleep 1
echo "######### finish ###################"

