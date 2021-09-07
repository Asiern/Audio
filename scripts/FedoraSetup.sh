#!/bin/bash
set -e

sudo dnf install -y gcc g++ gdb make cmake wxGTK-devel libcurl-devel


# Thirdparty BASS
wget -P thirdparty/BASS http://uk.un4seen.com/files/bass24-linux.zip && cd thirdparty/BASS
unzip bass24-linux.zip bass.h x64/libbass.so

# BASS FX
wget http://uk.un4seen.com/files/z/0/bass_fx24-linux.zip 
unzip bass_fx24-linux.zip C/bass_fx.h x64/libbass_fx.so
mv C/bass_fx.h ./bass_fx.h
rm -rf C/

# BASS ENC
wget https://www.un4seen.com/files/bassenc24-linux.zip
unzip bassenc24-linux.zip bassenc.h x64/libbassenc.so

# BASS ENC MP3
wget https://www.un4seen.com/files/bassenc_mp324-linux.zip 
unzip bassenc_mp324-linux.zip bassenc_mp3.h x64/libbassenc_mp3.so

rm *.zip

cd ../.. && mkdir build && cd build && cmake .. 