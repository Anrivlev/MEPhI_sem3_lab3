#pragma once

#include "sequence.h"
#include "matrix.h"

using namespace std;

template <class T>
class Graph
{
private:
    Matrix<T> *adjMatrix;
public:
    Graph(int size)
    {
        this->adjMatrix = new Matrix<T>(size, size);
    }
    ~Graph() = default;
    void addVertex()
    {
        this->adjMatrix->addRow();
        for (int i = 0; i < this->adjMatrix->GetColumns(); i++)
        {
            this->adjMatrix->Set(0, this->adjMatrix->GetRows() - 1, i);
        }
        this->adjMatrix->addColumn();
        for (int i = 0; i < this->adjMatrix->GetRows(); i++)
        {
            this->adjMatrix->Set(0, i, this->adjMatrix->GetColumns() - 1);
        }
    }
    void changeEdge(int vert1, int vert2, T weight)
    {
        this->adjMatrix->Set(weight, vert1, vert2);
        this->adjMatrix->Set(weight, vert2, vert1);
    }
    int getSize()
    {
        return this->adjMatrix->GetRows();
    }
    void print()
    {
        this->adjMatrix->Show();
    }
    ArraySequence<int>* getPath(int vert1, int vert2)
    {
        const int INF = 10^8;
        ArraySequence<int> dist(this->getSize());
        for(int i = 0; i < this->getSize(); i++)
            dist.set(INF, i);
        ArraySequence<bool> beenTo(this->getSize());
        for(int i = 0; i < this->getSize(); i++)
            beenTo.set(false, i);
        int min = 0;
        int index_min = 0;
        dist.set(0, vert1);
        ArraySequence<int> parent(this->getSize());
        for(int i = 0; i < this->getSize(); i++)
            parent.set(-1, i);

        for (int i = 0; i < this->getSize() - 1; i++)
        {
            min = INF;
            for(int j = 0; j < this->getSize(); j++)
            {
                if(!beenTo.get(j) && dist.get(j) < min)
                {
                    min = dist.get(j);
                    index_min = j;
                }
            }
            beenTo.set(true, index_min);
            for (int j = 0; j < this->getSize(); j++)
            {
                if(!beenTo.get(j) && adjMatrix->Get(index_min, j) > 0 && dist.get(index_min) != INF && dist.get(index_min) + adjMatrix->get(index_min, j) < dist.get(j))
                {
                    dist.set(dist.get(index_min) + adjMatrix->Get(index_min, j), j);
                    parent.set(index_min, j);
                }
            }
        }
        ArraySequence<int> *path = new ArraySequence<int>(0);
        for(int i = vert2; i != -1; i = parent.get(i))
            path->prepend(i);
        return path;
    }
};