#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <stack>
#include <queue>

#include "Nodo.h"
using namespace std;

//La clase Grafo tendra un vector de nodos de tipo Nodo, y en esta clase se iterara en busca del mejor camino
//usando el algoritmo de Bellman-Ford
//Este grafo fue implementado con la idea que cada nodo tiene multiples aristas(Conexion)
//las Conexiones contienen atributos necesarios para calcular el viaje, ademas del nodo destino
//cada Nodo es agregado a un vector de nodos, y cuando se quiere establecer una conexion a un nodo
//se le aplica a dicho nodo->conexiones y como conexiones es un vector de Conexion, le agrego la nueva Conexion
class Grafo{
    private:
        vector<Nodo*> nodos;
    public:
        Grafo();
        void insertarNodoAlGrafo(Nodo*);
        void insertarConexion(Nodo*,Nodo*,int, int);
        void establecerConexion(string,string,int,int);
        bool existeNodoEnGrafo(string);
        Nodo* getNodoEnGrafo(string);
        vector<pair<Nodo*, Nodo*>> bellmanFord(Nodo*,Nodo*, int);
        string mostrarServidores();
        string conexionesDeUnServidor(string);
        

};

//constructor de Grafo
Grafo::Grafo(){}


//inserta un nodo en el grafo
//condicion: el nodo no debe ser NULL y debe ser nuevo en el grafo para poder ser insertado
void Grafo::insertarNodoAlGrafo(Nodo* nuevoNodo){
    if(nuevoNodo){
        if(!existeNodoEnGrafo(nuevoNodo->id)){//si no existe en el grafo
            this->nodos.push_back(nuevoNodo);
        }
        else{
            cout<<"error: nodo repetido, no se agregara al grafo"<<endl;
        }
    }
    else{
        cout<<"ERROR: se esta intentando meter un NULL al grafo"<<endl;
    }
}


//establece la conexion entre dos nodos
//ambos nodos deben pertenecer previamente al grafo, si no pertenecen al grafo, no establecera la conexion.
//usa el parametro 'origen' y le asigna 'destino' como una nueva conexion de origen a destino
void Grafo::insertarConexion(Nodo* origen, Nodo* destino,int velocidad, int distancia){
    if(origen && destino){
        if(existeNodoEnGrafo(origen->id) && existeNodoEnGrafo(destino->id)){
            Conexion* nuevaConexion = new Conexion(destino,velocidad,distancia);
            if(origen->existeConexion(nuevaConexion) == false){
                //si origen aun no tenia esta conexion
                //entonces se la agrego
                origen->conexiones.push_back(nuevaConexion);
            }
            else{
                cout<<"error(leve): conexion repetida"<<endl;
            }
        }
        else{
            cout<<"error: se esta intentando conectar nodos que no pertenecen al grafo aun"<<endl;
        }
    }
    else{
        cout<<"ERROR: se esta intentando conectar con o desde NULL"<<endl;
    }
}

//Busqueda secuencial que retorna true si existe un nodo con el mismo ID en el grafo
//false sino
bool Grafo::existeNodoEnGrafo(string idBuscada){
    for(int i = 0 ; i < this->nodos.size();i++){
        Nodo* nodoActual = this->nodos[i];
        if(nodoActual->id == idBuscada){
            return true;
        }
    }
    return false;
}

//Retorna un nodo a partir de su ID
//busca secuencialmente(O(n)) un nodo en el grafo a partir de su ID
//punto critico: si no lo encuentra retorna NULL, es necesario corroborar que existe el nodo que este metodo retorne
//para evitar enviarle una instruccion a NULL
Nodo* Grafo::getNodoEnGrafo(string idBuscada){
    for(int i = 0 ; i < this->nodos.size();i++){
        Nodo* nodoActual = this->nodos[i];
        if(nodoActual->id == idBuscada){
            return nodoActual;
        }
    }
    return NULL;
}

//metodo auxiliar para facilitar el proceso de establecer conexiones en el grafo
void Grafo::establecerConexion(string idCliente,string idServidor, int speed,int distance){
    Nodo* nodoOrigen = this->getNodoEnGrafo(idCliente);
    Nodo* nodoDestino = this->getNodoEnGrafo(idServidor);
    if(nodoOrigen && nodoDestino){
        this->insertarConexion(nodoOrigen,nodoDestino,speed,distance);
        this->insertarConexion(nodoDestino,nodoOrigen,speed,distance);
    }
}

//algoritmo que a partir de un nodo de origen, determina la mejor ruta para todos los demas nodos
//cuando establece una mejor ruta para un nodo, cambia el peso acumulado de ese nodo por el nuevo
//ademas de cambiar el 'predecesor' de ese nodo, para asi saber de donde vino la mejor ruta
//y despues se puede iterar desde destino hasta origen, ya que todas las rutas vienen desde el origen
//por lo que cualquier nodoDestino que no tenga un pesoAcumulado de infinito(inalcanzable) puede llegar al nodoOrigen
//y crear la mejor ruta y retornarla
vector<pair<Nodo*, Nodo*>> Grafo::bellmanFord(Nodo* nodoOrigen, Nodo* nodoDestino,int sizeArchivo) {
    //inicializo los tiemposAcumulados en infinito positivo y sus predecesores en NULL
    for(Nodo* nodo:nodos){//para cada nodo en el vector de nodos
        nodo->predecesor = NULL;
        nodo->tiempoAcumulado = numeric_limits<int>::max();//infinito positivo
    }
    nodoOrigen->tiempoAcumulado = 0;//el nodo origen es el unico que debe tener un acumulado de cero
    //puesto que representa la distancia o tiempo en este caso para que llegue el archivo, 
    //los nodos no explorados tienen una cantidad que se asume como inalcanzable hasta que se demuestre lo contrario
    //ahora debo recorrer cada nodo y todas las aristas(conexion) de ese nodo
    for(Nodo* nodoActual:nodos){//nodoActual en el vector de nodos
        for(Conexion* conexionActual:nodoActual->conexiones){//conexionActual de ese nodo
            //if(peso u,v+pesoAcumulado u < pesoAcumulado v)
            //entonces hay una mejor ruta
            //en este caso el peso del archivo es una variable que afecta que tan efectiva puede ser una ruta
            //por lo que haciendo uso del metodo calcularTiempoConexion y pasandole el size del archivo a enviar
            //puedo considerarlo como 'peso' de la arista
            if(nodoActual->tiempoAcumulado != numeric_limits<int>::max()
                && nodoActual->tiempoAcumulado+conexionActual->calcularTiempoConexion(sizeArchivo)< conexionActual->destino->tiempoAcumulado){
                //nodoActual->tiempoAcumulado representa u
                //conexionActual->calcularTiempoConexion(int) representa la arista u,v
                //conexionActual->destino->tiempoAcumulado representa v
                //y verifico que el peso de u no sea infinito para evitar un error de overflow
                conexionActual->destino->tiempoAcumulado = nodoActual->tiempoAcumulado+conexionActual->calcularTiempoConexion(sizeArchivo);
                conexionActual->destino->predecesor = nodoActual;//le paso su predecesor que usare mas tarde para reconstruir la ruta
            }
        }
    }
    vector<pair<Nodo*,Nodo*>> ruta;
    if(nodoDestino->tiempoAcumulado == numeric_limits<int>::max()){
        cout<<"distancia infinita equivale a un nodo inalcanzable, no existe ruta de "<<nodoOrigen->id<<" a "<<nodoDestino->id<<endl;
        return ruta;
    }

    //esta listo, ahora a reconstruir la ruta
    //desde el destino hasta el origen usando un stack para que salga en el orden correcto
    stack<pair<Nodo*,Nodo*>> rutaInvertida;
    Nodo* aux = nodoDestino;
    while(aux->predecesor){
        rutaInvertida.push(make_pair(aux->predecesor,aux));
        aux = aux->predecesor;
    }
    //invierto el orden en el vector
    while(!rutaInvertida.empty()){
        ruta.push_back(rutaInvertida.top());
        rutaInvertida.pop();
    }
    int tiempoEntreNodos = 0;
    //imprimo la ruta desde origen a destino a la vez que muestro el tiempo de conexion de cada nodo a nodo
    cout<<"Ruta desde "<<nodoOrigen->id<<" hasta "<<nodoDestino->id<<endl;
    cout<<"El tiempo mostrado incluye las particiones necesarias para el transporte del archivo"<<endl;
    for(pair<Nodo*,Nodo*> p: ruta){//por cada pair en el vector de pair ruta
        tiempoEntreNodos = p.second->tiempoAcumulado -p.first->tiempoAcumulado;
        cout<<"( "<<p.first->id<<", "<<p.second->id<<"), en "<<tiempoEntreNodos<<" segundos"<<endl;
        if(p.second->id == nodoOrigen->id) break;
    }
    //y el tiempo total desde origen a destino
    cout<<"tiempoTotal: "<<nodoDestino->tiempoAcumulado<<" segundos"<<endl;

    return ruta;
}

//Retorna un string conteniendo el nombre y el id de cada servidor
//debido a que son muchos servidores se muestran de a 3
string Grafo::mostrarServidores(){
    string r = "";
    int distribucion = 0;
    for(Nodo* nodo: nodos){
        distribucion++;
        r += "nombreServidor: "+nodo->nombre+", id: "+nodo->id+"\t";
        if (distribucion >= 3){
            r += "\n";
            distribucion = 0;
        }
    }
    return r;
}



//para mostrar las posibles conexiones que un servidor puede hacer recorriendo las conexiones disponibles.
//se hace un recorrido por nivel o busqueda por anchura
string Grafo::conexionesDeUnServidor(string servidorID){
    Nodo* servidor = this->getNodoEnGrafo(servidorID);
    if(!servidor){
        return "ERROR: no existe ese nodo en el grafo";
    }
    string r = "Nombre del servidor: "+servidor->nombre+"\n";
    vector<bool> nodosVisitados;
    for(int i = 0;i < this->nodos.size();i++){
        nodosVisitados.push_back(false);//ninguno ha sido visitado
    }
    nodosVisitados[stoi(servidorID)] = true;
    queue<Nodo*> q;
    Nodo* aux = servidor;
    q.push(aux);
    int distribucion = 0;
    while(!q.empty()){
        distribucion++;
        aux = q.front();
        q.pop();

        r += "Nodo alcanzable ID: "+aux->id+",  ";
        if (distribucion < 3){
            r += "\t";
        }

        if(distribucion >= 3){
            r+= "\n";
            distribucion = 0;
        }
        for(Conexion* conexionActual : aux->conexiones){//como es un vector no necesito preguntar si tiene
        //pero si debo preguntar si no han sido visitados aun
        if(nodosVisitados[stoi(conexionActual->destino->id)] == false){//no visitado
            q.push(conexionActual->destino);//le pongo el nodo destino, no la conexion
            nodosVisitados[stoi(conexionActual->destino->id)] = true;//el nodo destino de esta conexion fue marcado
            //y eventualmente sera concatenado por el queue
            }
        }
    }
    r += "\n";
    return r;
}

