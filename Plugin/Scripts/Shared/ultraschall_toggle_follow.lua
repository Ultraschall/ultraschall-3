--[[
################################################################################
# 
# Copyright (c) 2014-2017 Ultraschall (http://ultraschall.fm)
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# 
################################################################################
]]
 
-- little helpers

local info = debug.getinfo(1,'S');
script_path = info.source:match[[^@?(.*[\/])[^\/]-$]]
dofile(script_path .. "ultraschall_helper_functions.lua")

-- main
followstate = ConsolidateFollowState()


is_new,name,sec,cmd,rel,res,val = reaper.get_action_context()
-- state = reaper.GetToggleCommandStateEx(sec, cmd)                           

if followstate <= 0 then                                                                  
	reaper.SetToggleCommandState(sec, cmd, 1)
	reaper.Main_OnCommand(40036, 0) -- View: Toggle auto-view-scroll during playback
	reaper.Main_OnCommand(40262, 0) -- Toggle auto-view-scroll while recording
	reaper.Main_OnCommand(41817, 0) -- Toggle continuous-scrolling
	runcommand("_BR_FOCUS_ARRANGE_WND")
	reaper.Main_OnCommand(40150,0) -- Got to play position

else
	reaper.SetToggleCommandState(sec, cmd, 0)
	reaper.Main_OnCommand(40036, 0) -- View: Toggle auto-view-scroll during playback
	reaper.Main_OnCommand(40262, 0) -- Toggle auto-view-scroll while recording
	reaper.Main_OnCommand(41817, 0) -- Toggle continuous-scrolling
	runcommand("_BR_FOCUS_ARRANGE_WND")

	
end

ultraschall.GetUSExternalState("ultraschall_follow", "state", followstate)
reaper.SetExtState("ultraschall_follow", "state2", followstate, false)
if followstate==0 then reaper.SetExtState("ultraschall_follow", "started", "started", false) end
reaper.RefreshToolbar2(sec, cmd)

-- Msg(cmd)



