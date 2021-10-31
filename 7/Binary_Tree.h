#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tTreeNode{
  char data;
  struct tTreeNode *left,*right;
} TreeNode, *pTreeNode;

pTreeNode create_tree (pTreeNode left, char item, pTreeNode right) {
  pTreeNode pnew = (pTreeNode) malloc (sizeof (TreeNode));
  if (pnew==NULL) {
    return NULL;
  }
  pnew->data=item;
  pnew->left=left;
  pnew->right=right;

  return pnew;
}

bool Preorder(pTreeNode root) {
  if (root==NULL) {
    return false;
  }
  printf("%c",root->data);
  Preorder(root->left);
  Preorder(root->right);
  return true;
}

bool Inorder(pTreeNode root) {
  if (root==NULL) {
    return false;
  }
  Inorder(root->left);
  printf("%c",root->data);
  Inorder(root->right);
  return true;
}

bool Postorder(pTreeNode root) {
  if (root==NULL) {
    return false;
  }
  Postorder(root->left);
  Postorder(root->right);
  printf("%c",root->data);
  return true;
}

bool DestroyTree(pTreeNode root) {
  if (root==NULL) {
    return false;
  }

  if (root->left!=NULL) {
    DestroyTree(root->left);
  }
  if (root->right!=NULL) {
    DestroyTree(root->right);
  }
  free(root);
  return true;
}

pTreeNode CopyTree(pTreeNode root) {
  if (root==NULL) {
    return NULL;
    }
  return create_tree(CopyTree(root->left),root->data,CopyTree(root->right));
}
  