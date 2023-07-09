@echo off
set solutionDir=%~dp0

echo Running post-build

set extName=GMSDLL
set dllName=GMSDLL
set gmlDir14=%solutionDir%GMSDLL.gmx
set gmlDir22=%solutionDir%GMSDLL_yy
set gmlDir23=%solutionDir%GMSDLL_23
set ext14=%gmlDir14%\extensions\%extName%
set ext22=%gmlDir22%\extensions\%extName%
set ext23=%gmlDir23%\extensions\%extName%
set gmlPath=%ext23%\*.gml
set jsPath=%ext23%\*.js
set docName=%extName%.html
set docPath=%solutionDir%export\%docName%

echo Copying documentation...
copy /Y %docPath% %gmlDir23%\datafiles\%docName%
copy /Y %docPath% %gmlDir22%\datafiles\%docName%
copy /Y %docPath% %gmlDir14%\datafiles\%docName%

where /q gmxgen
if %ERRORLEVEL% EQU 0 (
	
	echo Running GmxGen...
	
	gmxgen "%ext23%\%extName%.yy"

	gmxgen "%ext22%\%extName%.yy" ^
	--copy "%jsPath%" "*.js" ^
	--copy "%gmlPath%" "*.gml"
	
	gmxgen "%ext14%.extension.gmx" ^
	--copy "%jsPath%" "*.js" ^
	--copy "%gmlPath%" "*.gml"

) else (
	echo Copying GML/JS files...
	robocopy %ext23% %ext22% *.gml /L >nul
	robocopy %ext23% %ext14% *.gml /L >nul
	robocopy %ext23% %ext22% *.js /L >nul
	robocopy %ext23% %ext14% *.js /L >nul

	echo postBuild.bat: Warning N/A: Could not find GmxGen - extensions will not be updated automatically. See https://github.com/YAL-GameMaker-Tools/GmxGen for setup.
)
