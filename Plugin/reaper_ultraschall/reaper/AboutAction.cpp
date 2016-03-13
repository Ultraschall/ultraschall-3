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

#include <string>
#include <vector>
#include <fstream>

#include <cpr/cpr.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include "ReaperVersionCheck.h"
#include "ThemeVersionCheck.h"
#include "HubVersionCheck.h"
#include "SoundboardVersionCheck.h"
#include "StudioLinkVersionCheck.h"
#include "SWSVersionCheck.h"
#include "AboutAction.h"
#include "MessageBox.h"
#include "About.h"
#include "FileManager.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<AboutAction> action;

const char* AboutAction::UniqueId()
{
   return "ULTRASCHALL_ABOUT_ULTRASCHALL";
}

const ServiceStatus AboutAction::Execute()
{
#if 1
   std::string message1 = "\
http://ultraschall.fm\r\n\r\n\
Copyright (c) 2016 Ralf Stockmann, Daniel Lindenfelser, Katrin Leinweber, Andreas Pieper, Tim Pritlove, Heiko Panjas\r\n\r\n\
Ultraschall REAPER Extension " + QueryPluginVersion() + "\r\n";

   const std::string themeVersion = QueryThemeVersion();
   if(themeVersion.empty() == false)
   {
      message1 += "Ultraschall REAPER Theme " + themeVersion + "\r\n";
   }

#ifndef WIN32
   const std::string hubVersion = QueryHubVersion();
   if(hubVersion.empty() == false)
   {
      message1 += hubVersion + "\r\n";
   }
#endif // #ifndef WIN32

   const std::string soundboardVersion = QuerySoundboardVersion();
   if(soundboardVersion.empty() == false)
   {
      message1 += "Ultraschall Soundboard " + soundboardVersion + "\r\n";
   }

   const std::string studioLinkVersion = QueryStudioLinkVersion();
   if(studioLinkVersion.empty() == false)
   {
       message1 += "StudioLink Plug-in " + studioLinkVersion + "\r\n";
   }

   std::string message2 = "\
SWS REAPER Extension " + QuerySWSVersion() + "\r\n\
REAPER ";

   message2 += QueryReaperVersion();
   message2 += "\r\n";

   NotificationWindow::Show("About Ultraschall \"Gropius\"...", message1 + message2);
#else
   ShowAbout();
#endif
   return SERVICE_SUCCESS;
}

std::string AboutAction::QueryPluginVersion()
{
#ifdef WIN32
    const std::string path = FileManager::ProgramFilesDirectory() + "\\REAPER (x64)\\Plugins\\reaper_ultraschall.dll";
    return FileManager::ReadVersionFromFile(path);
#else
    return "2.2";
#endif // #ifdef WIN32
}
  
const void AboutAction::VersionCheck()
{
  auto future_text = cpr::GetCallback([](cpr::Response r) {
    if (!r.error && r.status_code == 200) {
      xmlInitParser();
      xmlDocPtr doc;
      xmlXPathContextPtr xpathCtx;
      xmlXPathObjectPtr xpathObj;
      xmlNodeSetPtr nodeset;
      xmlChar *textContent;

      doc = xmlParseDoc((xmlChar *)r.text.c_str());
      if (doc == NULL) {
        return;
      }
      
      xpathCtx = xmlXPathNewContext(doc);
      if(xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return;
      }
      
      const xmlChar* ns = (xmlChar *)"sparkle";
      const xmlChar* href = (xmlChar *)"http://www.andymatuschak.org/xml-namespaces/sparkle";
      
      if(xmlXPathRegisterNs(xpathCtx, ns, href) != 0) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return;
      }
      
      xpathObj = xmlXPathEvalExpression((xmlChar*)"//channel/item/enclosure/@sparkle:version", xpathCtx);
      if(xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return;
      }
      nodeset = xpathObj->nodesetval;
      const std::string net_version((char*)nodeset->nodeTab[0]->children[0].content);

      xpathObj = xmlXPathEvalExpression((xmlChar*)"//channel/item/description", xpathCtx);
      if(xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return;
      }
      nodeset = xpathObj->nodesetval;

      textContent = xmlNodeListGetString(doc, nodeset->nodeTab[0]->xmlChildrenNode, 1);
      std::string html_info((char*) textContent);
      xmlFree(textContent);

      xmlXPathFreeObject(xpathObj);
      xmlXPathFreeContext(xpathCtx);
      xmlFreeDoc(doc);
      xmlCleanupParser();
      
      const std::string local_version = QueryPluginVersion();
      if (local_version.compare(net_version) != 0) {
        NotificationWindow::ShowUpdateAvailable("Ultraschall Version Check", "Version " + net_version + " of Ultraschall is available.\nYou are currently running version " + local_version, html_info);
      }
    }
  }, cpr::Url{"https://raw.githubusercontent.com/Ultraschall/REAPER/version_check/ultraschall_version.xml"});
}


}}
