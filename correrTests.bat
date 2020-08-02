set dim=%2
set numExp=%1
set cantExp=%3
set cant=%4


@echo off
for /L %%G IN (1, 1, %cantExp%) DO make runtest d=%dim% m=%numExp% cant=%cant%

rundll32 user32.dll,MessageBeep