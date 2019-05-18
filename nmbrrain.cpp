// another pure c++ joke program created by lwys

#include <Windows.h>

HINSTANCE hinst; 
HWND hwnd;
HFONT hFont = CreateFont(20,10,0,0,FW_BOLD,false,false,false,
				ANSI_CHARSET,OUT_DEVICE_PRECIS,
				CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
				FF_MODERN,"Lucida Console");
HDC hDC;
int xlen = 60;
int ylen = 90;

HCRYPTPROV prov;

#include <string>

int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			return 0;

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE *)(&out));
	return out & 0x7fffffff;
}

LPCTSTR chooser(){
	// ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " "]
	switch(random() % 10){
		case 0:
			return "0";
			break;
		case 1:
			return "1";
			break;
		case 2:
			return "2";
			break;
		case 3:
			return "3";
			break;
		case 4:
			return "4";
			break;
		case 5:
			return "5";
			break;
		case 6:
			return "6";
			break;
		case 7:
			return "7";
			break;
		case 8:
			return "8";
			break;
		case 9:
			return "9";
			break;
		case 10:
			return " ";
			break;
		default:
			return " ";
			break;
	}
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	if (message == WM_CREATE){
	}
	if (message == WM_CLOSE){
		DeleteObject(hFont);
		DestroyWindow(hWnd);
		ExitProcess(0);
		return 0;
	}
	if (message == WM_PAINT){
		HDC hDC2 = BeginPaint( hwnd, &ps ) ;
		SetTextColor(hDC2, RGB(130, 130, 130));
		SetBkMode(hDC2, TRANSPARENT);
		SelectObject(hDC2, hFont);
		LPSTR line = "";
		for (int i = 0; i < xlen; i++){
			for (int i = 0; i < ylen; i++){
				lstrcpyA(line, chooser());
			}
			TextOut(hDC2, 0, i * 20 + (i == 1 ? 10 : 0), line, ylen);
			line = "";
		}
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
};  

BOOL InitInstance(HINSTANCE hinstance, int nCmdShow)  
{
    // Save the application-instance handle.  
  
    hinst = hinstance;  
  
    // Create the main window.  
  
    hwnd = CreateWindow(  
        "xhwin",        // name of window class  
        "Windows",            // title-bar string  
        WS_OVERLAPPED/** | WS_SYSMENU | WS_THICKFRAME | WS_CAPTION **/, // top-level window  
        CW_USEDEFAULT,       // default horizontal position  
        CW_USEDEFAULT,       // default vertical position  
        800,       // default width  
        600,       // default height  
        (HWND) NULL,         // no owner window  
        (HMENU) NULL,        // use class menu  
        hinstance,           // handle to application instance  
        (LPVOID) NULL);      // no window-creation data  
  
    if (!hwnd)  
        return FALSE;  
  
    // Show the window and send a WM_PAINT message to the window  
    // procedure.  
  
    ShowWindow(hwnd, nCmdShow);  
    UpdateWindow(hwnd);  
    return TRUE;  
  
} 

BOOL InitApplication(HINSTANCE hinstance)  
{  
    WNDCLASSEX wcx;
  
    // Fill in the window class structure with parameters  
    // that describe the main window.  
  
    wcx.cbSize = sizeof(wcx);          // size of structure  
    wcx.style = CS_HREDRAW;
    wcx.lpfnWndProc = MainWndProc;     // points to window procedure  
    wcx.cbClsExtra = 0;                // no extra class memory  
    wcx.cbWndExtra = 0;                // no extra window memory  
    wcx.hInstance = hinstance;         // handle to instance  
    wcx.hCursor = NULL;                    // predefined arrow  
    wcx.hbrBackground = CreateSolidBrush(RGB(242, 211, 8)); // white background brush  
    wcx.lpszMenuName =  "Windows";    // name of menu resource  
    wcx.lpszClassName = "xhwin";  // name of window class  
	wcx.hIcon = LoadIcon(NULL,  
		IDI_APPLICATION);              // predefined app. icon
	wcx.hIconSm = (HICON)LoadImage(hinstance, MAKEINTRESOURCE(5), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);  
  
    // Register the window class.  
  
    return RegisterClassEx(&wcx);  
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance,  
    LPSTR lpCmdLine, int nCmdShow)  
{  
    MSG msg;  
  
    if (!InitApplication(hinstance))  
        return FALSE;  
  
    if (!InitInstance(hinstance, nCmdShow))  
        return FALSE;  
  
    BOOL fGotMessage; 
    while ((fGotMessage = GetMessage(&msg, (HWND) NULL, 0, 0)) != 0 && fGotMessage != -1)  
    {  
        TranslateMessage(&msg);  
        DispatchMessage(&msg);  
    }
    return msg.wParam;
}