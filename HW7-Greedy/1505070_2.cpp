#include<iostream>

using namespace std;

int median( int * a, int p, int r, int k ){
    int x = a[r];
    int i = p-1;
    for( int j = p; j < r; j++ ){
        if( a[j] > x ){
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

void quickSort( int * a, int p, int r ){
    if( p < r ){
        int q = median( a, p, r, (r-p)/2+p );
        quickSort( a, p, q-1 );
        quickSort( a, q+1, r );
    }
}

int * greedy( int n, int * d, int v, int p ){
    int * q = new int[n];
    while( v != 0 ){
        q[p] = v/d[p];
        v = v%d[p];
        p++;
    }
    return q;
}

int main(){
    int n, v, sum;
    sum = 0;
    cout<<"Enter number of notes: "<<endl;
    cin>>n;
    int * d = new int[n];
    int * q = new int[n];
    cout<<"Enter denominations: "<<endl;
    for( int i = 0; i<n; i++){
        cin>>d[i];
    }
    cout<<"Enter the value: "<<endl;
    cin>>v;
    quickSort( d, 0, n-1 );
    q = greedy( n, d, v, 0 );
    for( int i = 0; i<n; i++ ){
        sum = sum+q[i];
    }
    cout<<"Total notes required: "<<sum<<endl;
    for( int i = 0; i<n; i++ ){
        if( q[i] != 0 )
            cout<<d[i]<<' '<<q[i]<<endl;
    }
    cout<<"\n\n";

    return 0;
}
