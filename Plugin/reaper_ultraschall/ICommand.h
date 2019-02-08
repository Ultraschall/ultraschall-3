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

#ifndef __ULTRASCHALL_REAPER_COMMAND_H_INCL__
#define __ULTRASCHALL_REAPER_COMMAND_H_INCL__

#include "SharedObject.h"
#include "ServiceStatus.h"

namespace ultraschall { namespace reaper {

class ICommand : public SharedObject
{
public:
    static bool ValidateCommandId(const int32_t id)
    {
        return id != INVALID_COMMAND_ID;
    }

    virtual ServiceStatus StartCommand() = 0;
    virtual ServiceStatus StopCommand()  = 0;

protected:
    ICommand() {}

    virtual ~ICommand() {}

private:
    ICommand(const ICommand&) = delete;
    ICommand& operator=(const ICommand&) = delete;

    static const int32_t INVALID_COMMAND_ID = 0;
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_ICOMMAND_H_INCL__
