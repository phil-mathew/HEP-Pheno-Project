# QCD @ FCC-ee
This repo tracks progress of my research project on QCD physics through event shapes and inclusive hadron spectra in electron-positron annihilations at the FCCee. The analysis uses Pythia 8.313, ROOT 6.32.04, and FastJet 3.4.3. For future reference, a guide on installation of necessary software has been compiled.

# Installation

## ROOT
```
\\ Dependencies
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

\\ Install
wget https://root.cern/download/root_v6.32.04.source.tar.gz
tar xzvf root_v6.32.04.source.tar.gz
cd root-6.32.04/
mkdir buildroot
cmake ..
cmake -Dall=on .
cmake -DCMAKE_INSTALL_PREFIX=~/0-software/root/root-6.32.04-install .
make -j4
make install

\\ Add these lines to bashrc
. /home/pmathew/0-software/root/root-6.32.04-install/bin/thisroot.sh

\\ Verify installation by running root in a new terminal
```

## PYTHIA 
```
\\ Dependencies
sudo apt install gcc g++ automake
\\ Install
wget https://pythia.org/download/pythia83/pythia8313.tgz
tar xvfz pythia8313.tgz
cd pythia8313/
./configure
make
sudo make install
```

## FASTJET 
```
curl -O https://fastjet.fr/repo/fastjet-3.4.3.tar.gz
tar zxvf fastjet-3.4.3.tar.gz
cd fastjet-3.4.3/
./configure --prefix=$PWD/../fastjet-install
make
make check
make install
cd ..
```

## FJCORE

## LHAPDF

## DELPHES

## GEANT4

## PYENV 
```
// Prepare dependencies
sudo apt update; sudo apt install make build-essential libssl-dev zlib1g-dev \
libbz2-dev libreadline-dev libsqlite3-dev curl git \
libncursesw5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev libffi-dev liblzma-dev

// Install pyenv
curl -fsSL https://pyenv.run | bash

// Set up shell
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
echo 'eval "$(pyenv init - bash)"' >> ~/.bashrc

// Copy these lines into ~/.profile
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.profile
echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.profile
echo 'eval "$(pyenv init - bash)"' >> ~/.profile

// Restart bash
exec "$SHELL"

// Install python version
pyenv install 3.8.0

// Set global version
pyenv global 3.8.0
```

## BASHRC 
```
# Starting up HEP software
. /home/pmathew/software/root/root-6.32.04-install/bin/thisroot.sh
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/pmathew/software/pythia8313/lib
export PYTHIA8=/home/pmathew/software/pythia8313
export LD_LIBRARY_PATH=$PYTHIA8/lib:$LD_LIBRARY_PATH
export PATH=$PATH:/home/pmathew/software/lhapdf-install-6.5.0/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/pmathew/software/lhapdf-install-6.5.0/lib
export LHAPDF_DATA_PATH=/home/pmathew/software/lhapdf-install-6.5.0/share/LHAPDF
export PATH=$PATH:/home/pmathew/software/lhapdf-install-6.5.0/bin
export PYTHONPATH=$PYTHONPATH:/home/pmathew/software/lhapdf-install-6.5.0/lib/python3.9/site-packages

# Alias to update bash
alias upbash='. ~/.bashrc'
# Alias to access HEP folder
alias runhep='cd /mnt/c/Users/pmathew/cernbox/WINDOWS/Desktop/Git-Projects/HEP-Pheno-Project'
# Alias to Git commit
alias gitp='git add .; git commit -m "File updates"; git push;'
```
