#!/bin/bash
set -e

sudo apt install -y gcc g++ gdb make cmake libwxgtk3.0-gtk3-dev libcurl4-openssl-dev

# Thirdparty BASS
wget -P thirdparty/ http://uk.un4seen.com/files/bass24-linux.zip && cd thirdparty
unzip bass24-linux.zip bass.h x64/libbass.so
rm bass24-linux.zip

cd .. && mkdir build && cd build && cmake .. 