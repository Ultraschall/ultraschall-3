////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// The MIT License (MIT)
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

#include "Application.h"
#include "FileManager.h"
#include "StringUtilities.h"
#include "Platform.h"

namespace ultraschall { namespace reaper {

UnicodeChar FileManager::PathSeparator()
{
    return Platform::PathSeparator();
}

UnicodeString FileManager::AppendPath(const UnicodeString& prefix, const UnicodeString& append)
{
    return Platform::AppendPath(prefix, append);
}

UnicodeString FileManager::StripPath(const UnicodeString& path)
{
    UnicodeString shortName;

    if (path.empty() == false)
    {
        shortName = path;

        const UnicodeString::size_type offset = path.rfind(FileManager::PathSeparator());
        if (offset != UnicodeString::npos)
        {
            shortName = path.substr(offset + 1, path.size()); // skip separator
        }
    }

    return shortName;
}

UnicodeStringArray FileManager::SplitPath(const UnicodeString& path)
{
    return UnicodeStringTokenize(path, PathSeparator());
}

bool FileManager::FileExists(const UnicodeString& path)
{
    return Platform::FileExists(path);
}

size_t FileManager::FileExists(const UnicodeStringArray& paths)
{
    size_t offset = static_cast<size_t>(-1);

    for (size_t i = 0; (i < paths.size()) && (offset == -1); i++)
    {
        if (FileExists(paths[i]) == true)
        {
            offset = i;
        }
    }

    return offset;
}

BinaryStream* FileManager::ReadBinaryFile(const UnicodeString& filename)
{
    BinaryStream* pStream = 0;

    std::ifstream file(U2H(filename), std::ios::in | std::ios::binary | std::ios::ate);
    if(file.is_open() == true)
    {
        const std::ifstream::pos_type fileSize = file.tellg();
        file.seekg(std::ios::beg);
        uint8_t* buffer = new uint8_t[fileSize];
        if(buffer != 0)
        {
            file.read(reinterpret_cast<char*>(buffer), fileSize);
            if(file)
            {
                pStream = new BinaryStream(fileSize);
                if(pStream != 0)
                {
                    const bool succeeded = pStream->Write(0, buffer, fileSize);
                    if(succeeded == false)
                    {
                        SafeRelease(pStream);
                    }
                }
            }

            SafeDeleteArray(buffer);
        }

        file.close();
    }

    return pStream;
}

UnicodeStringArray FileManager::ReadTextFile(const UnicodeString& filename)
{
    UnicodeStringArray lines;

    std::ifstream inputStream(U2H(filename).c_str());
    UnicodeString line;
    while(std::getline(inputStream, line))
    {
        lines.push_back(line);
    }

    return lines;
}

void FileManager::WriteTextFile(const UnicodeString& filename, const UnicodeStringArray& lines)
{
    if(filename.empty() == false)
    {
        std::ofstream os(U2H(filename).c_str());
        for(size_t i = 0; i < lines.size(); i++)
        {
            os << lines[i];
            os << "\r\n"; // TODO check whether this is fine
        }

        os.close();
    }
}

}}     // namespace ultraschall::reaper
