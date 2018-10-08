#include "bitree.h"
#include <iostream>
#include <stack>
biTree::biTree()
{
}

biTree::~biTree()
{
    makeTreeEmptyPrivate(root);
}

biTree::Node *biTree::createLeaf(int m_data)
{
    Node* newNode = new Node;
    newNode->data = m_data;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

int biTree::findSmallest()
{
    return findSmallestPrivate(root);
}

int biTree::findSmallestPrivate(Node *Ptr)
{
    if(root == nullptr)
    {
        std::cout << "The treei s empty\n";
        return -1000; //må sette negativ int value fordi, det ikke er en del av key values i treet
    }
    else
    {
        if(Ptr->left != nullptr)
        {
            return findSmallestPrivate(Ptr->left);
        }
        else
        {
            return Ptr->data;
        }
    }
}

biTree::Node *biTree::findNode(int m_data)
{
    return findNodePrivate(m_data, root);
}

biTree::Node *biTree::findNodePrivate(int m_data, biTree::Node *Ptr)
{
    if(Ptr != nullptr)
    {
        if(Ptr->data == m_data)
        {
            return Ptr;
        }
        else
        {
            if(m_data < Ptr->data)
            {
                return findNodePrivate(m_data, Ptr->left);
            }
            else
            {
                return findNodePrivate(m_data, Ptr->right);
            }
        }
    }
    else
    {
        return nullptr;
    }
}

int biTree::ReturnRootData()
{
    if(root != nullptr)
    {
        return root->data;
    }
    else
    {
        return -1000;
    }

}

void biTree::removeNode(int m_data)
{
    removeNodePrivate(m_data, root);
}

void biTree::makeTreeEmpty()
{
    makeTreeEmptyPrivate(root);
}



void biTree::makeTreeEmptyPrivate(biTree::Node *&Ptr)
{
    if(Ptr != nullptr)
    {
        makeTreeEmptyPrivate(Ptr->left);
        makeTreeEmptyPrivate(Ptr->right);
        delete Ptr;
        std::cout << "destructed!\n";
    }
    Ptr = nullptr;

}

void biTree::removeNodePrivate(int m_data, biTree::Node *parent)
{
    //først sjekke om treet er tomt
    if(root != nullptr)
    {
        //sjekke om det er root som skal fjernes
        if(root->data == m_data)
        {
            removeRootMatch();
        }
        else
        {
            if(m_data < parent->data && parent->left != nullptr)
            {
                //boolean check - turnery conditional
                parent->left->data == m_data ? removeMatch(parent, parent->left, true)  :   removeNodePrivate(m_data, parent->left);
            }
            else if (m_data >parent->data && parent->right != nullptr)
            {
                //boolean check
                parent->right->data == m_data ? removeMatch(parent, parent->right, false) : removeNodePrivate(m_data, parent->right);
            }
            else
            {
                std::cout << "The data " << m_data << " was not found in the tree\n";
            }
        }
    }
    else
    {
        std::cout<< "The tree is empty \n";
    }
}

void biTree::removeRootMatch()
{
    //sjekke at treet ikke er tomt
    if(root != nullptr)
    {
        Node* delPtr = root;
        int rootData = root->data;
        int smallestInRightSubtree;

        //case 0 - 0 children
        if(root->left == nullptr && root->right == nullptr)
        {
            root = nullptr;
            delete delPtr;
        }
        //case 1 - 1 child
        //one right child
        else if(root->left == nullptr && root->right != nullptr)
        {
            root = root->right;
            //disconection the old root from the tree, the child becomes the root
            delPtr->right = nullptr;
            delete  delPtr;
            std::cout << "The root node with data " << rootData << " was deleted. " <<
                         "The new root contains data " << root->data << std::endl;
        }
        //one left child
        else if(root != nullptr && root->right == nullptr)
        {
            root = root->left;
            //disconection the old root from the tree, the child becomes the root.
            delPtr->left = nullptr;
            delete delPtr;
            std::cout << "The root node with data " << rootData << " was deleted. " <<
                         "The new root contains data " << root->data << std::endl;
        }
        // case 2 - 2 children
        else
        {
            smallestInRightSubtree = findSmallestPrivate(root->right);
            //fjerne den minste
            removeNodePrivate(smallestInRightSubtree, root);
            //putte den minste inn i root
            root->data = smallestInRightSubtree;
            std::cout << "The root data containing data " << rootData <<
                         " was overwritten with key " << root->data << std::endl;
        }
    }
    //tree empty
    else
    {
        std::cout << "Can not remove root, tree empty\n";
    }
}

void biTree::removeMatch(Node* parent, Node* match, bool left)
{
    if(root != nullptr)
    {
        Node* delPtr;
        int matchKey = match->data;
        int smallestInRightSubtree;

        //case 0 - 0 children
        if(match->left == nullptr && match->right == nullptr)
        {
            delPtr = match;
            left == true ?
                        parent->left = nullptr: //true
                    parent->right = nullptr; //false
            delete delPtr;
            std::cout << "The node containing key " << matchKey << " was removed\n";

        }
        //case 1- 1 child
        else if (match->left == nullptr && match->right != nullptr)
        {
            left == true ?
                        parent->left = match->right:
                    parent->right = match->right;

            match->right = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing key " << matchKey << " was removed\n";
        }
        else if (match->left != nullptr && match->right == nullptr)
        {
            left == true ?
                        parent->left = match->left:
                    parent->right= match->left;

            match->left = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing key " << matchKey << " was removed\n";
        }

        // Case 2 - 2 children
        else
        {
            smallestInRightSubtree = findSmallestPrivate(match->right);
            removeNodePrivate(smallestInRightSubtree, match);
            match->data = smallestInRightSubtree;
        }
    }
    else
    {
        std::cout << "Can not remove match. The tree is empty.\n";
    }
}

void biTree::insert(int m_data)
{
    privateInsert(m_data, root);
}

void biTree::privateInsert(int m_data, Node *Ptr)
{   //først, sjekke om treet er tomt
    if(root == nullptr)
    {
        root = createLeaf(m_data);
    }
    //hvis m_data er mindre enn data
    else if(m_data <Ptr->data)
    {
        //sjekker om den peker på noe til venstre, hvis den gjør det, må vi mer til venstre. Dermed en rekursiv funksjon.
        if(Ptr->left != nullptr)
        {
            privateInsert(m_data, Ptr->left);
        }
        //hvis den ikke peker på noe til venstre, settes en ny node
        else
        {
            Ptr->left = createLeaf(m_data);
        }
    }
    //hvis m_data er større enn data:
    else if(m_data > Ptr->data)
    {
        //sjekker om den peker på noe til høyre
        if(Ptr->right != nullptr)
        {
            privateInsert(m_data, Ptr->right);
        }
        // hvis den ikke peker på noe til høyre, settes en ny node inn
        else
        {
            Ptr->right = createLeaf(m_data);
        }
    }
    else
    {
        // hvis data er lik som en data i treet
        std::cout << "The key " << m_data << "has already been added to the tree\n";
    }
}

void biTree::intrav()
{
    privateIntrav(root);
}

void biTree::privateIntrav(Node *Ptr)
{
    if(root != nullptr)
    {
        if(Ptr->left != nullptr)
        {
            privateIntrav(Ptr->left);
        }
        std::cout << Ptr->data << " ";
        if(Ptr->right != nullptr)
        {
            privateIntrav(Ptr->right);
        }
    }
    else
    {
        std::cout << "The tree is empty\n";
    }
}

void biTree::postrav()
{
    privatePostrav(root);
}

void biTree::privatePostrav(Node *Ptr)
{
    if(Ptr != nullptr)
    {
        //first recur on left subtree
        privatePostrav(Ptr->left);

        //then recur on right subtree
        privatePostrav(Ptr->right);
        //now print the node
        std::cout << Ptr->data << " ";
    }
}

void biTree::pretrav()
{
    privatePretrav(root);
}


void biTree::privatePretrav(biTree::Node *Ptr)
{
    if(Ptr != nullptr)
    {
        //first print data of Ptr
        std::cout << Ptr->data << " ";

        //then recur on left subtree
        privatePretrav(Ptr->left);

        //then recur on right subtree
        privatePretrav(Ptr->right);
    }
}

void biTree::PrintChildren(int m_data)
{
    //returnerer en pointer som peker på den noden
    Node* Ptr = findNode(m_data);

    if( Ptr != nullptr)
    {
        std::cout << "Parent Node = " << Ptr->data << std::endl;

        Ptr->left == nullptr ?
                    std::cout << "Left Child = nullptr\n":
                                 std::cout << "Left Child = " << Ptr->left->data << std::endl;

        Ptr->right == nullptr ?
                    std::cout << "Right Child = nullptr\n":
                                 std::cout << "Right Child = " << Ptr->right->data << std::endl;
    }
    else
    {
        std::cout << "Key " << m_data << " is not in the tree\n";
    }
}
//void biTree::makeTreeFromGround()
//{
//    int TotalNodes{10};
//    std::stack<Node*> workingStack;
//    while(TotalNodes >0)
//    {
//        while(TotalNodes > 7)
//        {
//            auto newNode = new Node;
//            if(!workingStack.empty())
//            {
//                newNode->left = std::move(workingStack.top());
//                workingStack.pop();
//            }
//            if(!workingStack.empty())
//            {
//                newNode->right = std::move(workingStack.top());
//                workingStack.pop();
//            }
//            //workingStack.push(<Node*>{newNode});
//        }
//    }
//}
