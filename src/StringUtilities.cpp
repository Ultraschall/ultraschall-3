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

#include "StringUtilities.h"
#include <codecvt>

namespace ultraschall { namespace reaper {

UnicodeStringArray UnicodeStringTokenize(const UnicodeString& input, const char delimiter)
{
    UnicodeStringArray tokens;
    std::stringstream  stream(input);
    UnicodeString      token;

    while(std::getline(stream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

// trim from start
UnicodeString& UnicodeStringTrimLeft(UnicodeString& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
UnicodeString& UnicodeStringTrimRight(UnicodeString& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
UnicodeString& UnicodeStringTrim(UnicodeString& s)
{
    return UnicodeStringTrimLeft(UnicodeStringTrimRight(s));
}

void UnicodeStringReplace(UnicodeString& str, const UnicodeString& source, const UnicodeString& target)
{
    size_t start_pos = 0;
    while((start_pos = str.find(source, start_pos)) != UnicodeString::npos)
    {
        str.replace(start_pos, source.length(), target);
        start_pos += target.length();
    }
}

int UnicodeStringToInt(const UnicodeString& str)
{
    int result = -1;

    if(str.empty() == false)
    {
        std::istringstream is(str);
        is >> result;
    }

    return result;
}

UnicodeString UnicodeStringFromInt(const int value)
{
	std::ostringstream os;
    os << value;
    return os.str();
}

UnicodeString StringLowercase(const UnicodeString& str)
{
    UnicodeString convertedString = str;
    if(convertedString.empty() == false)
    {
        std::transform(convertedString.begin(), convertedString.end(), convertedString.begin(), ::tolower);
    }

    return convertedString;
}

UnicodeString StringUppercase(const UnicodeString& str)
{
    UnicodeString convertedString = str;
    if(convertedString.empty() == false)
    {
        std::transform(convertedString.begin(), convertedString.end(), convertedString.begin(), ::toupper);
    }

    return convertedString;
}

struct ULTRASCHALL_TIMESTAMP
{
    uint16_t milliseconds;
    uint8_t  seconds;
    uint8_t  minutes;
    uint8_t  hours;

    ULTRASCHALL_TIMESTAMP() : milliseconds(0xffff), seconds(0xff), minutes(0xff), hours(0xff) {}
};

static bool ValidateTimestamp(const ULTRASCHALL_TIMESTAMP& timestamp)
{
    return (timestamp.milliseconds != 0xffff) && (timestamp.seconds != 0xff) && (timestamp.minutes != 0xff)
           && (timestamp.hours != 0xff);
}

static uint32_t TimestampToMilliseconds(const ULTRASCHALL_TIMESTAMP& ts)
{
    uint32_t ms = ts.hours * 1000 * 60 * 60;
    ms += ts.minutes * 1000 * 60;
    ms += ts.seconds * 1000;
    ms += ts.milliseconds;

    return ms;
}

static double TimestampToSeconds(const ULTRASCHALL_TIMESTAMP& ts)
{
    const uint32_t ms = TimestampToMilliseconds(ts);
    return ((double)ms / (double)1000);
}

static ULTRASCHALL_TIMESTAMP MillisecondsToTimestamp(const uint32_t milliseconds)
{
    ULTRASCHALL_TIMESTAMP ts;

    PRECONDITION_RETURN((milliseconds / (1000 * 60 * 60)) <= UINT8_MAX, ULTRASCHALL_TIMESTAMP());
    ts.hours               = static_cast<uint8_t>(milliseconds / (1000 * 60 * 60));
    const uint32_t minutes = milliseconds % (1000 * 60 * 60);

    PRECONDITION_RETURN((minutes / (1000 * 60)) <= UINT8_MAX, ULTRASCHALL_TIMESTAMP());
    ts.minutes             = static_cast<uint8_t>(minutes / (1000 * 60));
    const uint32_t seconds = minutes % (1000 * 60);

    PRECONDITION_RETURN((seconds / 1000) <= UINT8_MAX, ULTRASCHALL_TIMESTAMP());
    ts.seconds        = static_cast<uint8_t>(seconds / 1000);
    const uint32_t ms = seconds % 1000;

    PRECONDITION_RETURN(ms <= UINT16_MAX, ULTRASCHALL_TIMESTAMP());
    ts.milliseconds = static_cast<uint16_t>(ms);

    return ts;
}

static ULTRASCHALL_TIMESTAMP SecondsToTimestamp(const double seconds)
{
    const uint32_t milliseconds = (uint32_t)(seconds * (double)1000);
    return MillisecondsToTimestamp(milliseconds);
}

UnicodeString TimestampToString(const ULTRASCHALL_TIMESTAMP& timestamp, const bool roundSeconds)
{
    ULTRASCHALL_TIMESTAMP ts = timestamp;

    if(roundSeconds == true)
    {
        if(ts.milliseconds >= 500)
        {
            ts.seconds += 1;
            ts.milliseconds = 0;
        }

        if(ts.seconds >= 60)
        {
            ts.minutes += 1;
        }

        if(ts.minutes >= 60)
        {
            ts.hours += 1;
        }
    }

    std::ostringstream str;
    str << std::setw(2) << std::setfill('0') << (int)ts.hours << ':' << std::setw(2) << std::setfill('0')
        << (int)ts.minutes << ':' << std::setw(2) << std::setfill('0') << (int)ts.seconds;
    if(roundSeconds == false)
    {
        str << '.' << std::setw(3) << std::setfill('0') << (int)ts.milliseconds;
    }

    return str.str();
}

UnicodeString MillisecondsToString(const uint32_t milliseconds, const bool roundSeconds)
{
    ULTRASCHALL_TIMESTAMP timestamp = MillisecondsToTimestamp(milliseconds);
    return TimestampToString(timestamp, roundSeconds);
}

uint16_t StringToUint16(const UnicodeString& str, const int lowerLimit = 0, const int upperLimit = UINT16_MAX)
{
    uint16_t result = 0xffff;

    if(str.empty() == false)
    {
        try
        {
            const int number = std::stoi(str);
            if((number >= lowerLimit) && (number <= upperLimit))
            {
                result = (uint16_t)number;
            }
        }
        catch(std::invalid_argument&)
        {
            result = 0xffff;
        }
    }

    return result;
}

uint8_t StringToUint8(const UnicodeString& str, const int lowerLimit = 0, const int upperLimit = UINT8_MAX)
{
    uint8_t result = 0xff;

    if(str.empty() == false)
    {
        try
        {
            const int number = std::stoi(str);
            if((number >= lowerLimit) && (number <= upperLimit))
            {
                result = (uint8_t)number;
            }
        }
        catch(std::invalid_argument&)
        {
            result = 0xff;
        }
    }

    return result;
}

ULTRASCHALL_TIMESTAMP StringToTimestamp(const UnicodeString& str)
{
    ULTRASCHALL_TIMESTAMP timestamp;

    UnicodeStringArray tokens = UnicodeStringTokenize(str, '.');
    if(tokens.size() > 1)
    {
        timestamp.milliseconds = StringToUint16(tokens[1], 0, 999);
    }
    else
    {
        timestamp.milliseconds = 0;
    }

    if(timestamp.milliseconds != 0xffff)
    {
        timestamp.seconds = 0;
        timestamp.minutes = 0;
        timestamp.hours   = 0;

        tokens = UnicodeStringTokenize(tokens[0], ':');
        if(tokens.size() == 1)
        {
            timestamp.seconds = StringToUint8(tokens[0], 0, 59);
        }
        else if(tokens.size() == 2)
        {
            timestamp.seconds = StringToUint8(tokens[1], 0, 59);
            timestamp.minutes = StringToUint8(tokens[0], 0, 59);
        }
        else if(tokens.size() == 3)
        {
            timestamp.seconds = StringToUint8(tokens[2], 0, 59);
            timestamp.minutes = StringToUint8(tokens[1], 0, 59);
            timestamp.hours   = StringToUint8(tokens[0], 0, 24);
        }
    }

    return timestamp;
}

uint32_t StringToMilliseconds(const UnicodeString& str)
{
    uint32_t result = 0xffffffff;

    const ULTRASCHALL_TIMESTAMP timestamp = StringToTimestamp(str);
    if(ValidateTimestamp(timestamp) == true)
    {
        result = TimestampToMilliseconds(timestamp);
    }

    return result;
}

UnicodeString SecondsToString(const double seconds, const bool roundSeconds)
{
    UnicodeString str = "<Out of range>";

    const double offset = (roundSeconds == true) ? 0.5 : 0;
    if((seconds >= 0) && (seconds < ((60 * 60 * 24) - offset)))
    {
        ULTRASCHALL_TIMESTAMP timestamp = SecondsToTimestamp(seconds);
        str                             = TimestampToString(timestamp, roundSeconds);
    }

    return str;
}

double StringToSeconds(const UnicodeString& str)
{
    double result = -1;

    const ULTRASCHALL_TIMESTAMP timestamp = StringToTimestamp(str);
    if(ValidateTimestamp(timestamp) == true)
    {
        result = TimestampToSeconds(timestamp);
    }

    return result;
}

}} // namespace ultraschall::reaper
