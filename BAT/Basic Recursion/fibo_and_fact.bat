@echo off
setlocal enabledelayedexpansion
goto:main

:fibo 
	if %~1 equ !%~4! (
		goto:eof
	)
	set /a prevhere=!%~3!
	set /a %~3=!%~3!+!%~2!
	set /a %~2=!prevhere!
	set /a %~4=!%~4!+1
	call:fibo %~1 %~2 %~3 %~4

goto:eof

:fact
	if %~1 equ !%~2! (
		set /a %~3=!%~3!*!%~2!
		goto:eof
	)
	set /a %~3=!%~3!*!%~2!
	set /a %~2=!%~2!+1
	call:fact %~1 %~2 %~3 
goto:eof

:main
setlocal
	set /a now=1
	set /a prev=1
	call:fact %1 prev now
	echo factorial of %1 = !now!
	set /a which=1
	set /a now1=1
	set /a prev1=0
	call:fibo %2 prev1 now1 which
	echo %2th fibo number = !now1!
endlocal
goto:eof
