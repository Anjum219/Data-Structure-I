#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}

struct treeNode * searchParent(struct treeNode * node){
    struct treeNode * temp=0;
    struct treeNode * r=0;
    temp=root;
    while(temp->item!=node->item){
        r=temp;
        if(temp->item<node->item)
            temp=temp->left;
        else
            temp=temp->right;
    }
    return r;
};

int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==0)
        return 0;
    int l,r;
    l=getSize(node->left);
    r=getSize(node->right);
    return r+l+1;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    struct treeNode * temp=0;
    int count=0;
    temp=root;
    if(node==0)
        return -1;
    else{
        while(temp!=node){
            if(node->item<temp->item){
                temp=temp->left;
                count++;
            }
            else{
                temp=temp->right;
                count++;
            }
        }
        return count;
    }
}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
    struct treeNode * t=0;
    struct treeNode * temp=0;
    int count=0;
    t=searchItem(root,item);
    temp=root;
    if(t==0)
        return -1;
    else{
        while(temp!=t){
            if(t->item<temp->item){
                temp=temp->left;
                count++;
            }
            else{
                temp=temp->right;
                count++;
            }
        }
        return count;
    }
}

int deleteItem(struct treeNode * node, int item)
{
    //write your code here, return TRUE, FALSE
    struct treeNode * t=0;
    struct treeNode * parent=0;
    t=searchItem(node,item);
    parent=searchParent(t);
    if(t==0)
        return FALSE_VALUE;
    else{
        if(t->left==0 && t->right==0){
            if(parent->left==t)
                parent->left=0;
            else
                parent->right=0;
            free(t);
        }
        else if(t->left==0){
            if(parent->left==t)
                parent->left=t->right;
            else
                parent->right=t->right;
            free(t);
        }
        else if(t->right==0){
            if(parent->left==t)
                parent->left=t->left;
            else
                parent->right=t->left;
            free(t);
        }
        else{
            struct treeNode *temp=t->right;
            while(temp->left!=0)
                temp=temp->left;
            t->item=temp->item;
            deleteItem(t->right,temp->item);
        }
        return TRUE_VALUE;
    }
}



int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    struct treeNode * temp=0;
    temp=root;
    if(temp==0)
        return -1;
    else{
        while(temp->left!=0)
            temp=temp->left;
        return temp->item;
    }
}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    struct treeNode * temp=0;
    temp=root;
    if(temp==0)
        return -1;
    else{
        while(temp->right!=0)
            temp=temp->right;
        return temp->item;
    }
}

//int rangeSearch(strcut treeNode * node, int leftBound, int rightBound) //returns number of items in the
//{
    //write your codes here
//}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit.\n");
        printf("8. Print size of tree. 9.print depth of node. \n");
        printf("10. Print depth of an item. \n");
        printf("11. Print maximum item. 12. Print minimum item. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n\n");
            else printf("Not found.\n\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7)
        {
            break;
        }
        else if(ch==8){
            printf("Size of tree is = %d\n\n",getSize(root));
        }
        else if(ch==9){
            int item;
            scanf("%d", &item);
            struct treeNode * t;
            t=searchItem(root,item);
            printf("Depth of node is = %d\n\n",calcNodeDepth(t));
        }
        else if(ch==10){
            int item;
            scanf("%d", &item);
            printf("Depth of the %d is = %d\n",item,calcDepth(item));
        }
        else if(ch==11){
            printf("Maximum item is = %d\n\n",getMaxItem());
        }
        else if(ch==12){
            printf("Minimum item is = %d\n\n",getMinItem());
        }
    }

}
