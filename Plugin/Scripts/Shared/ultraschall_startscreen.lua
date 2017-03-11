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

------------------------------------------------------
-- Open an URL in a Browse - OS agnostic
------------------------------------------------------

function open_url(url)
  
  local OS=reaper.GetOS()
  if OS=="OSX32" or OS=="OSX64" then
  	os.execute("open ".. url)
  else
  	os.execute("start ".. url)
  end
end

------------------------------------------------------
--	Getting the values of a Checklist's options
------------------------------------------------------

function check_values()
	
	startscreen = reaper.GetExtState("ultraschall_start", "startscreen")
	startscript_check = GUI.Val("checkers")
	startscript = startscript_check[1]
	
	if startscript == true  and startscreen == "0" then-- ckeckbox is activated
		reaper.SetExtState("ultraschall_start", "startscreen", "1", true)
	elseif startscript == false and startscreen == "1" then-- ckeckbox is deactivated
		reaper.SetExtState("ultraschall_start", "startscreen", "0", true)
	end
end

------------------------------------------------------
--	End of functions
------------------------------------------------------


-- Grab all of the functions and classes from our GUI library

local info = debug.getinfo(1,'S');
script_path = info.source:match[[^@?(.*[\/])[^\/]-$]]
GUI = dofile(script_path .. "ultraschall_gui_lib.lua")

---- Window settings and user functions ----

GUI.name = "Ultraschall 3"
GUI.w, GUI.h = 680, 415

------------------------------------------------------
-- position always in the centre of the screen
------------------------------------------------------

l, t, r, b = 0, 0, GUI.w, GUI.h
__, __, screen_w, screen_h = reaper.my_getViewport(l, t, r, b, l, t, r, b, 1)
GUI.x, GUI.y = (screen_w - GUI.w) / 2, (screen_h - GUI.h) / 2



	-- body
	---- GUI Elements ----
	
GUI.elms = {
	
--     name          = element type          x      y    w    h     caption               ...other params...
	logo			= GUI.Pic:new(			240,10, 0, 0, 1, script_path.."us.png"),
	label           = GUI.Lbl:new(          165,  160,               "Ultraschall 3.0.2 - Miedinger - was successfully installed.", 0),
	label2           = GUI.Lbl:new(          135,  200,               "Visit the Podcast menu to explore the user interface and features.", 0),
	label3           = GUI.Lbl:new(          210,  220,               "Use Project templates for a quick setup.", 0),
	label4           = GUI.Lbl:new(          265,  290,               "If you need assistance:", 0),
	checkers      = GUI.Checklist:new(     20, 380, 240, 30,      "", "Show this Screen on Start", 4),
	tutorials      	= GUI.Btn:new(          30, 320, 190, 40,      "Tutorials", open_url, "http://ultraschall.fm/tutorials/"),
	twitter      	= GUI.Btn:new(          242, 320, 190, 40,      "Twitter", open_url, "https://twitter.com/ultraschall_fm"),
	forum      		= GUI.Btn:new(          455, 320, 190, 40,      "Userforum", open_url, "https://sendegate.de/c/ultraschall"),
		
}


---- Put all of your own functions and whatever here ----

startscreen = reaper.GetExtState("ultraschall_start", "startscreen")
if startscreen == "1" then
	GUI.Val("checkers",true)
end

GUI.func = check_values
GUI.freq = 0


	---- Main loop ----

--[[
	
	If you want to run a function during the update loop, use the variable GUI.func prior to
	starting GUI.Main() loop:
	
	GUI.func = my_function
	GUI.freq = 5     <-- How often in seconds to run the function, so we can avoid clogging up the CPU.
						- Will run once a second if no value is given.
						- Integers only, 0 will run every time.
	
	GUI.Init()
	GUI.Main()
	
]]--

-- local startscreen = GUI.val("checkers")
-- local startscreen = GUI.elms.checkers[GUI.Val()]

GUI.Init()
GUI.Main()
