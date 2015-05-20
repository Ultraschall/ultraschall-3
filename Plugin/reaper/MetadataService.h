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

#ifndef __ULTRASCHALL_REAPER_METADATA_SERVICE_H_INCL__
#define __ULTRASCHALL_REAPER_METADATA_SERVICE_H_INCL__

#include "IMetadataService.h"

namespace ultraschall { namespace reaper {

class MetadataService : public IMetadataService 
{
public:
   static const std::string Name();

   virtual const ServiceStatus ExportChapters(const std::string& path, const std::vector<ProjectMarker>& projectMarkers) const;
   virtual const ServiceStatus ImportChapters(const std::string& path, std::vector<ProjectMarker>& projectMarkers) const;

protected:
   virtual ~MetadataService();

private:
   MetadataService();

   MetadataService(const MetadataService&);
   MetadataService& operator=(const MetadataService&);
};

}}

#endif // #ifndef __ULTRASCHALL_REAPER_METADATA_SERVICE_H_INCL__
