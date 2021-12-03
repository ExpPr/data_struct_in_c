#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AD_Matrix3.h"

#define INF 1000

typedef struct datas {
    char first;
    char second;
    int weight;
} Data, *pData;


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

pData return_all_data(char *np,int *pData_size) {//한줄이라도 잘못 입력되면 바로 종료.
  FILE *fep=fopen(np,"r");
  if (fep==NULL) {
    return NULL;
  }
  if (check_file_line(np)<3) {
    return NULL;//잘못된 입력.
  }
  int count=0;
  int temp_int=0;
  char temp_chr[2];
  int line=check_file_line(np),chk=0;
  int check;

  pData temp=(pData)malloc(sizeof(pData));

	char qp[10];
	fgets(qp,9,fep);
	fgets(qp,9,fep);

  for (int i=2;i<line;i++) {
    check=fscanf(fep,"%c %c %d",&temp[i-2].first,&temp[i-2].second,&temp[i-2].weight);
    if (check!=3) {
      free(temp);
      return NULL;
    }
    count++;
    temp = (pData)realloc(temp,sizeof(Data)*(count+1));

    if (fgetc(fep)!='\n') {
			fseek(fep,-1,SEEK_CUR);
		}
  }
  *pData_size=count;
  return temp;
}

pVertex* insert_all_vertex(pGragh head, pData list,int pData_size,int *size) {
  if (head==NULL||list==NULL) {
    return NULL;
  }
  int count=0;
  pVertex* vertex_list=(pVertex*)malloc(sizeof(pVertex));
  pVertex tempary_vertex;
  for (int i=0;i<pData_size;i++) {
      tempary_vertex=addVertex(head,&list[i].first);
      if (tempary_vertex!=NULL) {
            vertex_list=(pVertex*)realloc(vertex_list,sizeof(pVertex)*(count+1));
            vertex_list[count]=tempary_vertex;
            count++;
      }
      tempary_vertex=addVertex(head,&list[i].second);
      if (tempary_vertex!=NULL) {
            vertex_list=(pVertex*)realloc(vertex_list,sizeof(pVertex)*(count+1));
            vertex_list[count]=tempary_vertex;
            count++;
      }
  }
   vertex_list=(pVertex*)realloc(vertex_list,sizeof(pVertex)*(count));
   *size=count;
   return vertex_list;
}

void insert_all_arcs(pGragh head, pData list, int pData_size) {
	for (int i=0;i<pData_size;i++) {
        add_arc(head,check_data(head,(void*)&(list[i].first)),check_data(head,(void*)&(list[i].second)),list[i].weight);
        add_arc(head,check_data(head,(void*)&(list[i].second)),check_data(head,(void*)&(list[i].first)),list[i].weight);
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

pVertex shortest_vertex(pGragh head, pVertex point) {//point 기준 방문하지 않은 노드들 중 가장 weight가 작은 값을 고름
  int min=INF;
  int idk;
  int return_idk=-1;
  int line = sequence_vertex(head,point);
  if (line<0) {
    return NULL;
  }
  for (idk=0;idk<head->count;idk++) {
    if (head->pArc[line][idk]<min && head->pArc[line][idk]>0 && return_vertex(head,idk)->processed==0) {
      min=head->pArc[line][idk];
      return_idk=idk;
    }
  }
  if (return_idk==-1) {
    return NULL;//없을 경우 NULL 리턴
  }
  return return_vertex(head,return_idk);
}

void prim_algorithm(pGragh head, pVertex start) {
  int size=head->count;
  int min_weight=INF;
  int line,row;//행렬 임시 저장소
  int min_line,min_row; // 가장 최소 weigh 찾을떄 저장할 그릇. 
  pVertex visited_vertex;
  pVertex non_visited_vertex=NULL;
  bool visited[size];
  for (int i=0;i<size;i++) {
    visited[i]=false;
  }
  visited[sequence_vertex(head,start)]=true;
  start->processed=1;
  
  for (int i=0;i<size-1;i++) {
    min_weight=INF;//한번 돌떄마다 초기화
    for (int k=0;k<size;k++) {
      if (visited[k]==true) {//이미 방문했던 모든 vertex각각 실행
        visited_vertex=return_vertex(head,k);//각각 그 vertex의 "방문하지 않은" 최소 노드 탐색.
        non_visited_vertex=shortest_vertex(head,visited_vertex);
        if (non_visited_vertex==NULL) {//해당 vertex 기준으로 더이상 없으므로 그 방문한 vertex는 더이상 신경쓰지 않음.
          continue;
        }
        else {
          line=sequence_vertex(head,visited_vertex);//찾은경우
          row=sequence_vertex(head,non_visited_vertex);
          if (min_weight>head->pArc[line][row]) {//만약 현재 저장된 min_weight보다 더욱더 작은 weight값이 있으면 그 vertex값들과 그 weight를 저장함
            min_weight=head->pArc[line][row];
            min_line=line,min_row=row;
          }
        }
      }
    }
    //for int k 루프 종료되면, 가장 최소 weight가 되는 이전에 저장했던 vertex 정보와 weight를 출력함. 그리고 선택된 vertex의 방문했음을 처리
    printf("%c %c %d\n",*(char*)return_vertex(head,min_line)->data,*(char*)return_vertex(head,min_row)->data,min_weight);
    visited[min_row]=true;
    return_vertex(head,min_row)->processed=1;
  }
}

void short_way(pGragh head, pVertex start) {
  int size=head->count;
  int ping=sequence_vertex(head,start);
  int arc[size][size];
  int location;
  int distance[size];
  bool visited[size];

  int min_data_index;
  int min_weight;

  for (int i=0;i<size;i++) {
    for (int k=0;k<size;k++) {
      if (head->pArc[i][k]<=0) {
        if (i==k) {
          arc[i][k]=0;
        }
        else {
          arc[i][k]=INF;
        }
      }
      else {
        arc[i][k]=head->pArc[i][k];
      }
    }
  }
  for (int i=0;i<size;i++) {
    if (i==0) {
      memcpy(distance,arc[ping],sizeof(int)*size);
      location=ping;
      visited[ping]=true;
    }
    else {
      min_weight=INF;
      for (int i=0;i<size;i++) {
        if (visited[i]==false && distance[i]<min_weight) {
          min_weight=distance[i];
          min_data_index=i;
        }
      }
      visited[min_data_index]=true;
      for (int i=0;i<size;i++) {
        if (visited[i]==false && arc[min_data_index][i]<INF && i!=min_data_index)  {
          arc[min_data_index][i]+=min_weight;
          if (distance[i]>arc[min_data_index][i]) {
            distance[i]=arc[min_data_index][i];
          }
        }
      }
    }
    for (int i=0;i<size;i++) {
      if (i!=ping)
      printf("%c %c : %d\n",*(char*)return_vertex(head,ping)->data,*(char*)return_vertex(head,i)->data,distance[i] );
    }
    printf("\n");
  }
}

int main(void) {
    pGragh head = CreateGragh(compare_chr);
    int data_size;
    int pVertex_size;
    char file_name[40];
    printf("File name of a gragh : ");
    scanf("%s",file_name);
    rewind(stdin);
    FILE *test=fopen(file_name,"r");

    if (test==NULL) {
     printf("File is not exist\n");
     return 1; 
    }

    char first=get_first_node(file_name);

    pData data_list=return_all_data(file_name,&data_size);
    pVertex* vertex_lists= insert_all_vertex(head,data_list,data_size,&pVertex_size);
		insert_all_arcs(head,data_list,data_size);

    pVertex test_vertex=check_data(head,(void*)&first);

    if (test_vertex==NULL) {
      printf("Wrong First Data input\n");
      delete_gragh(head);
      free(vertex_lists);
      return 0;
    }
    puts("");
    printf("The graph is : \n");
    for (int i=0;i<pVertex_size;i++) {
      printdata(vertex_lists[i]->data);
      printf(" : ");
      print_all_arc_data(head,vertex_lists[i],printdata);
    }

		printf("\nMinimum spanning tree : \n");
		prim_algorithm(head,test_vertex);
		clear_processed(head);
		puts("");
    printf("Shortest path from %c :\n",first);
    short_way(head,test_vertex);
    clear_processed(head);
    delete_gragh(head);
    free(vertex_lists);
		

    return 0;
}