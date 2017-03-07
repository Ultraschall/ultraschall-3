-- Grab all of the functions and classes from our GUI library
local info = debug.getinfo(1,'S');
script_path = info.source:match[[^@?(.*[\/])[^\/]-$]]
GUI = dofile(script_path .. "ultraschall_gui_lib.lua")

-- All functions in the GUI library are now contained in the GUI table,
-- so they can be accessed via:          GUI.function(params)

	---- Window settings and user functions ----


GUI.name = "Ultraschall 3"
GUI.w, GUI.h = 680, 415

-- position always in the centre of the screen

l, t, r, b = 0, 0, GUI.w, GUI.h
__, __, screen_w, screen_h = reaper.my_getViewport(l, t, r, b, l, t, r, b, 1)
GUI.x, GUI.y = (screen_w - GUI.w) / 2, (screen_h - GUI.h) / 2



-- Example of a user function that we'll run from a button
function userfunc(str)
		
	gfx.x, gfx.y = GUI.mouse.x, GUI.mouse.y
	gfx.showmenu(str)
	
end

function open_url(url)
  local OS=reaper.GetOS()
  if OS=="OSX32" or OS=="OSX64" then
  	os.execute("open ".. url)
  else
  	os.execute("start ".. url)
  end
end


--[[
	Getting the values of a Checklist's options
]]--
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



	-- body
	---- GUI Elements ----
	
GUI.elms = {
	
--     name          = element type          x      y    w    h     caption               ...other params...
	logo			= GUI.Pic:new(			240,10, 0, 0, 1, script_path.."us.png"),
	label           = GUI.Lbl:new(          165,  160,               "Ultraschall 3.0.2 - Miedinger - was successfully installed.", 0),
	label2           = GUI.Lbl:new(          135,  200,               "Visit the Podcast menu to explore the user interface and features.", 0),
	label3           = GUI.Lbl:new(          210,  220,               "Use Project templates for a quick setup.", 0),

	label4           = GUI.Lbl:new(          265,  290,               "If you need assistance:", 0),
--	label3           = GUI.Lbl:new(          455,  290,               "Visit our support forum:", 0),

	-- pan_sldr      = GUI.Sldr:new(          360, 280, 128,           "Pan:", -100, 100, 200, 4),
--	pan_knb      = GUI.Knob:new(          530, 100, 48,            "Awesomeness", 0, 9, 11, 5, 1),
--	label2           = GUI.Lbl:new(          508,  42,               "Awesomeness", 0),
	-- options      = GUI.OptLst:new(     50,  100, 150, 150, "Color notes by:", "Channel,Pitch,Velocity,Penis Size", 4),
	-- blah           = GUI.OptLst:new(     50,  260, 250, 200, "I have a crush on:", "Justin F,schwa,X-Raym,Jason Brian Merrill,pipelineaudio,Xenakios", 2, 0),
	-- newlist      = GUI.ChkLst:new(     210, 100, 120, 150, "I like to eat:", "Fruit,Veggies,Meat,Dairy", 4),
	checkers      = GUI.Checklist:new(     20, 380, 240, 30,      "", "Show this Screen on Start", 4),
	tutorials      	= GUI.Btn:new(          30, 320, 190, 40,      "Tutorials", open_url, "http://ultraschall.fm/tutorials/"),
	twitter      	= GUI.Btn:new(          242, 320, 190, 40,      "Twitter", open_url, "https://twitter.com/ultraschall_fm"),
	forum      		= GUI.Btn:new(          455, 320, 190, 40,      "Userforum", open_url, "https://sendegate.de/c/ultraschall"),
	-- label4          = GUI.Lbl:new(          300,  400,               "Have fun!", 0),

	 --testbtn2      = GUI.Btn:new(          450, 100, 100, 50,      "CLICK", userfunc, "This|#Is|A|!Menu"),
	-- newtext      = GUI.TxtBox:new(     340, 210, 200, 30,      "Favorite music player:", 4),
		
}


	---- Put all of your own functions and whatever here ----

--Msg("hallo")

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
