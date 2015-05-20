from reaper_python import *

if (RPR_GetPlayState() == 0) or (RPR_GetPlayState() == 2):  # 0 = Stop, 2 = Pause
	current_position = RPR_GetCursorPosition() # Position of edit-cursor
else:
	current_position = RPR_GetPlayPosition() # Position of play-cursor

# Debug RPR_ShowConsoleMsg(RPR_GetPlayState())

RPR_AddProjectMarker2(0, False, current_position, 0, "_Edit", 0, 0xFF0000|0x1000000) # set red edit-marker
