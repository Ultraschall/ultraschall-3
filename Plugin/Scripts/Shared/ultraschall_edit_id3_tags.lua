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


-- Print Message to console (debugging)
function Msg(val)
  reaper.ShowConsoleMsg(tostring(val).."\n")
end

-- Used to escape "'s by toCSV
function escapeCSV (s)
  if string.find(s, '[,"]') then
    s = '"' .. string.gsub(s, '"', '""') .. '"'
  end
  return s
end

function notes2csv ()
  local csv = ""
  notes = reaper.GetSetProjectNotes(0, false, "")
    for line in notes:gmatch"[^\n]*" do
      csv = csv .. "," .. escapeCSV(line)
    end  
  return string.sub(csv, 2) -- remove first ","
end

function csv2lines (csv)
  csv = string.gsub(csv, ", ", ";") --safe the regular commas. Yes, awkward.
  csv = string.gsub(csv, ",", "\n") -- replace comma with linebreak
  new_notes = string.gsub(csv, ";", ", ") -- back to comma
  -- Msg(new_notes)
  return new_notes
end


dialog_ret_vals = notes2csv() --default values
retval, result = reaper.GetUserInputs("Edit ID3 Podcast Metadata", 6, "Title:,Artist:,Album (Podcast):,Year:,Genre:,Comment:", dialog_ret_vals)
if retval == true then
  Msg(result)
  notes = reaper.GetSetProjectNotes(0, true, csv2lines(result)) -- write new notes
end



