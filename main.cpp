#include <iostream>
#include "bitree.h"
#include "tempbitree.h"

using namespace std;

int main()
{
    unsigned int number {1}; //to count number of nodes
    int TreeData[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};

    biTree myTree;
    cout << "Printing the tree in order\nBefore adding numbers.\n";
    myTree.intrav();

    for(int i = 0; i < 16; i ++)
    {
        myTree.insert(TreeData[i]);
    }
    cout << "Intrav: ";
    myTree.intrav();
    cout << endl << "Pretrav: ";
    myTree.pretrav();
    cout << endl << "Postrav: ";
    myTree.postrav();
    cout << endl;

    // Del 1 oppgave 3
    cout << "Printing the tree: ";
    for(int i = 0; i < 16; i ++)
    {
        myTree.PrintChildren(TreeData[i]);
        std::cout << std::endl;
    }
    std::cout << endl << "Intrav: ";
    myTree.intrav();
    cout<< endl;
    std::cout << endl << "Postrav: ";
    myTree.postrav();
    std::cout << endl;
    myTree.removeNode(14);
    myTree.removeNode(50);

    std::cout << endl << "Postrav after removing: ";
    myTree.postrav();

    // Del 2, gjøre klassen om til template klasse
//    MyNode::TBiTree<int> myTTree;
//    myTTree.insert(5);
//    myTTree.insert(6);
//    myTTree.insert(3);
//    myTTree.insert(2);
//    myTTree.insert(7);
//    myTTree.insert(4);
//    std::cout << endl << "Temp Intrav: ";
//    myTTree.intrav();
//    std::cout << endl << "Intrav Iterative: "; // Del 3 oppgave 1
//    myTTree.intravIterative();

//    std::cout << endl << "Temp Pretrav: "; // Del 1 oppgave 7
//    myTTree.pretrav();
//    std::cout << endl << "Temp Pretrav Iterative: "; // Del 3 oppgave 1
//    myTTree.pretravIterative();

//    std::cout << endl << "Temp Postrav: "; // Del 1 oppgave 7
//    myTTree.postrav();
//    std::cout << endl << "Temp Postrav Iterative: "; // Del 3 oppgave 1
//    myTTree.postravIterative();
//    std::cout << std::endl;

//    //  Del 3 oppg 2, nivåvis traversering.
//    std::cout << endl << "Temp level order traversal iterative: ";
//    myTTree.leveltrav();
//    std::cout << std::endl;

//    //tree capacity, Del 1 oppgave 4
//    unsigned int cap = myTTree.treeCapacity();
//    unsigned int numb = myTTree.countNodes(number);

//    std::cout << "Number of nodes: " << numb << endl;
//    std::cout << "Tree depth: " << myTTree.treeDepth() << endl;
//    std::cout << "Tree capacity: " << cap << endl;
//    std::cout << "Spaces left: " << cap-numb << std::endl;


    //// Del 1 oppgave 2, bygge et tre fra blad til rot
//        MyNode::TBiTree<int> groundTree;
//        groundTree.makeTreeFromGround();

//        groundTree.makeTreeFromGround2(10); ////alternative method

//        cout << endl << "Printing the tree: " << endl;

//            groundTree.PrintChildren(7);
//            std::cout << std::endl;
//            groundTree.PrintChildren(4);

//            std::cout << std::endl;
//            groundTree.PrintChildren(9);
//            std::cout << std::endl;
//            groundTree.PrintChildren(2);

//            std::cout << std::endl;
//            groundTree.PrintChildren(6);

//            std::cout << std::endl;
//            groundTree.PrintChildren(8);

//            std::cout << std::endl;
//            groundTree.PrintChildren(10);

//            std::cout << std::endl;
//            groundTree.PrintChildren(1);

//            std::cout << std::endl;
//            groundTree.PrintChildren(3);

//            std::cout << std::endl;
//            groundTree.PrintChildren(5);
//            std::cout << std::endl;

    return 0;
}
