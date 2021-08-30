#!/bin/bash
set -e

sudo dnf install -y gcc g++ gdb make cmake wxGTK-devel libcurl-devel


# Thirdparty BASS
wget -P thirdparty/ http://uk.un4seen.com/files/bass24-linux.zip && cd thirdparty
unzip bass24-linux.zip bass.h x64/libbass.so
rm bass24-linux.zip

cd .. && mkdir build && cd build && cmake .. 