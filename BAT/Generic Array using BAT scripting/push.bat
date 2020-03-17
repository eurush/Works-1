@echo off
rem setlocal enabledelayedexpansion
goto :add_element
:helper
	call create_element %~1 %~2 %~3
	echo bbbb
goto:eof
:add_element
	set %1[%index%]=%2
	call :helper %1[%index%] %2 %3
	echo aaaa !index!
	set /a index= %index% +1
	rem echo !index!

goto:eof

rem :add_integer
rem 	set /a %1[!index!]=%2
rem 	set /a index=!index!+1
rem goto:eof