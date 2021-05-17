#include "adjacents.h"
#include <QDebug>

Adjacents::Adjacents()
{
   ele=new listenoeuds();
   poid=*new QLinkedList<int>;
   ed=*new QLinkedList<Edge*>();
}
void Adjacents::sommetadjs(listenoeuds N,QString s1, QString s2,int i)
{
    if(N.list.contains(s1) && N.list.contains(s2)){
        if(!ele->list.contains(s1) || !ele->list.contains(s2)){
            if(!ele->list.contains(s1)) ele->list.append(s1);
            ele->list.append(s2);
            poid.append(i);
         }
    }
}


void Adjacents::supprimeradjs(QString s2)
{
    int i=0,j=0,k=0;
    QLinkedList<QString>::iterator it;
    it=ele->list.begin();
       while(it!=ele->list.end()){
           if(*(it)==s2) j=i-1;
           i++;
           it++;
       }
    ele->list.removeOne(s2);
    QLinkedList<int>::iterator it2;
    it2=poid.begin();
    while(it2!=poid.end()){
        if(k==j){
                  poid.removeOne(*(it2));
        }
        k++;
        it2++;

    }

}


void Adjacents::changeradjs(QString s2,int pd)
{
    int i=0,j=0,k=0;
    QLinkedList<QString>::iterator it;
    it=ele->list.begin();
       while(it!=ele->list.end()){
           if(*(it)==s2) j=i-1;
           i++;
           it++;
       }
    QLinkedList<int>::iterator it2;
    it2=poid.begin();
    while(it2!=poid.end()){
        if(k==j) (*it2)=pd;
        k++;
        it2++;

    }

}
