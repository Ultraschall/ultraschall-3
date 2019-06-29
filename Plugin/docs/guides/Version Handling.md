#Ultraschall Setup Checks

## Files that contain version numbers:

### Theme:

---
__startup.lua  (folder: REAPER/Scripts)

`theme_version_now = 20170221 -- version of this theme`

---

version.txt (folder: REAPER/ColorThemes/Ultraschall_2)

`Ultraschall Theme Version: 3.0.170221`

---

reaper-extstate.ini (folder: REAPER, key/value store)

`[ultraschall_versions]`
`plugin=20170221`
`theme=20170221`


---

## Files that perform version checks:

__startup.lua  (folder: REAPER/Scripts)

`plugin_version == theme_version == theme_version_now`