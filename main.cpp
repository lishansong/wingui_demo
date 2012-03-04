#include <windows.h>
#include "resource.h"
#include "commctrl.h"
#include "stdio.h"



HINSTANCE hInst;

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
        /*
         * TODO: Add code to initialize the dialog.
         */
        return TRUE;

    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
        return TRUE;

    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
            /*
             * TODO: Add more control ID's, when needed.
             */
        case BTN_EXIT:
            EndDialog(hwndDlg, 0);
            return TRUE;

        case BTN_TEST:
            MessageBox(hwndDlg, "You clicked \"Test\" button!", "Information", MB_ICONINFORMATION);
            return TRUE;

        case BTN_SetEditData:
            SetDlgItemTextA(hwndDlg,IDC_EDIT1,"Set Edit Control Data Demo.");
            return TRUE;

        case BTN_GetEditData:
            char str[50];
            GetDlgItemTextA(hwndDlg,IDC_EDIT1,str,50);
            MessageBox(hwndDlg, str, "Get Edit Control data", MB_ICONINFORMATION);
            return TRUE;

        case BTN_PBAR_TEST:
            SendDlgItemMessage(hwndDlg, IDC_PROGRESS1, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
            SendDlgItemMessage(hwndDlg, IDC_PROGRESS1, PBM_SETSTEP, 1, 0);
            for(int i=0; i<=100; i+=10)
            {
                SendDlgItemMessage(hwndDlg, IDC_PROGRESS1, PBM_SETPOS, i, 0);
                SendDlgItemMessage(hwndDlg, IDC_PROGRESS1, PBM_SETBARCOLOR,0,RGB(0,i*2,0));
                Sleep(20);
            }
            return TRUE;

        case BTN_GetCheck1Value:
            bool a;
            a = IsDlgButtonChecked(hwndDlg,IDC_CHECKBOX1);
            snprintf(str,sizeof(str),"%d",int(a));
            MessageBox(hwndDlg, str, "Get Check1 Value", MB_ICONINFORMATION);
            return TRUE;

        case BTN_ChangeCheck1Value:
            if(IsDlgButtonChecked(hwndDlg,IDC_CHECKBOX1))SendDlgItemMessage(hwndDlg, IDC_CHECKBOX1, BM_SETCHECK, BST_UNCHECKED, 0);
            else SendDlgItemMessage(hwndDlg, IDC_CHECKBOX1, BM_SETCHECK, BST_CHECKED, 0);
            return TRUE;

        case BTN_ListBoxAdd:
            SendDlgItemMessage(hwndDlg,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)("ListBoxItem"));
            return TRUE;

        case BTN_ListBoxDelete:
            SendDlgItemMessage(hwndDlg,IDC_LIST1,LB_DELETESTRING,0,0);
            return TRUE;

        case BTN_ListBoxItemNum:
            int dd = SendDlgItemMessage(hwndDlg,IDC_LIST1,LB_GETCOUNT,0,0);
            snprintf(str,sizeof(str),"%d",dd);
            MessageBox(hwndDlg, str, "Get List Box Item Number", MB_ICONINFORMATION);
            return TRUE;


        }
    }

    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;

    // The user interface is a modal dialog box
    return DialogBox(hInstance, MAKEINTRESOURCE(DLG_MAIN), NULL, DialogProc);
}
