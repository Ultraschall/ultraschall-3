# UBUNTU XENIAL ON DOCKER

## DOWNLOAD THE UBUNTU XENIAL DOCKER IMAGE

```
PS> docker pull ubuntu:xenial
```

## CREATE A DOCKER CONTAINER WITH UBUNTU XENIAL

```
PS> docker run --name ubuntu-xenial -ti ubuntu:xenial /bin/bash
```

## INSTALL SUDO

```
# apt-get update
# apt-get install -y sudo
# rm -rf /var/lib/apt/lists/*
```

## CREATE A SUDO USER

```
# adduser heiko
# usermod -aG sudo heiko
```

## LOGOUT

```
# exit
```

## START THE CONTAINER

```
PS> docker start ubuntu-xenial
```

## LOGIN

```
PS> docker exec -ti ubuntu-xenial login
```

## MAKE BASH FIT FOR HUMANS

```
$ echo "bind 'set completion-ignore-case on'" >> .bashrc
$ source .bashrc
```

## INSTALL THE ESSENTIAL BUILD TOOLS

```
$ sudo apt-get update
$ sudo apt-get install -y build-essential
```

## INSTALL CMAKE

```
$ sudo apt-get install -y wget
$ wget https://github.com/Kitware/CMake/releases/download/v3.13.2/cmake-3.13.2-Linux-x86_64.tar.gz
$ tar -xvf cmake-3.13.2-Linux-x86_64.tar.gz
$ cd cmake-3.13.2-Linux-x86_64
$ sudo cp -r bin /usr/local/
$ sudo cp -r share /usr/local/
$ sudo cp -r doc /usr/local/share/
$ sudo cp -r man /usr/local/share/
$ cd ..
$ rm -r cmake-3.13.2-Linux-x86_64
$ rm cmake-3.13.2-Linux-x86_64.tar.gz
```

## INSTALL THE CURRENT VERSION OF GIT

```
$ sudo apt-get install -y software-properties-common
$ sudo apt-add-repository ppa:git-core/ppa
$ sudo apt-get update
$ sudo apt-get install -y git
```

## CHECK OUT ULTRASCHALL

```
$ git clone https://github.com/Ultraschall/ultraschall-3.git
$ cd ultraschall-3/Plugin/reaper_ultraschall
```

## INSTALL THE REQUIRED LIBRARIES

```
$ sudo apt-get install -y libwxgtk3.0-0v5 libwxgtk3.0-dev
$ sudo apt-get install -y libtag1v5 libtag1-dev
$ sudo apt-get install -y libmp4v2-2 libmp4v2-dev
```

## SETUP THE BUILD ENVIRONMENT

```
$ mkdir build
$ cd build
$ cmake ../
```

## BUILD THE ULTRASCHALL PLUGIN FOR REAPER

```
$ cmake --build . --target reaper_ultraschall --config Debug -j
```
