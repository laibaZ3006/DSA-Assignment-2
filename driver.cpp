#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "BST.h"
using namespace std;
using namespace chrono;

int main()
{
    srand(time(0));

    const int SIZE = 100;

    double totalInsertTime = 0;
    double totalTraversalTime = 0;

 
    cout << "Set\tInsertion Time(us)\tInorder Traversal(us)\n";
  
    for (int set = 1; set <= 5; set++)
    {
        BST tree;

        int arr[SIZE];

        for (int i = 0; i < SIZE; i++)
        {
            arr[i] = rand() % 1000;
        }
        auto startInsert =  high_resolution_clock::now();

        for (int i = 0; i < SIZE; i++)
        {
            tree.insert(arr[i]);
        }

        auto endInsert =  high_resolution_clock::now();

        double insertTime =
            duration_cast<microseconds>
            (endInsert - startInsert).count();

        totalInsertTime += insertTime;
        auto startTraversal =  high_resolution_clock::now();

        tree.inorder();

        auto endTraversal =
            high_resolution_clock::now();

        double traversalTime =
            duration_cast<microseconds>
            (endTraversal - startTraversal).count();

        totalTraversalTime += traversalTime;
        cout << set << "\t"
             << insertTime << "\t\t\t"
             << traversalTime << endl;
    }

    cout << "Average\t"
         << totalInsertTime / 5 << "\t\t\t"
         << totalTraversalTime / 5 << endl;

    return 0;
}