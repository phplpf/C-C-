#include <windows.h>
int WinMain(HINSTANCE hInstance,HINSTANCE hPrevIns,
     LPSTR lpCmdLine,int nCmdShow)
{
    MessageBox(NULL,"Hello World!","Information",
        MB_ABORTRETRYIGNORE | MB_ICONINFORMATION);
    return 0;
}
/*
    CL.EXE -c Hello.c                      // ���� Hello.obj
    RC.EXE Hello.rc                        // ���� Hello.res
    LINK.EXE Hello.obj Hello.res user32.lib // ���� Hello.exe
    Hello.exe
    �����ı��롢���ӵĹ��̣�
             CL.EXE
    .c/.cpp ---------> .obj | LINK.EXE
            RC.EXE          |-----------> .exe
    .rc   -----------> .res |
*/