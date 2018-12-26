## Ubuntu 16.04

1. Install local build environment

```
$ sudo apt-get install build-essential

```

2. Install required libraries

```
$ sudo apt-get install libwxgtk3.0-0v5 libwxgtk3.0-dev
$ sudo apt-get install libtag1v5 libtag1-dev
$ sudo apt-get install libmp4v2-2 libmp4v2-dev

```

3. Upgrade git to current version

```
$ sudo apt-add-repository ppa:git-core/ppa
$ sudo apt-get update
$ sudo apt-get install git
```

4. Install cmake

```
$ curl -O https://github.com/Kitware/CMake/releases/download/v3.13.2/cmake-3.13.2-Linux-x86_64.tar.gz
$ tar -xvf cmake-3.13.2-Linux-x86_64.tar.gz
$ sudo cp -r bin /usr/local/
$ sudo cp -r share /usr/local/
$ sudo cp -r doc /usr/local/share/
$ sudo cp -r man /usr/local/share/
```

5. Check out ultraschall

```
$ git clone https://github.com/Ultraschall/ultraschall-3.git
$ cd ultraschall-3/Plugin/reaper_ultraschall
```

6. Setup the the build environment

```
$ mkdir build
$ cd build
$ cmake ../

```

7. Build the reaper_ultraschall plugin

```
$ cmake --build . --target reaper_ultraschall --config Debug -j

```
