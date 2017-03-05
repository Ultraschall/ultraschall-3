#ifndef __ULTRASCHALL_AGENT_THEME_RESOLVER_INCL_H__
#define __ULTRASCHALL_AGENT_THEME_RESOLVER_INCL_H__

using namespace System;

namespace Ultraschall 
{
public ref class ThemeResolver
{
public:
   static String^ ResolveVersion(String^ path);
};

}

#endif // #ifndef __ULTRASCHALL_AGENT_THEME_RESOLVER_INCL_H__
