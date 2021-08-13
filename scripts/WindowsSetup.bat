@echo off

setlocal

MD thirdparty

set WorkDir=%cd%

Rem Download CURL and BASS
bitsadmin /transfer CURL_Download /download /priority normal https://curl.se/windows/dl-7.78.0/curl-7.78.0-win64-mingw.zip %WorkDir%\thirdparty\curl.zip
bitsadmin /transfer BASS_Download /download /priority normal http://uk.un4seen.com/files/bass24.zip %WorkDir%\thirdparty\bass.zip

Rem Unzip files
powershell Expand-Archive %WorkDir%\thirdparty\curl.zip -DestinationPath %WorkDir%\thirdparty\
powershell Expand-Archive %WorkDir%\thirdparty\bass.zip -DestinationPath %WorkDir%\thirdparty\BASS
RENAME %WorkDir%\thirdparty\curl-7.78.0-win64-mingw CURL
DEL  %WorkDir%\thirdparty\*.zip