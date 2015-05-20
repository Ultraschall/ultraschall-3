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

#include <fstream>

#include <Framework.h>
#include "Application.h" 
#include "MetadataService.h"

namespace ultraschall { namespace reaper {

MetadataService::MetadataService()
{
}

MetadataService::~MetadataService()
{
}

const std::string MetadataService::Name()
{
   return "MetadataService";
}

const ServiceStatus MetadataService::ExportChapters(const std::string& path, const std::vector<ProjectMarker>& projectMarkers) const
{
   PRECONDITION_RETURN(path.empty() == false, SERVICE_INVALID_ARGUMENT);
   PRECONDITION_RETURN(projectMarkers.empty() == false, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE; 

   std::ofstream output(path, std::ios::out);
   for(size_t i = 0; i < projectMarkers.size(); i++)
   {
      const Application& application = Application::Instance();
      const std::string timestamp = application.TimestampToString(projectMarkers[i].Position());
      const std::string entry = timestamp + " " + projectMarkers[i].Name();
      output << entry << std::endl;
   }

   output.close();

   status = SERVICE_SUCCESS;
   return status;
}

const ServiceStatus MetadataService::ImportChapters(const std::string& path, std::vector<ProjectMarker>& projectMarkers) const
{
   PRECONDITION_RETURN(path.empty() == false, SERVICE_INVALID_ARGUMENT);
   PRECONDITION_RETURN(projectMarkers.empty() != false, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;

   return status;
}

}
}
