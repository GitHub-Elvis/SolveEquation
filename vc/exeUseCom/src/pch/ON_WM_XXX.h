//ON_WM_XXX.h
#pragma once

//���ļ����������� ON_WM_XXX()

/******************************************************************************\
ON_WM_ACTIVATEAPP()
vc6 ����Ӧ����Ϊ void OnActivateApp(BOOL bActive, HTASK hTask) 
�� vc2002 ��ʼ�ڶ��������� HTASK ��Ϊ DWORD
���û��ຯ�� CWnd::OnActivateApp
#if _MSC_VER >= 1300
    CWnd::OnActivateApp(BOOL.DWORD);
#else
    CWnd::OnActivateApp(BOOL.HTASK);
#endif
\******************************************************************************/

/******************************************************************************\
ON_WM_TIMER()
vc6 ����Ӧ����Ϊ void OnTimer(UINT nIDEvent) 
�� vc2002 ��ʼ��һ�������� UINT ��Ϊ UINT_PTR
\******************************************************************************/

/******************************************************************************\
ON_WM_NCHITTEST()
vc6 ����Ӧ����Ϊ UINT OnNcHitTest(CPoint point)
�� vc2005 ��ʼ������ֵ�� UINT ����Ϊ LRESULT
\******************************************************************************/
#if _MSC_VER == 1300 || _MSC_VER == 1310
    #undef  ON_WM_NCHITTEST
    #define ON_WM_NCHITTEST() {WM_NCHITTEST,0,0,0,AfxSig_wp,(AFX_PMSG)(AFX_PMSGW)(static_cast< LRESULT (AFX_MSG_CALL CWnd::*)(CPoint) > (OnNcHitTest))},
#endif
