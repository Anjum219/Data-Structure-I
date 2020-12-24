#include<iostream>>

using namespace std;

int median( int * a, int p, int r, int k ){
    int x = a[r];
    int i = p-1;
    for( int j = p; j < r; j++ ){
        if( a[j] <= x ){
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    int t = a[i+1];
    a[i+1] = a[r];
    a[r] = t;
    if( k == i+1 )
        return i+1;
    else if( k < i+1 )
        median( a, p, i, k );
    else
        median( a, i+2, r, k );
}

/*int Partition( int * a, int p, int r ){
    int x = median( a, p, r, (r-p)/2+p );
    int i = p-1;
    for( int j = p; j < r; j++ ){
        if( a[j] <= x ){
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    int t = a[i+1];
    a[i+1] = a[r];
    a[r] = t;
    return i+1;
}*/

void quickSort( int * a, int p, int r ){
    if( p < r ){
        int q = median( a, p, r, (r-p)/2+p );
        quickSort( a, p, q-1 );
        quickSort( a, q+1, r );
    }
}

int main(){
    int * a;
    int n, r;
    cout<<"Enter the number of elements: "<<endl;
    cin>>n;
    a= new int[n];
    cout<<"Enter the elements: "<<endl;
    for( int i = 0; i < n; i++ ){
        cin>>a[i];
    }
    cout<<median( a, 0, n-1, (n-1)/2)<<endl;
    quickSort( a, 0, n-1 );
    for( int i = 0; i < n; i++ ){
        cout<<a[i]<<' ';
    }
    cout<<"\n\n";
    //cout<<Partition( a, 0, n-1 );
    return 0;
}
