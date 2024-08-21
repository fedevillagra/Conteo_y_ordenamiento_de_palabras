# Conteo y ordenamiento de palabras

## Descripción

Este proyecto en C++ es parte del segundo parcial de la materia Algoritmos y Estructuras de Datos (2024). El objetivo principal del programa es contar y ordenar palabras en un archivo de texto, aplicando estructuras combinadas de lista y árbol binario de búsqueda (ABB), además de implementar algoritmos de ordenamiento como el de selección y quicksort. El objetivo de esta materia es el costo computacional, con un arbol tenemos un coste de orden O(log n).

## Uso

1. Escribe un texto en el archivo `test.txt`.

2. Ejecutar el archivo `main.cpp`.

## Resultados
El programa leerá el archivo `test.txt`, realizará el conteo y ordenamiento de palabras, y mostrará los resultados en la consola.

## Funcionalidades

1. **Conteo de Palabras**: 
   - El programa lee un archivo de texto (`test.txt`) y cuenta cuántas veces se repite cada palabra.
   - Para cada palabra distinta, se crea un nodo que se inserta en un ABB ordenado alfabéticamente y en una lista enlazada.

2. **Ordenamiento por Repeticiones**:
   - Una vez construido el ABB, los nodos de la lista se ordenan por la cantidad de repeticiones en forma decreciente utilizando el algoritmo de selección.
   - Este ordenamiento se realiza mediante intercambios de datos entre nodos sin alterar los punteros.

3. **Reordenamiento Alfabético**:
   - Después del ordenamiento por repeticiones, la lista se reordena alfabéticamente utilizando el algoritmo quicksort.
   - El acceso a los nodos para el ordenamiento se realiza mediante un árbol posicional binario.

## Nota

Este programa es una implementación básica del proyecto para el segundo parcial. Se pueden realizar mejoras adicionales, como el uso de un árbol AVL para garantizar un mejor balance del ABB. Se recomienda utilizar entornos como Replit online para evitar cualquier posible error.

## Autor

Proyecto realizado para la materia Algoritmos y Estructuras de Datos, Año 2024.
