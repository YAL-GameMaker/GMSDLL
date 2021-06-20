@echo off

cmd /C copyre ..\GMSDLL.gmx\extensions\GMSDLL.extension.gmx GMSDLL-for-GMS1\GMSDLL.extension.gmx
cmd /C copyre ..\GMSDLL.gmx\extensions\GMSDLL GMSDLL-for-GMS1\GMSDLL
cmd /C copyre ..\GMSDLL.gmx\datafiles\GMSDLL.html GMSDLL-for-GMS1\GMSDLL\Assets\datafiles\GMSDLL.html
cd GMSDLL-for-GMS1
cmd /C 7z a GMSDLL-for-GMS1.7z *
move /Y GMSDLL-for-GMS1.7z ../GMSDLL-for-GMS1.gmez
cd ..

if not exist "GMSDLL-for-GMS2\extensions" mkdir "GMSDLL-for-GMS2\extensions"
if not exist "GMSDLL-for-GMS2\datafiles" mkdir "GMSDLL-for-GMS2\datafiles"
if not exist "GMSDLL-for-GMS2\datafiles_yy" mkdir "GMSDLL-for-GMS2\datafiles_yy"
cmd /C copyre ..\GMSDLL_yy\extensions\GMSDLL GMSDLL-for-GMS2\extensions\GMSDLL
cmd /C copyre ..\GMSDLL_yy\datafiles\GMSDLL.html GMSDLL-for-GMS2\datafiles\GMSDLL.html
cmd /C copyre ..\GMSDLL_yy\datafiles_yy\GMSDLL.html.yy GMSDLL-for-GMS2\datafiles_yy\GMSDLL.html.yy
cd GMSDLL-for-GMS2
cmd /C 7z a GMSDLL-for-GMS2.zip *
move /Y GMSDLL-for-GMS2.zip ../GMSDLL-for-GMS2.yymp
cd ..

if not exist "GMSDLL-for-GMS2.3+\extensions" mkdir "GMSDLL-for-GMS2.3+\extensions"
if not exist "GMSDLL-for-GMS2.3+\datafiles" mkdir "GMSDLL-for-GMS2.3+\datafiles"
cmd /C copyre ..\GMSDLL_23\extensions\GMSDLL GMSDLL-for-GMS2.3+\extensions\GMSDLL
cmd /C copyre ..\GMSDLL_23\datafiles\GMSDLL.html GMSDLL-for-GMS2.3+\datafiles\GMSDLL.html
cd GMSDLL-for-GMS2.3+
cmd /C 7z a GMSDLL-for-GMS2.3+.zip *
move /Y GMSDLL-for-GMS2.3+.zip ../GMSDLL-for-GMS2.3+.yymps
cd ..

pause