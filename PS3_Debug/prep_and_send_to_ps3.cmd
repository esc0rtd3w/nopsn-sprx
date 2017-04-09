@echo off


:: esc0rtd3w / 100% BeasTm0de


:main

color 0e

set ip=192.168.1.250
set tempFile="%temp%\ps3ftp_temp.txt"
set sprx=nopsn.sprx

set localPath=%cd%
set remotePath=/dev_hdd0/tmp/

:ip
cls
echo Current IP: %ip%
echo.
echo.
echo Enter PS3 IP Address and press ENTER:
echo.
echo.

::set /p ip=
goto local


:local
cls
echo Current IP: %ip%
echo.
echo Current Local Path: %localPath%
echo.
echo.
echo Enter Local Path and press ENTER:
echo.
echo.

::set /p localPath=

goto remote


:remote
cls
echo Current IP: %ip%
echo.
echo Current Local Path: %localPath%
echo.
echo Current SPRX Filename: %sprx%
echo.
echo Current Remote Path: %remotePath%
echo.
echo.
echo Enter Remote Path and press ENTER:
echo.
echo.

::set /p remotePath=
goto upload


:upload
cls
color 0a
echo Current IP: %ip%
echo.
echo Current Local Path: %localPath%
echo.
echo Current SPRX Filename: %sprx%
echo.
echo Current Remote Path: %remotePath%
echo.
echo.
echo Uploading SPRX to PS3 Console....
echo.
echo.
echo.
echo Sending %sprx% to %ip%@%remotePath%....
echo.
echo.
echo cd "%localPath%">%tempFile%
echo user ps3>>%tempFile%
echo ps3>>%tempFile%
echo bin>>%tempFile%
echo cd %remotePath%>>%tempFile%
echo put "%cd%\%sprx%">>%tempFile%
echo quit>>%tempFile%
ftp -n -s:%tempFile% %ip%
del /f /q %tempFile%

goto end


:: ONLY LAND HERE IF CUSTOM SPRX NAME
:sprxCustom
cls
echo Current IP: %ip%
echo.
echo Current Local Path: %localPath%
echo.
echo Current SPRX Filename: %sprx%
echo.
echo.
echo Type SPRX Filename and press ENTER:
echo.
echo.

set /p sprx=

goto remote


::goto main



:end


echo.
echo.
pause
