// Alumna: Andrea Vargas Andia
#ifndef ARBOLB_MAS_H
#define ARBOLB_MAS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
int maxval=3;
struct BTreeNode
{
    int *key;
    BTreeNode **ptr_hijos;
    bool leaf;
    int tam;
}*root = NULL,*nodo=NULL, *x=NULL,*padre=NULL;

BTreeNode* init()
{
    int i;
    nodo = new BTreeNode;
    nodo->key = new int[maxval];
    nodo->ptr_hijos = new BTreeNode *[maxval+1];
    nodo->leaf = true;
    nodo->tam = 0;
    for (i = 0; i < maxval+1; i++)
    {
        nodo->ptr_hijos[i] = NULL;
    }
    return nodo;
}
void ordenar(int *n, int tam_)
{
    int i, j, temp;
    for (i = 0; i <tam_; i++)
    {
        for (j = i; j <= tam_; j++)
        {
            if (n[i] > n[j])
            {
                temp = n[i];
                n[i] = n[j];
                n[j] = temp;
            }
        }
    }
}
int split_child(BTreeNode *x, int i)
{
    int j, mitad;
    BTreeNode *p1, *p2, *y;
    p2 = init();
    p2->leaf = true;
    if (i == -1)
    {
        mitad = x->key[2];
        x->key[2] = 0;
        p1 = init();
        p1->leaf = false;
        x->leaf = true;
        for (j = 2; j < maxval; j++)
        {
            // pone los ultimos en un nuevo nodo luego los elimina
            p2->key[j - 2] = x->key[j];
            p2->ptr_hijos[j - 2] = x->ptr_hijos[j];
            p2->tam++;
            x->key[j] = 0;
            x->tam--;
        }
        for(j = 0; j < maxval+1; j++)
        {
            x->ptr_hijos[j] = NULL;
        }
        // une con los hijos
        p1->key[0] = mitad;
        p1->ptr_hijos[p1->tam] = x;
        p1->ptr_hijos[p1->tam + 1] = p2;
        p2->key[0]=p1->key[0];
        p1->tam++;
        root = p1;
    }
    else
    {
        // nodos a punto de llenarse
        y = x->ptr_hijos[i];
        mitad = y->key[2];
        y->key[2] = 0;
        for (j = 2; j < maxval; j++)
        {
            p2->key[j - 2] = y->key[j];
            p2->tam++;
            y->key[j] = 0;
            y->tam--;
        }
        x->ptr_hijos[i + 1] = y;
        p2->key[0]=mitad;
        x->ptr_hijos[i + 1] = p2;
    }
    return mitad;
}

bool buscar(int valor)
{
    if (root == NULL)
    {
        cout << "arbol esta vacio\n";
    }
    else
    {
        BTreeNode *recorr = root;
        while (recorr->leaf == false) {
          for (int i = 0; i < recorr->tam; i++) {
            if (valor < recorr->key[i]) {
              //lado izq raiz
              recorr = recorr->ptr_hijos[i];
              break;
            }
            if (i == recorr->tam - 1) {
              //lado derecho o ultimo numero de la raiz
              recorr = recorr->ptr_hijos[i + 1];
              break;
            }
          }
        }
        for (int i = 0; i < recorr->tam; i++) {
          if (recorr->key[i] == valor) {
            //cout << "encontrado\n";
            return true;
          }
        }
        //cout << "no encontrado\n";
        return false;
    }
}

BTreeNode* recorre(BTreeNode *r,BTreeNode *hijo)
{
    // para obtener el nodo padre
    BTreeNode *pdr;
    if (r->leaf || (r->ptr_hijos[0])->leaf)
    {
        return NULL;
    }
    for (int i = 0; i < r->tam+1; i++)
    {
        if (r->ptr_hijos[i] == hijo)
        {
            pdr=r;
            return pdr;
        }
        else
        {
            pdr = recorre(r->ptr_hijos[i],hijo);
            if (pdr != NULL)
            {
              return pdr;
            }
        }
    }
    return pdr;
}


void seq_insert(int numero)
{
    int i, temp;
    if (root==NULL)
    {
        root=init();
        x=root;
    }
    else
    {
        x=root;
        if(buscar(numero)==true)
        {
            cout<<"el elemento ya esta ingresado"<<endl;
        }
        else
        {
            if (x->leaf == true && x->tam == maxval)
            {
                //primer split raiz [1 2 3 5]
                temp = split_child(x, -1);
                x = root;
                for (i = 0; i < (x->tam); i++)
                {
                    if ((numero >x->key[i]) && (numero< x->key[i + 1]))
                    {
                        i++;
                        break;
                    }
                    else if (numero < x->key[0])
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }

                }
                x = x->ptr_hijos[i];
            }
            else
            {
                // split internos
                while (x->leaf == false)
                {
                    for (i = 0; i < (x->tam); i++)
                    {
                        if ((numero > x->key[i]) && (numero < x->key[i + 1]))
                        {
                            i++;
                            break;
                        }
                        else if (numero < x->key[0])
                        {
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                    if ((x->ptr_hijos[i])->tam == maxval && x->ptr_hijos[i]->ptr_hijos[maxval]==NULL)
                    {
                        temp = split_child(x, i);
                        x->key[x->tam] = temp;
                        x->tam++;
                        continue;
                    }
                    else
                    {
                        if(x->tam==maxval+1)
                        {
                            padre=root;
                            if(x==root)
                            {
                                // raiz se llena
                                BTreeNode *p1, *p2, *nw;
                                p1=init();
                                int mitad=padre->key[2];

                                for(int u=0;u<maxval-1;u++)
                                {
                                    p1->key[u]=padre->key[u];
                                    p1->ptr_hijos[u]=padre->ptr_hijos[u];
                                    p1->ptr_hijos[u]->leaf=true;
                                    p1->ptr_hijos[u]->tam=maxval-1;
                                    p1->tam=maxval-1;
                                }
                                p1->leaf=false;
                                p1->ptr_hijos[2]=padre->ptr_hijos[2];
                                p1->ptr_hijos[2]->leaf=true;

                                p2 = init();
                                p2->key[0]=padre->key[maxval];
                                for(int u=0;u<maxval-1;u++)
                                {
                                    p2->ptr_hijos[u]=padre->ptr_hijos[maxval+u];
                                    p2->ptr_hijos[u]->leaf=true;
                                    p2->ptr_hijos[u]->tam=maxval-1;

                                }
                                p2->tam=1;
                                p2->leaf=false;
                                nw=init();
                                nw->key[0]=mitad;
                                nw->ptr_hijos[0]=p1;
                                nw->ptr_hijos[1]=p2;
                                nw->tam=1;
                                nw->leaf=false;
                                root=nw;
                                root->tam=1;
                                x=root;
                                x=x->ptr_hijos[1]->ptr_hijos[1];
                                x->tam=1;
                                x->leaf=true;

                            }
                            else{
                                //algun nodo de la raiz se llena
                                BTreeNode *recor;
                                recor=root;
                                BTreeNode *pt;
                                pt=init();
                                pt=recorre(recor,x);
                                //if(pt==root){cout<<"es la cabeza"<<endl;}

                                BTreeNode *p1, *p2, *nw,*nwpt;

                                p1=init();
                                p1->leaf=false;
                                int mitd=x->key[2];//va al root
                                int nwp=x->key[maxval];// nuevo padre
                                for(int u=0;u<maxval-1;u++)
                                {
                                    p1->key[u]=x->key[u];
                                    p1->ptr_hijos[u]=x->ptr_hijos[u];
                                    p1->ptr_hijos[u]->leaf=true;
                                    p1->ptr_hijos[u]->tam=maxval-1;
                                    p1->tam=maxval-1;
                                }
                                p1->ptr_hijos[maxval-1]=x->ptr_hijos[maxval-1];
                                p1->ptr_hijos[maxval-1]->leaf=true;

                                p2 = init();
                                p2->key[0]=x->key[3];
                                for(int u=0;u<maxval-1;u++)
                                {
                                    p2->ptr_hijos[u]=x->ptr_hijos[maxval+u];
                                    p2->ptr_hijos[u]->leaf=true;
                                }
                                p2->tam=1;
                                p2->ptr_hijos[0]->tam=2;
                                p2->ptr_hijos[1]->tam=2;
                                p2->leaf=false;

                                pt->key[pt->tam]=mitd;
                                pt->tam++;
                                pt->ptr_hijos[1]=p1;
                                pt->ptr_hijos[2]=p2;
                                x=pt;
                                x=x->ptr_hijos[2]->ptr_hijos[1];
                                x->tam=1;
                                x->leaf=true;
                            }
                        }
                        else{
                            x = x->ptr_hijos[i];
                        }
                    }
                }

            }

        }
    }
    x->key[x->tam] = numero;
    ordenar(x->key, x->tam);
    x->tam++;
}

#endif // ARBOLB_MAS_H
