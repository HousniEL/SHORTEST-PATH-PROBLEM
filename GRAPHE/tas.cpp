#include "tas.h"


Tas_Min::Tas_Min(int cap)
{

    this->pos = (int *)malloc(cap * sizeof(int));
    //this->pos=new int[cap];
    this->taille = 0;
    this->capacite = cap;
    this->array = (Tas_Min::Noeud_Tas_Min**)malloc(cap*sizeof(Tas_Min::Noeud_Tas_Min*));
}

Tas_Min::Noeud_Tas_Min* Tas_Min::ajouter_Noeud_Tas_Min(QString v, int dist, int indice)
{
    Tas_Min::Noeud_Tas_Min* noeud_Tas_Min= new Tas_Min::Noeud_Tas_Min ;
    noeud_Tas_Min->v = v;
    noeud_Tas_Min->dist = dist;
    noeud_Tas_Min->indice = indice;
    return noeud_Tas_Min;
}

void Tas_Min::echanger_Noeud_Tas_Min(Tas_Min::Noeud_Tas_Min **a, Tas_Min::Noeud_Tas_Min **b)
{
    Tas_Min::Noeud_Tas_Min* t = *a;
    *a=*b;
    *b=t;
}

void Tas_Min::minHeapify(int i)
{
    int plus_petit, g, d;//g : gauche d : droit
    plus_petit = i;
    g = 2 * i + 1;
    d = 2 * i + 2;

    if (g < this->taille && this->array[g]->dist < this->array[plus_petit]->dist )
        plus_petit = g;

    if (d < this->taille && this->array[d]->dist < this->array[plus_petit]->dist )
        plus_petit = d;

    if (plus_petit != i){
        // Les noeuds à échanger dans le tas-min
        Tas_Min::Noeud_Tas_Min *pp_noeud = this->array[plus_petit];//pp : plus petit
        Tas_Min::Noeud_Tas_Min *i_noeud = this->array[i];

        // échanger les positions
        this->pos[pp_noeud->indice] = i;
        this->pos[i_noeud->indice] = plus_petit ;

        // échanger les noeuds
        this->echanger_Noeud_Tas_Min(&this->array[plus_petit], &this->array[i]);

        minHeapify(plus_petit);
    }
}

Tas_Min::Noeud_Tas_Min* Tas_Min::Min()
{
    if (this->vide())
        return NULL;

    //
    Tas_Min::Noeud_Tas_Min* racine = this->array[0];

    // Remplacer la racine par la dernière
    Tas_Min::Noeud_Tas_Min* dernier_noeud = this->array[(this->taille) - 1];
    this->array[0] = dernier_noeud;

    // Mettre à jour la position du dernier noeud
    this->pos[racine->indice] = this->taille-1;
    this->pos[dernier_noeud->indice] = 0;
    //this->echanger_Noeud_Tas_Min(&this->tab[0], &this->tab[this->size-1]);

    // Réduire la taille de tas et tassez la racine
    this->taille--;
    this->minHeapify(0);

    return racine;
}

void Tas_Min::decreaseKey(int &v, int dist)
{
    // Avoir l'indice du v dans le tableau de tas
    int i = this->pos[v];

    // Avoir le noeud et mettre à jour sa dist valeur
    this->array[i]->dist = dist;

    // C'est une boucle de complexité O(Logn)
    while (i>=0 && this->array[i]->dist < this->array[(i - 1) / 2]->dist)
    {
        // échanger cet noeud par son parent
        this->pos[this->array[i]->indice] = (i-1)/2;
        this->pos[this->array[(i-1)/2]->indice] = i;

        this->echanger_Noeud_Tas_Min(&this->array[i],  &this->array[(i - 1) / 2]);

        // passer à l'indice du parent
        i = (i - 1) / 2;
    }
}
