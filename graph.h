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
        if(vert1 == vert2) throw out_of_range("INCORRECT INDEX");
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
        const int INF = 100000000;
        ArraySequence<int> dist(this->getSize());
        ArraySequence<bool> beenTo(this->getSize());
        ArraySequence<int> parent(this->getSize());
        for(int i = 0; i < this->getSize(); i++)
        {
            dist.set(INF, i);
            beenTo.set(false, i);
            parent.set(-1, i);
        }
        int min = 0;
        int index_min = 0;
        int temp = 0;
        dist.set(0, vert1);

        for(int i = 0; i < this->getSize(); i++)
        {
            min = INF;
            for(int j = 0; j < this->getSize(); ++j)
            {
                if(!beenTo.get(j) && dist.get(j) < min)
                {
                    min = dist.get(j);
                    index_min = j;
                }
            }
            beenTo.set(true, index_min);
            for (int j = 0; j < this->getSize(); ++j)
            {
                if (adjMatrix->Get(index_min, j) > 0)
                {
                    temp = min + adjMatrix->Get(index_min, j);
                    if (temp < dist.get(j))
                    {
                        dist.set(temp, j);
                        parent.set(index_min, j);
                    }
                }
            }
        }
        ArraySequence<int> *path = new ArraySequence<int>(0);
        for(int i = vert2; i != -1; i = parent.get(i))
            path->prepend(i);
        return path;
    }
    T getPathWeight(ArraySequence<int> *path)
    {
        T result = 0;
        for (int i = 0; i < path->getSize() - 1; i++)
        {
            result += this->adjMatrix->Get(path->get(i), path->get(i + 1));
        }
        return result;
    }
};