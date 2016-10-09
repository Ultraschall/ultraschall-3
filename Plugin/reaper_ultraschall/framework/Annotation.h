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

#ifndef __ULTRASCHALL_FRAMEWORK_ANNOTATION_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_ANNOTATION_H_INCL__

#include <string>

namespace ultraschall { namespace framework {

class Annotation
{
public:
   inline double Position() const;
   inline const std::string& Name() const;
   inline int Color() const;
   inline int Index() const;

protected:
   Annotation();
   Annotation(const double position, const std::string& name, const int32_t color, const int index = -1);

   inline void Position(const double position);
   inline void Name(const std::string& name);
   inline void Color(const int color);
   inline void Index(const int index);
   
private:
   double position_;
   std::string name_;
   int index_;
   int color_;
};

inline double Annotation::Position() const
{
   return position_;
}

inline void Annotation::Position(const double position)
{
   position_ = position;
}

inline const std::string& Annotation::Name() const
{
   return name_;
}

inline void Annotation::Name(const std::string& name)
{
   name_ = name;
}

inline int Annotation::Index() const
{
   return index_;
}
   
inline void Annotation::Index(const int index)
{
   index_ = index;
}

inline int Annotation::Color() const
{
   return color_;
}

inline void Annotation::Color(const int color)
{
   color_ = color;
}

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_ANNOTATION_H_INCL__

