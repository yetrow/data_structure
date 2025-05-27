#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//搜索
//查找min,max
//高度

typedef struct BstNode{
    int data;
    struct BstNode* left;
    struct BstNode* right;
}BstNode;

BstNode* GetNew(int data)
{
    BstNode* new_root=(BstNode*)malloc(sizeof(BstNode));
    new_root->data=data;
    new_root->left=new_root->right=NULL;
    return new_root;
}

BstNode* Insert(BstNode* root,int data)
{
    if(root==NULL)  root=GetNew(data);
    else if(data<root->data)    root->left=Insert(root->left,data);
    else    root->right=Insert(root->right,data);
    return root;
}

bool search(BstNode* root,int data) 
{
    if(root==NULL)  return false;
    else if(data==root->data)    return true;
    else if(data<root->data)    return search(root->left,data);
    else return search(root->right,data);
}

int FindMin(BstNode* root)
{
    if(root==NULL)
    {
        printf("error:tree is empty\n");
        return -1;
    }
    while(root->left!=NULL) root=root->left;

    return root->data;
}

int FindMax(BstNode* root)
{
    if(root==NULL)
    {
        perror("tree is empty\n");
        return -1;
    }
    else if(root->right==NULL) return root->data;

    return FindMax(root->right);
}

//时间复杂度O(n)
int FindHeight(BstNode* root)
{
    if(root==NULL)  return -1; //树为空时高度为0

    int leftHeight=FindHeight(root->left);
    int rightHeight=FindHeight(root->right);
    if(leftHeight>rightHeight)  return leftHeight+1;

    else return rightHeight+1;
}

int main(void)
{
    BstNode* root=NULL;
    root=Insert(root,1);
    root=Insert(root,4);
    root=Insert(root,3);
    root=Insert(root,5);
    root=Insert(root,2);
    int num=1;
    //scanf_s("%d",&num);
    if(search(root,num)==true)    printf("found\n");
    else printf("not found\n");

    printf("the min is %d\n",FindMin(root));
    printf("the max is %d\n",FindMax(root));
    
    printf("the tree's height is %d\n",FindHeight(root));

    return 0;

}