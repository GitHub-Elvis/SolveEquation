@echo off
rem ���廷������-----------------------------------------------------------
set RunDirectory=%~dp0..\..\..\..\Run\
set VCWFILE="SolveEquation.vcw"
rem �������� CECONFIG �ǻ����ͺ�(Platform)��ע���Сд
set CECONFIG="Pocket PC"
rem �������� CFG �ǡ���Ŀ - ���á�
set CFG="SolveEquation - Win32 (WCE ARM) RU"
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
if not defined evc3path goto :eof
rem ִ�б���(MSDEV.EXE�ᴴ���µ������,MSDEV.COM����;/NORECURSE ��������������)
"%evc3path%EVC.COM" %VCWFILE% /make %CFG% /CEConfig=%CECONFIG% /rebuild
if not errorlevel 0 goto :eof
echo ����ɹ����
goto end
:eof
echo ����ʧ��
:end
pause