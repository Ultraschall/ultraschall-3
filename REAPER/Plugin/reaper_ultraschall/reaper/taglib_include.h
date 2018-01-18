#ifndef __ULTRASCHALL_REAPER_TAG_LIB_H_INCL__
#define __ULTRASCHALL_REAPER_TAG_LIB_H_INCL__

#ifdef ULTRASCHALL_PLATFORM_MACOS
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

#define TAGLIB_STATIC
#include <tstringlist.h>
#include <fileref.h>
#include <tag.h>
#include <tbytevectorlist.h>
#include <tpropertymap.h>

#include <mpegfile.h>
#include <id3v2tag.h>
#include <chapterframe.h>
#include <textidentificationframe.h>
#include <attachedpictureframe.h>
#include <commentsframe.h>
#include <tableofcontentsframe.h>
#include <podcastframe.h>

namespace taglib = TagLib;
namespace mp3 = TagLib::MPEG;
namespace id3v2 = TagLib::ID3v2;

#ifdef ULTRASCHALL_PLATFORM_MACOS
#pragma clang diagnostic pop
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

#endif // #ifndef __ULTRASCHALL_REAPER_TAG_LIB_H_INCL__
