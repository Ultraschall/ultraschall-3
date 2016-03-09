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

#ifndef __ULTRASCHALL_REAPER_APPLICATION_H_INCL__
#define __ULTRASCHALL_REAPER_APPLICATION_H_INCL__

#include <Framework.h>
#include <IActivationService.h>
#include <IConfigurationService.h>
#include <ChapterMarker.h>
#include <TranscriptItem.h>

#include "CustomActionManager.h"
#include "CustomActionFactory.h"

namespace framework = ultraschall::framework;

namespace ultraschall { namespace reaper {

class Application : public framework::IActivationService,
                    public framework::IConfigurationService
{
public:
   virtual ~Application();

   static Application& Instance();

   const ServiceStatus Start();
   void Stop();

   virtual const ServiceStatus Configure();
   
   template<class CustomActionType> const ServiceStatus RegisterCustomAction() const;
   static const bool OnCustomAction(const int32_t id);

   static const size_t MAX_REAPER_STRING_BUFFER_SIZE = 4096;

   const std::string GetExportPathName() const;
   const std::string GetProjectPathName() const;
   const std::string GetProjectFileName() const;
   const std::string GetProjectFolderName() const;
   const std::string GetProjectName() const;
   
   const std::string TimestampToString(const double timestamp) const;
   const double StringToTimestamp(const std::string& input) const;

   const intptr_t GetCurrentProject() const;
   
   const std::vector<framework::ChapterMarker> ChapterMarkers() const;
   const int32_t SetChapterMarker(const framework::ChapterMarker& chapterMarker) const;
   const bool DeleteChapterMarker(const framework::ChapterMarker& chapterMarker) const;
   void DeleteAllChapterMarkers() const;
   
   const bool InsertTransriptItem(const framework::TranscriptItem transcriptItem) const;
   
   static std::string ParseReaperVersion();
    
private:
   Application();

   static const bool HealthCheck();

   const int Register(const char* name, void* pInfoStruct) const;
};

typedef struct
{
   int uniqueSectionId; // 0/100=main/main alt, 32063=media explorer, 32060=midi editor, 32061=midi event list editor, 32062=midi inline editor, etc
   const char* idStr; // must be unique accross all sections
   const char* name;
   void *extra; // reserved for future use
} custom_action_register_t;
   
template<class CustomActionType> const ServiceStatus Application::RegisterCustomAction() const
{
   ServiceStatus status = SERVICE_FAILURE;

   const char* uniqueId = CustomActionType::UniqueId();
   if(uniqueId != 0)
   {
      CustomActionFactory& factory = CustomActionFactory::Instance();
      ICustomAction* pCustomAction = 0;
      status = factory.CreateCustomAction(uniqueId, pCustomAction);
      if(ServiceSucceeded(status) && (pCustomAction != 0))
      {
         const char* localisedName = pCustomAction->LocalizedName();
         if(localisedName != 0)
         {
            custom_action_register_t action = {0};
            action.idStr = uniqueId;
            action.name = localisedName;
            const int32_t id = Register("custom_action", (void*)&action);
            if(id != 0)
            {
               CustomActionManager& manager = CustomActionManager::Instance();
               status = manager.RegisterCustomAction(id, pCustomAction);
            }
         }
         else
         {
            status = SERVICE_INVALID_ARGUMENT;
         }
         
         framework::SafeRelease(pCustomAction);
      }
   }

   return status;
}

}}

#endif // #ifndef __ULTRASCHALL_REAPER_APPLICATION_H_INCL__
