# QCD @ FCC-ee
This repo tracks the progress of my research project studying QCD physics in electron-positron annihilations at the FCCee. The analyses are coded in C++ using the Pythia 8.313, ROOT 6.32.04, and FastJet 3.4.3 frameworks.

# Installation

## ROOT 6.32.04

### Dependencies
```
sudo apt install binutils cmake dpkg-dev g++ gcc libssl-dev git libx11-dev \
libxext-dev libxft-dev libxpm-dev python3 libtbb-dev libvdt-dev libgif-dev \
gfortran libpcre3-dev \
libglu1-mesa-dev libglew-dev libftgl-dev \
libfftw3-dev libcfitsio-dev libgraphviz-dev \
libavahi-compat-libdnssd-dev libldap2-dev \
python3-dev python3-numpy libxml2-dev libkrb5-dev \
libgsl-dev qtwebengine5-dev nlohmann-json3-dev libmysqlclient-dev \
libgl2ps-dev \
liblzma-dev libxxhash-dev liblz4-dev libzstd-dev
```

### Install
```
wget https://root.cern/download/root_v6.32.04.source.tar.gz
tar xzvf root_v6.32.04.source.tar.gz
cd root-6.32.04/
mkdir buildroot
cmake ..
cmake -Dall=on .
cmake -DCMAKE_INSTALL_PREFIX=~/0-software/root/root-6.32.04-install .
make -j4
make install
```
Add these lines to bashrc
```
. /home/pmathew/0-software/root/root-6.32.04-install/bin/thisroot.sh
```

Verify installation by running `root` in a new terminal.
