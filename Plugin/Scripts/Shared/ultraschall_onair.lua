--[[
################################################################################
# 
# Copyright (c) 2014-2016 Ultraschall (http://ultraschall.fm)
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
  
																	-- Print Message to console (debugging)
function Msg(val)
	reaper.ShowConsoleMsg(tostring(val).."\n")
end

reaper.Undo_BeginBlock()

m = reaper.GetMasterTrack(0)										--streaming is always on the master track
fx_name_retval, fx_name = reaper.TrackFX_GetFXName(m, 0, "") 		--get the name of the first effect, debug only
fx_slot = reaper.TrackFX_GetByName(m, "ITSR: StudioLinkLive", 1) 	--get the slot of the StudioLink effect. If there is none: initiate one.

is_new,name,sec,cmd,rel,res,val = reaper.get_action_context()
state = reaper.GetToggleCommandStateEx(sec, cmd)  					--get state of the OnAir Button: on/off

if state == 0 then 													--streaming is off: start streaming
	reaper.SetToggleCommandState(sec, cmd, 1)
	test2 = reaper.TrackFX_SetEnabled(m, fx_slot, true)
else																--streaming is on: stop streaming
	reaper.SetToggleCommandState(sec, cmd, 0)
	test2 = reaper.TrackFX_SetEnabled(m, fx_slot, false)
end     

reaper.RefreshToolbar2(sec, cmd)

reaper.Undo_EndBlock("Ultraschall toggle StudioLink OnAir", -1)
