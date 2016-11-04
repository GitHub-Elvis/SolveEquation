#include <windows.h>
#define COBJMACROS
#include "comMIDL.h"

/******************************************************************************\
1������ COM ���ʱ��MIDL.exe ��� idl �ļ�����Ϊ tlb �ļ���ͬʱ������ C/C++ �ӿ�
   �ļ�������������� comMIDL.h  �� comMIDL.c����C/C++ �ͻ�����ͨ���������ļ�����
   �ɷ��� COM �����
2������ĺ���ͨ�� comMIDL.h ��� interface IEquation �� struct IEquationVtbl ��
   �� COM ���
\******************************************************************************/
int Solve4MIDL_c(const double z[10],double x[12])
{
    IClassFactory*  pcf =   NULL;
    IEquation*      e   =   NULL;
    long            n   =   0;

    CoInitialize(NULL);
#if 0
    if(CoCreateInstance(&CLSID_Equation,NULL,CLSCTX_INPROC_SERVER,&IID_IEquation,(LPVOID*)&e) == S_OK)
#else
    if(CoGetClassObject(&CLSID_Equation,CLSCTX_INPROC_SERVER,NULL,&IID_IClassFactory,(void**)&pcf) == S_OK
    && pcf->lpVtbl->CreateInstance(pcf,NULL,&IID_IEquation,(void**)&e) == S_OK)
#endif
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
            e->lpVtbl->Solve(e,&v,&n);
            VariantClear(&v);
        }
        {//���������� double x[]
            int p   =   0;
            int i   =   0;
            for(;i < n;++i)
            {
                e->lpVtbl->real(e,i,&x[p++]);
                e->lpVtbl->imag(e,i,&x[p++]);
                e->lpVtbl->diff(e,i,&x[p++]);
            }
        }
        e->lpVtbl->Release(e);
    }
    if(pcf)
    {
        pcf->lpVtbl->Release(pcf);
    }
    CoUninitialize();
    return n;
}
