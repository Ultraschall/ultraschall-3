# UBUNTU BIONIC (18.04)

## Build Environment

1. Install the essential build tools

    ```bash
    sudo apt-get update
    sudo apt-get install -y build-essential
    ```

2. Install git

    ```bash
    sudo apt-get install -y git
    ```

3. Check out the plugin

    ```bash
    git clone https://github.com/Ultraschall/ultraschall-3.git
    ```

4. Install the required dependencies

    ```bash
    sudo apt-get install -y libz-dev
    sudo apt-get install -y libminizip-dev
    sudo apt-get install -y libcurl4-openssl-dev
    sudo apt-get install -y libtag1-dev
    sudo apt-get install -y libmp4v2-dev
    sudo apt-get install -y libgtk-3-dev
    sudo apt-get install -y libwxgtk3.0-dev
    ```

5. Install cmake

    ```bash
    sudo apt-get install -y cmake
    ```

6. Configure the plugin

    ```bash
    cd ultraschall-3
    cd Plugin
    mkdir build && cd build
    cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../
    ```

## Build Process

    ```bash
    cmake --build . --target reaper_ultraschall
    ```
