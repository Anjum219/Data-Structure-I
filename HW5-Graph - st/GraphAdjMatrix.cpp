#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int * color;
	int * parent;
	int * dist;
	int * d;
	int * f;
	int time;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs();
	void dfsVisit(int u);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    color=new int[nVertices];
	parent=new int[nVertices];
	dist=new int[nVertices];
    d=new int[nVertices];
	f=new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    if(matrix[u][v]==1)
        return true;
    else
        return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices) return 0;
    int count=0;
    int i;
    for(i=0;i<nVertices;i++){
        if(matrix[u][i]==1)
            count++;
    }
    return count;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    int count=0;
    int i;
    for(i=0;i<nVertices;i++){
        if(matrix[u][i]==1 && matrix[v][i]==1)
            count++;
    }
    if(count==0)
        return false;
    else
        return true;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int u,v;
        u=q.dequeue();
        for(int i=0; i<nVertices; i++){
            if(matrix[u][i]==1){
                v=i;
                if(color[v]==WHITE){
                color[v]=GREY;
                dist[v]=dist[u]+1;
                parent[v]=u;
                q.enqueue(v);
                }
            }
        }
        color[u]=BLACK;
    }

}

void Graph::dfsVisit(int u){
    time=time+1;
    d[u]=time;
    color[u]=GREY;
    for(int i=0; i<nVertices; i++){
        int v;
        if(matrix[u][i]==1){
            v=i;
            if(color[v]==WHITE){
                parent[v]=u;
                dfsVisit(v);
            }
        }
    }
    color[u]=BLACK;
    time=time+1;
    f[u]=time;
}

void Graph::dfs()
{
    //write this function
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
    }
    time=0;
    for(int i=0; i<nVertices; i++){
        if(color[i]==WHITE){
            dfsVisit(i);
        }
    }

    /*for(int i=0;i<nVertices;i++){
        printf("%d %d\n",i,color[i]);
    }
    printf("\n");
    for(int i=0;i<nVertices;i++){
        printf("%d %d\n",i,d[i]);
    }
    printf("\n");
    for(int i=0;i<nVertices;i++){
        printf("%d %d\n",i,f[i]);
    }
    printf("\n");*/
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return INFINITY ;
    bfs(u);
    return dist[v];
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(matrix) delete [] matrix;
    matrix = 0 ;
    if(color) delete [] color;
    color = 0 ;
    if(dist) delete [] dist;
    dist = 0 ;
    if(parent) delete [] parent;
    parent = 0 ;
    if(d) delete [] d;
    d = 0 ;
    if(f) delete [] f;
    f = 0 ;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2. Remove edge. 3. Is edge. \n");
        printf("4. Get degree. 5. Print Graph  6. Exit.\n");
        printf("7. Has common adjacent. 8. get shortest distance. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("is edge %d\n",g.isEdge(u,v));
        }
        else if(ch==4){
            int u;
            scanf("%d",&u);
            printf("Degree is %d\n",g.getDegree(u));
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7){
            int u,v;
            scanf("%d %d", &u, &v);
            printf("has common adjacent %d\n", g.hasCommonAdjacent(u,v));
        }
        else if(ch==8){
            int u,v;
            scanf("%d %d", &u, &v);
            printf("Shortest distance is %d\n", g.getDist(u,v));
        }
        /*else if(ch==9){
            g.dfs();
        }*/
    }

}
