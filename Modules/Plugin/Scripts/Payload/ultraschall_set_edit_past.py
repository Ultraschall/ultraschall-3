from reaper_python import *

if (RPR_GetPlayState() == 0) or (RPR_GetPlayState() == 2):  # 0 = Stop, 2 = Pause
	current_position = RPR_GetCursorPosition() # Position of edit-cursor
else:
	current_position = RPR_GetPlayPosition() # Position of play-cursor

if (current_position > 120):
	past_position = current_position - 120 # set past-marker 2 minutes back in time
else:
	past_position = current_position # ignore for the first 2 minutes

RPR_AddProjectMarker2(0, False, past_position, 0, "_Past", 0, 0x6666aa|0x1000000) # set blue past-marker