@echo off
rem ���廷������-----------------------------------------------------------
set RunDirectory=%~dp0..\..\..\..\Run\
set DSWFILE="SolveEquation.dsw"
rem ���VC�İ�װĿ¼-------------------------------------------------------
rem ���ñ��������ļ�����Ŀ¼Ϊ��ǰĿ¼
cd /d %~dp0
rem ִ�� vspath.vbs,���� vspath.bat
cscript -e:vbs vspath.vbs
rem ִ�� vspath.bat ���û�������(VC�İ�װĿ¼)
call vspath.bat
rem ɾ�� vspath.bat
del vspath.bat
rem �� dsw �ļ�----------------------------------------------------------
if defined vc6path start "" "%vc6path%MSDEV.EXE" %DSWFILE%
