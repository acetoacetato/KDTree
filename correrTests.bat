set dim=%2
set cant=%1
set cantExp=%3

@echo off
for /L %%G IN (1, 1, %cantExp%) DO make runtest d=%dim% m=%cant%