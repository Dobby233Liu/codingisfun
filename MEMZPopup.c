#include <Windows.h>

// Copy & Pasted(TM) from MEMZ 5.0. By LWYS

const char * KillMessages[] = {"YOU KILLED MY TROJAN!\r\nNow you are going to die.", "REST IN PISS, FOREVER MISS.", "I WARNED YOU...", "HAHA N00B L2P G3T R3KT", "You failed at your 1337 h4x0r skillz.", "YOU TRIED SO HARD AND GOT SO FAR, BUT IN THE END, YOUR PC WAS STILL FUCKED!", "HACKER!\r\nENJOY BAN!", "GET BETTER HAX NEXT TIME xD", "HAVE FUN TRYING TO RESTORE YOUR DATA :D", "|\\/|3|\\/|2", "BSOD INCOMING", "VIRUS PRANK (GONE WRONG)", "ENJOY THE NYAN CAT", "Get dank antivirus m9!", "You are an idiot!\r\nHA HA HA HA HA HA HA", "#MakeMalwareGreatAgain", "SOMEBODY ONCE TOLD ME THE MEMZ ARE GONNA ROLL ME", "Why did you even tried to kill MEMZ?\r\nYour PC is fucked anyway.", "SecureBoot sucks.", "gr8 m8 i r8 8/8", "Have you tried turning it off and on again?", "<Insert Joel quote here>", "Well, hello there. I don\'t believe we\'ve been properly introduced. I\'m Bonzi!", "\'This is everything I want in my computer\'\r\n - danooct1 2016", "\'Uh, Club Penguin. Time to get banned!\'\r\n - danooct1 2016"};
#define KillMessagesLen 25

HCRYPTPROV prov;

int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE *)(&out));
	return out & 0x7fffffff;
}

LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_CREATEWND) {
		CREATESTRUCT *pcs = ((CBT_CREATEWND *)lParam)->lpcs;

		if ((pcs->style & WS_DLGFRAME) || (pcs->style & WS_POPUP)) {
			HWND hwnd = (HWND)wParam;

			int x = random() % (GetSystemMetrics(SM_CXSCREEN) - pcs->cx);
			int y = random() % (GetSystemMetrics(SM_CYSCREEN) - pcs->cy);

			pcs->x = x;
			pcs->y = y;
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

DWORD WINAPI ripMessageThread(LPVOID parameter) {
	HHOOK hook = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
	MessageBoxA(NULL, (LPCSTR)KillMessages[random() % KillMessagesLen], "MEMZ", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	UnhookWindowsHookEx(hook);

	return 0;
}
int main(){
	Sleep(2000);
	for (int i = 0; i < 20; i++) {
		CreateThread(NULL, 4096, &ripMessageThread, NULL, NULL, NULL);
		Sleep(100);
	}
	for(;;){
		Sleep(100);
	}
	return 0;
}