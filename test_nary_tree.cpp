#include <iostream>
#include <cassert>
#include <string>
#include "nary_tree.h"

// Framework de testing simple
class TestFramework {
private:
    int tests_run = 0;
    int tests_passed = 0;

public:
    void test(const std::string& test_name, bool condition) {
        tests_run++;
        if (condition) {
            tests_passed++;
            std::cout << "[PASS] " << test_name << std::endl;
        } else {
            std::cout << "[FAIL] " << test_name << std::endl;
        }
    }

    void summary() {
        std::cout << "\n=== RESUMEN DE TESTS ===" << std::endl;
        std::cout << "Tests ejecutados: " << tests_run << std::endl;
        std::cout << "Tests exitosos: " << tests_passed << std::endl;
        std::cout << "Tests fallidos: " << (tests_run - tests_passed) << std::endl;
    
    }
};

// Tests unitarios básicos
void testTreeCreation() {
    std::cout << "\n==================TEST: Creación del árbol" << std::endl;
    TestFramework tf;
    
    NAryTree<std::string> tree("Raiz");
    
    tf.test("Árbol creado correctamente", tree.root != nullptr);
    tf.test("Valor de la raíz correcto", tree.root->value == "Raiz");
    tf.test("Raíz sin hijos inicialmente", tree.root->children.empty());
    
    tf.summary();
}

void testInsertionDirectOnRoot() {
    std::cout << "\n==================TEST: Inserción directa en la raíz" << std::endl;
    TestFramework tf;
    
    NAryTree<std::string> tree("Raiz");
    
    tree.addChild(tree.root, "Hijo1");
    tree.addChild(tree.root, "Hijo2");
    tree.addChild(tree.root, "Hijo3");
    
    tf.test("Se añadieron 3 hijos a la raíz", tree.root->children.size() == 3);
    tf.test("Primer hijo correcto", tree.root->children[0]->value == "Hijo1");
    tf.test("Segundo hijo correcto", tree.root->children[1]->value == "Hijo2");
    tf.test("Tercer hijo correcto", tree.root->children[2]->value == "Hijo3");
    
    tf.summary();
}

void testInsertionByIndex() {
    std::cout << "\n==================TEST: Inserción usando acceso por índice" << std::endl;
    TestFramework tf;
    
    NAryTree<std::string> tree("Raiz");
    
    tree.addChild(tree.root, "Hijo1");
    tree.addChild(tree.root, "Hijo2");
    
    // Insertar nietos usando índices
    tree.addChild(tree.root->children[0], "Nieto1.1");
    tree.addChild(tree.root->children[0], "Nieto1.2");
    tree.addChild(tree.root->children[1], "Nieto2.1");
    
    tf.test("Hijo1 tiene 2 nietos", tree.root->children[0]->children.size() == 2);
    tf.test("Hijo2 tiene 1 nieto", tree.root->children[1]->children.size() == 1);
    tf.test("Nieto1.1 correcto", tree.root->children[0]->children[0]->value == "Nieto1.1");
    tf.test("Nieto1.2 correcto", tree.root->children[0]->children[1]->value == "Nieto1.2");
    tf.test("Nieto2.1 correcto", tree.root->children[1]->children[0]->value == "Nieto2.1");
    
    tf.summary();
}

void testInsertionBySearch() {
    std::cout << "\n==================TEST: Inserción usando búsqueda por valor" << std::endl;
    TestFramework tf;
    
    NAryTree<std::string> tree("Raiz");
    
    tree.addChild(tree.root, "Hijo1");
    tree.addChild(tree.root, "Hijo2");
    tree.addChild(tree.root->children[0], "Nieto1.1");
    tree.addChild(tree.root->children[1], "Nieto2.1");
    
    // Insertar usando búsqueda
    auto nieto11 = tree.findNode(tree.root, "Nieto1.1");
    if (nieto11) {
        tree.addChild(nieto11, "Bisnieto1.1");
        tree.addChild(nieto11, "Bisnieto1.2");
    }
    
    auto nieto21 = tree.findNode(tree.root, "Nieto2.1");
    if (nieto21) {
        tree.addChild(nieto21, "Bisnieto2.1");
        tree.addChild(nieto21, "Bisnieto2.2");
        tree.addChild(nieto21, "Bisnieto2.3");
    }
    
    tf.test("Nieto1.1 encontrado", nieto11 != nullptr);
    tf.test("Nieto2.1 encontrado", nieto21 != nullptr);
    tf.test("Nieto1.1 tiene 2 bisnietos", nieto11->children.size() == 2);
    tf.test("Nieto2.1 tiene 3 bisnietos", nieto21->children.size() == 3);
    tf.test("Bisnieto1.1.1 correcto", nieto11->children[0]->value == "Bisnieto1.1");
    tf.test("Bisnieto2.1.3 correcto", nieto21->children[2]->value == "Bisnieto2.3");
    
    tf.summary();
}

void testDeepInsertion() {
    std::cout << "\n==================TEST: Inserción en nodos profundos (tataranietos)" << std::endl;
    TestFramework tf;
    
    NAryTree<std::string> tree("Raiz");
    
    tree.addChild(tree.root, "Hijo1");
    tree.addChild(tree.root->children[0], "Nieto1.1");
    tree.addChild(tree.root->children[0]->children[0], "Bisnieto1.1.1");
    tree.addChild(tree.root->children[0]->children[0], "Bisnieto1.1.2");
    
    // Insertar tataranietos usando búsqueda
    auto bisnieto111 = tree.findNode(tree.root, "Bisnieto1.1.1");
    if (bisnieto111) {
        tree.addChild(bisnieto111, "Tataranieto1.1.1.1");
        tree.addChild(bisnieto111, "Tataranieto1.1.1.2");
        tree.addChild(bisnieto111, "Tataranieto1.1.1.3");
    }
    
    auto bisnieto112 = tree.findNode(tree.root, "Bisnieto1.1.2");
    if (bisnieto112) {
        tree.addChild(bisnieto112, "Tataranieto1.1.2.1");
    }
    
    tf.test("Bisnieto1.1.1 encontrado", bisnieto111 != nullptr);
    tf.test("Bisnieto1.1.2 encontrado", bisnieto112 != nullptr);
    tf.test("Bisnieto1.1.1 tiene 3 tataranietos", bisnieto111->children.size() == 3);
    tf.test("Bisnieto1.1.2 tiene 1 tataranieto", bisnieto112->children.size() == 1);
    tf.test("Tataranieto1.1.1.1 correcto", bisnieto111->children[0]->value == "Tataranieto1.1.1.1");
    tf.test("Tataranieto1.1.2.1 correcto", bisnieto112->children[0]->value == "Tataranieto1.1.2.1");
    
    tf.summary();
}

void testDynamicExpansion() {
    std::cout << "\n==================TEST: Expansión dinámica del árbol" << std::endl;
    TestFramework tf;
    
    NAryTree<std::string> tree("Raiz");
    
    tree.addChild(tree.root, "Hijo1");
    tree.addChild(tree.root, "Hijo2");
    tree.addChild(tree.root, "Hijo3");
    
    // Expansión dinámica - agregar nueva rama
    tree.addChild(tree.root, "Hijo4");
    auto hijo4 = tree.findNode(tree.root, "Hijo4");
    if (hijo4) {
        tree.addChild(hijo4, "Nieto4.1");
        tree.addChild(hijo4, "Nieto4.2");
        tree.addChild(hijo4, "Nieto4.3");
        tree.addChild(hijo4, "Nieto4.4");
    }
    
    // Expandir un nieto específico
    auto nieto42 = tree.findNode(tree.root, "Nieto4.2");
    if (nieto42) {
        tree.addChild(nieto42, "Bisnieto4.2.1");
        tree.addChild(nieto42, "Bisnieto4.2.2");
    }
    
    tf.test("Árbol expandido a 4 hijos", tree.root->children.size() == 4);
    tf.test("Hijo4 encontrado", hijo4 != nullptr);
    tf.test("Hijo4 tiene 4 nietos", hijo4->children.size() == 4);
    tf.test("Nieto4.2 encontrado", nieto42 != nullptr);
    tf.test("Nieto4.2 tiene 2 bisnietos", nieto42->children.size() == 2);
    tf.test("Bisnieto4.2.1 correcto", nieto42->children[0]->value == "Bisnieto4.2.1");
    
    tf.summary();
}

void testComplexTreeStructure() {
    std::cout << "\n==================TEST: Estructura compleja con múltiples niveles" << std::endl;
    TestFramework tf;
    
    NAryTree<std::string> tree("Raiz");
    
    tree.addChild(tree.root, "Hijo1");
    tree.addChild(tree.root, "Hijo2");
    tree.addChild(tree.root, "Hijo3");
    
    // Nivel 2: Nietos
    tree.addChild(tree.root->children[0], "Nieto1.1");
    tree.addChild(tree.root->children[0], "Nieto1.2");
    tree.addChild(tree.root->children[0], "Nieto1.3");
    tree.addChild(tree.root->children[1], "Nieto2.1");
    tree.addChild(tree.root->children[1], "Nieto2.2");
    tree.addChild(tree.root->children[2], "Nieto3.1");
    
    // Nivel 3: Bisnietos
    tree.addChild(tree.root->children[0]->children[0], "Bisnieto1.1.1");
    tree.addChild(tree.root->children[0]->children[0], "Bisnieto1.1.2");
    tree.addChild(tree.root->children[0]->children[1], "Bisnieto1.2.1");
    tree.addChild(tree.root->children[1]->children[0], "Bisnieto2.1.1");
    
    // Nivel 4: Tataranietos
    tree.addChild(tree.root->children[0]->children[0]->children[0], "Tataranieto1.1.1.1");
    tree.addChild(tree.root->children[0]->children[0]->children[0], "Tataranieto1.1.1.2");
    tree.addChild(tree.root->children[0]->children[1]->children[0], "Tataranieto1.2.1.1");
    
    tf.test("Raíz tiene 3 hijos", tree.root->children.size() == 3);
    tf.test("Hijo1 tiene 3 nietos", tree.root->children[0]->children.size() == 3);
    tf.test("Hijo2 tiene 2 nietos", tree.root->children[1]->children.size() == 2);
    tf.test("Hijo3 tiene 1 nieto", tree.root->children[2]->children.size() == 1);
    tf.test("Nieto1.1 tiene 2 bisnietos", tree.root->children[0]->children[0]->children.size() == 2);
    tf.test("Bisnieto1.1.1 tiene 2 tataranietos", tree.root->children[0]->children[0]->children[0]->children.size() == 2);
    
    // Verificar nodos específicos
    auto tataranieto = tree.findNode(tree.root, "Tataranieto1.1.1.1");
    tf.test("Tataranieto encontrado en nivel 5", tataranieto != nullptr);
    
    tf.summary();
}

void testRemovalAfterInsertion() {
    std::cout << "\n==================TEST: Eliminación después de inserción compleja" << std::endl;
    TestFramework tf;
    
    NAryTree<std::string> tree("Raiz");
    
    tree.addChild(tree.root, "Hijo1");
    tree.addChild(tree.root, "Hijo2");
    tree.addChild(tree.root->children[0], "Nieto1.1");
    tree.addChild(tree.root->children[0], "Nieto1.2");
    tree.addChild(tree.root->children[0]->children[0], "Bisnieto1.1.1");
    tree.addChild(tree.root->children[0]->children[1], "Bisnieto1.2.1");
    tree.addChild(tree.root->children[0]->children[1], "Bisnieto1.2.2");
    
    int initial_children = tree.root->children.size();
    int initial_nietos = tree.root->children[0]->children.size();
    
    tf.test("Estructura inicial correcta", initial_children == 2 && initial_nietos == 2);
    
    // Eliminar un nieto específico
    tree.removeChild(tree.root->children[0], "Nieto1.2");
    
    tf.test("Nieto1.2 eliminado con sus descendientes", tree.root->children[0]->children.size() == 1);
    tf.test("Solo queda Nieto1.1", tree.root->children[0]->children[0]->value == "Nieto1.1");
    
    // Eliminar hijo completo
    tree.removeChild(tree.root, "Hijo1");
    
    tf.test("Hijo1 eliminado con toda su descendencia", tree.root->children.size() == 1);
    tf.test("Solo queda Hijo2", tree.root->children[0]->value == "Hijo2");
    
    tf.summary();
}

void testNAryCapabilities() {
    std::cout << "\n==================TEST: Capacidades N-arias (muchos hijos)" << std::endl;
    TestFramework tf;
    
    NAryTree<int> tree(0);
    
    // Añadir muchos hijos a la raíz
    for (int i = 1; i <= 10; ++i) {
        tree.addChild(tree.root, i);
    }
    
    tf.test("Raíz tiene 10 hijos", tree.root->children.size() == 10);
    tf.test("Primer hijo correcto", tree.root->children[0]->value == 1);
    tf.test("Último hijo correcto", tree.root->children[9]->value == 10);
    
    // Añadir diferentes cantidades de hijos a cada nodo
    tree.addChild(tree.root->children[0], 11); 
    tree.addChild(tree.root->children[1], 12); 
    tree.addChild(tree.root->children[1], 13);
    tree.addChild(tree.root->children[1], 14);
    
    for (int i = 15; i <= 19; ++i) { 
        tree.addChild(tree.root->children[2], i);
    }
    
    tf.test("Hijo 1 tiene 1 hijo", tree.root->children[0]->children.size() == 1);
    tf.test("Hijo 2 tiene 3 hijos", tree.root->children[1]->children.size() == 3);
    tf.test("Hijo 3 tiene 5 hijos", tree.root->children[2]->children.size() == 5);
    
    tf.summary();
}

int main() {
   
    // Tests básicos
    testTreeCreation();
    
    // Tests de inserción
    testInsertionDirectOnRoot();
    testInsertionByIndex();
    testInsertionBySearch();
    testDeepInsertion();
    testDynamicExpansion();
    
    // Tests de estructura compleja
    testComplexTreeStructure();
    testNAryCapabilities();
    
    // Tests de eliminación
    testRemovalAfterInsertion();
    
    return 0;
}