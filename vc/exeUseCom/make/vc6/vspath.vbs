dim wsh
Set wsh = WScript.CreateObject("WScript.Shell")
'evc3 ��ȫ·����
dim evc3path
evc3path = GetVCPath(wsh,"HKEY_CURRENT_USER\Software\Microsoft\CEStudio\3.0\evc\Directories\Install Dirs")
'evc4 ��ȫ·����
dim evc4path
evc4path = GetVCPath(wsh,"HKEY_CURRENT_USER\Software\Microsoft\CEStudio\4.0\evc\Directories\Install Dirs")
'vc6 ��ȫ·����
dim vc6path
vc6path = GetVCPath(wsh,"HKEY_CURRENT_USER\Software\Microsoft\DevStudio\6.0\Directories\Install Dirs")
'vs2002 ��ȫ·����
dim vs2002path
vs2002path = GetVSNETPath(wsh,"VSCOMNTOOLS")
'vs2003 ��ȫ·����
dim vs2003path
vs2003path = GetVSNETPath(wsh,"VS71COMNTOOLS")
'vs2005 ��ȫ·����
dim vs2005path
vs2005path = GetVSNETPath(wsh,"VS80COMNTOOLS")
'vs2008 ��ȫ·����
dim vs2008path
vs2008path = GetVSNETPath(wsh,"VS90COMNTOOLS")
'vs2010 ��ȫ·����
dim vs2010path
vs2010path = GetVSNETPath(wsh,"VS100COMNTOOLS")
'vs2012 ��ȫ·����
dim vs2012path
vs2012path = GetVSNETPath(wsh,"VS110COMNTOOLS")
'vs2013 ��ȫ·����
dim vs2013path
vs2013path = GetVSNETPath(wsh,"VS120COMNTOOLS")
'vs2015 ��ȫ·����
dim vs2015path
vs2015path = GetVSNETPath(wsh,"VS140COMNTOOLS")

Dim fso,f1   
Set fso =  CreateObject("Scripting.FileSystemObject")
Set f1  =  fso.CreateTextFile("vspath.bat",True)
if len(evc3path) > 0 then
  f1.writeline "set evc3path=" & evc3path
end if
if len(evc4path) > 0 then
  f1.writeline "set evc4path=" & evc4path
end if
if len(vc6path) > 0 then
  f1.writeline "set vc6path=" & vc6path
end if
if len(vs2002path) > 0 then
  f1.writeline "set vs2002path=" & vs2002path
end if
if len(vs2003path) > 0 then
  f1.writeline "set vs2003path=" & vs2003path
end if
if len(vs2005path) > 0 then
  f1.writeline "set vs2005path=" & vs2005path
end if
if len(vs2008path) > 0 then
  f1.writeline "set vs2008path=" & vs2008path
end if
if len(vs2010path) > 0 then
  f1.writeline "set vs2010path=" & vs2010path
end if
if len(vs2012path) > 0 then
  f1.writeline "set vs2012path=" & vs2012path
end if
if len(vs2013path) > 0 then
  f1.writeline "set vs2013path=" & vs2013path
end if
if len(vs2015path) > 0 then
  f1.writeline "set vs2015path=" & vs2015path
end if
f1.close

'��� EVC,VC++6.0 �İ�װĿ¼
'���ص�Ŀ¼,���һ���ַ�Ϊ\ʧ�ܷ��ؿ��ַ���
function GetVCPath(wsh,sKey)
  on error resume next
  GetVCPath = wsh.regread(sKey)
  if len(GetVCPath) > 0 and right(GetVCPath,1)<>"\" then
    GetVCPath = GetVCPath + "\"
  else
    GetVCPath = ""
  end if
  on error goto 0
end function

'��� VC++NET �İ�װĿ¼
'���ص�Ŀ¼,���һ���ַ�Ϊ\ʧ�ܷ��ؿ��ַ���
function GetVSNETPath(wsh,sName)
  GetVSNETPath = wsh.Environment("system").Item(sName)
  if len(GetVSNETPath) > 0 Then
  	'ȥ����β��˫����(VS2002��˫����)
    If Left(GetVSNETPath,1) = Chr(34) Then
    	GetVSNETPath = Mid(GetVSNETPath,2,len(GetVSNETPath) - 2)
    End If
    'ȥ������\
    If Right(GetVSNETPath,1) = "\" Then
    	GetVSNETPath = Left(GetVSNETPath,Len(GetVSNETPath) - 1)
    End If
    GetVSNETPath =    left(GetVSNETPath,InStrRev(GetVSNETPath,"\")) + "IDE\"
  else
    GetVSNETPath = ""
  end if
end function