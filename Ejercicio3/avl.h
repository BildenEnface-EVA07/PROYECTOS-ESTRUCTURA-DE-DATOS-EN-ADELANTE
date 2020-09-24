#ifndef _AVL_H_
#define _AVL_H_

#include <algorithm>

namespace Avl
{
    template <typename T>
    struct Node
    {
        Node() = default;

        Node(T k) : key(k), height(0), left(nullptr), right(nullptr)
        {
        }

        T key;
        long height;
        Node *left;
        Node *right;
    };

    template <typename T>
    void rotateRight(Node<T> *&root)
    {
        Node<T> *temp = root->right;
        root->right = temp->left;
        temp->left = root;
       if (root->right == nullptr && root->left == nullptr)
        {
            root->height = root->left->height +1;
        }
        else if (root->right != nullptr && root->left != nullptr)
        {
            root->height = std::max(root->right->height, root->left->height) + 1;
        }
        else if (root->right != nullptr && root->left == nullptr)
        {
            root->height = root->right->height +1;
        }
        
        if (temp->right == nullptr && temp->left == nullptr)
        {
            temp->height = temp->left->height +1;
        }
        else if (temp->right != nullptr && temp->left != nullptr)
        {
            temp->height = std::max(temp->right->height, temp->left->height) + 1;
        }
        else if (temp->right != nullptr && temp->left == nullptr)
        {
            temp->height = temp->right->height +1;
        }
        root = temp;
    }

    template <typename T>
    void rotateLeft(Node<T> *&root)
    {
        // TODO o la verdad no se
        Node<T> *temp = root->left;
        root->left = temp->right;
        temp->right = root;
        if (root->right == nullptr && root->left == nullptr)
        {
            root->height = root->right->height + 1;
        }
        else if (root->right != nullptr && root->left != nullptr)
        {
            root->height = std::max(root->left->height, root->right->height) + 1;
        }
        else if (root->right == nullptr && root->left != nullptr)
        {
            root->height = root->left->height + 1;
        }

        if (temp->right == nullptr && temp->left == nullptr)
        {
            temp->height = temp->right->height + 1;
        }
        else if (temp->right != nullptr && temp->left != nullptr)
        {
            temp->height = std::max(temp->left->height, temp->right->height) + 1;
        }
        else if (temp->right == nullptr && temp->left != nullptr)
        {
            temp->height = temp->left->height + 1;
        }
        root = temp;
    }

} // namespace Avl

#endif
