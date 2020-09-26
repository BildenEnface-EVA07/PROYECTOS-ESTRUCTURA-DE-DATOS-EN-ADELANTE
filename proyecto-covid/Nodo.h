#include "csvabin.h"
#include <iostream>


class Nodo
{
    public:
    Nodo(int dat)
    {
        datos = dat;
        izquierdo = nullptr;
        derecho = nullptr;
    }
    int datos;
    Nodo *izquierdo;
    Nodo *derecho;
    Nodo* padre;

    private:

};