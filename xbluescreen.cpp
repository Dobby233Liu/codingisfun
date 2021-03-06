// pure c++ joke program created by lwys

#include <Windows.h>

HINSTANCE hinst; 
HWND hwnd;
HFONT hFont;
HDC hDC;
LPCSTR blueText[24];
LPCSTR blueTextAfterDump[3];
bool stageComplete;

void DoEvents()
{
	MSG msg;
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} 
}

void defineBText(){
	// A problem has been detected and Windows has been shut down to prevent damage 
	// to your computer.
	//
	// If this is the first time you've seen this Stop error screen,
	// restart your computer. If this screen appears again, follow
	// these steps:
	//
	// Check to be sure you have adequate disk space. If a driver is
	// identified in the Stop message, disable the driver or check
	// with the manufacturer for driver updates. Try changing video
	// adapters.
	//
	// Check with your hardware vendor for any BIOS updates. Disable
	// BIOS memory options such as caching or shadowing. If you need
	// to use Safe Mode to remove or disable components, restart your
	// computer, press F8 to select Advanced Startup Options, and then
	// select Safe Mode.
	//
	// Technical information:
	//
	// *** STOP: 0x0000008E (0xC0000005,0x80545D06,0xF019FBF0,0x00000000)
	//
	//
	// Beginning dump of physical memory
	
	blueText[0] = "A problem has been detected and Windows has been shut down to prevent damage ";
	blueText[1] = "to your computer.";
	
	blueText[2] = "";
	
	blueText[3] = "If this is the first time you've seen this Stop error screen,";
	blueText[4] = "restart your computer. If this screen appears again, follow";
	blueText[5] = "these steps:";
	
	blueText[6] = "";
	
	blueText[7] = "Check to be sure you have adequate disk space. If a driver is";
	blueText[8] = "identified in the Stop message, disable the driver or check";
	blueText[9] = "with the manufacturer for driver updates. Try changing video";
	blueText[10] = "adapters.";
	
	blueText[11] = "";
	
	blueText[12] = "Check with your hardware vendor for any BIOS updates. Disable";
	blueText[13] = "BIOS memory options such as caching or shadowing. If you need";
	blueText[14] = "to use Safe Mode to remove or disable components, restart your";
	blueText[15] = "computer, press F8 to select Advanced Startup Options, and then";
	blueText[16] = "select Safe Mode.";
	
	blueText[17] = "";
	
	blueText[18] = "Technical information:";
	blueText[19] = "";
	blueText[20] = "*** STOP: 0x0000008E (0xC0000005,0x80545D06,0xF019FBF0,0x00000000)";
	
	blueText[21] = "";
	blueText[22] = "";
	blueText[23] = "Collecting data for crash dump ";
	blueText[24] = "Initalizing disk for crash dump ";
	blueText[25] = "Beginning dump of physical memory.";
	blueText[26] = "Dumping physical memory to disk:   ";
	// TODO
	// Collecting data for crash dump (...)
	// Initalizing disk for crash dump (...)
	// Beginning dump of physical memory.
	// Dumping physical memory to disk:   (percent)
	
	// Physical memory dump complete.
	// Contact your system administrator or technical support group for further
	// assistance.
	
	blueTextAfterDump[0] = "Physical memory dump complete.   ";
	blueTextAfterDump[1] = "Contact your system administrator or technical support group for further";
	blueTextAfterDump[2] = "assistance.";
	blueTextAfterDump[3] = "                                      "; // empty "Dumping ..."
}

void TextOutTyper(HDC hdc, int baseX, int y, LPCSTR lpchText, int cchText, int fontWidth, int delay);
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	if (message == WM_CREATE){
	}
	if (message == WM_CLOSE){
		if (!stageComplete) return 0;
		DeleteObject(hFont);
		DestroyWindow(hWnd);
		ExitProcess(-32767);
		return 0;
	}
	if (message == WM_PAINT){
		HDC hDC2 = BeginPaint( hwnd, &ps ) ;
		hFont=CreateFont(20,10,0,0,FW_NORMAL,false,false,false,
				ANSI_CHARSET,OUT_DEVICE_PRECIS,
				CLIP_CHARACTER_PRECIS,DRAFT_QUALITY/**sassy vga-style**/,
				FF_MODERN,"Consolas");
		SetTextColor(hDC2, RGB(255, 255, 255));
		SetBkMode(hDC2, TRANSPARENT);
		SetBkColor(hDC2, RGB(0,0,130));
		SelectObject(hDC2, hFont);
		TextOutTyper(hDC2, 0, 10, blueText[0], strlen(blueText[0]), 10, 10);
		for (int i = 1; i < (sizeof(blueText) / sizeof(blueText[i]) - 1); i++){
			TextOutTyper(hDC2, 0, i * 20 + (i == 1 ? 10 : 0), blueText[i], strlen(blueText[i]), 10, 10);
			Sleep(50);
		}
		for (int i = 0; i < 90; i++){ // toby-ish hardcode
			DoEvents();
		}
		TextOutTyper(hDC2, 0, 23 * 20, blueText[23], strlen(blueText[23]), 10, 10);
		for (int i = 0; i < 2000 * 6000; i++){
			DoEvents();
		}
		for (int i = 0; i < (sizeof(blueTextAfterDump) / sizeof(blueTextAfterDump[i])); i++){
			if(i==0) {
				SetBkMode(hDC2, OPAQUE); // hack
			}
			TextOutTyper(hDC2, 0, i * 20 + 23 * 20, blueTextAfterDump[i], strlen(blueTextAfterDump[i]), 10, 10);
			if(i==0) {
				SetBkMode(hDC2, TRANSPARENT);
			}
			Sleep(50);
		}
		// TextOutTyper(hDC2, 0, 30, blueText2, strlen(blueText2), 10, 10);
		EndPaint( hwnd, &ps ) ;
		stageComplete = true;
		for (int i = 0; i < 4000 * 3000/**12000000**/; i++){
			DoEvents();
		}
		SendMessage(hWnd, WM_CLOSE, NULL, NULL);
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
	
	defineBText();
  
    // Fill in the window class structure with parameters  
    // that describe the main window.  
  
    wcx.cbSize = sizeof(wcx);          // size of structure  
    wcx.style = CS_HREDRAW;
    wcx.lpfnWndProc = MainWndProc;     // points to window procedure  
    wcx.cbClsExtra = 0;                // no extra class memory  
    wcx.cbWndExtra = 0;                // no extra window memory  
    wcx.hInstance = hinstance;         // handle to instance  
    wcx.hCursor = NULL;                    // predefined arrow  
    wcx.hbrBackground = CreateSolidBrush(RGB(0, 0, 130)); // white background brush  
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

void TextOutTyper(HDC hdc, int baseX, int y, LPCSTR lpchText, int cchText, int fontWidth, int delay){
	int curXPos = baseX;
	int delay2 = (delay / 2) * 100;
	for(int z = 0; z < (cchText + 1); z++){
		char myChar[1];
		myChar[0] = lpchText[z];
		TextOut(hdc, curXPos, y, myChar, 1);
		curXPos = curXPos + fontWidth;
		for(int m = 0; m < delay2; m++) DoEvents();
	}
}