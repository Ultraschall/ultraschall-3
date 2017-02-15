////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016 Ultraschall (http://ultraschall.fm)
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

#include "MP3Properties.h"
#include "StringUtilities.h"
#include "taglib_include.h"

namespace ultraschall {
namespace reaper {

struct MP3Properties
{
   std::string title;
   std::string artist;
   std::string album;
   std::string year;
   std::string genre;
   std::string comment;
};
   
   
bool InsertMP3Properties(const std::string& target, const std::string& properties)
{
   PRECONDITION_RETURN(target.empty() == false, false);
   PRECONDITION_RETURN(properties.empty() == false, false);
   
   std::vector<std::string> tokens = framework::split(properties, '\n');
   PRECONDITION_RETURN(tokens.empty() == false, false);
   PRECONDITION_RETURN(tokens.size() == 6, false);
   
   return false;
}

bool InsertMP3Tags(const std::string& target, const std::vector<Marker> tags)
{
   PRECONDITION_RETURN(target.empty() == false, false);
   PRECONDITION_RETURN(tags.empty() == false, false);
   
   return false;
}

}}
