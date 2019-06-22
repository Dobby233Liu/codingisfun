#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	if(argc <= 1){
		printf("error\n");
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
			printf("?????\n");
			system("pause");
			break;
	}
	FILE *f = fopen(argv[1], "w");
	if (f == NULL){
		printf("error\n");
		system("pause");
		return 1;
	}
	fprintf(f, "%s", string);
	fclose(f);
	printf("ok\n");
	system("pause");
	return 0;
}