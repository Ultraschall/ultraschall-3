# WINDOWS SUBSYSTEM FOR LINUX

## INSTALL THE WINDOWS SUBSYSTEM FOR LINUX

First open PowerShell as Administrator. **CAUTION**: The computer restarts immediately after running these two commands!

```
PS> Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
PS> shutdown /r /f /t 0 /d p:04:01
```

## INSTALL UBUNTU XENIAL FROM THE MICROSOFT STORE

```
https://www.microsoft.com/en-us/p/ubuntu/9nblggh4msv6
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

## UPGRADE GIT TO THE CURRENT VERSION

```
$ sudo apt-add-repository ppa:git-core/ppa
$ sudo apt-get update
$ sudo apt-get install -y git
```

## CHECK-OUT ULTRASCHALL

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
