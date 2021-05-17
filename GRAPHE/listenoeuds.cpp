#include <QString>
#include "listenoeuds.h"

listenoeuds::listenoeuds()
{
    list=*new QLinkedList<QString>;

}

void listenoeuds::ajoutersommet(QString s)
{
    if(!list.contains(s)){
        list.append(s);
    }
}

void listenoeuds::supprimetsommet(QString s)
{
    list.removeOne(s);
}



QString listenoeuds::getnoeud(int i){
        int k=0;
        QLinkedList<QString>::iterator it;
             it=list.begin();
             while(it!=list.end()){
                 if(k==i) return *it;
                 k++;
                 it++;
             }
}
