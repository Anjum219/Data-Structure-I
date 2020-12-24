#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int count=0;

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;
struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
	tail = 0;
}

struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if(temp->item==item){
            return temp;
		}
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

//add required codes to insert item at the beginning, remember to properly set the tail pointer!
int insertItem(int oldItem, int newItem)
{
	//write your codes here
	struct listNode *temp,*prev,*newNode,*old;
	newNode=(struct listNode*)malloc(sizeof(struct listNode));
	newNode->item=newItem;
	temp=list;
	if(temp==0){
        newNode->next=0;
        list=newNode;
        tail=newNode;
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

//add required codes to delete item, remember to properly set the tail pointer!
int deleteAfter(int item)
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
    if(temp == 0)
        return NULL_VALUE ; //item not found to delete
	else{
    	while(temp!= 0){
            prev=temp;
            if(temp->item==item&&temp->next==0){
                return NULL_VALUE;
            }
            else if((temp->item==item)&&(temp->next->next==0)){
                count=1;
                temp=temp->next;
                break;
            }
            else if(temp->item==item){
                temp=temp->next;
                break ;
            }
            temp=temp->next ; //move to next node
        }
        if(temp==0)
            return NULL_VALUE;
        else if(count==1){
            prev->next=0;
            tail=prev;
            free(temp);
            count=0;
        }
        else{
            prev->next=temp->next;
            free(temp);
        }
	}

	return SUCCESS_VALUE ;
}

int insertLast(int item)
{
    //write your codes here
    struct listNode *temp,*newNode;
    newNode=(struct listNode*)malloc(sizeof(struct listNode));
    newNode->item=item;
    newNode->next=0;
    if(list==0){
        list=newNode;
        tail=newNode;
    }
    else{
        tail->next=newNode;
        tail=newNode;
    }
    return SUCCESS_VALUE;
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item before oldItem. 2. Delete item after one item. 3. Search item. \n");
        printf("4. Insert item at the last. 5. Print. 6. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int oldItem,newItem;
            printf("Insert old item: \n");
            scanf("%d", &oldItem);
            printf("Insert new item: \n");
            scanf("%d", &newItem);
            insertItem(oldItem,newItem);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
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
    }

}
