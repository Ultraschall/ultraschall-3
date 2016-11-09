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

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <string>

#include "reaper_plugin.h"
#define REAPERAPI_DECL
#define REAPERAPI_NO_LICE
#define REAPERAPI_MINIMAL
#include "reaper_plugin_functions.h"

std::map<int, std::string> commandTexts;

const CHAR* (*pfnReverseNamedCommandLookup)(int commandId);
KbdSectionInfo* (*pfnSectionFromUniqueID)(int uniqueID);

BOOL HookCommandCallback(int commandId, int flags);
void HookPostCommandCallback(int commandId, int flags);
BOOL HookCommand2Callback(KbdSectionInfo *pksi, int commandId, int value0, int value1, int mode, HWND hwnd);

extern "C"
{
REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(REAPER_PLUGIN_HINSTANCE, reaper_plugin_info_t *ppi)
{
	if(ppi != 0)
	{
		*((void **)&pfnReverseNamedCommandLookup) = ppi->GetFunc("ReverseNamedCommandLookup");
		if(pfnReverseNamedCommandLookup != 0)
		{
			*((void **)&pfnSectionFromUniqueID) = ppi->GetFunc("SectionFromUniqueID");
			if(pfnSectionFromUniqueID != 0)
			{
				ppi->Register("hookcommand", (void*)&HookCommandCallback);
				ppi->Register("hookpostcommand", (void*)&HookPostCommandCallback);
				ppi->Register("hookcommand2", (void*)&HookCommand2Callback);

				return 1;
			}
		}
	}

	return 0;
}
}

BOOL APIENTRY DllMain(HMODULE, ULONG ul_reason_for_call, LPVOID)
{
   switch (ul_reason_for_call)
   {
   case DLL_PROCESS_ATTACH:
   case DLL_THREAD_ATTACH:
   case DLL_THREAD_DETACH:
   case DLL_PROCESS_DETACH:
      break;
   }
   return TRUE;
}

BOOL HookCommandCallback(int commandId, int flags)
{
	if(pfnReverseNamedCommandLookup != 0)
	{
		const size_t MAX_MESSAGE_SIZE = 256;
		CHAR message[MAX_MESSAGE_SIZE + 1] = {0};

		const CHAR* commandName = (*pfnReverseNamedCommandLookup)(commandId);
		if(0 == commandName)
		{
			const std::map<int, std::string>::const_iterator i = commandTexts.find(commandId);
			if(i != commandTexts.end())
			{
				commandName = i->second.c_str();
			}
		}

		sprintf_s(message, "[REAPER] >> Entering '%s'... (CmdId = %d, Flags = %x)\n",
			((commandName != 0)?commandName : "<Native>"), commandId, flags);
		OutputDebugString(message);
	}

	return FALSE;
}

void HookPostCommandCallback(int commandId, int flags)
{
	if(pfnReverseNamedCommandLookup != 0)
	{
		const size_t MAX_MESSAGE_SIZE = 256;
		CHAR message[MAX_MESSAGE_SIZE + 1] = {0};

		const CHAR* commandName = (*pfnReverseNamedCommandLookup)(commandId);
		if(0 == commandName)
		{
			const std::map<int, std::string>::const_iterator i = commandTexts.find(commandId);
			if(i != commandTexts.end())
			{
				commandName = i->second.c_str();
			}
		}

		sprintf_s(message, "[REAPER] << Leaving '%s'... (CmdId = %d, Flags = %x)\n",
			((commandName != 0)?commandName : "<Native>"), commandId, flags);
		OutputDebugString(message);
	}
}

BOOL HookCommand2Callback(KbdSectionInfo *pksi, int commandId, int value0, int value1, int mode, HWND hwnd)
{
	if(pfnReverseNamedCommandLookup != 0)
	{
		const size_t MAX_MESSAGE_SIZE = 256;
		CHAR message[MAX_MESSAGE_SIZE + 1] = {0};

		if(commandTexts.empty() == true)
		{
			if(pksi != 0)
			{
				for(int i = 0; i < pksi->action_list_cnt; i++)
				{
					DWORD cmd = pksi->action_list[i].cmd;
					const char* text = pksi->action_list[i].text;
					if(text != 0)
					{
						commandTexts.insert(std::map<int, std::string>::value_type(cmd, text));
					}
				}
			}
		}

		const CHAR* commandName = (*pfnReverseNamedCommandLookup)(commandId);
		if(0 == commandName)
		{
			const std::map<int, std::string>::const_iterator i = commandTexts.find(commandId);
			if(i != commandTexts.end())
			{
				commandName = i->second.c_str();
			}
			else
			{
				if(pksi != 0)
				{
					for(int i = 0; (i < pksi->action_list_cnt) && (0 == commandName); i++)
					{
						DWORD cmd = pksi->action_list[i].cmd;
						if(commandId == cmd)
						{
							commandName = pksi->action_list[i].text;
							commandTexts.insert(std::map<int, std::string>::value_type(commandId, commandName));
						}
					}
				}
			}
		}

		sprintf_s(message, "[REAPER] && Executing '%s'... (CmdId = %d, Value0 = %d, Value1 = %d, Mode = %d, Hwnd = 0x%llx)\n", 
			((commandName != 0)?commandName : "<Native>"), commandId, value0, value1, mode, (UINT_PTR)hwnd);
		OutputDebugString(message);
	}

	return FALSE;
}

