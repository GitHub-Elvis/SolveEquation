//StdAfxUser.h
#pragma once

#if defined(_LIB)   //�������ɾ�̬��
    //����һ��ĺ�������
    #define SolveEquationDllI
#else               //�������ɶ�̬��
    //����һ��ĺ�������
    #define SolveEquationDllI __declspec(dllexport)
#endif

#include "../inc/+inc.h"
