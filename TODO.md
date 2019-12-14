# Por hacer

- [x] Para eliminar

  - se busca el nodo a eliminar
  - si se encuentra, se va buscando la hoja más profunda
  - una vez encontrada, se le intercambia por el nodo
  - eliminar y se actualizan los rangos(?)
  - retornar el nodo eliminado
  - Si no se encuentra, retornar null
  - Faltaría actualizar las profundidades y los rangos.

- [x] Para actualizar
  - Se comienza con el padre de la hoja reemplazada, guardando los rangos de las dimensiones de la hoja y si es hijo de izq o der.
  - Se recorre los rangos de cada dimensión:
      Si el minimo guardado existe en el dato del nodo actual o en el rango del otro hijo, se omite.
    - Sino, se reemplaza el valor del rango actual con el menor entre el valor del nodo actual y el rango del otro hijo.

  - Si el maximo guardado existe en el dato del nodo actual o en el rango del otro hijo, se omite.
    - Sino, se reemplaza el valor del rango actual con el mayor entre el valor del nodo actual y el rango del otro hijo.

  - se avanza hacia el padre y se repite el proceso.

- [ ] Para testearlo:
  - Tomar el arreglo completo de los puntos de prueba, elegir una cantidad aleatoria cercana a la mitad para dividir el arreglo.
  - Insertar la primera sección y comprobar que se encuentra todo lo que debería.
  - ir eliminando algunos de los insertados, junto con agregar otros que hayan quedado pendientes.
  - comprobar que los cambios funcionan
  - agregar los eliminados y eliminar la mitad
  - comprobar que funciona todo.

- [ ] implementar funcion puntos dominados
    recibe intervalos en cada dimension, retorna lista de puntos que están dentro del intervalo.

- [x] transformar el punto a vector, en vez de arreglo
- [x] el eliminar debe hacerlo hasta que llegue uno arriba del padre que no modifique el intervalo.
- [x] implementar visualizador con links de wsp
- [ ] graficar tiempos de busqueda y de busqueda de intervalos con cantidad de puntos fija.

- [ ] hay que probar distintas inserciones, todas las posibilidades que puedan existir
- [ ] hay que probar eliminación, búsqueda e inserción, para así comprobar que no se rompe nada

- [x] funciones para nodo
  - [x] StrPunto
  - [x] StrPadre, si no existe -1
  - [x] getChildren
  - [x] StrRangos

- [ ] Para las inserciones: considerar que tanto se modifica el rango al hacer la inserción en el sub arbol de la izquierda o de la derecha.
- [ ] Para medir tiempos, hacerlo con el promedio de búsqueda de todos los datos de los árboles, mostrar la desv est tmbn.

## Para nuevo KD-Tree

- [x] Cada nodo ahora tendrá una variable para guardar en qué dimensión se hace la disjunción.
- [ ] La disjunción se hace por la dimensión más disjunta.
  - Si es nodo hoja, se usa la regla del KD-Tree normal.
  - Si tiene un sólo hijo, se verifica si el punto tiene al menos una dimensión disjunta con ese hijo.
    - Se selecciona la que tenga los rangos más disjuntos.
  - Si tiene 2 hijos, se verifica si está contenido en alguno de los rangos (cajas, es decir, en todas las dimensiones debe estar contenido).
  - Si no lo está, se selecciona el que tenga menor profundidad.
  - Si tienen la misma profundidad, se selecciona el que tenga más rangos contenidos (o menos, testear eso).
  - Si se iguala la cantidad de rangos, entonces se selecciona la menor distancia entre rangos.
- [x] Que al insertar con un hijo nodo se evalue el cambiar al hijo de izq a der o viceversa, para poder así insertar en un nodo nulo casi siempre.
- [ ] Los nodos en un futuro ya no guardarán la dimensión que disjunta a sus hijos, sino que se elegirá de manera implícita al analizar los rangos contenidos:
  - Al analizar en que sub-árbol insertar, la posibilidad base es que haya sólo un rango disjunto.
  - Si hay más de uno, se insertaría en el que signifique aumentar en la menor medida la cajita.

La distancia más cercana en la dimensión disjunta que estén más lejanos los rangos.

Probar guardando dimensión disjunta al actualizar inserciones (profundidad)
al eliminar:
  Buscar nodo con sólo un hijo de la rama más profunda, o el nodo más profundo
