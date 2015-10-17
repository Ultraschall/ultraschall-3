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

"""This module prompts the reaper user to open an osf shownote file.
   It parses the file and creates Empty Timeline items with the shownote text attached
"""
import os
import sys
import codecs
import os.path
import datetime
from ctypes import *

import ultraschall_functions as ULT

# Get the Reaper scripts folder and add it to pythons library path
script_path = os.path.join(os.path.expanduser("~"), 'Library', 'Application Support', 'REAPER', 'Scripts')
sys.path.append(script_path)
from sws_python64 import *

def createShownoteTrack():
	"""create the shownote track"""
	RPR_InsertTrackAtIndex(RPR_GetNumTracks() + 1, True)
	RPR_UpdateArrange()
	track = RPR_GetTrack(0, RPR_GetNumTracks()-1)
	RPR_GetSetMediaTrackInfo_String(track, 'P_NAME', 'Shownotes', True)
	return track


def createShownoteItem(lines, starttime, track):
	"""iterate the shownote content and create shownote items on the track
	   for the moment I omit the shownotes starting with '-'
	"""

	lastposition = None
	maxlength = 30 # default length of shownote entries
	concat_string = ''

	for line in lines:

		splitstring = line.strip().split(' ')

		# This line has no information
		if line == '\n':
			continue

		# notes on this line need to be put on the same note as the last one
		if line.startswith('-'):
			note = ' '.join(splitstring[1:len(splitstring)])
			concat_string = concat_string + "\n-------------------------------------\n"
			concat_string = concat_string + note


		if not line.startswith('-'):
			timestamp = datetime.datetime.fromtimestamp(int(splitstring[0]))
			position = (timestamp-starttime).total_seconds()

			if lastposition == None:
				length = maxlength
			else:
				length = (lastposition-timestamp).total_seconds()
				if length > maxlength: # es folgt im maxlenght Abstand kein neuer Eintrag
					length = maxlength

			lastposition = timestamp

			note = ' '.join(splitstring[1:len(splitstring)])

			if concat_string != '':
				note = note + concat_string
				concat_string = ''

			item = RPR_AddMediaItemToTrack(track)
			RPR_SetMediaItemLength(item, length, False)
			RPR_SetMediaItemPosition(item, position, False)
			ULT_SetMediaItemNote(item, note.encode('ascii', 'replace'))
			#buffer = create_unicode_buffer(note)
			#ULT_SetMediaItemNote(item, buffer.value)

def loadShowNoteFile():
	"""new main function. used to bail out if the user cancels the import request"""


	# Show the open file dialog. 
	selected_file_tuple = RPR_GetUserFileNameForRead(None, 'Select Shownote file to import', 'osf')
	filepath = None
	if(selected_file_tuple[0] == 0):
		return
	else:
		filepath = selected_file_tuple[1]


	# open the file and read the content into an arrayreap
	with codecs.open(filepath, 'r', encoding='utf-8') as f:
		lines = f.readlines()[15:]

	# get the first starttime. This is our 0 time
	starttime = datetime.datetime.fromtimestamp(int(lines[0].split(' ')[0]))

	# we start at the end to have the length information available
	lines.reverse()

	# check if there is a shownote track. If not create one
	track = ULT.getTrackByName('Shownotes')
	if not track:
		track = createShownoteTrack()

	# call the function that creates the shownote items
	createShownoteItem(lines, starttime, track)

	# update the gui -> does not work right now
	RPR_UpdateArrange()

loadShowNoteFile()
