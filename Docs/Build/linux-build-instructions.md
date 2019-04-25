# UBUNTU BIONIC (18.04)

## INSTALL THE ESSENTIAL BUILD TOOLS

```bash
sudo apt-get update
sudo apt-get install -y build-essential
```

## INSTALL GIT

```bash
sudo apt-get install -y git
```

## CHECK OUT ULTRASCHALL

```bash
git clone https://github.com/Ultraschall/ultraschall-3.git
```

## INSTALL THE REQUIRED DEPENDENCIES

```bash
sudo apt-get install -y libz-dev
sudo apt-get install -y libminizip-dev
sudo apt-get install -y libcurl4-openssl-dev
sudo apt-get install -y libtag1-dev
sudo apt-get install -y libmp4v2-dev
sudo apt-get install -y libgtk-3-dev
sudo apt-get install -y libwxgtk3.0-dev
```

## INSTALL CMAKE

```bash
sudo apt-get install -y cmake
```

## SETUP THE BUILD ENVIRONMENT

```bash
cd ultraschall-3/Plugin
mkdir build && cd build
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../
```

## BUILD THE ULTRASCHALL PLUGIN FOR REAPER

```bash
cmake --build . --target reaper_ultraschall
```
