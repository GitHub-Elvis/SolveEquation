@echo off
rem ���廷������-----------------------------------------------------------
set RunDirectory=%~dp0..\..\..\..\Run\
set VCWFILE="SolveEquation.vcw"
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
if defined evc3path start "" "%evc3path%EVC.EXE" %VCWFILE%
