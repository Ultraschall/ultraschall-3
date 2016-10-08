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

#include "ResourceId.h"

namespace ultraschall { namespace framework {

std::atomic<uint32_t> ResourceId::nextId_(0);
   
ResourceId::ResourceId() :
   id_(NextId())
{
}

ResourceId::~ResourceId()
{
   id_ = static_cast<uint32_t>(-1);
}
   
ResourceId::ResourceId(const ResourceId& rhs)
{
   *this = rhs;
}
      
ResourceId& ResourceId::operator=(const ResourceId& rhs)
{
   if(this != &rhs)
   {
      id_ = rhs.id_;
   }
         
   return *this;
}
      
bool ResourceId::operator==(const ResourceId& rhs) const
{
   return rhs.id_ == id_;
}
      
bool ResourceId::operator!=(const ResourceId& rhs) const
{
   return (operator==(rhs) == false);
}
      
bool ResourceId::operator<(const ResourceId& rhs) const
{
   return id_ < rhs.id_;
}
      
ResourceId ResourceId::Invalid()
{
   return ResourceId(static_cast<uint32_t>(-1));
}

uint32_t ResourceId::NextId()
{
   return ++nextId_;
}
      
ResourceId::ResourceId(uint32_t id) :
   id_(id)
{
}

}}

