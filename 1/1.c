#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	struct student {
		char name[50];
		int age;
		char sex;
		char* namep;
	};
	struct student* pl = malloc(sizeof(struct student));
	while (1) {
		printf("Full Name (ÀÌ¸§ ¼º) : ");
		scanf(" %[^\n]", pl->name);
		getchar();

		if (strcmp(pl->name, "stop") == 0) {
			
			break;
		}


		else {
			pl->namep = strchr(pl->name, ' ') + 1;



			printf("age : ");
			scanf("%d", &(*pl).age);
			getchar();

			printf("sex(M/F)");
			scanf("%c", &pl->sex);
	

			printf("Your name is %s ", pl->namep);
			printf("%s, your age is %d, your sex is %c\n", strtok(pl->name, " "),pl->age,pl->sex);
			strcpy(pl->name, "");
		}
	}
	free(pl);
	return 0;
}


	
