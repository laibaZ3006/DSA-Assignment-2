#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

class BST
{
private:

    struct Node
    {
        int data;
        Node* left;
        Node* right;

        Node(int value)
        {
            data = value;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;

    
    Node* insert(Node* node, int value)
    {
        if (node == NULL)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);

        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    
    bool search(Node* node, int value)
    {
        if (node == NULL)
            return false;

        if (node->data == value)
            return true;

        if (value < node->data)
            return search(node->left, value);

        return search(node->right, value);
    }

    
    void inorder(Node* node)
    {
        if (node == NULL)
            return;

        inorder(node->left);
        inorder(node->right);
    }

    
    Node* findMin(Node* node)
    {
        while (node->left != NULL)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node* node, int value)
    {
        if (node == NULL)
            return NULL;

        if (value < node->data)
        {
            node->left = deleteNode(node->left, value);
        }

        else if (value > node->data)
        {
            node->right = deleteNode(node->right, value);
        }

        else
        {
            
            if (node->left == NULL && node->right == NULL)
            {
                delete node;
                return NULL;
            }
  
            else if (node->left == NULL)
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == NULL)
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            
            else
            {
                Node* temp = findMin(node->right);

                node->data = temp->data;

                node->right =
                    deleteNode(node->right, temp->data);
            }
        }

        return node;
    }

public:

    BST()
    {
        root = NULL;
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    bool search(int value)
    {
        return search(root, value);
    }

    void inorder()
    {
        inorder(root);
    }

    void deleteValue(int value)
    {
        root = deleteNode(root, value);
    }
};

#endif