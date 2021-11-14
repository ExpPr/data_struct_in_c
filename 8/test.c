#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AD_Matrix_test2.h"

int compare_q(const void *a1, const void *a2) {
  return *(char*)a1-*(char*)a2;
}
int compare_chr(void *a1,void *a2) {
  return *(char*)a1-*(char*)a2;
}

void printdata(void *item) {
  printf("%c ",*(char*)item);
}

int check_file_line(char *np) {//파일 줄 확인. 파일명이 존재하지 않으면 -1 리턴
  int line=0;
  char c[60];//임시저장소

  FILE *fep=fopen(np,"r");

  if (fep==NULL) {
    return -1;
  }

  while(!feof(fep)) {
    line++;
    fgets(c,60,fep);
  }
  fseek(fep, -1, SEEK_CUR);

  if (fgetc(fep)=='\n') {
    line--;
  }
  fclose(fep);
  return line;
}

char *return_all_char(char *np) {//한줄이라도 잘못 입력되면 바로 종료.
  FILE *fep=fopen(np,"r");
  if (fep==NULL) {
    return NULL;
  }
  if (check_file_line(np)<3) {
    return NULL;//잘못된 입력.
  }
  int count=0;
  int line=check_file_line(np),chk=0;
  char *temp=(char*)malloc(sizeof(char));
  char tempary[2];

	char qp[10];
	fgets(qp,9,fep);
	fgets(qp,9,fep);

  for (int i=2;i<line;i++) {
    chk=fscanf(fep,"%c %c",&tempary[0],&tempary[1]);
    if (chk!=2) {
      free(temp);
      fclose(fep);
      return NULL;//강제종료. 잘못된 입력.
    }
    count+=2;
    temp=(char*)realloc(temp,sizeof(char)*(count+1));
    temp[count-2]=tempary[0];
    temp[count-1]=tempary[1];

		if (fgetc(fep)!='\n') {
			fseek(fep,-1,SEEK_CUR);
		}
  }
  temp[count]='\0';
	fclose(fep);
  return temp;
}


pVertex* insert_all_vertex(pGragh head, char *list,int *size) {
  if (head==NULL||list==NULL||strlen(list)==0) {
    return NULL;
  }
  int length=strlen(list);
  int count=0;
  pVertex* vertex_list=(pVertex*)malloc(sizeof(pVertex));
  for (int i=0;i<length;i++) {
    vertex_list[count]=addVertex(head,&list[i]);
    if (vertex_list[count]!=NULL) {
      count++;
      vertex_list=(pVertex*)realloc(vertex_list,sizeof(pVertex)*(count+1));
    }
  }
  vertex_list=(pVertex*)realloc(vertex_list,sizeof(pVertex)*(count));
  return vertex_list;
}

void insert_all_arcs(pGragh head, char *list) {
	int length=strlen(list);
  for (int i=0;i<length;i++) {
    add_arc(head,check_data(head,(void*)&list[i]),check_data(head,(void*)&list[i+1]));
		i++;
  }
}

char get_first_node(char *np) {
	FILE *fep=fopen(np,"r");
  if (fep==NULL) {
    return '\0';
  }
	char c=fgetc(fep);
	fclose(fep);
	return c;
}

int main(void) {
	pQueue p=createQueue(1);
  pGragh head = CreateGragh(compare_chr);
	char test[30];
	int size;

	printf("File Name of a gragh : ");
	scanf("%s",test);
	rewind(stdin);

	char *temp = return_all_char(test);
	pVertex *lists=insert_all_vertex(head, temp, &size);
	insert_all_arcs(head, temp);

	printf("\nThe Gragh is : \n");

	for (pVertex check=head->first;check!=NULL;check=check->pnextvertex)  {
		printdata(check->data);
		printf(" : ");
		print_all_arc_data(head,check,printdata);
		printf("\n");

	}
	char firstNode=get_first_node(test);

	printf("Depth First Traversal : ");
	DepthFirstTraversal(head, check_data(head,(void*)&firstNode), printdata);
	clear_processed(head);
	printf("\nBreadth First Traversal : ");
	BreathFirstTraversal(head,check_data(head,(void*)&firstNode) ,printdata, p);
	delete_gragh(head);
	

	
  return 0;
}