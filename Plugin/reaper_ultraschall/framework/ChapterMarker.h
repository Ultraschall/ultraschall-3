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

#ifndef __ULTRASCHALL_REAPER_CHAPTER_MARKER_H_INCL__
#define __ULTRASCHALL_REAPER_CHAPTER_MARKER_H_INCL__

#include <string>

namespace ultraschall { namespace framework {

class ChapterMarker
{
public:
   ChapterMarker(const double position, const std::string& name, const int index = -1);
   ChapterMarker(const double position, const double endOfRegion, const std::string& name, const int index = -1);
   virtual ~ChapterMarker()
   {
   }

   inline bool IsRegion() const;
   inline double Position() const;
   inline double EndOfRegion() const;
   inline const std::string& Name() const;
   inline int Index() const;

protected:
   inline void IsRegion(const bool isRegion);
   inline void Position(const double position);
   inline void EndOfRegion(const double endOfRegion);
   inline void Name(const std::string& name);
   inline void Index(const int index);
   
private:
   bool isRegion_;
   double position_;
   double endOfRegion_;
   std::string name_;
   int index_;
};

inline bool ChapterMarker::IsRegion() const
{
   return isRegion_;
}

inline void ChapterMarker::IsRegion(const bool isRegion)
{
   isRegion_ = isRegion;
}

inline double ChapterMarker::Position() const
{
   return position_;
}

inline void ChapterMarker::Position(const double position)
{
   position_ = position;
}

inline double ChapterMarker::EndOfRegion() const
{
   return endOfRegion_;
}

inline void ChapterMarker::EndOfRegion(const double endOfRegion)
{
   endOfRegion_ = endOfRegion;
}

inline const std::string& ChapterMarker::Name() const
{
   return name_;
}

inline void ChapterMarker::Name(const std::string& name)
{
   name_ = name;
}

inline int ChapterMarker::Index() const
{
   return index_;
}
   
inline void ChapterMarker::Index(const int index)
{
   index_ = index;
}
   
}}

#endif // #ifndef __ULTRASCHALL_REAPER_CHAPTER_MARKER_H_INCL__

