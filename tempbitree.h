#ifndef TEMPBITREE_H
#define TEMPBITREE_H

#include <iostream>
#include <stack>
#include <cmath> //pow
#include <memory>
#include <queue>


namespace MyNode
{
template<class T>
class TBiTree;
template <class U>
struct Node;
}

namespace MyNode
{
template<class T>
class TBiTree
{
private:
    template<class U>
    struct Node
    {
        int data;  // the data in the node
        Node<U>* left {nullptr}; //left child
        Node<U>* right {nullptr}; //right child
    };
    Node<T>* root{nullptr};
    //unsigned int number {1};
public:
    TBiTree()
    {
    }
    ~TBiTree()
    {
        makeTreeEmptyPrivate(root);
    }

    Node<T> *createLeaf(int m_data)
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = m_data;
        newNode->left = nullptr;
        newNode->right = nullptr;

        return newNode;
    }

    int findSmallest()
    {
        return findSmallestPrivate(root);
    }
    Node<T> *findNode(int m_data)
    {
        return findNodePrivate(m_data, root);
    }
private:
    int findSmallestPrivate(Node<T> *Ptr)
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
    Node<T> *findNodePrivate(int m_data, Node<T> *Ptr)
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
public:
    int ReturnRootData()
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

    void removeNode(int m_data)
    {
        removeNodePrivate(m_data, root);
    }

    void makeTreeEmpty()
    {
        makeTreeEmptyPrivate(root);
    }

    void makeTreeEmptyPrivate(Node<T> *&Ptr)
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
private:
    void removeNodePrivate(int m_data, Node<T> *parent)
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
public:
    void removeRootMatch()
    {
        //sjekke at treet ikke er tomt
        if(root != nullptr)
        {
            Node<T>* delPtr = root;
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

    void removeMatch(Node<T>* parent, Node<T>* match, bool left)
    {
        if(root != nullptr)
        {
            Node<T>* delPtr;
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

    void insert(int m_data)
    {
        privateInsert(m_data, root);
    }
private:
    void privateInsert(int m_data, Node<T> *Ptr)
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
public:
    void intrav()
    {
        privateIntrav(root);
    }

    void intravIterative()
    {
        //create empty stack
        std::stack<Node<T>*> s;
        //Start from root node (set current node to root node)
        Node<T>* curr = root;

        //if current node is null and stack is also empty, we're done
        while(!s.empty() || curr !=nullptr)
        {
            //if current node si not null, push it to the stack (defer it)
            // and move to its left child
            if(curr != nullptr)
            {
                s.push(curr);
                curr = curr->left;
            }
            else
            {
                //else if current node is null, we pop an element from stack
                curr = s.top();
                s.pop();
                //print it
                std::cout << curr->data << " ";
                //set current node to its right child
                curr = curr->right;
            }
        }
    }
    void postrav()
    {
        privatePostrav(root);
    }

    void postravIterative()
    {
        privatePostravIterative(root);
    }
    void pretrav()
    {
        privatePretrav(root);
    }
    void pretravIterative()
    {
        privatePretravIterative(root);
    }
private:
    void privateIntrav(Node<T> *Ptr)
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
    void privatePostrav(Node<T> *Ptr)
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
    //iterative function to perform post-order traversal of the tree
    void privatePostravIterative( Node<T>* Ptr )
    {
        //create an empty stack and push root node
        std::stack<Node<T>*> stk;
        stk.push(Ptr);

        //create an empty stack for det data
        std::stack<int> out;

        //run till stack is not empty
        while(!stk.empty())
        {    //we pop a node from the stack and push the data to output stack
            Node<T>* curr = stk.top();
            stk.pop();

            out.push(curr->data);
            //push left and right child of popped node to the stack
            if(curr->left)
            {
                stk.push(curr->left);
            }
            if(curr->right)
            {
                stk.push(curr->right);
            }
            //print post-order traversal
        }
        while (!out.empty())
        {
            std::cout << out.top() << " ";
            out.pop();
        }

    }

    void privatePretravIterative(Node<T> *Ptr)
    {
        //create empty stack

        //Start from root node (set current node to root node)

        if(Ptr == nullptr)
        {
            return;
        }
        std::stack<Node<T>*> s;
        s.push(Ptr);
        //if current node is null and stack is also empty, we're done
        while(!s.empty())
        {
            Node<T>* curr = s.top();
            s.pop();
            std::cout << curr->data << " ";
            //push right child of popped node to the stack
            if(curr->right)
            {
                s.push(curr->right);
            }
            //push left child of popped node to the stack
            if(curr->left)
                s.push(curr->left);
        }

    }

    void privatePretrav(Node<T> *Ptr)
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
public:
    void PrintChildren(int m_data)
    {
        //returnerer en pointer som peker på den noden
        Node<T>* Ptr = findNode(m_data);

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

    void makeTreeFromGround()
    {

        Node<int>* newNode {nullptr};
        std::stack<Node<int>*> chStack{};
        std::stack<Node<int>*> prStack{};
         //Skal lage 10 noder
        // Med disse tallene
        //          7
        //       4      9
        //    2    6  8  10
        //  1  3  5
        //Lage de 3 nodene i 4. level fra høyre mot venstre slik at det kommer i riktig rekkefølge for parent
        newNode = createLeaf(5);
        chStack.push(newNode);

        newNode = createLeaf(3);
        chStack.push(newNode);

        newNode = createLeaf(1);

        chStack.push(newNode);
        //std::cout << std::endl << "Stack size: " << chStack.size();
        //lage første node i 3. level og gi den venstre og høyre child
        newNode = createLeaf(2);
        newNode->left = std::move(chStack.top());
        chStack.pop();

        newNode->right = std::move(chStack.top());
        chStack.pop();

        // pushe 1. node på parent stack
        prStack.push(newNode);

        //lage 2. node level 3

        newNode = createLeaf(6);

        // gi den siste childe
        newNode->left = std::move(chStack.top());
        chStack.pop();

        // pushe 2. node på parent stack
        prStack.push(newNode);

        //lage 3. node //3. og 4. har ingen child
        newNode = createLeaf(8);
        // pushe 3. node på parent stack
        prStack.push(newNode);
        // lage 4. node
        newNode = createLeaf(10);
        prStack.push(newNode);

        //pushe level 2 på childstack

        //lag venstre i level 2
        newNode = createLeaf(9);
        // høyre
        newNode->right = std::move(prStack.top());
        prStack.pop();

        //venstre child
        newNode->left = std::move(prStack.top());
        prStack.pop();
        //push ny node på childstack
        chStack.push(newNode);

        //lage høyre i level 2
        newNode = createLeaf(4);
        //set høyre child
        newNode->right = std::move(prStack.top());
        prStack.pop();
        //set venstre child
        newNode->left = std::move(prStack.top());
        prStack.pop();
        //push ny node på childstack
        chStack.push(newNode);

        //Lager root node:
        newNode = createLeaf(7);
        // setter venstre child
        newNode->left = std::move(chStack.top());
        chStack.pop();
        // setter høyre child
        newNode->right = std::move(chStack.top());
        chStack.pop();

        // setter noden til root
        root = newNode;

    }
    //level order traversal
    void leveltrav()
    {
        Node<T>* Ptr = root;
        std::queue<Node<int>*> q;
        if(!Ptr)
        {
            return;
        }
        for(q.push(Ptr); !q.empty(); q.pop())
        {
            const Node<T>* const temp = q.front();
            std::cout << temp->data << " ";

            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
        }


    }
    int treeDepth()
    {
        return privateTreeDepth(root);
    }
    unsigned int countNodes(unsigned int number)
    {
        return privateCountNodes(root, number);
    }
    unsigned  int treeCapacity()
    {
        return std::pow(2, treeDepth()) - 1;
    }

private:
    int privateTreeDepth(Node<T>* &Ptr)
    {
        if(Ptr == nullptr)
        {
            return 0;
        }
        else
        {
            int lchild = privateTreeDepth(Ptr->left);
            int rchild = privateTreeDepth(Ptr->right);
            if(lchild <= rchild)
            {
                return rchild+1;
            }
            else
                return lchild+1;
        }
    }

    unsigned int privateCountNodes(Node<T>* Ptr, unsigned int number)
    {
        if(Ptr == 0)
        {
            return 0;
        }
        if(Ptr->left != nullptr)
        {
            number = number+1;
            number = privateCountNodes(Ptr->left, number);
        }
        if(Ptr->right != nullptr)
        {
            number = number+1;
            number = privateCountNodes(Ptr->right, number);
        }
        return number;
    }

};
}
#endif // TEMPBITREE_H
