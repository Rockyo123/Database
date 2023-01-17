#include "binary_search_tree.hpp"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    clone(rhs.root);
}

// this is an alternative implementationusing a stack to simulate the recursion
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::clone(Node<KeyType, ItemType>* rhs)
{
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(const BinarySearchTree<KeyType, ItemType>& rhs)
{
    if (&rhs == this)
        return *this;

    destroy();

    root = 0;
    clone(rhs.root);

    return *this;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
    if(isEmpty())
    {
        temp -> data = item;
        temp -> key = key;
        root = temp;
        return true;
    }
    Node<KeyType, ItemType>* tempParent = new Node<KeyType, ItemType>;
    search(key, temp, tempParent);
    if(key != temp -> key);
    {
        Node<KeyType, ItemType>* temp2 = new Node<KeyType, ItemType>;
        if(key < temp -> key)
        {
            temp2 -> data = item;
            temp2 -> key = key;
            temp -> left = temp2;
            return true;
        }
        else if( key > temp -> key)
        {
            temp2 -> data = item;
            temp2 -> key = key;
            temp -> right = temp2;
            return true;
        }
    } 
    return false;  
}
template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    if (isEmpty())
        return false; // empty tree

    Node<KeyType, ItemType>* tempParent = new Node<KeyType, ItemType>;
    Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
    search(key, temp, tempParent);

    //not found
    if(key != temp -> key)
    {
        return false;
    }
    // case one thing in the tree
    if(tempParent == 0)
    {
        root = 0;
        delete tempParent;
        delete temp;
        return true;
    }

    // case, found deleted item at leaf
    if(temp -> left == 0 && temp -> right == 0)
    {
        if(tempParent -> left == temp)
        {
            delete temp;
            tempParent -> left = 0;
            return true;
        }
        if(tempParent -> right == temp)
        {
            delete temp;
            tempParent -> right = 0;
            return true;
        }
    }

    // case, item to delete has only a right child
    if(temp -> left == 0 && !(temp -> right == 0))
    {
        if(tempParent -> left == temp)
        {
            tempParent -> left = temp -> right;
            delete temp;
            return true;
        }
        if(tempParent -> right == temp)
        {
            tempParent -> right = temp -> right;
            delete temp;
            return true;
        }
    }
    // case, item to delete has only a left child
    if(temp -> right == 0 && !(temp -> left == 0))
    {
        if(tempParent -> left == temp)
        {
            tempParent -> left = temp -> left;
            delete temp;
            return true;
        }
        if(tempParent -> right == temp)
        {
            tempParent -> right = temp -> left;
            delete temp;
            return true;
        }
    }
    // case, item to delete has two children
    if(temp -> left != 0 && temp -> right != 0)
    {
   
        Node<KeyType, ItemType>* temp2 = temp;
        Node<KeyType, ItemType>* temp3 = temp;
        Node<KeyType, ItemType>* temp4 = tempParent;
  
        inorder(temp2, temp3, temp4);
    
        temp = temp3;
        remove(temp3 ->key);
        return true;
    }
    return false; // default should never get here
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
    if(in -> right != 0)
    {
        curr = in -> right;
        while(curr -> left != 0)
        {
            curr = curr -> left;
        }
        in = curr;
    }
    else
    {
        curr = 0;
        parent = root;
        while(parent != in)
        {
            if(in -> key < parent -> key)
            {
                curr = parent;
                parent = parent -> left;
            }
            else
            {
                parent = parent -> right;
            }
        }
        in = curr;
    }
}

int depth = 0;

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;
    

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else {
                break;
            }
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else {
                break;
            }
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(ItemType arr[], int size) 
{
// check for duplicate items in the input array
    for(int i= 0; i < size; i++)
    {
        ItemType type = arr[i];
        for(int j = 0; j< size; j++)
        {
            if((type == arr[j]) && (i != j))
            {
                return;
            }
        }
    }
    //use the tree to sort the array items
    for(int i = 0; i < size; i++)
    {
        insert(arr[i], arr[i]);
    }

    //overwrite input array values with sorted values
    Node<KeyType, ItemType>* temp;
    Node<KeyType, ItemType>* temp2;
    Node<KeyType, ItemType>* temp3; 

    temp = root;
    temp3 = root;
    while(temp -> left != 0)
    {
        temp = temp -> left;
    }
    temp2 = temp;
    arr[0] = temp -> data;
    for(int i = 1; i<size; i++)
    {
        inorder(temp2, temp, temp3);
        printf("temp equals: %d\n", temp2->data);
        arr[i] = temp -> data;
    } 
}