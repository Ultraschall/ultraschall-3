////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#include "FileUtilities.h"
#include "ByteStream.h"

namespace ultraschall { namespace reaper {

ByteStream* ReadBinaryFile(const std::string& filename)
{
    ByteStream* pStream = 0;

    std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open() == true)
    {
        const std::ifstream::pos_type fileSize = file.tellg();
        file.seekg(std::ios::beg);
        uint8_t* buffer = new uint8_t[fileSize];
        if (buffer != 0)
        {
            file.read(reinterpret_cast<char*>(buffer), fileSize);
            if (file)
            {
                pStream = new ByteStream(fileSize);
                if (pStream != 0)
                {
                    const bool succeeded = pStream->Write(0, buffer, fileSize);
                    if (succeeded == false)
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

StringArray ReadTextFile(const std::string& filename)
{
    StringArray lines;

    std::ifstream inputStream(filename.c_str());
    std::string   line;
    while (std::getline(inputStream, line))
    {
        lines.push_back(line);
    }

    return lines;
}

void WriteTextFile(const std::string& filename, const StringArray& lines)
{
    if (filename.empty() == false)
    {
        std::ofstream os(filename.c_str());

        for (size_t i = 0; i < lines.size(); i++)
        {
            os << lines[i];
            //            os << std::endl;
            os << "\r\n";
        }

        os.close();
    }
}

}}     // namespace ultraschall::reaper
