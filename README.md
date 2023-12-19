Taller3EDatos_Bellman-Ford
Tercer taller de estructura de datos, uso de Bellman-Ford para determinar la mejor ruta desde un nodo a cualquier otro nodo en el grafo

Comandos.
crear ejecutable:
g++ -o main main.cpp
ejecutar ejecutable:
./main

Integrantes:
//Javier Moraga Sanhueza
//Inti Cerda Ramirez


//La clase Grafo tendra un vector de nodos de tipo Nodo, y en esta clase se iterara en busca del mejor camino
//usando el algoritmo de Bellman-Ford
//Este grafo fue implementado con la idea que cada nodo tiene multiples aristas(Conexion)
//las Conexiones contienen atributos necesarios para calcular el viaje, ademas del nodo destino
//cada Nodo es agregado a un vector de nodos, y cuando se quiere establecer una conexion a un nodo
//se le aplica a dicho nodo->conexiones y como conexiones es un vector de Conexion, le agrego la nueva Conexion

//clase Nodo, debe tener el id, nombre y tipo, los 3 seran string
//ademas cada nodo puede tener multiples conexiones, por lo que necesitara un vector de Conexion

//tiempoAcumulado es una variable usada para el algoritmo de Bellman-Ford(parametro interno de la clase usado para Bellman-Ford)
//predecesor es otra variable usada para el algoritmo de Bellman-Ford, usado para reconstruir la mejor ruta de origen a destino(parametro interno de la clase usado para Bellman-Ford)


//La clase Conexion es usada para representar la conexion entre 2 nodos, si nodo A tiene conexion a nodo B
//entonces la conexion hacia B debe contener, distancia hacia B, velocidad hacia B, y el nodo B, todo esto respecto al nodo A

Bellman-Ford:
//algoritmo que a partir de un nodo de origen, determina la mejor ruta para todos los demas nodos
//cuando establece una mejor ruta para un nodo, cambia el peso acumulado de ese nodo por el nuevo
//ademas de cambiar el 'predecesor' de ese nodo, para asi saber de donde vino la mejor ruta
//y despues se puede iterar desde destino hasta origen, ya que todas las rutas vienen desde el origen
//por lo que cualquier nodoDestino que no tenga un pesoAcumulado de infinito(inalcanzable) puede llegar al nodoOrigen
//y crear la mejor ruta y retornarla
vector<pair<Nodo*, Nodo*>> Grafo::bellmanFord(Nodo* nodoOrigen, Nodo* nodoDestino,int sizeArchivo)
