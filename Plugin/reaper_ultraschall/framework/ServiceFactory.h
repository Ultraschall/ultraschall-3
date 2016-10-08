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

#ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_FACTORY_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_SERVICE_FACTORY_H_INCL__

#include <string>
#include <mutex>
#include <map>

#include <IService.h>

namespace ultraschall { namespace framework {

class ServiceFactory
{
public:
   ServiceFactory();
   virtual ~ServiceFactory();

   typedef ServiceStatus (*CREATE_SERVICE_FUNCTION)(IService*&);
   ServiceStatus RegisterService(const std::string& name, const CREATE_SERVICE_FUNCTION pfn);
   void UnregisterService(const std::string& name);
   void UnregisterAllServices();

   ServiceStatus CreateService(const std::string& name, IService*& pService) const;

private:
   ServiceFactory(const ServiceFactory&);
   ServiceFactory& operator=(const ServiceFactory&);

   typedef std::map<std::string, CREATE_SERVICE_FUNCTION> FunctionDictionary;
   FunctionDictionary functions_;
   mutable std::recursive_mutex functionsLock_;
};

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_FACTORY_H_INCL__
