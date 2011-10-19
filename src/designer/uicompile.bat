@echo off

FOR /f "usebackq" %%i in (`Dir /b *.ui`) do (
    C:\Qt\4.5.2\bin\uic.exe %%i > ui_%%~ni%.h
)
