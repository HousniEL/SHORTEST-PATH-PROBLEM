#ifndef TAS_H
#define TAS_H
#include <QString>
#include <QVector>

class Tas_Min{
public:
    class Noeud_Tas_Min{
    public :
        QString  v;//valeur du noeud
        int indice;
        int dist;//distance
        Noeud_Tas_Min(){}
    };


    int taille;    // Nombre du noeud curamment presenter dans le tas-min
    int capacite;  // Capacite du tas-min
    int *pos;     // On est besoin de ca pour decreaseKey()
    Noeud_Tas_Min **array;


    Tas_Min(int);
    //Fonction pour créer un nouveau noeud dans le tas-min
    Noeud_Tas_Min* ajouter_Noeud_Tas_Min(QString v,int dist,int indice);


    //Fonction pour échanger deux noeuds du tas-min. On est bsoin pour le tri
    void echanger_Noeud_Tas_Min(Noeud_Tas_Min** a,Noeud_Tas_Min** b);


    //Cette fonction aussi mettre à jour la position des noeuds lorsqu'ils sont échangé.
    //la position est nécessaire pour decreaseKey()
    void minHeapify(int i);

    //Fonction pour extrait le noeud le plus petit du tas
    Noeud_Tas_Min* Min();

    // Fonction pour decrementer la distance d'un sommet v.
    // Cette fonction utilise pos[] du tas-min pour avoir l'indice current du noeud dans le tas-min
    void decreaseKey(int &v, int dist);

    // Fonction pour tester si un sommet d'indice 'v' appartient au tas-min ou non
    bool Appartient(int v)
    {
       if (this->pos[v] < this->taille)
         return true;
       return false;
    }

    int vide()
    {
        return (this->taille == 0);
    }

};

#endif // TAS_H
