#include <Windows.h>
#include <tlhelp32.h>
#include <stdlib.h>
#include <psapi.h>
#include <string>
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='7.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <commctrl.h>

int ProcessWithKeywordRunningA(char *keyword);

int main(int argc, char **argv){
	if (argc < 2){
		MessageBoxA(NULL,"File name must be defined as argv[1] (maybe...)","CENotify",MB_ICONERROR|MB_OK);
		return 2;
	}
	std::string xargs1 = "";
	if (argc >= 3) {
		for(int i = 3 - 1; i < argc; i++) {
			xargs1 += (std::string)argv[i] + " ";
		}
	}
	char *xargs = &xargs1[0u];
	if (ProcessWithKeywordRunningA((char*)"cheatengine") == 1){
		MessageBoxA(NULL,"Cheat Engine was running!!!\nOr this was misdetection.","CENotify",MB_ICONERROR|MB_OK);	
		return 1;
	} else {
		ShellExecute(NULL, "open", argv[1], xargs, NULL, SW_SHOWNORMAL);
	}
	return 0;
}

int ProcessWithKeywordRunningA(char *keyword){
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 proc;
	proc.dwSize = sizeof(proc);

	Process32First(snapshot, &proc);
	do {
		HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, proc.th32ProcessID);
		char *fn2 = (char *)LocalAlloc(LMEM_ZEROINIT, 512);
		GetProcessImageFileNameA(hProc, fn2, 512);

		if (strstr(strlwr(fn2), strlwr(keyword)) != NULL) {
			CloseHandle(hProc);
			LocalFree(fn2);
			return 1;
		}

		CloseHandle(hProc);
		LocalFree(fn2);
	} while (Process32Next(snapshot, &proc));

	CloseHandle(snapshot);

	return 0;
}