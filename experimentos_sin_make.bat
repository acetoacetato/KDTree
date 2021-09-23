set dim=%2
set numExp=%1
set cantExp=%3
set cant=%4
set dist=%5


@echo off
for /L %%G IN (1, 1, %cantExp%) DO (
    g++ generaPuntos.cpp Argument_helper/*.cc -o generaPuntos.exe
    .\generaPuntos.exe -m %numExp% -M %dist% -d %dim%
    g++ main3.cpp -O3 -Wno-write-strings -o a.exe
    .\a.exe antiguo insertados %cant%
    .\a.exe nuevo insertados %cant%
)

rundll32 user32.dll,MessageBeep