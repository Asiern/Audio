#!/bin/bash
apt install -y gcc g++ gdb make cmake libwxgtk3.0-gtk3-dev
mkdir build && cd build && cmake ..