#include "StdAfx.h"
#import "SolveEquationCom.dll"

/******************************************************************************\
1��Ԥ�������� #import "SolveEquationCom.dll" �Ĵ���
   1������ SolveEquationCom.dll ������Ϳ����� SolveEquationCom.tlh��COM �����
      �ں����� C++ �������� SolveEquationCom.tli��COM ����ӿں����� C++ ʵ�֣�
   2��#include "SolveEquationCom.tlh" �������ļ� SolveEquationCom.tlh�����ļ���
      ������ SolveEquationCom.tli��
2������ĺ���ͨ������ָ�� IEquationPtr ���� COM �����IEquationPtr �� SolveEqua
   tionCom.tlh ��������SolveEquationLib �������ռ䡣
\******************************************************************************/
int Solve2import(const double z[10],double x[12])
{
    long n = 0;
    CoInitialize(NULL);
    try
    {
        SolveEquationLib::IEquationPtr e(__uuidof(SolveEquationLib::Equation));
        VARIANT v;
        VariantInit(&v);
        {//�� double z[10] ��װ�� VARIANT ���� v ��
            v.vt = VT_R8 | VT_ARRAY;
            if(v.parray = SafeArrayCreateVector(VT_R8,0,10))
            {
		        void*pData  =   NULL;
                if(SafeArrayAccessData(v.parray,&pData) == S_OK)
                {
		            memcpy(pData,z,SafeArrayGetElemsize(v.parray) * 10);
		            SafeArrayUnaccessData(v.parray);
                }
                else
                {
                    SafeArrayDestroy(v.parray);
                    v.parray = NULL;
                }
            }
        }
        if(v.parray)
        {
            n   =   e->Solve(&v);
            VariantClear(&v);
        }
        int p       =   0;
        for(int i = 0;i < n;++i)
        {
            x[p++]  =   e->real(i);
            x[p++]  =   e->imag(i);
            x[p++]  =   e->diff(i);
        }
    }//���е��ˣ�����ָ�� e ����������e->Relase �����Զ�����
    catch(_com_error&e)
    {
        AfxMessageBox(e.Description() + "\n" + e.ErrorMessage());
    }
    CoUninitialize();
    return n;
}
