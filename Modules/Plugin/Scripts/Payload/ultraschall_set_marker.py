from reaper_python import *

if (RPR_GetPlayState() == 0) or (RPR_GetPlayState() == 2):  # 0 = Stop, 2 = Pause
  current_position = RPR_GetCursorPosition() # Position of edit-cursor
else:
  current_position = RPR_GetPlayPosition() # Position of play-cursor

RPR_SetTempoTimeSigMarker(0, -1, current_position, -1, -1, -1, 0, 0, True)
