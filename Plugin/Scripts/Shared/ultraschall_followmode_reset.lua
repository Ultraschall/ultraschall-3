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


-- Resets the Followmode, when someone stops the scrolling by moving outside of the current arrange-timerange
-- or by pausing the scrolling.
-- does not stop followmode during zoom in/out, stop/pause of play/rec, jump to end or begin of project

-- it uses the external-state ultraschall_follow->started, which shall signal, if followmode has been enabled.
-- it is for edge-cases, where the scrolling doesn't start immediately(e.g. playcursor isn't in the center of the screen like in
-- the beginning of a project) and shall keep this script from stopping followmode immediately in such cases.
--
-- if that state is set to "started", this script will not stop followmode until a scrolling-movement has been started in the firstplace
-- if the state is set to "recognized", the checking happens that could lead to stopping of the followmode
-- this state is set to "started" by the script "ultraschall_toggle_follow.lua".

count=1  -- as the script has to check the current shown-time in the arrange-view three times,
         -- this count calculates the delay-factor between these three checks
         -- try higher, if it creates false positives
         -- count is the timeframe to check for scrolling in seconds, can be given in float.
         -- minimum value is 0.6, 2 or higher is recommended

if count<0.6 then reaper.MB("Variable \"count\" must be bigger or equal 0.6!","Error",0) return end

        
--initialize the variables
cmdID=reaper.NamedCommandLookup("_Ultraschall_Toggle_Follow") -- Get Command-ID of Follow-Mode-Script

count2= count/3--(math.floor(count/2))-1   -- calculates the second checkpoint-count, in relation to the value-count of "count"
count3= (count/3)*2--(math.floor(count/2)*2)-1 -- calculates the third checkpoint-count, in relation to the value-count of "count"

Start1, End1 = "","" -- first checkpoint
Start2, End2 = "","" -- second checkpoint
Start3, End3 = "","" -- third checkpoint
A=0                  -- counting variable
Zoom=reaper.GetHZoomLevel()
Position_Start=reaper.time_precise()
EditcursorPos=reaper.GetCursorPosition()

function main()
  if reaper.GetExtState("ultraschall_follow", "state2")=="0" and reaper.GetPlayState()~=0 then 
    --A=A+1 -- if followmode is on, start counting the countingvariable A
    if reaper.time_precise()-Position_Start>=0 and reaper.time_precise()-Position_Start<count2 then A=0.1
    elseif reaper.time_precise()-Position_Start>=count2 and reaper.time_precise()-Position_Start<count3 then A=count2
    elseif reaper.time_precise()-Position_Start>=count3 and reaper.time_precise()-Position_Start<count then A=count3
    else
      A=count
    end
    playposition=reaper.GetPlayPosition()
    Editcursor_current=reaper.GetCursorPosition()
    if reaper.GetHZoomLevel()~=Zoom then Zoom=reaper.GetHZoomLevel() 
      -- if user has zoomed in or out, keep followmode rolling by setting external-state ultraschall_follow->started to started
      reaper.SetExtState("ultraschall_follow", "started", "started", false) 
      A=0
      Start1, End1 = "","" -- first checkpoint
      Start2, End2 = "","" -- second checkpoint
      Start3, End3 = "","" -- third checkpoint
    elseif EditcursorPos~=Editcursor_current then
      -- if user changes position of the editcursor(by clicking or moving with arrowkeys), end followmode as
      -- long as the click didn't happen in the ruler.

      window, segment, details = reaper.BR_GetMouseCursorContext()
      mousepos=reaper.BR_GetMouseCursorContext_Position()
      reaper.ClearConsole()
      
      -- Reaper seems to work with greater precision in projecttime than we can use do in Lua, 
      -- so I have to trick it somehow into using lower precision, as otherwise, it will never 
      -- find out, if the mouseposition==editcursor
      mousepos=tostring(mousepos)
      T1=mousepos:match("(.*)%.")
      T2=mousepos:match("%.(.*)")
      mousepos=tonumber(T1.."."..T2:sub(1,7))

      Editcursor_temp=tostring(Editcursor_current)
      T1=Editcursor_temp:match("(.*)%.")
      T2=Editcursor_temp:match("%.(.*)")
      Editcursor_temp=tonumber(T1.."."..T2:sub(1,7))
      
      if window=="arrange" and  Editcursor_temp==mousepos then 
        -- if editcursor got repositioned by clicking somewhere, except the ruler, stop followmode
        -- will have no effect, if the editcursor is moved by something else than the mouse,
        -- as it will check, whether the changed position of the cursor matches the mouse-position
      
         reaper.SetExtState("ultraschall_follow", "started", "started", false)
        reaper.Main_OnCommand(cmdID, 0)
      else
        -- else, keep the followmode going
        reaper.SetExtState("ultraschall_follow", "started", "started", false)
        Start1, End1 = "",""
        Start2, End2 = "",""
        Start3, End3 = "",""
        A=0 
        Position_Start=reaper.time_precise()--]]
      end
      EditcursorPos=reaper.GetCursorPosition()
    elseif A==0.1 then Start1, End1 = reaper.GetSet_ArrangeView2(0, false, 0, 0) -- set first checkpoint
    elseif A==count2 then Start2, End2 = reaper.GetSet_ArrangeView2(0, false, 0, 0) -- set second checkpoint
    elseif A==count3 then Start3, End3 = reaper.GetSet_ArrangeView2(0, false, 0, 0) -- set third checkpoint
    elseif A==count then -- if maximum count has been reached:
      start, ende = reaper.GetSet_ArrangeView2(0, false, 0, 0)
      -- do the checking for retaining or stopping the followmode
      if start==0 and playposition>ende then
        -- if playcursor is outside of arrangeview-timerange and start of arrange-timerange is 0, stop followmode.
        -- workaround for the zoom-out workaround (check the second else-if below this one)
        reaper.Main_OnCommand(cmdID, 0)    
      elseif reaper.GetPlayState()==0 and reaper.GetExtState("ultraschall_follow", "state2")=="0" then 
        -- if play/rec gets stopped (end of project or when hittin the stop-button), retain followmode set to on by
        -- setting external-state ultraschall_follow->started to started
        reaper.SetExtState("ultraschall_follow", "started", "started", false)
      elseif Start1==0 and Start2==0 and Start3== 0 then
        -- if arrange view starts at project-position 0, don't stop when not scrolling. Workaround for zoomout-cases.
        reaper.SetExtState("ultraschall_follow", "started", "started", false)
      elseif Start1==Start2 and Start2==Start2 and End1==End2 and End2==End3 and reaper.GetPlayState()&2==2 and reaper.GetExtState("ultraschall_follow", "started")~="started" then 
        -- if Start and End of all three checkpoints are the same and playstate is(!) paused, assume, the followmode has just been started
        -- setting the external state ultraschall_follow->started to started (as the followmode script does, when started)
        reaper.SetExtState("ultraschall_follow", "started", "started", false)
      elseif (Start1~=Start2 and Start2~=Start3) and reaper.GetPlayState()&2~=2 and reaper.GetExtState("ultraschall_follow", "started")=="started" then 
        -- as soon as the movement of the checkpoints have begun, reset the external state ultraschall_follow->started to recognised, so this script
        -- knows, when to start checking and resetting the FollowMode
        reaper.SetExtState("ultraschall_follow", "started", "recognized", false)
      elseif Start1==Start2 and Start2==Start2 and End1==End2 and End2==End3 and reaper.GetPlayState()&2~=2 and reaper.GetExtState("ultraschall_follow", "started")~="started" then 
        -- if Start and End of all three checkpoints are the same and playstate is not paused, run the followmode-script
        reaper.Main_OnCommand(cmdID, 0)
      elseif playposition==0 and reaper.GetPlayState()~=0 then
        -- edgecase, when position is at 0 and play/rec is not stopped(when using "got to start of project"), reset
        -- the external state ultraschall_follow->started to started (as the followmode script does, when started)
        reaper.SetExtState("ultraschall_follow", "started", "started", false)      
      elseif (playposition<start or playposition>ende) and start~=0.0 and reaper.GetHZoomLevel()<20000 then -- and reaper.GetPlayState()&2~=2 and reaper.GetExtState("ultraschall_follow", "started")=="started" then
        -- when playcursor is outside the timerange of the arrange-window, set followmode to off
        reaper.Main_OnCommand(cmdID, 0)
      elseif playposition>((ende-start)*0.53)+start then --and reaper.GetExtState("ultraschall_follow", "started")~="started" then
        -- if the playcursor is at 53% of the arrangeview(as seen from the left), stop followmode
        reaper.Main_OnCommand(cmdID, 0)
      end
      -- reset variables
      Start1, End1 = "",""
      Start2, End2 = "",""
      Start3, End3 = "",""
      A=0 
      Position_Start=reaper.time_precise()
    end
  elseif A>0 then
    A=0  -- if followmode is off, reset countingvariable A to 0
  else
    EditcursorPos=reaper.GetCursorPosition() -- if followmode is off, get the current position of the editcursor. Otherwise, turning followmode on
                                             -- results in immediate turning off of followmode
  end
  
  reaper.defer(main)
end

main() 
