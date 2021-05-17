#ifndef LISTENOEUDS_H
#define LISTENOEUDS_H

#include <QLinkedList>
class listenoeuds
{
public:

    listenoeuds();
    void ajoutersommet(QString);
    void supprimetsommet(QString);
    QString getnoeud(int);
    ~listenoeuds(){};

public :
    QLinkedList<QString> list;
};

#endif // LISTENOEUDS_H
