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


function Msg(val)
	reaper.ShowConsoleMsg(tostring(val).."\n")
end

-- Grab all of the functions and classes from our GUI library
local info = debug.getinfo(1,'S');
script_path = info.source:match[[^@?(.*[\/])[^\/]-$]]
GUI = dofile(script_path .. "ultraschall_gui_lib.lua")

-- All functions in the GUI library are now contained in the GUI table,
-- so they can be accessed via:          GUI.function(params)

	---- Window settings and user functions ----


GUI.name = "Ultraschall Export Assistant"
GUI.x, GUI.y, GUI.w, GUI.h = 200, 200, 660, 440


function runcommand(cmd)

	start_id = reaper.NamedCommandLookup(cmd)
	reaper.Main_OnCommand(start_id,0) 	--Show Startscreen	

end



--

y_offset = -30  -- move all content up/down



	-- body
	---- GUI Elements ----
	
GUI.elms = {
	
--     name          = element type          x      y    w    h     caption               ...other params...
	-- logo			= GUI.Pic:new(			474,278, 0, 0, 0.5, script_path.."us.png"),
	label           = GUI.Lbl:new(          50,  120+y_offset,               "Export MP3\nRender your Podcast to a MP3 File.\n\n\nChapter Markers\nYou may take a final look at your chapter markers.\n\n\nID3 Metadata\nUse the ID3 Editor to add metadata to your podcast.\n\n\nPodcast Image\nJust put a square .jpg, .jpeg or .png image\nwith the same name as your project file (.RPP)\nin the project folder.\n\n\nFinalize MP3\nHit the button and select your MP3 to finalize it\nwith metadata, chapters and episode image!", 0),
	label2           = GUI.Lbl:new(          30,  120+y_offset,               "1.\n\n\n\n2.\n\n\n\n3.\n\n\n\n4.\n\n\n\n\n\n5.", 0),
	label3           = GUI.Lbl:new(          30,  70+y_offset,               "Follow these simple steps:", 0),

--	label4           = GUI.Lbl:new(          265,  290,               "If you need assistance:", 0),
--	label3           = GUI.Lbl:new(          455,  290,               "Visit our support forum:", 0),

	-- pan_sldr      = GUI.Sldr:new(          360, 280, 128,           "Pan:", -100, 100, 200, 4),
--	pan_knb      = GUI.Knob:new(          530, 100, 48,            "Awesomeness", 0, 9, 11, 5, 1),
--	label2           = GUI.Lbl:new(          508,  42,               "Awesomeness", 0),
	-- options      = GUI.OptLst:new(     50,  100, 150, 150, "Color notes by:", "Channel,Pitch,Velocity,Penis Size", 4),
	-- blah           = GUI.OptLst:new(     50,  260, 250, 200, "I have a crush on:", "Justin F,schwa,X-Raym,Jason Brian Merrill,pipelineaudio,Xenakios", 2, 0),
	-- newlist      = GUI.ChkLst:new(     210, 100, 120, 150, "I like to eat:", "Fruit,Veggies,Meat,Dairy", 4),
	-- checkers      = GUI.Checklist:new(     20, 380, 240, 30,      "", "Show this Screen on Start", 4),
	export      	= GUI.Btn:new(          430, 120+y_offset, 190, 40,      "Export MP3", runcommand, "_3fd5566413d8497486c9981b4bb963e8"),
	chapters      	= GUI.Btn:new(          430, 185+y_offset, 190, 40,      "View Chapters", runcommand, "_SWSMARKERLIST1"),
	metadata      	= GUI.Btn:new(          430, 250+y_offset, 190, 40,      "Edit ID3V2 Metadata", runcommand, "_RSd0ee00a4ab7a2619e32ba3a9d27e1786123274da"),
	image      		= GUI.Btn:new(          430, 315+y_offset, 190, 40,      "Open Project Folder", runcommand, "_RS410ef7587f335d359f2df776d1e58b01ca7443bc"),
	finalize      	= GUI.Btn:new(          430, 412+y_offset, 190, 40,      "Finalize MP3!", runcommand, "_ULTRASCHALL_INSERT_MP3_CHAPTER_MARKERS"),
	-- label4          = GUI.Lbl:new(          300,  400,               "Have fun!", 0),

	 --testbtn2      = GUI.Btn:new(          450, 100, 100, 50,      "CLICK", userfunc, "This|#Is|A|!Menu"),
	-- newtext      = GUI.TxtBox:new(     340, 210, 200, 30,      "Favorite music player:", 4),
		
}


	---- Put all of your own functions and whatever here ----

--Msg("hallo")



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
