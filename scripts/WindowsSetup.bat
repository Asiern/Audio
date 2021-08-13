@echo off

setlocal

MD thirdparty

set WorkDir=%cd%

Rem Download CURL and BASS
bitsadmin /transfer CURL_Download /download /priority normal https://curl.se/windows/dl-7.78.0/curl-7.78.0-win64-mingw.zip %WorkDir%\thirdparty\curl.zip
bitsadmin /transfer BASS_Download /download /priority normal http://uk.un4seen.com/files/bass24.zip %WorkDir%\thirdparty\bass.zip
bitsadmin /transfer WX_Download /download /priority normal https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.5/wxWidgets-3.1.5-headers.7z %WorkDir%\thirdparty\wxinclude.7z
bitsadmin /transfer WX_Download /download /priority normal https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.5/wxMSW-3.1.5_vc14x_x64_Dev.7z %WorkDir%\thirdparty\wxlib.7z
bitsadmin /transfer 7z_Download /download /priority normal https://www.7-zip.org/a/7z1900-x64.exe %WorkDir%\thirdparty\7z.exe

Rem install 7z
If Exist "C:\Program Files\7-Zip\" GoTo :UNZIP
start %WorkDir%\thirdparty\7z.exe /S /D="C:\Program Files\7-Zip\" /VERYSILENT

Rem Unzip files
:UNZIP
powershell Expand-Archive %WorkDir%\thirdparty\curl.zip -DestinationPath %WorkDir%\thirdparty\
powershell Expand-Archive %WorkDir%\thirdparty\bass.zip -DestinationPath %WorkDir%\thirdparty\BASS
"C:\Program Files\7-Zip\7z.exe" x %WorkDir%\thirdparty\wxinclude.7z -o%WorkDir%\thirdparty\WX
"C:\Program Files\7-Zip\7z.exe" x %WorkDir%\thirdparty\wxlib.7z -o%WorkDir%\thirdparty\WX

Rem Cleanup
RENAME %WorkDir%\thirdparty\curl-7.78.0-win64-mingw CURL
DEL  %WorkDir%\thirdparty\*.zip
DEL  %WorkDir%\thirdparty\*.7z
DEL  %WorkDir%\thirdparty\*.exe