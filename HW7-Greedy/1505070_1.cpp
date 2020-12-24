#include<iostream>
#include<cstring>

using namespace std;

#define MAX_HEAP_SIZE 100000

#define MAXREAL 999999.0

class HeapItem
{
public:
	char data; //actual data that is stored
	int key; //key value of the data, heap is constructed based on key
	HeapItem * left;
	HeapItem * right;
};

//MinHeap class, minimum item stored at the root of heap tree

class MinHeap
{
public:
	HeapItem * A; //stores heap items, e.g., nodes
	int heapLength;
	int * map;

	MinHeap() //constructor
	{
		A = new HeapItem[MAX_HEAP_SIZE];
		map = new int[MAX_HEAP_SIZE];
		heapLength=0;
		A->left = 0;
		A->right = 0;
	}

	~MinHeap() //destructor
	{
		if(map) delete [] map;
		if(A) delete [] A;
		map = 0; //set to NULL after deletion
		A = 0; //set to NULL after deletion
	}

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
	void initialize(int v[], int n)
	{
		heapLength = n;
		for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
		{
			A[i+1].data = v[i];
			A[i+1].key = MAXREAL;
			map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
		}
	}

	//this function inserts a new (data,key) pair in the heap
    //call to buHeapify is required
    void insertItem(HeapItem * hItem)
    {
        //Write your codes here
        heapLength++;
        A[heapLength].data=hItem->data;
        A[heapLength].key=hItem->key;
        map[hItem->data]=heapLength;
        buHeapify(heapLength);
    }

    //this function removes (and returns) the node which contains the minimum key value
	HeapItem * removeMin()
	{
	    //write your codes here
	    HeapItem * t;
	    t=&A[1];
	    A[1]=A[heapLength];
        A[heapLength]=*t;
        heapLength--;
        heapify(1);
        return t;
	}


    //The function updates the key value of an existing data
    //stored in the heap
	//Note that updates can result in an increase or decrease of key value
	//Call to heapify or buheapify is required
	void updateKey(int data, float key)
	{
		//Write your codes here.
        int i;
        i=map[data];
        if(A[i].key<key){
            A[i].key=key;
            heapify(i);
        }

        else if(A[i].key>key){
            A[i].key=key;
            buHeapify(i);
        }
	}


    //This function returns the key value of a data stored in heap
	int getKey(int data)
	{
		int i = map[data];
		return A[i].key;
	}

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
	void heapify(int i)
	{
		int l,r,smallest;
		while(1)
		{
			l=2*i;      //left child index
			r=2*i+1;    //right child index
			smallest=i;

			if(l>heapLength && r>heapLength)
				break; //nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

			if(A[i].key <= A[smallest].key)
				break;	//we are done heapifying
            else
			{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[smallest];
				map[A[i].data]=i;
				A[smallest]=t;
				map[A[smallest].data]=smallest;
				i=smallest;
			}

		}
	}

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
	void buHeapify(int i)
	{
        int p;
        while(p!=0){
            p=i/2;
            if(A[p].key<=A[i].key)
                break;
            else{
                HeapItem t;
                t=A[i];
                A[i]=A[p];
                map[A[i].data]=i;
                A[p]=t;
                map[A[p].data]=p;
                i=p;
            }
        }
	}

	HeapItem * huffman(){
        for( int i = 0; i < heapLength; i++ ){
            HeapItem * temp;
            temp->left = removeMin();
            temp->right = removeMin();
            temp->data = '$';
            temp->key = temp->left->key + temp->right->key;
            insertItem(temp);
        }
        return removeMin();
	}

    void printHeap()
    {
        cout<<"Heap length: heapLength"<<endl;
        for(int i=1;i<=heapLength;i++)
        {
            cout<<'('<<A[i].data<<','<<A[i].key<<')'<<' ';
        }
        cout<<"\n";
    }

	bool Empty()
	{
		if(heapLength==0)return true;
		else return false;
	}
};


int main()
{
    int n;
    char data;
    int key;
    HeapItem hItem;
    MinHeap heap;
    cout<<"Enter total number of characters: "<<endl;
    cin>>n;
    cout<<"Enter characters and frequencies: "<<endl;
    for( int i = 0; i<n; i++ ){
        cin>>hItem.data>>hItem.key;
        heap.insertItem( & hItem );
    }
    heap.printHeap();
    cout<<'\n';
    cout<<heap.huffman()->data<<' '<<heap.huffman()->key<<endl;

    return 0;
}
