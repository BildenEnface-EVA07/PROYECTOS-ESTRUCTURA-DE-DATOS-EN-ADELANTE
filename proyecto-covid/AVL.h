#include "Nodo.h"
#include "csvabin.h"
#include <iostream>

class AVL
{
    public:
    Nodo *Raiz;
    AVL()
    {
        Raiz = nullptr;
    }

    int GetAltura(Nodo *actual)
    {
        if (actual == nullptr)
        {
            return 0;
        }
        int ladoderecho = GetAltura(actual->derecho);
        int ladoizquierdo = GetAltura(actual->izquierdo);
        if (ladoderecho > ladoizquierdo)
        {
            return ladoderecho+1;
        }
        else
        {
            return ladoizquierdo + 1;
        }
    }



    private:
    Nodo* Insertar(Nodo *padre, int dat)
    {
        if (padre == nullptr)
        {
            padre = new Nodo(dat);
        }
        else if (dat < padre->datos)
        {
            padre->izquierdo = Insertar(padre->izquierdo,dat);
        }
        else if (dat > padre->datos)
        {
            padre->derecho = Insertar(padre->derecho, dat);
        }
        padre = Balancear(padre);
        return padre;
    }

    Nodo *Agregar(int valor)
    {
        Raiz = Insertar(Raiz,valor);
        return Raiz;
    }

    Nodo* Buscar(int valor)
    {
        return Encontrar(Raiz, valor);
    }

    Nodo* Encontrar(Nodo* padre, int valor)
    {
        int valorn = valor;
        int valoractual = padre->datos;
        if (padre == nullptr)
        {
            return nullptr;
        }
        else if (padre->datos == valor)
        {
            return padre;
        }
        else if (valorn < valoractual)
        {
            return Encontrar(padre->izquierdo,valor);
        }
        else
        {
            return Encontrar(padre->derecho,valor);
        }
    }

    void Eliminar(int valor)
    {
        Nodo *valorencontrado = Buscar(valor);
        Nodo *padreencontrado = valorencontrado->padre;

        if (valorencontrado->derecho == nullptr)
        {
            if (padreencontrado == nullptr)
            {
                Raiz = valorencontrado->izquierdo;
            }
            else
            {
                if (padreencontrado->datos > valorencontrado->datos)
                {
                    padreencontrado->izquierdo = valorencontrado->izquierdo;
                }
                else if (padreencontrado->datos < valorencontrado->datos)
                {
                    padreencontrado->derecho = valorencontrado->izquierdo;
                }   
            } 
        }
        else if (valorencontrado->derecho->izquierdo == nullptr)
        {
            valorencontrado->derecho->izquierdo = valorencontrado->izquierdo;

            if (padreencontrado == nullptr)
            {
                Raiz = valorencontrado->derecho;
            }
            else
            {
                if (padreencontrado->datos > valorencontrado->datos)
                {
                    padreencontrado->izquierdo = valorencontrado->derecho;
                }
                else if (padreencontrado->datos < valorencontrado->datos)
                {
                    padreencontrado->derecho = valorencontrado->derecho;
                }
            }
        }
        else
        {
            Nodo* masizquierdo = valorencontrado->derecho->izquierdo;
            Nodo* masizquierdopadre = valorencontrado->derecho;

            while (masizquierdo->izquierdo != nullptr)
            {
                masizquierdopadre = masizquierdo;
                masizquierdo = masizquierdo->izquierdo;
            }
            masizquierdopadre->izquierdo = masizquierdo->derecho;
            masizquierdo->izquierdo = valorencontrado->izquierdo;
            masizquierdo->derecho = valorencontrado->derecho;
            if (padreencontrado == nullptr)
            {
                Raiz = masizquierdo;
            }
            else
            {
                if (padreencontrado->datos > valorencontrado->datos)
                {
                    padreencontrado->izquierdo = valorencontrado->derecho;
                }
                else if (padreencontrado->datos < valorencontrado->datos)
                {
                    padreencontrado->derecho = valorencontrado->derecho;
                }
                
            }
            
        }
        
    }

    Nodo* Balancear(Nodo* padre)
    {
        if (padre != nullptr)
        {
            int ladoizquierdo = GetAltura(padre->izquierdo);
            int ladoderecho = GetAltura(padre->derecho);

            int desbalance = ladoizquierdo - ladoderecho;
            int peso = 1;

            if (desbalance == 2)
            {
                peso = 2; // peso al lado izquierdo
            }
            if (desbalance == -2)
            {
                peso = 3; //peso al derecho
            }
            

            if (peso == 3)
            {
                int ladoderechoizquierdo = GetAltura(padre->derecho->izquierdo);
                int ladoderechoderecho = GetAltura(padre->derecho->derecho);
                int desbalancederecho = ladoderechoderecho - ladoderechoizquierdo;

                if (padre->derecho != nullptr && desbalancederecho < 0)
                {
                    return RotacionDerechaIzquierda(padre);
                    //derecha izquierda
                }
                else
                {
                    return RotacionIzquierda(padre);
                    //rotacion izquierda
                }
            }
            else if (peso == 2)
            {
                int ladoderechoizquierdo = GetAltura(padre->izquierdo->izquierdo);
                int ladoderechoderecho = GetAltura(padre->izquierdo->derecho);
                int desbalanceizquierdo = ladoderechoderecho - ladoderechoizquierdo;

                if (padre->izquierdo != nullptr && desbalanceizquierdo > 0)
                {
                    return RotacionIzquierdaDerecha(padre);
                    //izquierda derecha
                }
                else
                {
                    return RotacionDerecha(padre);
                    //rotacion derecha
                }
                
                
            }
            
        }
        return padre;
    }


    Nodo* RotacionDerecha(Nodo *padre)
    {
        
        Nodo *reemplazo = padre->izquierdo;
        padre->izquierdo = reemplazo->derecho;
        reemplazo->derecho = padre;
        return reemplazo;
    }

    Nodo* RotacionIzquierda(Nodo *padre)
    {
        Nodo *reemplazo = padre->derecho;
        padre->derecho = reemplazo->izquierdo;
        reemplazo->izquierdo = padre;
        return reemplazo;
    }

    Nodo* RotacionIzquierdaDerecha(Nodo *padre)
    {
        Nodo *reemplazo = padre->izquierdo;
        Nodo *resultado = RotacionIzquierda(reemplazo);
        padre->izquierdo = resultado;
        Nodo *terminado = RotacionDerecha(padre);
        return terminado;
    }

    Nodo* RotacionDerechaIzquierda(Nodo *padre)
    {
        Nodo *reemplazo = padre->derecho;
        Nodo *resultado = RotacionDerecha(reemplazo);
        padre->derecho = resultado;
        Nodo *terminado = RotacionIzquierda(padre);
        return terminado;
    }
};