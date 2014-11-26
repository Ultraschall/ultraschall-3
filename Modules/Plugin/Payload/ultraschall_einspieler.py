# Ultraschall Script by Ralf Stockmann
######################################
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
        # msg(currentName) # debug
        if currentName == "Einspieler":
            RPR_SetOnlyTrackSelected(trackId)  #selektiere nur die Einspieler-Spur
            return
    msg("Es existiert keine Spur mit dem Namen 'Einspieler'")
            
SelectEinspieler() 
