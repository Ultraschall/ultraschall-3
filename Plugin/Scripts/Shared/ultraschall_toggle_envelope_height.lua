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

-- Toggle height of all envelopes.
-- Toggles between minimum height and the default-compactible-height of Reaper.
-- Has no effect, if there's no envelope in the project

local info = debug.getinfo(1,'S');
script_path = info.source:match[[^@?(.*[\/])[^\/]-$]]
dofile(script_path .. "ultraschall_helper_functions.lua")

-- now, we set the minimum height of all envelopes in the project
-- set to nil, to use the user settings instead
  defheight=24

-------------------------------------
--reaper.Undo_BeginBlock() -- Begining of the undo block. Leave it at the top of your main function.
-------------------------------------

--get all current envelopes
  TEnvAr, CountTracks, FstTrack, MstTrack=ultraschall.GetAllTrackEnvelopes()


-- now we check the first trackenvelope(either from a track or master-track), if it is compacted or not
-- this will be the basis for setting all other envelope's-compactible states

  if FstTrack>-1 then TrackEnvelope=TEnvAr[FstTrack][1][0] -- if there's a track with envelope, use that one
  elseif MstTrack>-1 then TrackEnvelope=TEnvAr[MstTrack][1][0] -- if there's envelope in master track, use that one
  else TrackEnvelope=nil -- if there's none, use none
  end
  if TrackEnvelope==nil then return end -- end script, when there's no envelope
  
  retval, str = reaper.GetEnvelopeStateChunk(TrackEnvelope, "", false) -- get statechunk of first envelope in the project
  compacted=str:match("LANEHEIGHT .- (.-)%c") -- get compacted-state of first envelope in the project
  
-- now, we do the toggling
  if compacted=="0" then compacted="1"
  else compacted="0"
  end  
  
-- now, we set the height, as well as the compactible state of all envelope-tracks
  for i=0, CountTracks do
    for a=0, TEnvAr[i][0] do
      retval, str = reaper.GetEnvelopeStateChunk(TEnvAr[i][1][a], "", false) -- get envelopestatechunk

      -- get settings, we don't want to change
      part1=str:match("(.-)LANE")
      part2=str:match("LANEHEIGHT.-%c(.*)")

      -- set height
      if defheight==nil then height=str:match("LANEHEIGHT (.-) .-%c")
      else height=defheight
      end

      newstr=part1.."LANEHEIGHT "..height.." "..compacted.."\n"..part2 -- insert new height and compacted-state
      retval, str2 = reaper.SetEnvelopeStateChunk(TEnvAr[i][1][a], newstr, false) -- set envelope to new settings
    end
  end

-------------------------------------
--reaper.Undo_EndBlock("Ultraschall Toggle Envelope Height", -1) -- End of the undo block. Leave it at the bottom of your main function.
-------------------------------------

