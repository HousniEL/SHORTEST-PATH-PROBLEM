#include "graphe.h"
#include "tas.h"
#include <QDebug>
#include <QMessageBox>


Graphe::Graphe(bool is)
{
    noeuds=*new listenoeuds();
    lsadj=*new QVector<Adjacents*>();
    dist=*new QVector<int>(1);
    oriente=is;

    //Initialiser la matrice Adjacents

    M=new int * [noeuds.list.size()];
    for(int k=0;k<noeuds.list.size();k++){
         M[k]=new int[noeuds.list.size()];
    }
    for(int k=0;k<noeuds.list.size();k++){
        for(int j=0;j<noeuds.list.size();j++){
            if(k==j) M[j][k]=0;
             else M[j][k]=inf;
          }

    }
}

void Graphe::ajouter_noeud(QString n)
{
//Ajouter "n" premièrement à notre liste des noeuds
    noeuds.ajoutersommet(n);
    int i=noeuds.list.size();
//redimensionner notre vecteur des listes des adjacents
    lsadj.resize(i);
//Initialiser le nouvel élément de notre vecteur et ajouter "n" a notre vecteur
    lsadj[i-1]=new Adjacents();
    lsadj[i-1]->ele->list.append(n);
//Ajouter une ligne et une colonne a notre Matrice d'adjacence
    aj_Matrice();

}



void Graphe::ajouter_arete(QString n1, QString n2,int pd)
{
//les variables "src" et "dst" sont respectivement les indices des noeuds "n1" et "n2"
    int i=0,src,dst;
//"it" est l'itérateur de la liste des noeuds
    QLinkedList<QString>::iterator it;
            it=noeuds.list.begin();
            while(it!=noeuds.list.end()){
                if(*(lsadj[i]->ele->list.begin())==n1){
                    src=i;
                  //Ajouter "n2" à la liste d'adjacence de "n1"
                    lsadj[i]->sommetadjs(noeuds,n1,n2,pd);
                 }
               if(*(lsadj[i]->ele->list.begin())==n2){
                   dst=i;
                  //Si notre Graphe est non orientée alors la relation se passe dans les deux sens
                  //  d'où l'ajoute de "n1" aussi à la liste d'adjacence de "n2"
                   if(!oriente) lsadj[i]->sommetadjs(noeuds,n2,n1,pd);
               }

              i++;
              it++;
            }
//On suite le même principe de la matrice d'adjacence
    M[src][dst]=pd;
     if(!oriente) M[dst][src]=pd;
}




void Graphe::supprimer_noeud(QString n)
{
  int i=noeuds.list.size();
  int cpy=0,indice=0;
//La fonction "get_indice" retourne l'indice du noeud "n" dans notre liste des noeuds.
  indice=get_indice(n);
//Créer temporairement un vecteur pour pouvoir copier notre vecteur "lsadj" sans l'existence de "n".
  QVector<Adjacents*> tmp;
  tmp=*new QVector<Adjacents*>(i-1);
   for(int d=0,j=0;d<i-1 && j<i;d++,j++){
      tmp[d]=new Adjacents();
   //Si le tête de la liste de notre vecteur "lsadj" égale à "n" on le supprime du vecteur.
      if(*(lsadj[j]->ele->list.begin())==n){
          cpy=j;
       //Sauter la liste où "n" est le tête .
          tmp[d]=lsadj[++j];
       //Si la liste suivante contient "n" , on supprime "n" de la liste .
          if(tmp[d]->ele->list.contains(n))tmp[d]->supprimeradjs(n);
       //On remplace l'élément du vecteur "lsadj" avec son suivant.
          lsadj[cpy]=NULL;
          lsadj[cpy]=new Adjacents();
          lsadj[cpy]=tmp[d];
    //Si non ,s'il existe on supprime "n" du liste puis on copie.
      }else{
          tmp[d]=lsadj[j];
          if(tmp[d]->ele->list.contains(n))tmp[d]->supprimeradjs(n);
          lsadj[d]=NULL;
          lsadj[d]=new Adjacents();
          lsadj[d]=tmp[d];
      }
  }
//Le vecteur "lsadj" a la fin de la boucle ,reste avec un dernier élément vide ,donc on le supprime de le vecteur.
  lsadj.remove(i-1);
//On supprime "n" de notre liste des noeuds.
  noeuds.supprimetsommet(n);
//On supprime de la matrice la ligne et la colonne correspond à l'indice du "n" dans la liste des noeuds.
  sup_Matrice(indice);
}




void Graphe::supprimer_arete(QString n1, QString n2)
{
//les variables "src" et "dst" sont respectivement les indices des noeuds "n1" et "n2".
   int src,dst;
   for(int i=0;i<noeuds.list.size();i++){
    //Si le tête de l'élément de notre vecteur "lsadj" égal "n1" .
       if(*(lsadj[i]->ele->list.begin())==n1){
           src=i;
       //Si l'élément contient "n2",on supprime "n2" de la liste d'adjacence de "n1".
           lsadj[i]->supprimeradjs(n2);
       }
    //Si le tête de l'élément de notre vecteur "lsadj" égal "n2" .
       if(*(lsadj[i]->ele->list.begin())==n2){
           dst=i;
       //Si notre Graphe est non orientée ,on supprime aussi "n1" de la liste d'adjacence de "n2".
            if(!oriente) lsadj[i]->supprimeradjs(n1);
       }

   }

//Suivant le même principe de la matrice d'adjacence .
   M[src][dst]=inf;
   if(!oriente)  M[dst][src]=inf;
}

int Graphe::get_indice(QString n){
    for(int d=0;noeuds.list.size();d++){
        if(*(lsadj[d]->ele->list.begin())==n) return d;

    }
    return NULL;
}



void Graphe::sup_Matrice(int S){
    int** tmp;
             tmp=new int * [noeuds.list.size()];
             for(int k=0;k<noeuds.list.size();k++){
                tmp[k]=new int[noeuds.list.size()];
             }
             int j=0,k=0,i=0,l=0;
             for(k=0,i=0;k<noeuds.list.size() && i<(noeuds.list.size()+1);k++,i++){
                 for(j=0,l=0;j<noeuds.list.size() && l<(noeuds.list.size()+1);j++,l++){
                  if(i==S){
                    if(l==S) tmp[k][j]=M[++i][++l];
                     else tmp[k][j]=M[++i][l];
                    }else{
                     if(l==S) tmp[k][j]=M[i][++l];
                     else tmp[k][j]=M[i][l];
                  }
                 }


             }
             delete M;
             M=tmp;
}




void Graphe::aj_Matrice(){
    int** tmp;
     tmp=new int * [noeuds.list.size()];
     for(int k=0;k<noeuds.list.size();k++){
        tmp[k]=new int[noeuds.list.size()];
     }
     int j=0,k=0,i=0,l=0;
     for(k=0,i=0;k<noeuds.list.size() && i<noeuds.list.size();k++,i++){
         for(j=0,l=0;j<noeuds.list.size()  && l<noeuds.list.size();j++,l++){
          if(i==(noeuds.list.size()-1)|| l==(noeuds.list.size()-1)){
                   if(k==j) tmp[k][j]=0;
                   else tmp[k][j]=inf;
          }else tmp[k][j]=M[i][l];


         }
     }
     delete M;
     M=tmp;
}


void Graphe::changer_arete(QString n1, QString n2,int pd)
{
  if(noeuds.list.contains(n1) && noeuds.list.contains(n2)){
     if(lsadj[get_indice(n1)]->ele->list.contains(n2)) lsadj[get_indice(n1)]->changeradjs(n2,pd);
     M[get_indice(n1)][get_indice(n2)]=pd;
      if(!oriente) M[get_indice(n2)][get_indice(n1)]=pd;
  }

}



int Graphe::Get_Poid(int n1, int n2){
    int i=0,j=0,k=0;
    QLinkedList<QString>::iterator it;
    it=lsadj[n1]->ele->list.begin();
       while(it!=lsadj[n1]->ele->list.end()){
           if(*(it)==noeuds.getnoeud(n2)) j=i-1;
           i++;
           it++;
       }

    QLinkedList<int>::iterator it2;
    it2=lsadj[n1]->poid.begin();
    while(it2!=lsadj[n1]->poid.end()){
        if(k==j){
                 return *it2;
        }
        k++;
        it2++;

    }

}



///Floyd Warshall



QLinkedList<QString> Graphe::floyd_Warshall(QString n1, QString n2){
//Déclaration d'une Matrice temporaire
//Matrice qui contient dans chaque cellule ij,le plus court chemin entre les sommets i et j (partant de i).
    int** tmp;
//Déclaration de la Matrice π
//Matrice qui contient dans chaque cellule ij, le prédécesseur de j dans le plus court chemin entre i et j (partant de i).
    QString** pi;
    bool circuit_absorbant=false;
//initialisation de tmp.
    tmp=new int * [noeuds.list.size()];
    for(int k=0;k<noeuds.list.size();k++){
        tmp[k]=new int[noeuds.list.size()];
    }
    for(int i=0;i<noeuds.list.size();i++){
          for(int j=0;j<noeuds.list.size();j++){
              tmp[i][j]=M[i][j];
          }
    }
//initialisation de π.
    pi=new QString * [noeuds.list.size()];
    for(int k=0;k<noeuds.list.size();k++){
        pi[k]=new QString[noeuds.list.size()];
    }
    for(int i=0;i<noeuds.list.size();i++){
          for(int j=0;j<noeuds.list.size();j++){
             if(M[i][j]==inf || i==j) pi[i][j]="null";
             else pi[i][j]=lsadj[i]->ele->list.front();
          }
    }
//Une fois ces matrices initialisées, on fera les calculs suivants ,avec
// une répétition "k" égale la dimension de notre liste des noeuds .
    for (int k=0;k<noeuds.list.size();k++){
        for (int i=0;i<noeuds.list.size();i++){
            for (int j=0;j<noeuds.list.size();j++){
            //Suivant le principe d'algorithme du floyd-Warshall
                if ((tmp[i][k] + tmp[k][j])< tmp[i][j]){
                    tmp[i][j] = tmp[i][k] + tmp[k][j];
                    pi[i][j]=pi[k][j];
            }
         }
       }
    }

//détection d'un circuit absorbant.
    for (int i=0;i<noeuds.list.size();i++){
      if(tmp[i][i]<0) circuit_absorbant=true;
    }

//Création de la liste des sommets qui construit le plus court chemin
// entre la source " n1 " et la destination " n2 ".

   QLinkedList<QString> chemin;
//S'il n'y a aucun circuit absorbant
   if(!circuit_absorbant){
   //S'il existe un prédécesseur de "n2" dans le plus court chemin entre "n1" et "n2" .
     if(pi[get_indice(n1)][get_indice(n2)]!="null"){
       int l=0;
       QString k;
       for(int i=0;i<noeuds.list.size();i++){
          if(i==get_indice(n1)){
              l=get_indice(n2);
              k=pi[get_indice(n1)][l];
            for(int j=0;j<noeuds.list.size();j++){
                if(j==l && k!=n1){
                //Ajouter au debut de liste.
                  chemin.prepend(k);
                  l=get_indice(k);
                  k=pi[get_indice(n1)][l];
                  while(j>=0) j--;
                }
           }
          }
         }
        chemin.prepend(n1);
        //Ajouter à la fin de la liste.
        chemin.append(n2);
     }
   }else chemin.append("-1");

   return chemin;
}


//-----------------------------------------------------------------------------
///DIJKSTRA


QLinkedList<QString> Graphe::dijkstra(QString src)
{
    int V = this->noeuds.list.size();// Le nombre des sommets dans le  graphe.
    dist.clear();
    dist.resize(V);

    QString predecesseur[V];//table des prédécesseurs.
    QLinkedList<QString> list_nouv; //liste des prédécesseurs.

    //Création du tas.
    Tas_Min tas_min(V);

    QLinkedList<QString>::iterator it=this->noeuds.list.begin();
    int v=0;
    // Insérer au tas min les sommets avec des distances égale à l'infinie
    // et positions identique à l'ordre d'insertion de chaque sommets.
    // Initialiser la valeur de prédécesseurs par -1.
    it=this->noeuds.list.begin();
    while(it!=this->noeuds.list.end()){
        predecesseur[v]="-1";
        this->dist[v]= INT_MAX;
        tas_min.array[v] = tas_min.ajouter_Noeud_Tas_Min(*it,dist[v],v);
        tas_min.pos[v] = v;
        v++;
        it++;
    }

    // Changer la valeur de distance du source à 0 et mettre à jour le tas.
    it=this->noeuds.list.begin();
    v = 0;
    while(it!=this->noeuds.list.end()){
        if((*it)==src){
            tas_min.array[v] = tas_min.ajouter_Noeud_Tas_Min(src, dist[v],v);
            tas_min.pos[v] = v;
            this->dist[v] = 0;
            tas_min.decreaseKey(v, this->dist[v]);
        }
        v++;
        it++;
    }

    // Initialliser la taille du tas-min à V
    tas_min.taille= V;
    // Dans la boucle suivante, le tas-min contient tous les noeuds
    // dont la distance la plus courte n'est pas encore finalisée.
    int i = 0;
    while (!tas_min.vide()){
        // Extraire le sommet avec la valeur de distance minimale.
        Tas_Min::Noeud_Tas_Min* noeud_Tas_Min = tas_min.Min();
        // Stocker l'indice de sommet extrait.
        int u = noeud_Tas_Min->indice;
        // Traversez tous les sommets adjacents de u (le sommet extrait) avec leurs poids
        // et mettez à jour leurs valeurs de distance.
        QLinkedList<QString>::iterator it_1=this->lsadj[u]->ele->list.begin();
        QLinkedList<int>::iterator it_poid=this->lsadj[u]->poid.begin();
        it_1++;
        while (it_poid!= this->lsadj[u]->poid.end()){
            for(int y=0;y<V;y++) {
                if(tas_min.array[y]->v==*it_1){
                    i = tas_min.array[y]->indice;
                    // Si la distance la plus courte jusqu'à *it_1 n'est pas encore finalisée et si la distance jusqu'à *it_1
                    // à travers u est inférieure à sa distance calculée précèdamment.
                    if (tas_min.Appartient(i) && this->dist[u] != INT_MAX && ((*it_poid) + this->dist[u]) < this->dist[i])
                    {
                        // Mettre à jour la valeur du predecesseur du u.
                        predecesseur[i]=noeud_Tas_Min->v;
                        this->dist[i] = (this->dist[u] + (*it_poid));
                        // Mettre à jour la valeur de distance en tas min.
                        tas_min.decreaseKey(i,this->dist[i]);
                    }
                    break;
                }
                //J'avais ajouter cette condition puisque parfois le tas ne contient plus la valeur 0 après l'initialisation.
                if(*it_1==0){
                    i=0;
                    // Si la distance la plus courte jusqu'à *it_1 n'est pas encore finalisée et si la distance jusqu'à *it_1
                    // à travers u est inférieure à sa distance calculée précèdamment.
                    if (tas_min.Appartient(i) && this->dist[u] != INT_MAX && ((*it_poid) + this->dist[u]) < this->dist[i])
                    {
                        // Mettre à jour la valeur du predecesseur du u.
                        predecesseur[i]=noeud_Tas_Min->v;
                        this->dist[i] = (this->dist[u] + (*it_poid));
                        // Mettre à jour la valeur de distance en tas min.
                        tas_min.decreaseKey(i,this->dist[i]);
                    }
                    break;
                }
            }
                it_1++;
                it_poid++;
        }
    }
    // Remplire notre liste par les prédécesseurs de chaque noeud.
    for(int y=0;y<V;y++) {
        list_nouv.push_back(predecesseur[y]);
    }
    return list_nouv;
}


//--------------------------------------------------------
///Bellman Ford


QLinkedList<QString>* Graphe::Bellman_Ford(QString n1){
    QLinkedList<QString>* chemin;
    QString *Previous;
    chemin = new QLinkedList<QString> [noeuds.list.size()];
    Distance = new int  [noeuds.list.size()];
    Previous = new QString  [noeuds.list.size()];
    for(int i = 0; i < noeuds.list.size(); i++){
        Distance[i] = inf;
        Previous[i] = "NULL";
    }
    Distance[get_indice(n1)] = 0;
    int tempDistance;
    for(int k = 0; k < noeuds.list.size(); k++){
        int l = 0;
        for (int i = 0; i < noeuds.list.size(); i++){
                    QLinkedList<QString>::iterator it;
                    it = lsadj[i]->ele->list.begin();
                    while (it != lsadj[i]->ele->list.end()){
                            tempDistance = Distance[i] +  Get_Poid(i,get_indice(*it));
                            if(tempDistance < Distance[get_indice(*it)]){
                                Distance[get_indice(*it)] = tempDistance;
                                Previous[get_indice(*it)] = noeuds.getnoeud(i);
                                l++;
                            }
                            it++;
                        }
                    }
        if(l == 0)break;
}
    for (int i = 0; i < noeuds.list.size(); i++){
                QLinkedList<QString>::iterator it;
                it = lsadj[i]->ele->list.begin();
                while (it != lsadj[i]->ele->list.end()){
                        tempDistance = Distance[i] +  Get_Poid(i,get_indice(*it));
                        if(tempDistance < Distance[get_indice(*it)]){
                            QMessageBox msgBox;
                            msgBox.setIcon(QMessageBox::Warning);
                            msgBox.setText("ATTENTION !!!Vous avez un cycle negative dans ce graph.");
                            msgBox.exec();
                            return NULL;
                    }
                        it++;
                }
            }
         QString Pre;
    for (int i = 0; i < noeuds.list.size(); i++){
        Pre = noeuds.getnoeud(i);
        chemin[i].prepend(Pre);
        if(i != get_indice(n1) ){
            do{
                if(Distance[get_indice(Pre)] < inf){
                    Pre = Previous[get_indice(Pre)];
                    chemin[i].prepend(Pre);
                  }else{
                    Pre = n1;
                         }
               }while(Pre != n1 );
       }
    }


    return chemin;
}


//--------------------------------------------------------
///Johnson


QLinkedList<QString> *Graphe::Johnson()
{
       QString text = "Johnson";
       QLinkedList<QString>::iterator it;
       QLinkedList<QString>::iterator it1;
       QLinkedList<Edge*>::iterator it2;
        QLinkedList<QString>* chemin;
        QLinkedList<QString>* Bell_chemin;
        chemin = new QLinkedList<QString> [noeuds.list.size()];
        int negative = 0;
        for(int l=0;l<noeuds.list.size();l++){
            QLinkedList<int>::iterator it_poid=lsadj[l]->poid.begin();
            while(it_poid!=lsadj[l]->poid.end()){
                if((*it_poid)<0){
                    negative++;
                }
                it_poid++;
            }
        }
        int w;
        Bell_chemin = new QLinkedList<QString> [noeuds.list.size()];
        it = noeuds.list.begin();
       Distance_Johnson = new int*[noeuds.list.size()];
       it = noeuds.list.begin();
          while(it!=noeuds.list.end()){
              int i = get_indice(*it);
              Distance_Johnson[i] = new int [noeuds.list.size()];
              it++;
          }
        if(negative != 0){
       ajouter_noeud(text);

       it = noeuds.list.begin();
          while(it!=noeuds.list.end()){
              if (*it != text){
                  ajouter_arete(text , *it , 0);
              }
              it++;
          }

          Bell_chemin = Bellman_Ford(text);
          it = noeuds.list.begin();
             while(it!=noeuds.list.end()){
                 int i = get_indice(*it);
                 if (*it != text){
                     it1 = lsadj[i]->ele->list.begin();
                         while(it1 !=lsadj[i]->ele->list.end()){
                         int j = get_indice(*it1);
                           w = Get_Poid(i,j);
                           changer_arete(*it , *it1 , w + Distance[i] - Distance[j]);
                            it1++;
                       }
                 }
                 it++;
               }

             it = noeuds.list.begin();
                while(it!= noeuds.list.end()){
                    if(*it != text){
                        supprimer_arete(text , *it );
                    }
                       it++;
                   }

                supprimer_noeud(text);

           if (Bell_chemin != NULL || negative == 0){
           it = noeuds.list.begin();
              while(it!=noeuds.list.end()){
                  if(*it != text ){
                   int i = get_indice(*it);
                   chemin[i] = dijkstra(*it);
                   it1 = noeuds.list.begin();
                       while(it1 != noeuds.list.end()){
                           int j = get_indice(*it1);
                           Distance_Johnson[i][j] = dist[j] + Distance[j] - Distance[i];
                           it1++;
                       }
                  }
                       it++;
              }
              it = noeuds.list.begin();
                 while(it!=noeuds.list.end()){
                     int i = get_indice(*it);
                     if (*it != text){
                         it1 = lsadj[i]->ele->list.begin();
                             while(it1 !=lsadj[i]->ele->list.end()){
                             int j = get_indice(*it1);
                               w = Get_Poid(i,j);
                               changer_arete(*it , *it1 , w + Distance[j] - Distance[i]);
                                it1++;
                           }
                     }
                     it++;
                   }
                }else return NULL;
        }else{
            it = noeuds.list.begin();
               while(it!=noeuds.list.end()){
                   if(*it != text ){
                    int i = get_indice(*it);
                    chemin[i] = dijkstra(*it);
                    it1 = noeuds.list.begin();
                        while(it1 != noeuds.list.end()){
                            int j = get_indice(*it1);
                            Distance_Johnson[i][j] = dist[j];
                            it1++;
                        }
                   }
                        it++;
               }
        }
        return chemin;
}
