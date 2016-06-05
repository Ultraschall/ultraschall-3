////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2014-2015 Ultraschall (http://ultraschall.fm)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#include <zlib.h>
#include <Stream.h>
#include <BinaryFileReader.h>
#include "SWSVersionCheck.h"
#include "FileManager.h"

namespace ultraschall {
    namespace reaper {

        const bool SWSVersionCheck()
        {
            bool result = false;

#ifndef WIN32
            const std::string swsPlugin2_8UserPath = FileManager::UserApplicationSupportDirectory() +
                "/REAPER/UserPlugins/reaper_sws_extension.dylib";
#else
            const std::string swsPlugin2_8UserPath = FileManager::ProgramFilesDirectory() + 
                "\\REAPER (x64)\\Plugins\\reaper_sws64.dll";
#endif // #ifndef WIN32 

            if(FileManager::FileExists(swsPlugin2_8UserPath) == true)
            {
                framework::Stream<uint8_t>* pStream = framework::BinaryFileReader::ReadBytes(swsPlugin2_8UserPath);
                if(pStream != 0)
                {
#ifndef WIN32
                    static const uint64_t originalCrc = 749893719;
#else
                    static const uint64_t originalCrc = 3584691243;
#endif // #ifndef WIN32

                    const uint64_t crc = pStream->CRC32();
                    if(originalCrc == crc)
                    {
                        result = true;
                    }

                    SafeRelease(pStream);
                }
            }

            return result;
        }

        std::string QuerySWSVersion()
        {
#ifdef WIN32
            const std::string path = FileManager::ProgramFilesDirectory() + "\\REAPER (x64)\\Plugins\\reaper_sws64.dll";
            return FileManager::ReadVersionFromFile(path);
#else
            return "2.8.3";
#endif // #ifdef WIN32
        }
    }
}
