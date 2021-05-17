#ifndef ADJACENTS_H
#define ADJACENTS_H
#include "listenoeuds.h"
#include "edge.h"
#include <QLinkedList>


class Adjacents :public listenoeuds
{
public:
    Adjacents();
    void sommetadjs(listenoeuds,QString,QString,int);
    void supprimeradjs(QString);
    void changeradjs(QString,int);
    ~Adjacents(){};

public:
    listenoeuds *ele;
    QLinkedList<int> poid;
    QLinkedList<Edge*> ed;
};

#endif // ADJACENTS_H
