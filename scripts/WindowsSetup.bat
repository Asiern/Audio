@echo off

setlocal

MD thirdparty

set WorkDir=%cd%

Rem Download BASS
bitsadmin /transfer BASS_Download /download /priority normal http://uk.un4seen.com/files/bass24.zip %WorkDir%\thirdparty\bass.zip

Rem Download BASS FX
bitsadmin /transfer BASS_FX_Download /download /priority normal http://uk.un4seen.com/files/z/0//bass_fx24.zip %WorkDir%\thirdparty\bass_fx.zip

Rem Unzip files
powershell Expand-Archive %WorkDir%\thirdparty\bass.zip -DestinationPath %WorkDir%\thirdparty\BASS
powershell Expand-Archive %WorkDir%\thirdparty\bass_fx.zip -DestinationPath %WorkDir%\thirdparty\BASS_FX

Rem Cleanup
DEL  %WorkDir%\thirdparty\*.zip
