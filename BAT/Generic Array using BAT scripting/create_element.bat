@echo off
echo dddd
if %3 equ 1 (
	goto :main1
)else (
	goto:main
)
:main
	set string=%2
	for /f "usebackq tokens=*" %%g in ('%string%') do set string=%%~g
	echo %string% > temp1.txt
	set /a len=0
	for %%g in ( temp1.txt ) do (
		set /a len=%%~zg-3
	)
	set /a %1.length=%len%
	set len=
	del temp1.txt
	set %1=%string%
	set string=
goto:eof
:main1
	set /a %1=%2
	set /a %1.length=1
goto:eof