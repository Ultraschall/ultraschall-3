from reaper_python import *

if (RPR_GetPlayState() == 0) or (RPR_GetPlayState() == 2):  # 0 = Stop, 2 = Pause
	current_position = RPR_GetCursorPosition() # Position of edit-cursor
else:
	current_position = RPR_GetPlayPosition() # Position of play-cursor

markeridxOut = 0
regionidxOut = 0

markerid = RPR_GetLastMarkerAndCurRegion(0, current_position, markeridxOut, regionidxOut) # get the last marker to the left of cursor

## RPR_ShowConsoleMsg(markerid[2])

RPR_DeleteProjectMarkerByIndex(0, markerid[2]) # delete marker [2] is the id