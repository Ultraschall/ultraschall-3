
"""This module prompts the reaper user to open an osf shownote file.
   It parses the file and creates Empty Timeline items with the shownote text attached
"""

import sys
import codecs
import os.path
import datetime
#import pdb

# Get the Reaper scripts folder and add it to pythons library path
script_path = os.path.join(os.path.expanduser("~"), 'Library', 'Application Support', 'REAPER', 'Scripts')
sys.path.append(script_path)
from sws_python64 import *


__author__ = "Malte Dreschert, Ralf Stockmann"
__copyright__ = "Copyright 2014, Ultraschall"
__credits__ = []
__license__ = "MIT"
__version__ = "0.1"
__maintainer__ = ""
__email__ = ""
__status__ = "Development"


#filepath = os.path.join(os.path.expanduser("~"), 'Desktop', 'freak-show-128.osf')

def getTrackByName(name):
	"""iterate all tracks and find the one with the specified name"""
	for i in range(RPR_GetNumTracks()):
		track = RPR_GetTrack(0, i)
		track_name = RPR_GetSetMediaTrackInfo_String(track, 'P_NAME', None, False)[3]
		if track_name == name:
			return track
		else:
			return None


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
	maxlength = 30 # Standardlänge für Shownotes-Einträge

	for line in lines:

		splitstring = line.strip().split(' ')
		if line == '\n':
			continue
		if line.startswith('-'):
			continue

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


			item = RPR_AddMediaItemToTrack(track)
			RPR_SetMediaItemLength(item, length, False)
			RPR_SetMediaItemPosition(item, position, False)
			ULT_SetMediaItemNote(item, note.encode('ascii', 'replace'))

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
	track = getTrackByName('Shownotes')
	if not track:
		track = createShownoteTrack()

	# call the function that creates the shownote items
	createShownoteItem(lines, starttime, track)

	# update the gui -> does not work right now
	RPR_UpdateArrange()

loadShowNoteFile()
