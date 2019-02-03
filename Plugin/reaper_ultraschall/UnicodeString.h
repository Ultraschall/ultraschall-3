#ifndef __ULTRASCHALL_FRAMEWORK_UNICODE_STRING_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_UNICODE_STRING_H_INCL__

#include <map>
#include <string>
#include <vector>
namespace ultraschall { namespace reaper {

typedef char     UnicodeChar;
typedef char16_t WideUnicodeChar;

typedef std::string    UnicodeString;
typedef std::u16string WideUnicodeString;

typedef std::vector<UnicodeString>             UnicodeStringArray;
typedef std::map<UnicodeString, UnicodeString> UnicodeStringDictionary;

typedef std::vector<WideUnicodeString>                 WideUnicodeStringArray;
typedef std::map<WideUnicodeString, WideUnicodeString> WideUnicodeStringDictionary;

typedef enum { NO_UTF16_BOM = 0, WITH_UTF16_BOM_LE = 1, WITH_UTF16_BOM_BE = 2 } UTF16_BOM_SPEC;
static const char16_t* UTF16_BOM_LE = u"\xfffe"; // intel
static const char16_t* UTF16_BOM_BE = u"\xfeff";

WideUnicodeString UnicodeStringToWideUnicodeString(
    const UnicodeString& uncodeString, const UTF16_BOM_SPEC bomSpec = NO_UTF16_BOM);

typedef enum { NO_UTF8_BOM = 0, WITH_UTF8_BOM = 1 } UTF8_BOM_SPEC;
static const char* UTF8_BOM = "\xef\xbb\xbf";

UnicodeString WideUnicodeStringToUnicodeString(
    const WideUnicodeString& wideUnicodeString, const UTF8_BOM_SPEC bomSpec = NO_UTF8_BOM);

UnicodeString HostStringToUnicodeString(const std::string& hostString, const UTF8_BOM_SPEC bomSpec = NO_UTF8_BOM);

WideUnicodeString HostStringToWideUnicodeString(
    const std::string& hostString, const UTF16_BOM_SPEC bomSpec = NO_UTF16_BOM);

std::string UnicodeStringToHostString(const UnicodeString& unicodeString);
std::string WideUnicodeStringToHostString(const WideUnicodeString& wideUnicodeString);

#define H2U(a) HostStringToUnicodeString((a))
#define H2WU(a) HostStringToWideUnicodeString((a))

#define U2H(a) UnicodeStringToHostString((a))
#define WU2H(a) WideUnicodeStringToHostString((a))

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_UNICODE_STRING_H_INCL__
