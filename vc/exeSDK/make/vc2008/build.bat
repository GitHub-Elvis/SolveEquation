@echo off
rem ���廷������-----------------------------------------------------------
set RunDirectory=%~dp0..\..\..\..\Run\
set SLNFILE="SolveEquation.sln"
set CFG="RA|Win32"
set PROJECT="SolveEquation"
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
if not defined vs2008path goto :eof
rem ִ�б���(devenv.exe�ᴴ���µ������,devenv.com����)
"%vs2008path%devenv.com" %SLNFILE% /rebuild %CFG% /project %PROJECT%
if not errorlevel 0 goto :eof
echo ����ɹ����
goto end
:eof
echo ����ʧ��
:end
pause
