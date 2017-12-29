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

local info = debug.getinfo(1,'S');
script_path = info.source:match[[^@?(.*[\/])[^\/]-$]]
dofile(script_path .. "ultraschall_helper_functions.lua")


-- Zooms out stepwise, until the arrange-view could show the whole project and centers view around it
-- When the editcursor is after the project, the toom will go until the arrange-view could show from 
-- Beginning of the project(position 0) to edit-cursor-position and center that to the arrangeview

steplength = 0.4 -- factor to adjust the steplength of the zoom
max_zoom_factor=1.2 -- project-length (or edit-cursor-position) * max_zoom_factor is the maximum allowed
                    -- zoomout-factor.
                    -- Minimum value is 1.

_,_,_,_,mode,res,val = reaper.get_action_context()
if mode==-1 and res==-1 and val==-1 then val=0 end


val = val * steplength

reaper.adjustZoom(val, 0, false, -1)
start_time, end_time = reaper.GetSet_ArrangeView2(0, false, 0, 0)


if end_time-start_time>(reaper.GetProjectLength()*max_zoom_factor) and reaper.GetCursorPosition()>reaper.GetProjectLength() then 
  if end_time-start_time>(reaper.GetProjectLength()*max_zoom_factor)+reaper.GetCursorPosition() then
    reaper.adjustZoom(val, 1, false, 1)
    reaper.BR_SetArrangeView(0, 0, reaper.GetCursorPosition()*max_zoom_factor)
  else
    start_time, end_time = reaper.GetSet_ArrangeView2(0, false, 0, 0)
    if end_time>reaper.GetCursorPosition() then
      reaper.adjustZoom(val, 1, false, 1)
      reaper.BR_SetArrangeView(0, 0, reaper.GetCursorPosition()*max_zoom_factor)
    end
  end
elseif end_time-start_time>reaper.GetProjectLength()*max_zoom_factor and reaper.GetCursorPosition()<reaper.GetProjectLength() then 
  reaper.adjustZoom(val, 1, false, 1)
  reaper.BR_SetArrangeView(0, 0, reaper.GetProjectLength()*max_zoom_factor) 
end

 reaper.UpdateTimeline()
 reaper.UpdateArrange()
