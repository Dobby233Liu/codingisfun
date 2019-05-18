#include <stdio.h>
#include <Windows.h>
int main(){
	printf("Cheat Engine 5.1.0 (x86_64) CUI for Windows\n");
	printf("Hooking 0x025133A...\n");
	for(;;){
		void *fakeAddress = (void*)0x025133A;
		Sleep(10000);
		printf("Hooking fail, rehooking...\n");
	}
	return 0;
}