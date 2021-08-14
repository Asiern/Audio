@echo off

setlocal

MD thirdparty

set WorkDir=%cd%

Rem Download CURL and BASS
bitsadmin /transfer BASS_Download /download /priority normal http://uk.un4seen.com/files/bass24.zip %WorkDir%\thirdparty\bass.zip

Rem Unzip files
powershell Expand-Archive %WorkDir%\thirdparty\bass.zip -DestinationPath %WorkDir%\thirdparty\BASS

Rem Cleanup
DEL  %WorkDir%\thirdparty\*.zip