//StdAfx.h
#pragma once

#define _CRT_NONSTDC_NO_WARNINGS           //ʹ�� POSIX ����ʱ������������Ϣ
#define _CRT_NON_CONFORMING_SWPRINTFS      //�����ϰ汾�� swprintf ����
#define _CRT_SECURE_NO_WARNINGS            //ʹ�ò���ȫ����ʱ������������Ϣ

//����ϵͳͷ�ļ�----------------------------------------------------------------
#ifdef _WIN32_WCE
    //�����豸
    #if _MSC_VER==1200        //EVC3.0
        #include "StdAfx3.h"
    #elif _MSC_VER==1201      //EVC4.0
        #include "StdAfx4.h"
    #elif _MSC_VER==1400      //VC++8.0(VC2005)
        #include "StdAfx2005CE.h"
    #elif _MSC_VER==1500      //VC++9.0(VC2008)
        #include "StdAfx2008CE.h"
    #endif
#else
    //PC ����
    #if _MSC_VER==1200        //VC++6.0
        #include "StdAfx6.h"
    #elif _MSC_VER==1300      //VC++7.0(VC2002)
        #include "StdAfx2002.h"
    #elif _MSC_VER==1310      //VC++7.1(VC2003)
        #include "StdAfx2003.h"
    #elif _MSC_VER==1400      //VC++8.0(VC2005)
        #include "StdAfx2005.h"
    #elif _MSC_VER==1500      //VC++9.0(VC2008)
        #include "StdAfx2008.h"
    #elif _MSC_VER==1600      //VC++10.0(VC2010)
        #include "StdAfx2010.h"
    #elif _MSC_VER==1700      //VC++11.0(VC2012)
        #include "StdAfx2012.h"
    #elif _MSC_VER==1800      //VC++12.0(VC2013)
        #include "StdAfx2013.h"
    #elif _MSC_VER==1900      //VC++14.0(VC2015)
        #include "StdAfx2015.h"
    #endif
#endif

#include "ON_WM_XXX.h"        //������ ON_WM_XXX()

//�����Զ���ͷ�ļ�--------------------------------------------------------------
#include "../StdAfxUser.h"
