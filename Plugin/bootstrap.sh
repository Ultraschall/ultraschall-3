#!/bin/sh

################################################################################
#
# Copyright (c) The Ultraschall Project (http://ultraschall.fm)
#
# The MIT License (MIT)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
################################################################################

BUILD_DIRECTORY="_build"
ERROR_LEVEL=0
if [ -x "$(command -v cmake)" ]; then
    if [ -d "$BUILD_DIRECTORY"]; then
        if [ -L "$BUILD_DIRECTORY"]; then
            rm -f "$BUILD_DIRECTORY"
        else
            rm -rf "$BUILD_DIRECTORY"
        fi
    fi
    mkdir "$BUILD_DIRECTORY" && pushd "$BUILD_DIRECTORY"
    echo 'Configuring projects...'
    cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../
    echo 'Done.'
    if [ $? -eq 0]; then
        echo 'Building projects...'
        cmake --build . --target reaper_ultraschall --config Debug
        echo 'Done.'
        if [ $? -ne 0]; then
            ERROR_LEVEL=$?
            echo 'The cmake build step failed.'
        fi
    else
        ERROR_LEVEL=$?
        echo 'Error: The cmake configure step failed.'
    fi
    popd
    exit $ERROR_LEVEL
else
    echo 'Error: cmake not found.' >&2
    exit 1
fi
