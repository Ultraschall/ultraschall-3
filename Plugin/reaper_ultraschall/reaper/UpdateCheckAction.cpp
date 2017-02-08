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


#include <string>
#include <vector>
#include <fstream>

#ifndef WIN32
#else
#include <windows.h>
#include "..\resource.h"
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch(message)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwndDlg, wParam);
			return TRUE;
		}
	}
	return FALSE;
}
#endif // #ifndef WIN32

#include <ResourceManager.h>
#include <Framework.h>
#include <StringUtilities.h>

#include "UpdateCheckAction.h"
#include "CustomActionFactory.h"
#include "VersionHandler.h"
#include "ReaperEntryPoints.h"
#include "PluginVersionCheck.h"
#include "NotificationWindow.h"

namespace ultraschall {
namespace reaper {

static DeclareCustomAction<UpdateCheckAction> action;

const char* UpdateCheckAction::UPDATE_FILE_URL = "http://url.ultraschall-podcast.de/version";

UpdateCheckAction::UpdateCheckAction()
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   ServiceStatus status = resourceManager.RegisterLocalizedString(actionNameId_);
   if(ServiceSucceeded(status))
   {
      resourceManager.SetLocalizedString(actionNameId_, "en-EN", "ULTRASCHALL: Check for Updates...");
   }
}

UpdateCheckAction::~UpdateCheckAction()
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   resourceManager.UnregisterLocalizedString(actionNameId_);
}

ServiceStatus UpdateCheckAction::CreateCustomAction(ICustomAction*& pCustomAction)
{
   pCustomAction = new UpdateCheckAction();
   PRECONDITION_RETURN(pCustomAction != 0, SERVICE_FAILURE);
   return SERVICE_SUCCESS;
}

const char* UpdateCheckAction::LocalizedName() const
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   return resourceManager.GetLocalizedString(actionNameId_);
}

const char* UpdateCheckAction::UniqueId()
{
	return "ULTRASCHALL_UPDATE_CHECK";
}

ServiceStatus UpdateCheckAction::Execute()
{
	return SERVICE_SUCCESS;
}

std::string UpdateCheckAction::QueryUpdatedVersion()
{
	std::string updatedVersion;

	std::string versionfile = DownloadVersionFile();
	if(versionfile.empty() == false)
	{
		updatedVersion = ParseVersionFile(versionfile);
	}

	return updatedVersion;
}

std::vector<int> UpdateCheckAction::NormalizeVersionString(const std::string& version)
{
	std::vector<int> result(MAX_VERSION_LENGTH);

	const std::vector<std::string> versionParts = framework::split(version, '.');
	for(size_t i = 0; i < MAX_VERSION_LENGTH; i++)
	{
		if(i < versionParts.size())
		{
			std::stringstream str(versionParts[i]);
			str >> result[i];
		}
		else
		{
			result[i] = 0;
		}
	}

	return result;
}

int UpdateCheckAction::CompareVersions(const std::string& lhs, const std::string& rhs)
{
	int result = 0;
	const std::vector<int> left = NormalizeVersionString(lhs);
	const std::vector<int> right = NormalizeVersionString(rhs);

	for(size_t i = 0; (i < MAX_VERSION_LENGTH) && (0 == result); i++)
	{
		if(left[i] < right[i])
		{
			result = -1;
		}
		else if(left[i] < right[i])
		{
			result = 1;
		}
		else
		{
			result = 0;
		}
	}

	return result;
}

std::string UpdateCheckAction::DownloadVersionFile()
{
	std::string file;
	return file;
}

void UpdateCheckAction::DownloadVersionFileCallback()
{

}

std::string UpdateCheckAction::ParseVersionFile(const std::string& versionFile)
{
	std::string version;

	return version;
}

}
}
