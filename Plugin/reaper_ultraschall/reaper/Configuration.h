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

#ifndef __ULTRASCHALL_REAPER_CONFIGURATION_H_INCL__
#define __ULTRASCHALL_REAPER_CONFIGURATION_H_INCL__

#include <string>
#include <vector>

namespace ultraschall { namespace reaper {
   
class Configuration
{
public:
   virtual ~Configuration();
   
   static Configuration& Instance();

   void Read();
   void Reset();

   inline const std::string& HostPinCode() const
   {
      return hostPinCode_;
   }
   
   inline const std::string& GuestPinCode() const
   {
      return guestPinCode_;
   }
   
   inline const std::vector<std::string>& ProjectMarkers() const
   {
      return projectMarkers_;
   }
   
private:
   Configuration();
   
   Configuration(const Configuration&);
   Configuration& operator=(const Configuration&);
   
   std::string hostPinCode_;
   std::string guestPinCode_;
   std::vector<std::string> projectMarkers_;
};
   
}}

#endif // #ifndef __ULTRASCHALL_REAPER_CONFIGURATION_H_INCL__

