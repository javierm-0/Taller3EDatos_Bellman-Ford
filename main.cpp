#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


#include "Grafo.h"

//Integrantes:
//Javier Moraga Sanhueza
//Inti Cerda Ramirez


//Este metodo esta encargado de crear Nodos con la informacion entregada e insertarlos en el grafo
//se verifica, se crea el nodo y se inserta si la linea leida no es un encabezado
void leerYcrearNodos(Grafo* grafo){
    ifstream archivo("servidores.csv");
    if(archivo.is_open()){
        string linea = "";
        while(getline(archivo,linea)){
            istringstream splitter(linea);//le paso el contenido de linea al splitter
            string id = "", nombre = "", tipo = "";

            getline(splitter,id,',');
            getline(splitter,nombre,',');
            getline(splitter,tipo,',');
            if(linea != "" && id != "id" && nombre != "nombre" && tipo != "tipo"){
            //mientras no sea una linea de encabezado ni una linea en blanco
            Nodo* nuevoNodo = new Nodo(id,nombre,tipo);
            grafo->insertarNodoAlGrafo(nuevoNodo);
            }
            else if(linea == ""){//indicar cual fue la razon por la que esta linea fue evitada
                cout<<"una linea en blanco dentro del archivo 'servidores.csv' fue evitada"<<endl;
            }
            else{//la razon fue de que era una linea de encabezado
                cout<<"El archivo 'servidores.csv' posee encabezado y se evito la creacion de un nodo erroneo"<<endl;
            }

        }
        archivo.close();
    }
    else{
        cout<<"No se pudo abrir: 'servidores.csv'"<<endl;
    }
}

//funcion bool
//si encuentra un char que no sea un digito retorna false
//retorna true si no se logra demostrar que que no es digito
//retorna false si es un espacio en blanco
bool soloDigitos(string numero){
    if(numero == "") return false;
    for(int i = 0;i < numero.size();i++){
        if(!isdigit(numero[i])) return false;
    }
    return true;
}

//Esta funcion esta encargada de acceder al archivo conexiones.csv
//corrobora si son datos convertibles y establece las conexiones entre los nodos del grafo
void leerYestablecerConexiones(Grafo* grafo){
    ifstream archivoConexiones("conexiones.csv");
    if(archivoConexiones.is_open()){
        string linea = "";
        while(getline(archivoConexiones,linea)){
            istringstream splitterB(linea);
            string idCliente = "",idServidor = "", strVelocidad = "", strDistancia = "";
            int velocidad = 0,distancia = 0;

            getline(splitterB,idCliente,',');
            getline(splitterB,idServidor,',');
            getline(splitterB,strVelocidad,',');
            getline(splitterB,strDistancia,',');
            if(soloDigitos(strVelocidad)){
                velocidad = stoi(strVelocidad);
            }
            if(soloDigitos(strDistancia)){
                distancia = stoi(strDistancia);
            }
            //idCliente,idServidor,velocidad,distancia
            if(linea != "" && idCliente != "idCliente" && idServidor != "idServidor" 
            && strVelocidad != "velocidad" && strDistancia != "distancia"){
                //corroborar que la linea actual no sea ni un espacio en blanco ni un encabezado
                //y establecer la conexion
                grafo->establecerConexion(idCliente,idServidor,velocidad,distancia);
                //cout<<"idCliente: "<<idCliente<<", idServidor: "<<idServidor<<
                //", velocidad: "<<velocidad<<", distancia: "<<distancia<<endl;
            }
            else if(linea == ""){//indicar cual fue la razon por la que esta linea fue evitada
                cout<<"una linea en blanco dentro del archivo 'conexiones.csv' fue evitada"<<endl;
            }
            else{//la razon fue de que era una linea de encabezado
                cout<<"El archivo 'conexiones.csv' posee encabezado y se evito la creacion de un nodo erroneo"<<endl;
            }
        }

        archivoConexiones.close();
    }
}

//funcion auxiliar usada en el menu
//encargada de preguntar por el ID del emisor
//preguntara hasta que sea un ID valido o hasta que se ingrese -1
//si se ingresa -1 retornara NULL para mostrar que no se ha elegido ningun emisor
Nodo* elegirEmisor(Grafo* grafo){
    string inputID = "";
    Nodo* emisorElegido;
    while(true){
        cout<<"Ingrese el ID del servidor para elegirlo como emisor"<<endl;
        cout<<"Ingrese '-1' para regresar al MENU"<<endl;
        getline(cin,inputID);
        if(inputID == "-1"){
            return NULL;
        }
        emisorElegido = grafo->getNodoEnGrafo(inputID);
        if(emisorElegido){
            return emisorElegido;
        }
        else{
            cout<<"error: ID invalido"<<endl;
        }
    }
}


//funcion auxiliar de menu
//pregunta por el id del receptor en un while true
//se puede salir en cualquier momento ingresando '-1'
//si el id es valida retornara un nodo que hara de receptor
Nodo* elegirReceptor(Grafo* grafo){
    string inputID = "";
    Nodo* receptorElegido;
    while(true){
        cout<<"Ingrese el ID del servidor para elegirlo como receptor"<<endl;
        cout<<"Ingrese '-1' para regresar al MENU"<<endl;
        getline(cin,inputID);
        if(inputID == "-1"){
            return NULL;
        }
        receptorElegido = grafo->getNodoEnGrafo(inputID);
        if(receptorElegido){
            return receptorElegido;
        }
        else{
            cout<<"error: ID invalido"<<endl;
        }
    }
}

//funcion auxiliar de menu
//se pide un int y se corrobora char por char que sea un numero
//y lo retorna
int enviarArchivo(){
    string magnitud;
    while(true){
        cout<<"Ingrese la cantidad de mb de su archivo a enviar"<<endl;
        cout<<"Ingrese '-1' para regresar al MENU"<<endl;
        getline(cin,magnitud);
        if(magnitud == "-1"){
            return -1;//usar este numero para saber que se cancelo el envio
        }
        if(soloDigitos(magnitud)){
            //char por char no hubo ninguno que no fuese un numero
            int magnitudNumerica = stoi(magnitud);
            return magnitudNumerica;
        }
        else{
            cout<<"error:"<<magnitud<<" no es un numero valido"<<endl;
        }
    }
}

//funcion que representa el menu principal para probar las funcionalidades del taller
//ver todos los servidores, elegir emisor,receptor y realizar un envio de archivo de un nodo a otro
void menu(Grafo* grafo){
    string decorativo = "==============================";
    string altDeco =    "------------------------------";
    string input = "";

    Nodo* emisor = NULL;
    bool hayEmisor = false;
    Nodo* receptor = NULL;
    bool hayReceptor = false;
    bool hayArchivo = false;
    while(true){
        cout<<decorativo<<endl;
        cout<<"MENU"<<endl;
        cout<<decorativo<<endl;
        cout<<altDeco<<endl;
        cout<<"Ingrese '0' para ver todos los servidores"<<endl;
        cout<<"Ingrese '1' para elegir un emisor"<<endl;
        if(hayEmisor){
            cout<<"Ingrese '2' para mostrar todos los puntos accesibles por el emisor elegido"<<endl;//opcion disponible luego de elegir emisor
            cout<<"Ingrese '3' para elegir un receptor"<<endl;//opcion disponible luego de elegir emisor
        }
        if(hayEmisor && hayReceptor){
            cout<<"Ingrese '4' para enviar un archivo"<<endl;
        }
        cout<<"Ingrese '-1' para salir"<<endl;
        cout<<altDeco<<endl;
        
        getline(cin,input);
        if(input == "0"){
            cout<<"opcion 0: mostrar nodos servidores"<<endl;
            cout<<grafo->mostrarServidores()<<endl;
        }
        else if(input == "1"){
            cout<<"opcion 1: elegir nodo emisor del mensaje"<<endl;
            emisor = elegirEmisor(grafo);
            if(emisor){
                hayEmisor = true;
                cout<<"Ha elegido como emisor al servidor con id: "<<emisor->id<<endl;
            }
            else{
                hayEmisor = false;
            }
        }
        else if(hayEmisor && input == "2"){
            cout<<"opcion 2:mostrar puntos accesibles por el emisor elegido"<<endl;
            string servidorID = "";
            cout<<grafo->conexionesDeUnServidor(emisor->id);
        }
        else if(hayEmisor && input == "3"){
            cout<<"opcion 3: elegir nodo receptor del mensaje"<<endl;
            receptor = elegirReceptor(grafo);
            if(receptor){
                cout<<"Ha elegido como receptor al servidor con id: "<<receptor->id<<endl;
                hayReceptor = true;
            }
            else{
                hayReceptor = false;
            }
        }
        else if(hayEmisor && hayReceptor && input == "4"){
            cout<<"opcion 4: enviar un archivo al receptor, indique la magnitud del archivo"<<endl;
            int tamano = enviarArchivo();
            if(tamano != -1){
                grafo->bellmanFord(emisor,receptor,tamano);
                tamano = -1;//se vuelve a poner -1 para que se tenga que ingresar otro numero para otro archivo
            }
        }
        else if(input == "-1"){
            cout<<"terminando programa"<<endl;
            return;
        }
        else{
            cout<<"opcion invalida"<<endl;
        }
    }
}

int main()
{
    Grafo* grafo = new Grafo();
    leerYcrearNodos(grafo);
    cout<<"Se han creado los nodos del grafo"<<endl;
    leerYestablecerConexiones(grafo);
    cout<<"Se han establecido las conexiones de cada nodo en el grafo"<<endl;

    menu(grafo);
    

    return 0;
}