//SolveEquation.c
#include "StdAfx.h"
#include <math.h>
#include "resource.h"

HINSTANCE   g_hInst =   NULL;
double      m_z[10];    //���̵�ϵ��
double      m_x[12];    //���̵ĸ�

INT_PTR CALLBACK DlgProc(HWND hDlg,UINT uMsg,WPARAM wp,LPARAM lp)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
        {//����ͼ��
            HICON hIcon = LoadIcon(g_hInst,MAKEINTRESOURCE(IDR_MAINFRAME));
            SendMessage(hDlg,WM_SETICON,TRUE ,(LPARAM)hIcon);
            SendMessage(hDlg,WM_SETICON,FALSE,(LPARAM)hIcon);
        }
        {//��Ļ����
            RECT rc;
            GetWindowRect(hDlg,&rc);
            SetWindowPos(hDlg,NULL
                       ,(GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2
                       ,(GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2
                       ,0,0,SWP_NOZORDER | SWP_NOSIZE);
        }
        return TRUE;
    case WM_COMMAND:
        if(HIWORD(wp) == EN_CHANGE
        && LOWORD(wp) >= IDC_TXT_ZX4
        && LOWORD(wp) <= IDC_TXT_ZY0
        )
        {
            TCHAR   szText[512];
            HWND    hWnd    =   GetDlgItem(hDlg,IDC_TXT_ZX4);
            double  x       =   0.0;
            double  y       =   0.0;
            int     i       =   0;
            int     n       =   0;
            int     bOK     =   0;

            for(i = 0;i < 5;++i)
            {
                //��ȡʵ��
                GetWindowText(hWnd,szText,sizeof(szText) / sizeof(szText[0]));
                x           =   _tcstod(szText,NULL);
                //��ȡ�鲿
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
                GetWindowText(hWnd,szText,sizeof(szText) / sizeof(szText[0]));
                y           =   _tcstod(szText,NULL);
                //��һ��
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
                //
                m_z[2 * (4 - i)    ]    =   x;
                m_z[2 * (4 - i) + 1]    =   y;
            }
            //��ⷽ��
            n       =   SolveEquation(m_z,m_x);
            //��д���
            hWnd    =   GetDlgItem(hDlg,IDC_TXT_X1);
            hWnd    =   GetWindow(hWnd,GW_HWNDPREV);
            for(i = 0;i < 4;++i)
            {
                bOK         =   i < n;
                szText[0]   =   _T('\0');
                if(bOK)
                {//����
                    _stprintf(szText,_T("%.0le"),m_x[3 * i + 2]);
                }
                SetWindowText(hWnd,szText);
                //ʵ��
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
                if(bOK)
                {
                    _stprintf(szText,_T("%.13lg"),m_x[3 * i]);
                }
                SetWindowText(hWnd,szText);
                //�鲿
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
                if(bOK)
                {
                    _stprintf(szText,_T("%.13lg"),m_x[3 * i + 1]);
                }
                SetWindowText(hWnd,szText);
                //��һ��
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
                hWnd        =   GetWindow(hWnd,GW_HWNDNEXT);
            }
        }
        return TRUE;
    case WM_CTLCOLORSTATIC:
        {
            LRESULT hBrush  =   DefWindowProc(hDlg,uMsg,wp,lp);
            HWND    hWnd    =   (HWND)lp;
            UINT    uID     =   GetDlgCtrlID(hWnd);
            if(IDC_LBL_X1 == uID
            || IDC_LBL_X2 == uID
            || IDC_LBL_X3 == uID
            || IDC_LBL_X4 == uID)
            {
                TCHAR   szText[512];
                GetWindowText(hWnd,szText,sizeof(szText) / sizeof(szText[0]));
                if(szText[0] >= _T('0') && szText[0] <= _T('9'))
                {//���Ƿ��̵ĸ����Ժ�ɫ��ʾ��
                    HDC hDC =   (HDC)wp;
                    SetTextColor(hDC,fabs(_tcstod(szText,NULL)) < 1e-10 ? RGB(0,0,255) : RGB(255,0,0));
                }
            }
            return (INT_PTR)hBrush;
        }
    case WM_CLOSE:
        EndDialog(hDlg,0);
        return TRUE;
    }
    return FALSE;
}

int WINAPI _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow) 
{    
    return DialogBox(g_hInst = hInstance,MAKEINTRESOURCE(IDD_MAIN),NULL,(DLGPROC)DlgProc);
}
