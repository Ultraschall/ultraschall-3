################################################################################
# 
# Copyright (c) 2014-2015 Ultraschall (http://ultraschall.fm)
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

from reaper_python import *

if (RPR_GetPlayState() == 0) or (RPR_GetPlayState() == 2):  # 0 = Stop, 2 = Pause
	current_position = RPR_GetCursorPosition() # Position of edit-cursor
else:
	current_position = RPR_GetPlayPosition() # Position of play-cursor

markeridxOut = 0
regionidxOut = 0

markerid = RPR_GetLastMarkerAndCurRegion(0, current_position, markeridxOut, regionidxOut) # get the last marker to the left of cursor

RPR_DeleteProjectMarkerByIndex(0, markerid[2]) # delete marker [2] is the id
