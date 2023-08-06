@echo off
cl.exe /Zi ray.cpp  /link SDL2main.lib SDL2.lib "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x64\shell32.lib" /SUBSYSTEM:CONSOLE

start ray.exe