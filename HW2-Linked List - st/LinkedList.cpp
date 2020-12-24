#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning of the linked list
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;
}


struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

int insertLast(int item)
{
    //write your codes here
    struct listNode *temp,*newNode;
    newNode=(struct listNode*)malloc(sizeof(struct listNode));
    newNode->item=item;
    newNode->next=0;
    temp=list;
    if(temp==0){
        list=newNode;
    }
    else{
        while(temp->next!=0){
            temp=temp->next;
        }
        temp->next=newNode;
    }
    return SUCCESS_VALUE;
}

int insertBefore(int oldItem, int newItem)
{
	//write your codes here
	struct listNode *temp,*prev,*newNode,*old;
	newNode=(struct listNode*)malloc(sizeof(struct listNode));
	newNode->item=newItem;
	temp=list;
	if(temp==0){
        newNode->next=0;
        list=newNode;
	}
	else{
        old=searchItem(oldItem);
        if(old!=0){
            while(temp!=old){
                prev=temp;
                temp=temp->next;
            }
            newNode->next=temp;
            prev->next=newNode;
        }
        else{
            newNode->next = list ; //point to previous first node
            list = newNode ;
        }
	}
	return SUCCESS_VALUE;
}

int deleteAfter(int item){
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
    if(temp == 0)
        return NULL_VALUE ; //item not found to delete
	else{
    	while(temp!= 0){
            prev=temp;
            if(temp->item==item){
                temp=temp->next;
                break ;
            }
            temp=temp->next ; //move to next node
        }
        if(temp==0)
            return NULL_VALUE;
        else{
            prev->next=temp->next ;
            free(temp);
        }
	}

	return SUCCESS_VALUE ;
}

int deleteLast()
{
    //write your codes here
    struct listNode *temp,*prev;
	temp = list ;
	if(temp==0)
        return NULL_VALUE;
    else{
        while(temp->next!=0){
            prev=temp;
            temp=temp->next;
        }
        prev->next=0;
        free(temp);
    }
    return SUCCESS_VALUE;
}



int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert item at last. 5. Print. 6. exit.\n");
        printf("7. Insert new item before old item. 8. Delete after one item. 9. Delete from last. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7){
            int oldItem,newItem;
            printf("Insert old item: \n");
            scanf("%d", &oldItem);
            printf("Insert new item: \n");
            scanf("%d", &newItem);
            insertBefore(oldItem,newItem);
        }
        else if(ch==8)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==9){
            deleteLast();
        }
    }

}
