#include <cstdlib>
#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

Graph<int>* getDefaultGraph()
{
    Graph<int> *gr = new Graph<int>(8);
    gr->changeEdge(0, 1, 5);
    gr->changeEdge(0, 2, 12);
    gr->changeEdge(1, 2, 4);
    gr->changeEdge(1, 4, 1);
    gr->changeEdge(2, 3, 2);
    gr->changeEdge(3, 4, 5);
    gr->changeEdge(3, 7, 4);
    gr->changeEdge(4, 5, 9);
    gr->changeEdge(1, 5, 11);
    gr->changeEdge(5, 6, 3);
    gr->changeEdge(6, 7, 4);
    return gr;
}
void editGraph(Graph<int> *gr)
{
    int choose = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    while(true)
    {
        cout << "Adjacency matrix:" << endl;
        gr->print();
        cout << endl;
        cout << "Enter 1 to add an edge" << endl;
        cout << "Enter 2 to add a vertex" << endl;
        cout << "Enter anything else to continue" << endl;
        cin >> choose;
        cout << endl;
        switch(choose)
        {
            case 1:
                cout << "Enter the first vertex" << endl;
                cin >> vert1;
                cout << endl;
                cout << "Enter the second vertex" << endl;
                cin >> vert2;
                cout << endl;
                cout << "Enter a weight of the edge" << endl;
                cin >> weight;
                cout << endl;
                gr->changeEdge(vert1, vert2, weight);
                break;
            case 2:
                gr->addVertex();
                break;
            default:
                return;
        }
    }
}

void interface()
{
    int choose = 0;
    int i = 0;
    int j = 0;
    Graph<int> *gr;
    ArraySequence<int> *path;

    while(true)
    {
        cout << "Enter 1 to get a default graph:" << endl;
        cout << "Enter 2 to create a custom graph" << endl;
        cout << "Enter a different number to quit" << endl;
        cin >> choose;
        cout << endl;

        switch (choose)
        {
            case 1:
                gr = getDefaultGraph();
                break;
            case 2:
                cout << "Enter a number of vertexes" << endl;
                cin >> choose;
                cout << endl;
                gr = new Graph<int>(choose);
                break;
            default:
                return;
        }
        editGraph(gr);
        cout << "Enter 1 find a path on the graph:" << endl;
        cout << "Enter a different number to quit" << endl;
        cin >> choose;
        cout << endl;
        switch(choose)
        {
            case 1:
                cout << "Enter a starting vertex:" << endl;
                cin >> i;
                cout << endl;
                cout << "Enter an ending vertex" << endl;
                cin >> j;
                cout << endl;
                path = gr->getPath(i, j);
                cout << "The shortest path:" << endl;
                for (int i = 0; i < path->getSize(); i++)
                    cout << path->get(i) << " ";
                cout << endl;
                cout << "It's weight: " << gr->getPathWeight(path) << endl;
                break;
            default:
                return;
        }
    }
}

int main(int argc, const char *argv[])
{
    interface();
	return 0;
}