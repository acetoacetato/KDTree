# Implementación de un KD-Tree en c++

Este repositorio contiene una propuesta de KD-Tree que intenta resolver el problema de esta estructura al eliminar e insertar muchos datos sobre este.

La estrategia utilizada comienza con guardar los rangos de cada sub árbol, en cada dimensión, en cada nodo.

![Ejemplo](Figuras/arbol.png)

Con esto, se pueden realizar acciones que permitan reducir la profundidad del árbol al momento de realizar eliminaciones e inserciones.

## Eliminación

Al momento de eliminar un dato, este es reemplazado por el del nodo más profundo de su sub-árbol, para así reducir la profundidad.
Esto es posible gracias a que se utilizan rangos para las inserciones y búsquedas, en vez de los puntos de cada nodo.

![Eliminar](Figuras/eliminar.png)

## Inserción

Al momento de insertar un dato, se usan principalmente las reglas del KD-Tree normal, utilizando los rangos. La estrategia cambia en cuanto el dato a insertar no pertenece a ninguno de los rangos de los sub-árboles.
En este último caso, se realizan las siguientes comprobaciones:

1) Si alguno de los nodos es nulo, se inserta ahí.
2) Sino, se inserta en el sub árbol que contenga la menor profundidad.
3) Pendiente: hacer que priorice también el agrandar lo menos posible los rangos.
