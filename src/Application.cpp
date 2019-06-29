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

#include "Application.h"
#include "CustomAction.h"
#include "FileManager.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "UIMessageSupervisor.h"
#include "UpdateCheck.h"
#include "VersionHandler.h"

namespace ultraschall { namespace reaper {

Application::Application() {}

Application::~Application() {}

Application& Application::Instance()
{
    static Application self;
    return self;
}

ServiceStatus Application::Start()
{
    ServiceStatus status = SERVICE_FAILURE;
    if(HealthCheck() == true)
    {
        UpdateBillOfMaterials();
        UpdateCheck();
        status = SERVICE_SUCCESS;
    }

    return status;
}

void Application::Stop() {}

bool Application::OnCustomAction(const int32_t id)
{
    PRECONDITION_RETURN(CustomAction::ValidateCustomActionId(id) != false, false);

    bool executed = false;

    CustomActionManager& manager       = CustomActionManager::Instance();
    ICustomAction*       pCustomAction = 0;
    ServiceStatus        status        = manager.LookupCustomAction(id, pCustomAction);
    if(ServiceSucceeded(status) && (pCustomAction != 0))
    {
        if(CustomAction::RegisterProject() == true)
        {
            pCustomAction->Execute();
            executed = true;
        }

        SafeRelease(pCustomAction);
    }

    return executed;
}

bool Application::HealthCheck()
{
    bool ok = true;
    UIMessageSupervisor supervisor;

    const std::string information1("\
The Application Support directory of your system contains an unsupported \
file that must be removed in order to use the Ultraschall REAPER Extension. Please move '\
");
    const std::string information2("\
' to a different folder on your system and restart REAPER.\
");

// TODO: checks for legacy installations of ultraschall. remove in 4.x
#ifdef _APPLE_
    const std::string swsPlugin2_8SystemPath
        = Platform::ProgramFilesDirectory() + "/REAPER/UserPlugins/reaper_sws_extension.dylib";
    if((true == ok) && (FileManager::FileExists(swsPlugin2_8SystemPath) == true))
    {
        NotificationWindow::Show(message, information1 + swsPlugin2_8SystemPath + information2, true);
        ok = false;
    }

    const std::string swsPlugin2_7SystemPath
        = Platform::ProgramFilesDirectory() + "/REAPER/UserPlugins/reaper_sws.dylib";
    if((true == ok) && (FileManager::FileExists(swsPlugin2_7SystemPath) == true))
    {
        NotificationWindow::Show(message, information1 + swsPlugin2_7SystemPath + information2, true);
        ok = false;
    }

    const std::string ultraschallPluginSystemPath
        = Platform::ProgramFilesDirectory() + "/REAPER/UserPlugins/reaper_ultraschall.dylib";
    if((true == ok) && (FileManager::FileExists(ultraschallPluginSystemPath) == true))
    {
        NotificationWindow::Show(message, information1 + ultraschallPluginSystemPath + information2, true);
        ok = false;
    }
#endif // #ifdef _APPLE_

    if((true == ok) && (VersionHandler::ReaperVersionCheck() == false))
    {
        supervisor.RegisterError("The Ultraschall REAPER Extension requires REAPER 5.70.");
        supervisor.RegisterError("If you want to use the Ultraschall REAPER extension, you must install REAPER 5.70");
        ok = false;
    }

    if((true == ok) && (VersionHandler::SWSVersionCheck() == false))
    {
        supervisor.RegisterError("The installation of the Ultraschall REAPER extension has been corrupted.");
        supervisor.RegisterError("Please reinstall the Ultraschall REAPER extension using the original or an updated installer.");
        ok = false;
    }

	if(false == ok)
    {
        supervisor.RegisterFatalError("Ultraschall cannot continue!");
    }

    return ok;
}

}} // namespace ultraschall::reaper
