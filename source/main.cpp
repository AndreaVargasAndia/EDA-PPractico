// Alumna: Andrea Vargas Andia
#include <iostream>
#include "arbolb_mas.h"
using namespace std;

int main()
{
    int i, n, t;
    /*n=20;
    int arr[20]={1,2,3,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
    for(i = 0; i < n; i++)
    {
        t=arr[i];
        seq_insert(t);
    }
    printer.print();*/
    srand(time(NULL));
    int cant;
    cout<<"cuantos valores:";
    cin>>cant;
    int s[cant];
    for(int i=0;i<cant;i++)
    {
        s[i]=i;
        //cout<<"s"<<s[i]<<"i"<<i<<endl;
    }
    for(int i=0;i<cant;i++)
    {
        t=s[i];
        seq_insert(t);
    }
    cout<<"ARBOL creado"<<endl;

    if(buscar(19)==true)
    {
        cout<<"si encontro"<<endl;
    }
    else{
        cout<<"no encontro"<<endl;
    }
    cout<<"--------------"<<endl;
    if(buscar(3)==true)
    {
        cout<<"si encontro"<<endl;
    }
    else{
        cout<<"no encontro"<<endl;
    }
    cout<<"--------------"<<endl;
    if(buscar(52)==true)
    {
        cout<<"si encontro"<<endl;
    }
    else{
        cout<<"no encontro"<<endl;
    }
    seq_insert(5);

    return 0;
}
