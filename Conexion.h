#pragma once

#include <iostream>
#include <cmath>
class Nodo;
#include "Nodo.h"

using namespace std;
//La clase Conexion es usada para representar la conexion entre 2 nodos, si nodo A tiene conexion a nodo B
//entonces la conexion hacia B debe contener, distancia hacia B, velocidad hacia B, y el nodo B, todo esto respecto al nodo A
class Conexion{
    public:
        Nodo* destino;
        int velocidad;
        int distancia;
        Conexion(Nodo*,int,int);
        int calcularTiempoConexion(int);
};

//constructor de Conexion
Conexion::Conexion(Nodo* destino, int velocidad, int distancia){
    this->destino = destino;
    this->velocidad = velocidad;
    this->distancia = distancia;
}

//Debido a que un archivo mas grande que la velocidad de la conexion implica que debera particionarse
//puedo calcular la cantidad de particiones necesarias dividiendo el tamaño del archivo con la velocidad de la conexion
//y aproximar hacia arriba, luego este numero actua como multiplicador para la distancia y asi determinar el tiempo de conexion
//de un nodo a otro
//el tiempo en segundos retornado sera un numero entero de tipo int
int Conexion::calcularTiempoConexion(int sizeArchivo){
    //sizeArchivo lo hago double temporalmente para poder dividirlo y conservar el decimal y asi poder aproximar hacia arriba
    double particiones = ceil(static_cast<double>(sizeArchivo)/this->velocidad);
    return particiones*this->distancia;
}

