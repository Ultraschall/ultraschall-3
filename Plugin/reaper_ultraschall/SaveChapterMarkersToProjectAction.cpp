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

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Application.h"
#include "FileManager.h"
#include "ReaperProjectManager.h"
#include "SaveChapterMarkersToProjectAction.h"
#include "SystemProperties.h"
#include "TimeUtilities.h"
#include "UIMessageDialog.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<SaveChapterMarkersToProjectAction> action;

ServiceStatus SaveChapterMarkersToProjectAction::Execute()
{
    ServiceStatus status = SERVICE_FAILURE;

    const ReaperProjectManager& projectManager = ReaperProjectManager::Instance();
    ReaperProject               currentProject = projectManager.CurrentProject();
    const UnicodeString   projectFolder  = currentProject.FolderName();
    if(projectFolder.empty() == false)
    {
        const UnicodeString projectName = currentProject.Name();
        if((projectName.empty() == false) && (ConfigureAssets() == true))
        {
            UnicodeStringArray errorMessages = ValidateChapterMarkers();
            if(errorMessages.empty() == false)
            {
                const UnicodeString fullPath = FileManager::AppendPath(projectFolder, projectName + ".chapters.txt");
                std::ofstream       os(fullPath, std::ios::out);
                if(os.is_open() == true)
                {
                    for(size_t i = 0; i < chapters_.size(); i++)
                    {
                        const UnicodeString timestamp = SecondsToString(chapters_[i].Position());
                        const UnicodeString item      = timestamp + " " + chapters_[i].Name();

                        os << item << std::endl;
                    }
                }
                else
                {
#ifndef ULTRASCHALL_BROADCASTER
                    UIMessageDialog::ShowError("Failed to export chapter markers.");
#endif // #ifndef ULTRASCHALL_BROADCASTER
                }

                os.close();

                status = SERVICE_SUCCESS;

#ifndef ULTRASCHALL_BROADCASTER
                UIMessageDialog::Show("The chapter markers have been saved successfully.");
#endif // #ifndef ULTRASCHALL_BROADCASTER
            }
            else
            {
                if(errorMessages.empty() == false)
                {
#ifndef ULTRASCHALL_BROADCASTER
                    std::ostringstream os;
                    os << "Ultraschall failed to validate chapter markers.";
                    os << "\r\n\r\n";

                    for(size_t l = 0; l < errorMessages.size(); l++)
                    {
                        os << errorMessages[l];
                    }

                    os << "\r\n\r\n";

                    UIMessageDialog::ShowError(os.str());
#endif // #ifndef ULTRASCHALL_BROADCASTER
                }
            }
        }
        else
        {
            UIMessageDialog::Show("The project has no name yet. Please save the project and try again.");
        }
    }
    else
    {
        UIMessageDialog::Show("The project has no name yet. Please save the project and try again.");
    }

    return status;
}

bool SaveChapterMarkersToProjectAction::ConfigureAssets()
{
    bool               result = false;
    UnicodeStringArray messages;
    size_t             invalidAssetCount = 0;

    ReaperProjectManager& projectManager = ReaperProjectManager::Instance();
    ReaperProject         currentProject = projectManager.CurrentProject();
    if(ReaperProject::Validate(currentProject) == true)
    {
        chapters_ = currentProject.AllMarkers();
        if(chapters_.empty() == true)
        {
            const UnicodeString message = "No chapters have been set.";
            messages.push_back(message);
            invalidAssetCount++;
        }

#ifndef ULTRASCHALL_BROADCASTER
        if(invalidAssetCount >= 1)
        {
            std::stringstream os;
            os << "Your project does not meet the minimum requirements for the export to continue.";
            os << "\r\n\r\n";
            os << "Specify at least one ID3v2 tag, a cover image or a chapter marker.";
            os << "\r\n\r\n";

            UIMessageDialog::ShowError(os.str());

            result = false;
        }
        else if(messages.size() > 0)
        {
            std::stringstream os;

            os << "Ultraschall has found the following non-critical issues and will continue after you close this "
                  "message:\r\n\r\n";
            for(size_t i = 0; i < messages.size(); i++)
            {
                os << (i + 1) << ") " << messages[i] << "\r\n";
            }

            os << "\r\n\r\n";

            UIMessageDialog::Show(os.str());

            result = true;
        }
        else
        {
            result = true;
        }
    }
#endif // #ifndef ULTRASCHALL_BROADCASTER

    else
    {
        UIMessageDialog::ShowError("The REAPER project must be saved before the export can continue");

        result = false;
    }

    return result;
}

void SaveChapterMarkersToProjectAction::ResetAssets()
{
    chapters_.clear();
}

UnicodeStringArray SaveChapterMarkersToProjectAction::ValidateChapterMarkers()
{
    PRECONDITION_RETURN(chapters_.empty() == false, UnicodeStringArray());

    UnicodeStringArray errorMessages;

    for(size_t i = 0; i < chapters_.size(); i++)
    {
        const Marker&       current      = chapters_[i];
        const UnicodeString safeName     = current.Name();
        const double        safePosition = current.Position();

        ReaperProjectManager& projectManager = ReaperProjectManager::Instance();
        ReaperProject         currentProject = projectManager.CurrentProject();
        if(currentProject.IsValidPosition(current.Position()) == false)
        {
            std::stringstream os;
            os << "Chapter marker '" << ((safeName.empty() == false) ? safeName : UnicodeString("Unknown"))
               << "' is out of track range.";
            errorMessages.push_back(os.str());
        }

        if(current.Name().empty() == true)
        {
            std::stringstream os;
            os << "Chapter marker at '" << SecondsToString(safePosition) << "' has no name.";
            os << "\r\n";
            errorMessages.push_back(os.str());
        }
    }

    return errorMessages;
}

}} // namespace ultraschall::reaper
