#include "StdAfx.h"
#include "comMFC.h"

/******************************************************************************\
1����� COM ���ʵ���� IDispatch �ӿڣ���ô�Ϳ��Ը������Ϳ����� MFC ��װ�ࡣ
   VC++6.0 ���� MFC ��װ��Ĳ��裺Ctrl+W ==> Add Class ==> From a type library
   �����������ɵ� MFC ��װ�����ļ� comMFC.h �� comMFC.cpp �
2������ĺ��������� MFC ��װ�࣬ͨ�� IDispatch �ӿڷ��� COM �����
\******************************************************************************/
int Solve1MFC(const double z[10],double x[12])
{
    int n   =   0;
    CoInitialize(NULL);
    {
        TRY 
        {
            IEquation e;
            if(e.CreateDispatch(_T("SolveEquation")))
            {
                COleSafeArray   osa;
                osa.CreateOneDim(VT_R8,10,z);   //�� double z[10] ��װ�� VARIANT ���� osa ��
                n       =   e.Solve(&osa);
                int p   =   0;
                for(int i = 0;i < n;++i)
                {
                    x[p++]  =   e.real(i);
                    x[p++]  =   e.imag(i);
                    x[p++]  =   e.diff(i);
                }
            }
        }//���е��ˣ�equ ��������IDispatch ���Զ� Release
        CATCH (CException, e)//catch (CException* e)
        {
            e->Delete();
        }
        END_CATCH
    }
    CoUninitialize();
    return n;
}
