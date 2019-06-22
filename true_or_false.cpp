#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	if(argc <= 1){
		printf("error");
		getchar();
		return 1;
	}
	printf("input 0(true) 1(false)\nselection: ");
	char selection;
	scanf("%c",&selection);
	char* string = "true";
	switch(selection){
		case '0':
			string = "true";
			break;
		case '1':
			string = "false";
			break;
		default:
			printf("?????");
			getchar();
			break;
	}
	FILE *f = _fsopen(argv[0], "w", 0x40);
	if (f == NULL){
		printf("error");
		getchar();
		return 1;
	}
	fprintf(f, "%s", string);
	fclose(f);
	printf("ok");
	getchar();
	return 0;
}