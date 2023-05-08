@echo off
color 0f
if not exist exe\ mkdir exe
if exist exe\raw-input.exe del exe\raw-input.exe

echo Processing raw-input.exe
csc /out:exe\raw-input.exe src\raw-input.cs

if not exist exe\raw-input.exe goto end

echo.
echo Run...
exe\raw-input.exe

:end
echo.