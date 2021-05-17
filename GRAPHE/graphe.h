#ifndef GRAPHE_H
#define GRAPHE_H
#include <adjacents.h>
#include <QVector>
#include <QMessageBox>

class Graphe:public Adjacents
{
public:

   Graphe(bool);
   void ajouter_noeud(QString);
   void ajouter_arete(QString,QString,int);
   void supprimer_noeud(QString);
   void supprimer_arete(QString,QString);
   void changer_arete(QString,QString,int);
   int Get_Poid(int , int);
   listenoeuds get_noeud(){
        return  noeuds;
   }
   int get_indice(QString);
   void sup_Matrice(int);
   void aj_Matrice();

   QLinkedList<QString> floyd_Warshall(QString,QString);
   QLinkedList<QString>* Bellman_Ford(QString);
   QLinkedList<QString> dijkstra(QString);
   QLinkedList<QString>* Johnson();

   ~Graphe(){};
public:

    bool oriente;
    QVector<Adjacents*> lsadj;
    listenoeuds noeuds;
    int** M;
    const int inf=20000000;
    QVector<int> dist;//Dijkstra
    int *Distance;//Bellman
    int  **Distance_Johnson;
};

#endif // GRAPHE_H
