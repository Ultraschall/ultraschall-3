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

#include <string>
#include <fstream>
#include <BinaryFileReader.h>

namespace ultraschall { namespace framework {
   
Stream<uint8_t>* BinaryFileReader::ReadBytes(const std::string& filename)
{
   Stream<uint8_t>* pStream = 0;
   
   std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
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
            pStream = new Stream<uint8_t>(fileSize);
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
   
}}

