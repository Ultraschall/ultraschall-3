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


--Ultraschall ultraclock alpha 0.5

width=400
height=300
refresh= 0.5 --in seconds

--text positions y (0-1)
line1=0.1
--line2=0.35
line3=0.51
line4=0.62

function InitGFX()
  --set font depending on os
  if reaper.GetOS()=="OSX64" or osname=="OSX32" then
    clockfont="Helvetica" clockfont_bold="Helvetica Bold"
    font_divisor=3.2 --window height / font_divisor = fontsize
  elseif reaper.GetOS()=="Win64" or osname=="Win32" then
    clockfont="Arial" clockfont_bold="Arial"
    font_divisor=2.8 --window height / font_divisor = fontsize
  else clockfont="Arial" clockfont_bold="Arial"
  end
  
  gfx.clear=0x333333 --background color
  gfx.init("Ultraclock",width,height,1) --create window
  gfx.dock( 1 + 256*4) -- dock it do docker 4 (&1=docked)
  gfx.update()
end

function WriteCenteredText(text, color, font, size, y) -- if y=-1 then center horizontaly
  gfx.r=(color & 0xff0000) / 0xffffff
  gfx.g=(color & 0x00ff00) / 0xffff
  gfx.b=(color & 0x0000ff) / 0xff  
  gfx.setfont(1, font, size)
  w,h=gfx.measurestr(text)
  if y<0 then y=(gfx.h-h)/2 end -- center if y<0
  gfx.x=(gfx.w-w)/2
  gfx.y=y 
  gfx.drawstr(text)
end

function get_position()
    playstate=reaper.GetPlayState() --0 stop, 1 play, 2 pause, 4 rec possible to combine bits
    if playstate==1 or playstate==5 then return reaper.GetPlayPosition()
    else return reaper.GetCursorPosition() end
end

function exit_clock()
  gfx.quit()
end

function MainLoop()
  if reaper.time_precise() > lasttime+refresh or gfx.w~=lastw or gfx.h~=lasth then   --redraw screen if size has changed or time is up
    
    --define status text and color for timecode
    playstate=reaper.GetPlayState()
    if reaper.GetSetRepeat(-1)==1 then repeat_txt=" (REPEAT)" else repeat_txt="" end
    if playstate == 1 then
      if repeat_txt~="" then txt_color=0x15729d else txt_color=0x2092c7 end 
      status="PLAY"..repeat_txt --play
      elseif playstate == 5 then txt_color=0xf24949 status="REC" --record
      elseif playstate == 2 then 
        if repeat_txt~="" then txt_color=0xa86010 else txt_color=0xd17814 end
        status="PAUSE"..repeat_txt --play/pause
      elseif playstate == 6 then txt_color=0xff6b4d status="REC/PAUSE" --record/pause
      elseif playstate == 0 then txt_color=0xb3b3b3 status="STOP" --record/pause  
      else txt_color=0xb3b3b3 status=""
    end
    
    pos=get_position()//1
    pos=string.format("%02d:%02d:%02d",pos//3600,(pos %3600) // 60,pos % 60)
   
    -- calculate fontsize and textpositions depending on aspect ratio of window
    if gfx.w/gfx.h < 4/3 then -- if narrower than 4:3 add empty space on top and bottom
      fsize=gfx.w/4*3/font_divisor
      border=(gfx.h-gfx.w/4*3)/2
      y1=gfx.w/4*3*line1 + border
      --y2=gfx.w/4*3*line2 + border
      y3=gfx.w/4*3*line3 + border
      y4=gfx.w/4*3*line4 + border
    else  
      fsize=gfx.h/font_divisor
      y1=gfx.h*line1
      --y2=gfx.h*line2
      y3=gfx.h*line3
      y4=gfx.h*line4
    end
    fsize2=fsize*0.3  
    fsize3=fsize*0.3
    fsize4=fsize
    
    --write text
    WriteCenteredText(os.date("%H:%M:%S"),0xb3b3b3, clockfont_bold, fsize,y1) -- print realtime hh:mm:ss  
    --WriteCenteredText(os.date("(%d.%m.%Y)"),0xb3b3b3, clockfont, fsize2,y2) -- print realtime hh:mm:ss
    WriteCenteredText(status,txt_color, clockfont_bold, fsize3,y3) -- print Status (Pause/Play...)
    WriteCenteredText(pos, txt_color, clockfont_bold, fsize4,y4) --print timecode in h:mm:ss format

    lasttime=reaper.time_precise()
  end

  count, view = ultraschall.GetUSExternalState("ultraschall_gui", "view") -- get the actual view

  if view ~= "record" then  -- terminate clock in al views but recording
    exit_clock()
    do return end
  end

  --loop if GUI is NOT closed
  if gfx.getchar() ~= -1 then 
    lastw=gfx.w
    lasth=gfx.h
    gfx.update()
    reaper.defer(MainLoop)
  end
end



reaper.atexit(exit_clock)
InitGFX()
lasttime=reaper.time_precise()-1
reaper.defer(MainLoop)
