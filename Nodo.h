#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include "Conexion.h"

//clase Nodo, debe tener el id, nombre y tipo, los 3 seran string
//ademas cada nodo puede tener multiples conexiones, por lo que necesitara un vector de Conexion
class Nodo{
    public:
        string id,nombre,tipo;
        vector<Conexion*> conexiones;
        Nodo* predecesor;
        int tiempoAcumulado;
        Nodo(string,string,string);
};

//constructor de Nodo
//tiempoAcumulado es una variable usada para el algoritmo de Bellman-Ford
//predecesor es otra variable usada para el algoritmo de Bellman-Ford, usado para reconstruir la mejor ruta de origen a destino
Nodo::Nodo(string id,string nombre, string tipo){
    this->id = id;
    this->nombre = nombre;
    this->tipo = tipo;
    this->predecesor = NULL;
    this->tiempoAcumulado = 0;
}

