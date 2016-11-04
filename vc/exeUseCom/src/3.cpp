#include "StdAfx.h"
#define COBJMACROS
#include "comMIDL.h"

/******************************************************************************\
1������ COM ���ʱ��MIDL.exe ��� idl �ļ�����Ϊ tlb �ļ���ͬʱ������ C/C++ �ӿ�
   �ļ�������������� comMIDL.h  �� comMIDL.c����C/C++ �ͻ�����ͨ���������ļ�����
   �ɷ��� COM �����
2������ĺ���ͨ�� comMIDL.h ��� C++ �� IEquation ���� COM �����
\******************************************************************************/
int Solve3MIDL_cpp(const double z[10],double x[12])
{
    IEquation*  e   =   NULL;
    long        n   =   0;

    CoInitialize(NULL);
    if(CoCreateInstance(CLSID_Equation,NULL,CLSCTX_INPROC_SERVER,IID_IEquation,(LPVOID*)&e) == S_OK)
    {
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
            e->Solve(&v,&n);
            VariantClear(&v);
        }
        {//���������� double x[]
            int p   =   0;
            int i   =   0;
            for(;i < n;++i)
            {
                e->real(i,&x[p++]);
                e->imag(i,&x[p++]);
                e->diff(i,&x[p++]);
            }
        }
        e->Release();
    }
    CoUninitialize();
    return n;
}
