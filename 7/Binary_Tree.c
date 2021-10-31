
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Binary_Tree.h"
#include "Tree_Queue.h"//순수 포인터저장. 반드시 형변환을  동반될 것

pQueue str_to_queue(char *inp) {//각각 한글자마다 전부 TreeNode*로 바꿈
  pQueue p = createQueue(1);
  int len = strlen(inp);
  for (int i=0;i<len;i++) {
    Enqueue(p, create_tree(NULL, inp[i], NULL));
  }
  return p;
}

void printqueue(pQueueNode head) {//확인용.
  printf("%c",((pTreeNode)head->data)->data);
  if (head->next!=NULL) {
    printqueue(head->next);
  }
}

pTreeNode connect_to_left(pTreeNode root, pTreeNode left) {//노드연결 명령어
    root->left=left;
    return left;
}

pTreeNode connect_to_right(pTreeNode root, pTreeNode  right) {//노드 연결 명령어
    root->right=right;
    return right;
}

pTreeNode str_to_tree(pTreeNode root,pQueue chr_tree, pQueue temp) {//chr_tree는 최상위root 제외한 노드들이 담긴 queue, temp는 무조건 비어있는 queue
    if (IsEmptyQueue(chr_tree)) {//담겨잇는 node들이 비어있을 경우를 종료시점.
      return NULL;
    }
    
    if (IsEmptyQueue(temp)) {//가장 최상위 헤더 전용. 단 한번만 실행됨
      Enqueue(temp, root);
      
    }
    else {
      if (root->left==NULL) {//왼쪽 노드 비어있을때 연결하고 그 노드를 temp에 queue.
        Enqueue(temp, connect_to_left(root,(pTreeNode)Dequeue(chr_tree)));

      }
      else if (root->left!=NULL&&root->right==NULL) {//왼쪽 노드 안비어있고 오른쪽이 비어잇을때 그걸 연결하고 그 노드를 temp에 queue.
        Enqueue(temp, connect_to_right(root,(pTreeNode)Dequeue(chr_tree)));

      }
      else {//양쪽 다 node 들이 연결되면 그 root 주소값을 temp에 dequeue 한다.
        Dequeue(temp);
      }
    }

    str_to_tree(((pTreeNode)temp->front->data),chr_tree,temp);//헤더 값을 temp에 담긴 최우선 주소값을 넣어 recursive function 시도.
  return root;
  }


  void print_bfs(pTreeNode head,pQueue nodes) {//bfs 출력
    if (head!=NULL) {//head값이 null이 아닌 경우에 데이터 출력
    printf("%c",head->data); }

    if (head->left !=NULL) {//head의 left - child에 주소가 있으면 enqueue
    Enqueue(nodes, head->left); }
    if (head->right!=NULL) {//head의 right - child에 주소가 있으면 enqueue
    Enqueue(nodes, head->right); }

    if (!IsEmptyQueue(nodes)) {//nodes queue가 비어있는 상태가 아닌 경우 재귀함수 실행.
    print_bfs((pTreeNode)Dequeue(nodes),nodes); 
    }
    
    }


int main(void) {
  printf("Input a string : ");
  char input[40];
  scanf("%s",input);
  rewind(stdin);

  pQueue lists=str_to_queue(input);
  pQueue empty=createQueue(1);
  pTreeNode head=(pTreeNode) Dequeue(lists);
  str_to_tree(head,lists,empty);
  pQueue nodes=createQueue(1);
  

  printf("Pre - Order : ");
  Preorder(head);
  printf("\n\n");

  printf("In - Order : ");
  Inorder(head);
  printf("\n\n");

  printf("Post - Order : ");
  Postorder(head);
  printf("\n\n");

  printf("Breath - First : ");
  print_bfs(head,nodes);

  
  DestroyTree(head);
  destroyQueue(lists);
  destroyQueue(nodes);
  

    return 0;
}