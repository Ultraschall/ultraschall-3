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

theme_version_now = 20170306 -- version of this theme

-- reaper.SetExtState("ultraschall_versions", "theme", theme_version_now, true)
-- not a godd idea: something went wrong during the installation of the theme, so don't fix but reinstall

error_msg = false

---------------------------------------
-- get data from system key/value store
---------------------------------------

theme_version = reaper.GetExtState("ultraschall_versions", "theme")
plugin_version = reaper.GetExtState("ultraschall_versions", "plugin")
view = tonumber(reaper.GetExtState("ultraschall_gui", "views"))
sec = tonumber(reaper.GetExtState("ultraschall_gui", "sec"))
mouse = tonumber(reaper.GetExtState("ultraschall_mouse", "state"))
first_start = reaper.GetExtState("ultraschall_start", "firststart")
startscreen = reaper.GetExtState("ultraschall_start", "startscreen")


if theme_version ~= tostring(theme_version_now) then 
	error_msg = "Your ULTRASCHALL THEME is out of date. \n\nULTRASCHALL wil NOT work properly until you fix this. \n\nPlease get the latest release on http://ultraschall.fm/install/" 
end

if plugin_version ~= theme_version then -- different versions of theme and plugin isntalled
	error_msg = "There is a configuration mismatch between the ULTRASCHALL THEME ("..theme_version..") and PLUGIN ("..plugin_version..").\n\nULTRASCHALL will NOT work properly until you fix this. \n\nPlease get the latest release on http://ultraschall.fm/install/" 
end

if plugin_version == "" then 
	error_msg = "The ULTRASCHALL PLUGIN was not properly installed.\n\nULTRASCHALL wil NOT work properly until you fix this.\n\nPlease check the installation guide on http://ultraschall.fm/install/" 
end

if theme_version == "" then 
	error_msg = "There are parts of the ULTRASCHALL THEME missing.\n\nULTRASCHALL wil NOT work properly until you fix this.\n\nPlease check the installation guide on http://ultraschall.fm/install/" 
end



if error_msg then
		type = 0
		title = "Ultraschall Configuration Problem"
 		result = reaper.ShowMessageBox( error_msg, title, type )

elseif first_start == "true" or startscreen == "1" then
	start_id = reaper.NamedCommandLookup("_RSc78c66b79c72969f3d554fc9bc414cc8c2c9a89f")
	reaper.Main_OnCommand(start_id,0) 	--Show Startscreen		
end



--------------------------
-- Restore GUI and Buttons
--------------------------

if view then
	reaper.SetToggleCommandState(sec, view, 1)
	reaper.RefreshToolbar2(sec, view)
end

if mouse <= 0 then -- selection is activated
	mouse_id = reaper.NamedCommandLookup("_RS04f578c9a12a05c62111fffb2403eaca640a11a0")
	reaper.SetToggleCommandState(sec, mouse_id, 1)
	reaper.RefreshToolbar2(sec, mouse_id)
end

-- set OnAir button off

reaper.SetToggleCommandState(sec, 55695, 0)


--------------------------
-- Run on every start ----
--------------------------

-- remove StudioLink OnAir FX from Master

m = reaper.GetMasterTrack(0)                                                  --streaming is always on the master track
os = reaper.GetOS()

if string.match(os, "OSX") then 
	fx_slot = reaper.TrackFX_GetByName(m, "ITSR: StudioLinkOnAir", 1)      --get the slot of the StudioLink effect. If there is none: initiate one.
else	-- Windows
	fx_slot = reaper.TrackFX_GetByName(m, "StudioLinkOnAir (IT-Service Sebastian Reimers)", 1)      --get the slot of the StudioLink effect. If there is none: initiate one.
end
reaper.SNM_MoveOrRemoveTrackFX(m, fx_slot, 0)

-- is the ReaperThemeZip loaded? Only then (probably on first start) reload the ReaperTheme to get the colors working 

curtheme = reaper.GetLastColorThemeFile()
if string.find(curtheme, "ReaperThemeZip", 1) then
	themeadress = reaper.GetResourcePath() .. "/ColorThemes/Ultraschall_3.0.ReaperTheme"
	reaper.OpenColorThemeFile(themeadress)
end


--------------------------
-- First start actions
--------------------------

-- not really needed right now, but maybe in coming releases

if first_start == "true" then
	reaper.SetExtState("ultraschall_start", "firststart", "false", true)	-- there will be only one first start
end



