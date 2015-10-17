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

# Selektiere nur die Einspielerspur, gib eine Fehlermeldung aus wenn es keine gibt

from reaper_python import *

def msg(m):
    RPR_ShowConsoleMsg(str(m) + "\n") # Ausgabe

def SelectEinspieler():
    trackCount = RPR_CountTracks(0) # Anzahl der Tracks im Projekt
    if trackCount < 1: # noch komplett leer
        msg("Es sind noch keine Spuren angelegt.")
        return
    for i in range(trackCount): # gehe alle Tracks durch
        trackId = RPR_GetTrack(0, i) # die Track-ID muss bekannt sein
        currentName = str(RPR_GetSetMediaTrackInfo_String(trackId, "P_NAME", "", 0)[3]) # Name zur TrackID
        if currentName == "Einspieler":
            RPR_SetOnlyTrackSelected(trackId)  #selektiere nur die Einspieler-Spur
            return
    msg("Es existiert keine Spur mit dem Namen 'Einspieler'")
            
SelectEinspieler() 
