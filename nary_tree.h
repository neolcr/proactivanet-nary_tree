#ifndef NARY_TREE_H
#define NARY_TREE_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Nodo del árbol n-ario
template <typename T>
class Node {
public:
    T value;
    std::vector<std::shared_ptr<Node<T>>> children;

    Node(const T& val) : value(val) {}
};

// Árbol n-ario
template <typename T>
class NAryTree {
public:
    std::shared_ptr<Node<T>> root;

    NAryTree(const T& rootValue) {
        root = std::make_shared<Node<T>>(rootValue);
    }

    // Añadir un hijo a un nodo dado
    void addChild(const std::shared_ptr<Node<T>>& parent, const T& childValue) {
        parent->children.push_back(std::make_shared<Node<T>>(childValue));
    }

    // Eliminar un hijo con cierto valor de un nodo dado
    void removeChild(const std::shared_ptr<Node<T>>& parent, const T& childValue) {
        auto& children = parent->children;
        children.erase(std::remove_if(children.begin(), children.end(),
            [&](const std::shared_ptr<Node<T>>& child) {
                return child->value == childValue;
            }), children.end());
    }

    // Buscar un nodo por valor
    std::shared_ptr<Node<T>> findNode(const std::shared_ptr<Node<T>>& node, const T& value) {
        if (!node) return nullptr;
        if (node->value == value) return node;
        
        for (const auto& child : node->children) {
            auto found = findNode(child, value);
            if (found) return found;
        }
        return nullptr;
    }

    // Recorrer y mostrar el árbol recursivamente
    void printTree(const std::shared_ptr<Node<T>>& node, int depth = 0) {
        if (!node) return;
        for (int i = 0; i < depth; ++i) std::cout << "  ";
        std::cout << node->value << std::endl;
        for (const auto& child : node->children) {
            printTree(child, depth + 1);
        }
    }
};

#endif // NARY_TREE_H