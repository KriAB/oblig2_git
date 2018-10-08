#ifndef BITREE_H
#define BITREE_H


class biTree
{
private:
    struct Node
    {
      int data;  // the data in the node
      Node* left {nullptr}; //left child
      Node* right {nullptr}; //right child
    };
    Node* root {nullptr};
    //int data;
    Node* createLeaf(int m_data);
    void privateInsert(int m_data, Node *Ptr);

    void privateIntrav(Node* Ptr);
    void privatePostrav(Node* Ptr);
    void privatePretrav(Node* Ptr);


    int findSmallestPrivate(Node* Ptr);
    Node* findNodePrivate(int m_data, Node *Ptr);

    void removeNodePrivate(int m_data, Node *parent);
    void removeRootMatch();
    void removeMatch(Node* parent, Node* match, bool left); //not root
    void makeTreeEmptyPrivate(Node * & Ptr);

public:
    biTree();
    ~biTree();
    void insert(int m_data);

    void intrav();
    void postrav();
    void pretrav();
    void PrintChildren(int m_data);

    int findSmallest();
    Node* findNode(int m_data);
    int ReturnRootData();
    void removeNode(int m_data);
    void makeTreeEmpty();
    //void makeTreeFromGround();

    //Node (int m_data, Node* vSub= nullptr, Node* hSub = nullptr) : data{data}, left{vSub}, right{hSub} {};
// for å lage treet fra bun til top kan det hardkodes.
};

#endif // BITREE_H
