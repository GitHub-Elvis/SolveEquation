@echo off
rem ���廷������-----------------------------------------------------------
set RunDirectory=%~dp0..\..\..\..\Run\
set DSWFILE="SolveEquation.dsw"
set CFG="SolveEquation - Win32 RA"
rem ���VC�İ�װĿ¼-------------------------------------------------------
rem ���ñ��������ļ�����Ŀ¼Ϊ��ǰĿ¼
cd /d %~dp0
rem ִ�� vspath.vbs,���� vspath.bat
cscript -e:vbs vspath.vbs
rem ִ�� vspath.bat ���û�������(VC�İ�װĿ¼)
call vspath.bat
rem ɾ�� vspath.bat
del vspath.bat
rem ִ�б���--------------------------------------------------------------
if not defined vc6path goto :eof
rem ִ�б���(MSDEV.EXE�ᴴ���µ������,MSDEV.COM����;/NORECURSE ��������������)
"%vc6path%MSDEV.COM" %DSWFILE% /make %CFG% /rebuild
if not errorlevel 0 goto :eof
echo ����ɹ����
goto end
:eof
echo ����ʧ��
:end
pause
