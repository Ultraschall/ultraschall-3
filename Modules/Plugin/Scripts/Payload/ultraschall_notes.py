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
 
# Modify these to suit your needs
suffix_list = [".aif", ".aiff", ".bwf", ".flac", ".kar", ".mid", ".mp2", ".mp3", ".ogg", ".wav", ".w64"]
prefix_list = ["*"]
clean_white_space = True
Verbose = True
 
def clean_name(name, check_list, suffix = True):
    New_Name = ""
    lower_name = name.lower() # handle all cases
    for item in check_list:
        if suffix:
            if lower_name.endswith(item):
                New_Name = name[:-len(item)]
                return (True, New_Name)
        else:
            if lower_name.startswith(item):
                New_Name = name[len(item):]
                return (True, New_Name)
    return (False, name)
 
# Get number of media items in current project
Item_Count = RPR_CountMediaItems(0)
# Scan each item in project
Item_Index = 0
Found = 0
if Verbose:
    RPR_ShowConsoleMsg("Checking {0} item(s)\n".format(Item_Count))
 
while Item_Index < Item_Count: ###############################################
    Item_ID = RPR_GetMediaItem(0, Item_Index)
    Current_Take = RPR_GetMediaItemInfo_Value(Item_ID, "I_CURTAKE") # Get active take index for current item
    Take_ID = RPR_GetMediaItemTake(Item_ID, int(Current_Take)); 
    Take_Name = RPR_GetSetMediaItemTakeInfo_String(Take_ID, "g_mediaItemNote", "", 0)[3] # Get active take name
	RPR_ShowConsoleMsg(Take_Name)
    Old_Name = Take_Name
    (removed_suffix, Take_Name) = clean_name(Take_Name, suffix_list, suffix = True)
    (removed_prefix, Take_Name) = clean_name(Take_Name, prefix_list, suffix = False)
    removed_white_space = False
    if clean_white_space:
        New_Name = Take_Name.strip()
        if len(New_Name) != len(Take_Name):
            Take_Name = New_Name
            removed_white_space = True
 
    if removed_suffix or removed_prefix or removed_white_space: # Rename active take if changed
        Found = Found + 1
        RPR_GetSetMediaItemTakeInfo_String(Take_ID, "g_mediaItemNote", Take_Name, 1) 
        if Verbose:
            Msg = "Item {0} of {1}: Converted '{2}' to '{3}'\n".format(Item_Index + 1, Item_Count, Old_Name, Take_Name)
            RPR_ShowConsoleMsg(Msg)
    Item_Index = Item_Index + 1;
 
if Verbose:
    RPR_ShowConsoleMsg(str(Found) + " item(s) cleaned\n")
    