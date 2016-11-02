#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _TreeNode {
  int key;
  struct _TreeNode *subNode[2];
} TreeNode;

TreeNode* root = NULL;
int treeSize = 0;

void printTree(TreeNode* node) {
  if(node) {
    printf("(");
    printTree(node->subNode[0]);
    printf("%d", node->key);
    printTree(node->subNode[1]);
    printf(")");
  }
}

void printInOrder(TreeNode* node) {
  printf("\nInorder Listing: ");
  printTree(node);
}

void freeTree(TreeNode* node) {
  if(node) {
    freeTree(node->subNode[0]);
    freeTree(node->subNode[1]);
    free(node);
  }
}

TreeNode* createNode(int k) {
  TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
  node->key = k;
  node->subNode[0] = NULL;
  node->subNode[1] = NULL;
  treeSize++;
  return node;
}

TreeNode* search(TreeNode* treeNode, int key) {
  TreeNode* node = treeNode;
  while(node) {
    if(node->key==key) break;
    if(key > node->key) {
      node = node->subNode[1];
    }
    else {
      node = node->subNode[0];
    }
  }
  if(node) {
    printf("\nSearching      : %5d EXISTS!", key);
  }
  else {
    printf("\nSearching      : %5d NOT EXIST", key);
  }
  return node;
}

//-1: not found, 0: left, 1: right, 2: self
TreeNode* findParent(TreeNode* treeNode, int key, int *child) {
  *child = -1;
  if(treeNode==NULL) return NULL;

  *child = 2;
  if(treeNode->key == key) return treeNode;
  
  TreeNode* node = treeNode;
  TreeNode* pNode;
  while(node) {
    if(node->key==key) break;
    pNode = node;
    *child = (key > node->key) ? 1 : 0;
    node = node->subNode[*child];
  } 
  return pNode;
}

TreeNode* insert(TreeNode* treeNode, int key) {
  int child;
  TreeNode* pNode = findParent(treeNode, key, &child);  
  if(pNode==NULL) {
    pNode = createNode(key);
    root = pNode;
    printf("\nInserting      : %5d SUCCEEDED.", key);
    return pNode;
  }
  TreeNode* node;
  if(child==2) {
    node = pNode;
    printf("\nInserting      : %5d FAILED(already in the list)", key);
  }
  else if (pNode->subNode[child]) {
    printf("\nInserting      : %5d FAILED(already in the list)", key);
    node = pNode->subNode[child];
  }
  else {
    node = pNode->subNode[child] = createNode(key);
    printf("\nInserting      : %5d SUCCEEDED.", key);
  }
  return node;  
}

//child: 0 - no child,  1 - has child
TreeNode* findMaxParent(TreeNode* treeNode, int *child) {
  TreeNode* node = treeNode;
  TreeNode* pNode = treeNode;
  *child = 0;
  while(node->subNode[1]) {
    pNode = node;
    node = node->subNode[1];
  }
  if(pNode!=node) *child = 1;
  return pNode;
}

void delete(TreeNode* treeNode, int key) {
  int child;
  TreeNode* pNode = findParent(treeNode, key, &child);
  
  TreeNode* node;
  TreeNode* toBeDel;
  
  if(child==2) {      //root is to be deleted
    node = pNode;
  }
  else if(child==-1 || !pNode->subNode[child]) {    //root is null or key not found
    printf("\nDeleting       : %5d FAILED(not in the list)", key);
    return;
  }
  else {              //found key in sub nodes of root
    node = pNode->subNode[child];
  }
  
  if(node->subNode[0] && node->subNode[1]) {    //node has two children
    int c;
    TreeNode* leftMaxP = findMaxParent(node->subNode[0], &c);   //find max key in left tree
    TreeNode* leftMaxNode = leftMaxP;
    if(c==1) {        //has right child
      leftMaxNode = leftMaxP->subNode[1];
      node->key = leftMaxNode->key;     //copy max key in left tree to the deleted node
      leftMaxP->subNode[1] = leftMaxNode->subNode[0]; 
    }
    else {            //left node has no right child
      node->key = leftMaxNode->key;     //copy key value
      node->subNode[0] = leftMaxNode->subNode[0];
    }
    toBeDel = leftMaxNode;
  }
  else if(node->subNode[0]) {     //node only has left child
    node->key = node->subNode[0]->key;
    toBeDel = node->subNode[0];
    node->subNode[1] = node->subNode[0]->subNode[1];
    node->subNode[0] = node->subNode[0]->subNode[0];
  }
  else if(node->subNode[1]) {     //node only has right child
    toBeDel = node->subNode[1];
    node->key = node->subNode[1]->key;
    node->subNode[0] = node->subNode[1]->subNode[0];
    node->subNode[1] = node->subNode[1]->subNode[1];
  }
  else {                          //node has no child
    toBeDel = node;
    if(child==2) {                //the only root is deleted
      root = NULL;
    }
    else {                        //parent's child node set to null
      pNode->subNode[child] = NULL;
    }
  }
  free(toBeDel); 
  treeSize--;
  toBeDel = NULL;
  printf("\nDeleting       : %5d. SUCCEEDED.", key);
  //printInOrder(root);
}


int main(int argc, char * argv[]) {
  printf("Usage: %s [cmdfile]\n\n", argv[0]);
  if (argc>=3){
    exit(0);
  }
  char cmdfile[100];
  char buff[10];
  if (argc==2) {
    strcpy(cmdfile, argv[1]);
  }
  else if(argc==1) {
    printf("\nPlease specify input file (default f.txt): ");
    fgets(cmdfile, 99, stdin);
    if(strcmp(cmdfile, "\n")==0) strcpy(cmdfile, "f.txt");
    for(int i=0; i<99; i++) {
      if(cmdfile[i]=='\n') {
        cmdfile[i] = '\0';
        break;
      }
    }
  }
  
  FILE *fin;
  if ((fin=fopen(cmdfile,"r"))==NULL){
    printf("\nfopen %s error", cmdfile);
    exit(0);
  }
  int value;
  int cmd;
  while(fscanf(fin, "%9s", buff)!=EOF) {
    //printf("\nInput is %s", buff);
    switch(buff[0]) {
    case 'i':
    case 'I':
      cmd = 1;
      break;
    case 'd':
    case 'D':
      cmd = 2;
      break;
    case 's':
    case 'S':
      cmd = 4;
      break;
    case 'p':
    case 'P':
      cmd = 3;
      printInOrder(root);
      break;
    default:
      sscanf(buff, "%d", &value);
      switch(cmd) {
      case 1:
        insert(root, value);
        break;
      case 2:
        delete(root, value);
        break;
      case 4:
        search(root, value);
        break;
      }
    }
  }
  freeTree(root);
  return 0;
}

