# Árbol N-ario en C++

Este proyecto implementa una estructura de datos de árbol n-ario genérico en C++, junto con un conjunto de pruebas unitarias para validar su funcionamiento.

## Estructura del proyecto

- `nary_tree.h`: Implementación de la clase plantilla `NAryTree<T>` y el nodo `Node<T>`.
- `test_nary_tree.cpp`: Pruebas unitarias y ejemplos de uso del árbol n-ario.
- `runTest.sh`: Script para compilar y ejecutar las pruebas.

## Características principales

- Árbol n-ario genérico (soporta cualquier tipo de dato).
- Métodos para añadir y eliminar hijos en cualquier nodo.
- Búsqueda de nodos por valor.
- Recorrido e impresión del árbol.
- Pruebas unitarias cubriendo inserciones, eliminaciones y estructuras complejas.

## Uso

### Compilar y ejecutar pruebas

```sh
sh runTest.sh
```

### Ejemplo de uso básico

```cpp
#include "nary_tree.h"

NAryTree<std::string> tree("Raiz");
auto root = tree.root;
tree.addChild(root, "Hijo1");
tree.addChild(root, "Hijo2");
tree.printTree(root);
```

### Ejemplo de salida

```
Raiz
  Hijo1
  Hijo2
```
