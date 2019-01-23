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

#include <fstream>
#include <string>
#include <vector>

#include "CustomActionFactory.h"
#include "FileManager.h"
#include "InsertChapterMarkersAction.h"
#include "Marker.h"
#include "ProjectManager.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "TextFileReader.h"
#include "TimeUtilities.h"
#include "UIMessage.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<InsertChapterMarkersAction> action;

ServiceStatus InsertChapterMarkersAction::Execute()
{
    ServiceStatus status = SERVICE_FAILURE;

    const std::string path = FileManager::BrowseForFiles("Import chapter markers...");
    PRECONDITION_RETURN(path.empty() == false, SERVICE_FAILURE);

    const ProjectManager& projectManager = ProjectManager::Instance();
    Project               currentProject = projectManager.CurrentProject();

    std::vector<Marker>      tags;
    std::vector<std::string> errorMessages;

    const std::vector<std::string> lines = framework::TextFileReader::ReadLines(path);
    if (lines.empty() == false)
    {
        for (size_t i = 0; i < lines.size(); i++)
        {
            const std::string& line = lines[i];

            const std::vector<std::string> items = framework::StringTokenize(line, ' ');
            if (items.size() > 0)
            {
                const double position = framework::StringToSeconds(items[0]);
                if (position >= 0)
                {
                    std::string name;
                    if (items.size() > 1)
                    {
                        name = items[1];
                    }

                    for (size_t j = 2; j < items.size(); j++)
                    {
                        name += " " + items[j];
                    }

                    tags.push_back(Marker(position, name, 0));
                }
                else
                {
                    std::stringstream os;
                    os << "Line " << (i + 1) << " does not start with a valid timestamp.";
                    errorMessages.push_back(os.str());
                }
            }
        }
    }
    else
    {
        std::stringstream os;
        os << "The file '" << path << "' does not contain any chapter markers";
        errorMessages.push_back(os.str());
    }

    size_t addedTags = 0;
    for (size_t i = 0; i < tags.size(); i++)
    {
        if (currentProject.InsertChapterMarker(tags[i].Name(), tags[i].Position()) == true)
        {
            addedTags++;
        }
        else
        {
            std::stringstream os;
            os << "Chapter marker '" << tags[i].Name() << "' at position '" << framework::SecondsToString(tags[i].Position()) << "' could not be added.";
            errorMessages.push_back(os.str());
        }
    }

    if ((tags.size() != addedTags) || (errorMessages.empty() == false))
    {
        std::stringstream os;
        os << "The chapter marker import failed:";
        os << "\r\n\r\n";

        for (size_t i = 0; i < errorMessages.size(); i++)
        {
            os << errorMessages[i] << "\r\n";
        }

        os << "\r\n\r\n";

        ui::Message::Error(os.str());
    }
    else
    {
#ifndef ULTRASCHALL_BROADCASTER
        ui::Message::Notification("The chapter markers have been added successfully.");
#endif // #ifndef ULTRASCHALL_BROADCASTER
        status = SERVICE_SUCCESS;
    }

    return status;
}

}} // namespace ultraschall::reaper
