#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsView>
#include<QtMath>
#include <QGraphicsScene>
#include <QMessageBox>
#include<QInputDialog>
#include<QTranslator>



static int New_j1=0;
QPoint t[40][40] ;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //un élèment de chaque vecteurs est crée lorsqu'une tab est crée. (voir 'ajouter_tab')
    scenes=*new QVector<QGraphicsScene*>();
    // li = nombre des sommets dans le graphe + 1 , elle s'incremente chaque fois on insére un sommet
    // ou se décremente chaque fois on supprime un sommet.
    li=*new QVector<int>();
    // les élèments du vecteur "fois" , permet de controller , avec la fonction "initialise" , la coloration de notre graphe.
    // On les utilises dans les boutons des algorithmes , ils prend les valeurs 1 et 0.
    fois=*new QVector<int>();
    saved=*new QVector<int>();
    loaded=*new QVector<int>();
    path=*new QVector<QString>();
    //Pour les éléments du vecteur "Oriented" , on les initialise par la valeur 'false'.
    Oriented=*new QVector<bool>();
    // les élèments du vecteur labels , sont utilisés pour afficher les labelss générer par des algorithmes au-dessus des sommets.
    labels=*new QVector<QVector<QGraphicsTextItem*>>();
    nodes=*new QVector<QVector<square*>>();
    graphes=*new QVector<Graphe*>();

}
 int c =1;
 int ns =0;
 int na =0;
 int pdm = 0;
MainWindow::~MainWindow()
{
    delete ui;
}

//Cette fonction permet de coloré nos sommets et arête/arc avec leurs couleurs initiales.
//On l'utilise pour controller la coloration de notre graphe.
void MainWindow::initilaise(){
   QLinkedList<Edge*>::iterator it1;
   for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
        labels[actuel][i]->setPlainText("");
        nodes[actuel][i]->set_Pen(QPen(QColor(42,42,41),1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        nodes[actuel][i]->UnSet_boundingRect();
        it1=graphes[actuel]->lsadj[i]->ed.begin();
        while(it1!=graphes[actuel]->lsadj[i]->ed.end()){
            (*it1)->set_Pen(QPen(QColor(20,149,194),1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            it1++;
          }
   }
}






//Generer un graphe

//Si tous les conditions sont satisfée (Graphe est construit).L'appel de se boutton se fait une seul fois (pour évitez le confusion).
//La lecture des données entrer se fait à l'aide du QInputDialog (getText) .
void MainWindow::on_Generer_Graphe_clicked(){
  //Si le vecteur scenes est vide se bouton ne fonctionera pas.
  if(!scenes.empty()){
     bool ok=false;
     //Si n'existe aucun sommet dans le graphe , rien ne sera exécuté.
     if(li[actuel]==0){
        //ce messagebox (questionner) permet  à l'utilisateur de choisir le type du Graphe,il prend comme retour un booléen et ses options sont yes:orientées ou No:non orientées
         //Rmq : Le messageBox prendre en consideration aussi ça fermeture au tant qu'une réponse non.
        QMessageBox::StandardButton reply;
        reply=QMessageBox::question(this,"Type de Graphe","Graphe Orienté ?",
                                    QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes) Oriented[actuel]=true;
        else Oriented[actuel]=false;

         QString text = QInputDialog::getText(this, "Generer un graphe",
                                          (tr("Entrer le nbr de sommets :")), QLineEdit::Normal, QString(),&ok);
         //les commands suivantes ne seront éxécutée si et seulement si ok == true , c.à.d , si on a cliqué sur 'ok' du InputDialog .
         if(ok){
            if(text!=""){
                reply=QMessageBox::question(this,"Les Signe des Poids","Voulez vous des poids négatifs ?",
                                            QMessageBox::Yes|QMessageBox::No);
                int signe = 0;
                if(reply==QMessageBox::Yes)signe = 1;

              if(text.contains(QRegExp("^\\d*$"))){
                ns = text.toInt();
                int h = qCeil(qSqrt(ns));
                int divx = 1400/h;
                int divy = 800/h;
                for(int i = 0; i < h ; i++){
                    for(int j = 0; j < h ; j++){
                    t[i][j].setX(-700+divx*i);
                    t[i][j].setY(-400+divy*j);
                    }
                }
                graphes[actuel]=new Graphe(Oriented[actuel]);
                for(int a=0;a<ns;a++){
                    QString text = QString::number(a);
                    labels[actuel].resize(li[actuel]+1);
                    nodes[actuel].resize(li[actuel]+1);
                       graphes[actuel]->ajouter_noeud(text);
                       nodes[actuel][li[actuel]]=new square(text);
                       nodes[actuel][li[actuel]]->is_oriented(Oriented[actuel]);
                       labels[actuel][li[actuel]] = new QGraphicsTextItem(nodes[actuel][li[actuel]]);
                       scenes[actuel]->addItem(nodes[actuel][li[actuel]]);
                       int rest = a/h;
                       int x = a%h;
                       int y = rest;
                       nodes[actuel][li[actuel]]->setPos(t[x][y]);
                       li[actuel]++;
                }
                QString text1 = QInputDialog::getText(this, "Generer un graphe",
                                                      (tr("Entrer le nbr de arretes :")), QLineEdit::Normal, QString(),&ok);
                if(ok){
                  if(text1!=""){
                   if(text1.contains(QRegExp("^\\d*$"))){
                    na = text1.toInt();
                    if(Oriented[actuel]){
                         while(na > ns*(ns-1)){
                            int V = ns*(ns-1);
                             QString Vtext = QString::number(V);
                             QString text1 = QInputDialog::getText(this, "Generer un graphe",
                                                                   (/*tr*/("Il faut que le nbr des aretes soit inferieur a "+ Vtext +" :")));
                                    QString str = text1;
                                    na = str.toInt();
                         }
                    }else{
                         while(na > (ns*(ns-1)/2)){
                             int V = (ns*(ns-1)/2);
                             QString Vtext = QString::number(V);
                             QString text1 = QInputDialog::getText(this, "Generer un graphe ",
                                                               (/*tr*/("Il faut que le nbr des aretes soit inferieur a "+ Vtext +" :")));
                                         na = text1.toInt();
                         }

                    }

                   QString text2 = QInputDialog::getText(this, "Generer un graphe",
                                                    (tr("Entrer le poids maximal :")),QLineEdit::Normal, QString(),&ok);
                   if(ok){
                     if(text2!=""){
                        if(text2.contains(QRegExp("^\\d*$"))){
                           pdm = text2.toInt();
                           for(c=0; c<na;c++){
                             int x = 0;
                             int k1=0;
                             int k2=0;
                             int inf = 20000000;
                             QString m;
                             QString t;

                             while(x == 0 ){
                                 k1 = rand()%ns;
                                 k2 = rand()%ns;
                                 x = k1 - k2;
                                 t = QString::number(k2);
                                  if(graphes[actuel]->lsadj[k1]->ele->list.contains(t)){
                                     x = 0;
                                 }
                             }

                             m = QString::number(k1);
                             t = QString::number(k2);
                             int pd=rand() %pdm;
//                             if (signe == 1){
//                                 int rans = rand()%100;
//                                if (rans < 5){
//                                    pd = -rand()%(pdm/4);
//                                }else pd=(rand()%(pdm/2))+pdm/2;
//                             }
                             if (signe == 1){
                                 int rans = rand()%100;
                                if (rans < 5){
                                    pd = -rand()%(pdm);
                                }else pd=rand()%(pdm);
                             }

                             Edge *D=new Edge(nodes[actuel][k1],nodes[actuel][k2],pd);
                             if(graphes[actuel]->lsadj[k2]->ele->list.contains(m) && Oriented[actuel]){
                                 D->darrow = true ;
                                 graphes[actuel]->lsadj[k1]->ed.append(D);
                             }else{
                                graphes[actuel]->lsadj[k1]->ed.prepend(D);
                                if(!Oriented[actuel]) graphes[actuel]->lsadj[k2]->ed.prepend(D);
                              }
                              scenes[actuel]->addItem(D);
                              graphes[actuel]->ajouter_arete(m,t,pd);
                              int d=0;
                              if(loaded[actuel]==1 || saved[actuel]==1) d=1;
                              if(d==1) ui->tabWidget->setTabText(actuel, path[actuel]+" *");
                              saved[actuel]=0;
                              int rpeat = 0;
                              if(signe == 1){
                              do{
                                  rpeat = 0;
                                  graphes[actuel]->Distance = new int  [graphes[actuel]->noeuds.list.size()];
                                  for(int i = 0; i < graphes[actuel]->noeuds.list.size(); i++){
                                      graphes[actuel]->Distance[i] = inf;
                                  }
                                  graphes[actuel]->Distance[k1] = 0;
                                  int tempDistance;
                                  int k;
                                  graphes[actuel]->Distance = new int  [graphes[actuel]->noeuds.list.size()];
                                  for(k = 0; k < ns+1; k++){
                                      int l = 0;
                                      for (int i = 0; i < graphes[actuel]->noeuds.list.size(); i++){
                                                  QLinkedList<QString>::iterator it;
                                                  it = graphes[actuel]->lsadj[i]->ele->list.begin();
                                                  while (it != graphes[actuel]->lsadj[i]->ele->list.end()){
                                                          tempDistance = graphes[actuel]->Distance[i] +  graphes[actuel]->Get_Poid(i,graphes[actuel]->get_indice(*it));
                                                          if(tempDistance < graphes[actuel]->Distance[graphes[actuel]->get_indice(*it)]){
                                                              graphes[actuel]->Distance[graphes[actuel]->get_indice(*it)] = tempDistance;
                                                              l++;
                                                          }
                                                          it++;
                                                      }
                                                  }
                                      if(l == 0)break;
                                  }
                                  if(k == ns+1){
                                      graphes[actuel]->changer_arete(m,t,((rand()%(pdm/2))+pdm/2));
                                      rpeat++;
                                  }
                              }while(rpeat != 0);

                           }
                         }
                       }else QMessageBox::warning(this,"Interdit","Entier seulement !");
                    }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie !");
                  }
               }else QMessageBox::warning(this,"Interdit","Entier seulement !");
            }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie");
          }
         }else QMessageBox::warning(this,"Interdit","Entier seulement !");
       }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie !");
      }
     }
    }

}


//Ajouter un Noeud


//Si la scène est vide  (Graphe ne contient aucun sommet) .La première fois qu'on click sur ce boutton pour créer un noeud
//,apparaître un seul fois un messagebox(questionner) .ce messagebox permet  à l'utilisateur de choisir le type du Graphe,
//il prend comme retour un booléen et ses options sont yes:orientées ou No:non orientées .
//Rmq : Le messageBox prendre en consideration aussi ça fermeture au tant qu'une réponse non.
void MainWindow :: on_Ajouter_Noeud_clicked(){
 //Si le vecteur scenes est vide se bouton ne fonctionera pas.
 if(!scenes.empty()){

    if(li[actuel]==0){//Pour afficher le message si n'existe aucun noeud
        QMessageBox::StandardButton reply;
        reply=QMessageBox::question(this,"Type de Graphe","Graphe Orienté ?",
                                      QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes) Oriented[actuel]=true;
        else Oriented[actuel]=false;
        graphes[actuel]=new Graphe(Oriented[actuel]);
    }
       bool ok=false;
       QString text = QInputDialog::getText(this, "Ajouter sommet",
                                          (tr("Entrer le valeur du sommet :")),QLineEdit::Normal, QString(), &ok);
       if (ok){
        if(text!=""){
            int h = qCeil(qSqrt(li[actuel]+1));
            int divx = 1400/h;
            int divy = 800/h;
            for(int i = 0; i < h ; i++){
                for(int j = 0; j < h ; j++){
                t[i][j].setX(-700+divx*i);
                t[i][j].setY(-400+divy*j);
                }
            }
          //La lecture des données entrer se fait à l'aide du QInputDialog (getText) selon la condition qu'il n'y a aucun espace
            //au début et à la fin de la chaine de caractère
          if(text.back()!=" " && text.front()!=" "){
            if(!graphes[actuel]->noeuds.list.contains(text)){
                labels[actuel].resize(li[actuel]+1);
                nodes[actuel].resize(li[actuel]+1);
                nodes[actuel][li[actuel]]=new square(text);
                nodes[actuel][li[actuel]]->is_oriented(Oriented[actuel]);
                labels[actuel][li[actuel]] = new QGraphicsTextItem(nodes[actuel][li[actuel]]);
                scenes[actuel]->addItem(nodes[actuel][li[actuel]]);
                graphes[actuel]->ajouter_noeud(text); 
                for(int i = 0; i < li[actuel]+1 ; i++){
                    int rest = i/h;
                    int x = i%h;
                    int y = rest;
                    nodes[actuel][i]->setPos(t[x][y]);
                }
                li[actuel]++;
                initilaise();
                int d=0;
                if(loaded[actuel]==1 && saved[actuel]==1) d=1;
                if(d==1) ui->tabWidget->setTabText(actuel, path[actuel]+" *");
                saved[actuel]=0;
           }else QMessageBox::warning(this,"Interdit","Le sommet déjà existe essayez avec une autre valeur !");
         }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
       }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie");
     }
  }
}



//Ajouter aretes



void MainWindow::on_Ajouter_Arete_clicked(){
 //Si le vecteur scenes est vide se bouton ne fonctionera pas.
 if(!scenes.empty() && li[actuel]>1){
    QString m;
    int k1=0,k2=0;
        bool ok = false;
        QString t = QInputDialog::getText(this, "Arêtes","Déterminer la source",
                                            QLineEdit::Normal, QString(),&ok);

   if (ok){
    if(t!=""){
     if(t.back()!=" " && t.front()!=" "){
      if(graphes[actuel]->noeuds.list.contains(t)){
            for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
              if(graphes[actuel]->noeuds.getnoeud(i)==t){
                      k1=i;
                      m=t;
              }
            }

     QString t = QInputDialog::getText(this,"Arêtes","Déterminer la Destination",
                                                 QLineEdit::Normal, QString(), &ok);

     if (ok){
      if(t!=""){
          //La lecture des données entrer se fait à l'aide du QInputDialog (getText) selon la condition qu'il n'y a aucun espace
            //au début et à la fin de la chaine de caractère
        if(t.back()!=" " && t.front()!=" "){
         if(graphes[actuel]->noeuds.list.contains(t)){
            for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
              if(graphes[actuel]->noeuds.getnoeud(i)==t) k2=i;
           }
          if(!graphes[actuel]->lsadj[k1]->ele->list.contains(t)){

           QString poid = QInputDialog::getText(this,"Arêtes","Déterminer le poids",
                                                           QLineEdit::Normal,QString(), &ok);
                  if (ok){
                   if(poid!=""){
                     if(poid.contains(QRegExp("^-?\\d*$")) && poid!="-"){
                      int pd=poid.toInt();
                       Edge *D=new Edge(nodes[actuel][k1],nodes[actuel][k2],pd);
                          if(graphes[actuel]->lsadj[k2]->ele->list.contains(m) && Oriented[actuel]){
                              QLinkedList<Edge*>::iterator it1;
                              it1=graphes[actuel]->lsadj[k2]->ed.begin();
                              while(it1!=graphes[actuel]->lsadj[k2]->ed.end()){
                                   if((*it1)->sourceNode()==nodes[actuel][k2] && (*it1)->destNode()==nodes[actuel][k1]){
                                      if((*it1)->darrow==true){
                                          graphes[actuel]->lsadj[k1]->ed.append(D);
                                      }else{
                                          D->darrow = true ;
                                          graphes[actuel]->lsadj[k1]->ed.append(D);
                                      }
                                  }
                                   it1++;
                              }
                          }else{
                            graphes[actuel]->lsadj[k1]->ed.append(D);
                            if(!Oriented[actuel]) graphes[actuel]->lsadj[k2]->ed.append(D);
                          }
                           scenes[actuel]->addItem(D);
                           graphes[actuel]->ajouter_arete(m,t,pd);
                           initilaise();
                           int d=0;
                           if(loaded[actuel]==1 || saved[actuel]==1) d=1;
                           if(d==1) ui->tabWidget->setTabText(actuel, path[actuel]+" *");
                           saved[actuel]=0;

                    }else QMessageBox::warning(this,"Interdit","Entier seulement !");
                   }else QMessageBox::warning(this,"Interdit","Aucune  valeur saisie !");
                 }

               }else QMessageBox::warning(this,"Interdit","l'arête existe deja!");

              }else QMessageBox::warning(this,"Interdit","La valeur n'existe pas, essayez avec une autre valeur !");
             }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
            }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie!");
           }
          }else QMessageBox::warning(this,"Interdit","La valeur n'existe pas, essayez avec une autre valeur !");

        }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
      }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie");
    }
  }

}




//Supprimer noeud



void MainWindow::on_Supprimer_Noeud_clicked(){
  //Si le vecteur scenes est vide se bouton ne fonctionera pas.
  if(!scenes.empty() && li[actuel]>0){
    bool ok = false;
    QString text = QInputDialog::getText(this, "Suppresion du Sommet",
                                      (tr("Veuillez insérer la valeur ici :")), QLineEdit::Normal, QString(),&ok);

    if(ok){
      if(text!=""){
         if(text.back()!=" " && text.front()!=" "){
           int k=-1;
           if(graphes[actuel]->noeuds.list.contains(text)){
                for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
                  if(graphes[actuel]->noeuds.getnoeud(i)==text) k=i;
                 }
             for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
                  if(*(graphes[actuel]->lsadj[i]->ele->list.begin())!=text){
                      if(graphes[actuel]->lsadj[i]->ele->list.contains(text)){
                         QLinkedList<Edge*>::iterator it;
                         it=graphes[actuel]->lsadj[i]->ed.begin();
                         while(it!=graphes[actuel]->lsadj[i]->ed.end()){
                            if((*it)->sourceNode()==nodes[actuel][i] && (*it)->destNode()==nodes[actuel][k]){
                               graphes[actuel]->lsadj[i]->ed.removeOne(*it);
                               scenes[actuel]->removeItem(*it);
                            }
                            it++;
                        }

                     }
                 }
             }
             if(!graphes[actuel]->lsadj[k]->ed.empty()){
                 QLinkedList<Edge*>::iterator it;
                  it=graphes[actuel]->lsadj[k]->ed.begin();
                  while(it!=graphes[actuel]->lsadj[k]->ed.end()){
                        graphes[actuel]->lsadj[k]->ed.removeOne(*it);
                        scenes[actuel]->removeItem(*it);
                        it++;
                    }
             }
             scenes[actuel]->removeItem(nodes[actuel][k]);
             graphes[actuel]->supprimer_noeud(text);
             nodes[actuel].remove(k);
             labels[actuel].remove(k);
             li[actuel]--;
             int h = qCeil(qSqrt(li[actuel]));
             int divx = 1400/h;
             int divy = 800/h;
             for(int i = 0; i < h ; i++){
                 for(int j = 0; j < h ; j++){
                 t[i][j].setX(-700+divx*i);
                 t[i][j].setY(-400+divy*j);
                 }
             }
             for(int i = 0; i < li[actuel] ; i++){
                 int rest = i/h;
                 int x = i%h;
                 int y = rest;
                 nodes[actuel][i]->setPos(t[x][y]);
             }
             initilaise();
             int d=0;
             if(loaded[actuel]==1 || saved[actuel]==1) d=1;
             if(d==1) ui->tabWidget->setTabText(actuel, path[actuel]+" *");
             saved[actuel]=0;
          }else QMessageBox::warning(this,"Interdit","Le sommet que vous vient de saisit n'existe pas !");
         }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
       }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie");
    }
  }
}


//Supprimer aretes




void MainWindow::on_Supprimer_Arete_clicked() {
  //Si le vecteur scenes est vide se bouton ne fonctionera pas.
  if(!scenes.empty() && li[actuel]>1){
    QString m;
    int k1=0,k2=0;
    bool ok = false;
    QString t = QInputDialog::getText(this, "Arêtes","Déterminer la source",
                                          QLineEdit::Normal, QString(), &ok);

    if (ok){
      if(t!=""){
         if(t.back()!=" " && t.front()!=" "){
          if(graphes[actuel]->noeuds.list.contains(t)){
              for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
                if(graphes[actuel]->noeuds.getnoeud(i)==t) k1=i;
               }
              m=t;
        QString t = QInputDialog::getText(this,"Arêtes","Déterminer la Destination",
                                                 QLineEdit::Normal, QString(), &ok);

        if (ok){
         if(t!=""){
          if(t.back()!=" " && t.front()!=" "){
            if(graphes[actuel]->noeuds.list.contains(t)){
             if(graphes[actuel]->lsadj[k1]->ele->list.contains(t)){
               for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
                  if(graphes[actuel]->noeuds.getnoeud(i)==t)k2=i;
               }
               for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
                  if(graphes[actuel]->lsadj[i]->ele->list.contains(t)){
                     if(!graphes[actuel]->lsadj[i]->ed.empty()){
                       QLinkedList<Edge*>::iterator it;
                       it=graphes[actuel]->lsadj[i]->ed.begin();
                       while(it!=graphes[actuel]->lsadj[i]->ed.end()){
                          if((*it)->sourceNode()==nodes[actuel][k1] && (*it)->destNode()==nodes[actuel][k2]){
                              graphes[actuel]->lsadj[i]->ed.removeOne(*it);
                              scenes[actuel]->removeItem(*it);
                          }
                          if(!Oriented[actuel]){
                            if((*it)->sourceNode()==nodes[actuel][k2] && (*it)->destNode()==nodes[actuel][k1]){
                                  graphes[actuel]->lsadj[i]->ed.removeOne(*it);
                            }
                          }
                          it++;
                        }
                      }
                   }
                 }
                graphes[actuel]->supprimer_arete(m,t);
                initilaise();
                int d=0;
                if(loaded[actuel]==1 || saved[actuel]==1) d=1;
                if(d==1) ui->tabWidget->setTabText(actuel, path[actuel]+" *");
                saved[actuel]=0;

               }else QMessageBox::warning(this,"Interdit","Il n'y a aucune arête entre "+ m+" et" +t);
             }else QMessageBox::warning(this,"Interdit","Le sommet "+t+" n'existe pas essayez avec une autre valeur !");
           }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
          }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie");
         }
       }else QMessageBox::warning(this,"Interdit","Le sommet "+t+" n'existe pas essayez avec une autre valeur !");
      }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
     }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie");
   }
  }
}



///Floyd-Warshall



void MainWindow::on_Floyd_Warshall_clicked(){
 //Si le vecteur graphes est vide se bouton ne fonctionera pas.
 if(!graphes.empty()){

  if(li[actuel]!=0){

    QString m;
    if(Oriented[actuel]){
      bool ok = false;
      QString t = QInputDialog::getText(this, "Arêtes","Déterminer la source",
                                            QLineEdit::Normal, QString(), &ok);
      if (ok){
        if(t!=""){
          if(t.back()!=" " && t.front()!=" "){
            if(graphes[actuel]->noeuds.list.contains(t)){
             m=t;
             QString t = QInputDialog::getText(this,"Arêtes","Déterminer la Destination",
                                                        QLineEdit::Normal, QString(), &ok);

            if (ok){
             if(t!=""){
               if(t.back()!=" " && t.front()!=" "){
                  if(graphes[actuel]->noeuds.list.contains(t)){
                       if(fois[actuel]!=0){
                           initilaise();
                       }
                   QLinkedList<QString> chemin;
                   chemin=graphes[actuel]->floyd_Warshall(m,t);
                   if(!chemin.empty()){
                     if(chemin.front()!="-1"){
                       int k=0;
                       QVector<int> valeurs=*new QVector<int>(chemin.size());
                       QLinkedList<QString>::iterator it;
                       it=chemin.begin();
                      while(it!=chemin.end()){
                           for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
                               if(nodes[actuel][i]->te==(*it)){
                                   nodes[actuel][i]->set_Pen(QPen(QColor("#9B654A"),3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                                   nodes[actuel][i]->Set_boundingRect(28);
                                   valeurs[k++]=i;
                                }
                            }
                           it++;
                       }
                      k=0;
                      QLinkedList<Edge*>::iterator it1;
                      int dist=0;
                      for(int i=0;i<(chemin.size()-1);i++){
                          k=i+1;
                           it1=graphes[actuel]->lsadj[valeurs[i]]->ed.begin();
                           while(it1!=graphes[actuel]->lsadj[valeurs[i]]->ed.end()){
                             if((*it1)->sourceNode()==nodes[actuel][valeurs[i]] && (*it1)->destNode()==nodes[actuel][valeurs[k]]){
                                 (*it1)->set_Pen(QPen(QColor("#9B654A"),4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//                                 (*it1)->cont->setHtml("<h2 style =\"background-color :#9B654A ;color : #000; border-radius:2px; \" >"+(*it1)->cont->toPlainText()+"</h2>");
                                 dist=dist+(*it1)->cont->toPlainText().toInt();

                            }
                            it1++;
                           }
                            if(nodes[actuel][valeurs[k]]->te==t){
                                QString c = QString::number(dist);
                                QString text = "<div  style=\"color:#000;font-weight:bold \"> "+ c +" </div>";
                                labels[actuel][valeurs[k]]->setHtml(text);
                                labels[actuel][valeurs[k]]->setDefaultTextColor(Qt::black);
                                labels[actuel][valeurs[k]]->setPos(0,-25);
                                labels[actuel][valeurs[k]]->setFont(QFont("serif",11));
                             }
                             if(nodes[actuel][valeurs[i]]->te==m){
                                QString c = "Source";
                                QString text = "<div  style=\"color:#000;font-weight:bold \"> "+ c +" </div>";
                                labels[actuel][valeurs[i]]->setHtml(text);
                                labels[actuel][valeurs[i]]->setDefaultTextColor(Qt::black);
                                labels[actuel][valeurs[i]]->setPos(-8,-25);
                                labels[actuel][valeurs[i]]->setFont(QFont("serif",11));
                             }
                      }
                       fois[actuel]=1;
                   }else QMessageBox::warning(this,"Interdit"," Circuit Absorbant !");
                 }else QMessageBox::warning(this,"Interdit"," Aucun chemin existe");
               }else QMessageBox::warning(this,"Interdit",t+" n'existe pas essayez avec une autre valeur !");
              }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
             }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie");
           }
          }else QMessageBox::warning(this,"Interdit",t+" n'existe pas essayez avec une autre valeur !");
         }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
        }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie");
      }
    }else  QMessageBox::warning(this,"Interdit","Graphe non Orienter");

   }//li[actuel]!=0

 }//if(!graphes.empty())

}


///DIJKSTRA


void MainWindow::on_DIJKSTRA_clicked(){
 //Si le vecteur graphes est vide se bouton ne fonctionera pas.
 if(!graphes.empty()){

  if(li[actuel]!=0){

    int negative = 0;
    for(int l=0;l<graphes[actuel]->noeuds.list.size();l++){
        QLinkedList<int>::iterator it_poid=graphes[actuel]->lsadj[l]->poid.begin();
        while(it_poid!=graphes[actuel]->lsadj[l]->poid.end()){
            if((*it_poid)<0){
                negative = 1;
            }
            it_poid++;
        }
    }
    if(negative==1) QMessageBox::warning(this,"Interdit","Il existe des poids négatifs !");
    if(negative==0){
        bool ok=false;
        if(fois[actuel]!=0){
            initilaise();
        }
        QString t = QInputDialog::getText(this,"ALGORITHME DIJKSTRA","Déterminer la source",
                                                     QLineEdit::Normal, QString(),&ok);
        if (ok){
          if(t!=""){
           if(t.back()!=" " && t.front()!=" "){
              if(graphes[actuel]->noeuds.list.contains(t)){
                  QLinkedList<QString> chemin(graphes[actuel]->dijkstra(t));
                  int i = 0; // indice du destinatination
                  int z = 0; // indice du source
                  QLinkedList<QString>::iterator it_2=chemin.begin();
                  while(it_2!=chemin.end()){
                      if(*it_2!="-1"){
                          z=graphes[actuel]->get_indice(*it_2);
                          for(int j=0;j<graphes[actuel]->noeuds.list.size();j++){
                              QLinkedList<Edge*>::iterator it_ed=graphes[actuel]->lsadj[j]->ed.begin();
                              while(it_ed!=graphes[actuel]->lsadj[j]->ed.end()){

                              if((*it_ed)->sourceNode()==nodes[actuel][z] && (*it_ed)->destNode()==nodes[actuel][i])
                              (*it_ed)->set_Pen(QPen(QColor("#059567"),4,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

                              if(!Oriented[actuel]){
                                  if((*it_ed)->sourceNode()==nodes[actuel][i] && (*it_ed)->destNode()==nodes[actuel][z])
                                  (*it_ed)->set_Pen(QPen(QColor("#059567"),4,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                              }
                               it_ed++;
                              }
                          }
                      }
                      if(graphes[actuel]->dist[i]!=INT_MAX){
                          QString c = QString::number(graphes[actuel]->dist[i]);
                          QString text = "<div  style=\"color:#000;font-weight:bold \"> "+ c +" </div>";
                          labels[actuel][i]->setHtml(text);
                          labels[actuel][i]->setDefaultTextColor(Qt::black);
                          labels[actuel][i]->setPos(0,-25);
                          labels[actuel][i]->setFont(QFont("serif",11));
                          nodes[actuel][i]->set_Pen(QPen(QColor("#059567"),3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                          nodes[actuel][i]->Set_boundingRect(28);
                      }
                      if(nodes[actuel][i]->te==t){
                          QString c = "Source";
                          QString text = "<div  style=\"color:#000;font-weight:bold \"> "+ c +" </div>";
                          labels[actuel][i]->setHtml(text);
                          labels[actuel][i]->setDefaultTextColor(Qt::black);
                          labels[actuel][i]->setPos(-8,-25);
                          labels[actuel][i]->setFont(QFont("serif",11));
                          nodes[actuel][i]->set_Pen(QPen(QColor("#059567"),3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                          nodes[actuel][i]->Set_boundingRect(28);
                      }
                      i++;
                      it_2++;
                  }
             fois[actuel]=1;
          }else QMessageBox::warning(this,"Interdit",t+" n'existe pas essayez avec une autre valeur !");
         }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
        }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie");
      }
    }

  }//li[actuel]!=0
 }//if(!graphes.empty())

}


///Bellman


void MainWindow::on_Bellman_clicked()
{
 //Si le vecteur graphes est vide se bouton ne fonctionera pas.
 if(!graphes.empty()){

  if(li[actuel]!=0){

    QString m;
    if(Oriented[actuel]){
        bool ok = false;
        m = QInputDialog::getText(this, "Arêtes","Déterminer la source",
                                            QLineEdit::Normal, QString(), &ok);
      if(fois[actuel] !=0)   initilaise();
       if (ok){
        if(m!=""){
         if(m.back()!=" " && m.front()!=" "){
           if(graphes[actuel]->noeuds.list.contains(m)){

               QLinkedList<QString> *chemin;
               chemin = new QLinkedList<QString> [graphes[actuel]->noeuds.list.size()];
               chemin= graphes[actuel]->Bellman_Ford(m);
               if(chemin != NULL){
               for(int l = 0; l < graphes[actuel]->noeuds.list.size() ;l++ ){
                   QString t = graphes[actuel]->noeuds.getnoeud(l);
                   if(chemin[l].contains(m)){
                       int k=0;
                       QVector<int> valeurs=*new QVector<int>(chemin[graphes[actuel]->get_indice(t)].size());
                       QLinkedList<QString>::iterator it;
                       it=chemin[graphes[actuel]->get_indice(t)].begin();
                      while(it!=chemin[graphes[actuel]->get_indice(t)].end()){
                           for(int i=0;i<graphes[actuel]->noeuds.list.size();i++){
                               if(nodes[actuel][i]->te==(*it)){
                                   nodes[actuel][i]->set_Pen(QPen(QColor("#7E1E4B"),3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                                   nodes[actuel][i]->Set_boundingRect(28);
                                   valeurs[k++]=i;
                          }
                         }
                           it++;
                       }
                      k=0;
                      QLinkedList<Edge*>::iterator it1;
                      for(int i=0;i<(chemin[graphes[actuel]->get_indice(t)].size()-1);i++){
                          k=i+1;
                           it1=graphes[actuel]->lsadj[valeurs[i]]->ed.begin();
                           while(it1!=graphes[actuel]->lsadj[valeurs[i]]->ed.end()){
                                    if((*it1)->sourceNode()==nodes[actuel][valeurs[i]] && (*it1)->destNode()==nodes[actuel][valeurs[k]]){
                                       (*it1)->set_Pen(QPen(QColor("#7E1E4B"),4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                                     }
                                  it1++;
                             }
                          }
                      if(l==graphes[actuel]->get_indice(m)){
                          QString c = "Source";
                          QString text = "<div  style=\"color:#000;font-weight:bold \"> "+ c +" </div>";
                          labels[actuel][l]->setHtml(text);
                          labels[actuel][l]->setPos(-8,-25);
                      }else{
                          QString c = QString::number(graphes[actuel]->Distance[l]);
                          QString text = "<div  style=\"color:#000;font-weight:bold \"> "+ c +" </div>";
                          labels[actuel][l]->setHtml(text);
                          labels[actuel][l]->setPos(0,-25);
                      }
                          labels[actuel][l]->setFont(QFont("serif",11));
                          nodes[actuel][l]->set_Pen(QPen(QColor("#7E1E4B"),3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                          nodes[actuel][l]->Set_boundingRect(28);
                   }
             }
               fois[actuel]++;
               }
         }else QMessageBox::warning(this,"Interdit","Le sommet "+m+" n'existe pas essayez avec une autre valeur !");
        }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
       }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie.");
      }
    }else  QMessageBox::warning(this,"Interdit","Graphe non Orienter.");

   }//if(li[actuel]!=0)

  }//if(!graphes.empty())

}

///Johnson


void MainWindow::on_Johnson_clicked()
{

if(!graphes.empty()){

 if(li[actuel]!=0){

    QLinkedList<QString>* chemin=graphes[actuel]->Johnson();
    if(Oriented[actuel]){
        if(chemin!=NULL){
          QLinkedList<QString>::iterator it;
          bool ok;
          do{
            QString m;
            ok=false;
            QString t = QInputDialog::getText(this, "Johnson","Déterminer la source",
                                                  QLineEdit::Normal, QString(), &ok);

            if (ok){
             if(t!="" && ok){
              if(t.back()!=" " && t.front()!=" " && ok){
               if(graphes[actuel]->noeuds.list.contains(t)){
                  m=t;
                QString t = QInputDialog::getText(this,"Johnson","Déterminer la Destination",
                                                                 QLineEdit::Normal, QString(), &ok);

               if (ok){
                if(t!="" && ok){
                 if(t.back()!=" " && t.front()!=" " && ok){
                  if(graphes[actuel]->noeuds.list.contains(t)){
                     if(fois[actuel]!=0){
                          initilaise();
                      }
                    int s = graphes[actuel]->get_indice(m);
                    int d = graphes[actuel]->get_indice(t);
                    it = chemin[s].begin();
                    int comp=0;
                    QString copy;
                    while(it!=chemin[s].end()){
                        if(comp==d) copy=*it;
                        it++;
                        comp++;
                      }
                    if(copy != "-1"){
                      QString c;
                      c = QString::number(graphes[actuel]->Distance_Johnson[s][d]);
                      QString text = "<div  style=\"color:#000;font-weight:bold \"> "+ c +" </div>";
                      labels[actuel][d]->setHtml(text);
                      labels[actuel][d]->setPos(0,-25);
                      labels[actuel][d]->setFont(QFont("serif",11));
                      while(d != s){
                        it = chemin[s].begin();
                        comp=0;
                        while(it!=chemin[s].end()){
                           if(comp==d) copy=*it;
                           it++;
                           comp++;
                        }
                        QLinkedList<Edge*>::iterator it_ed=graphes[actuel]->lsadj[graphes[actuel]->get_indice(copy)]->ed.begin();
                        while(it_ed!=graphes[actuel]->lsadj[graphes[actuel]->get_indice(copy)]->ed.end()){
                          if((*it_ed)->sourceNode()==nodes[actuel][graphes[actuel]->get_indice(copy)] && (*it_ed)->destNode()==nodes[actuel][d])
                           (*it_ed)->set_Pen(QPen(QColor("#29807D"),4,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                            it_ed++;
                        }
                        nodes[actuel][d]->set_Pen(QPen(QColor("#29807D"),3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                        nodes[actuel][d]->Set_boundingRect(28);
                        d = graphes[actuel]->get_indice(copy);
                      }
                      c = "Source";
                      text = "<div  style=\"color:#000;font-weight:bold \"> "+ c +" </div>";
                      labels[actuel][s]->setHtml(text);
                      labels[actuel][s]->setPos(-8,-25);
                      labels[actuel][s]->setFont(QFont("serif",11));
                      nodes[actuel][s]->set_Pen(QPen(QColor("#29807D"),3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                      nodes[actuel][s]->Set_boundingRect(28);
                      fois[actuel] = 1;
                       }else QMessageBox::warning(this,"Interdit"," Il n'y a pas de chemin entre "+m+" et "+t+" !");
                      }else QMessageBox::warning(this,"Interdit",t+" n'existe pas essayez avec une autre valeur !");
                     }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
                    }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie.");
                   }
                  }else QMessageBox::warning(this,"Interdit",t+" n'existe pas essayez avec une autre valeur !");
                 }else QMessageBox::warning(this,"Interdit","Erreur de saisie ( ESPACE ) ");
                }else QMessageBox::warning(this,"Interdit","Aucune valeur saisie.");
               }
                QMessageBox msgBox;
                msgBox.setWindowTitle("Johnson");
                msgBox.setText("Choisir un autre pair ??");
                msgBox.setStandardButtons(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::Yes);
                if(msgBox.exec() == QMessageBox::Yes)ok =true;
                else ok =false;
              }while(ok == true);
        }
    }else QMessageBox::warning(this,"Interdit","Graphe non Orienter.");

    }//if(li[actuel]!=0)

 }//if(!graphes.empty())

}

///fermer

void MainWindow::fermer()
{
    int vider=1;
    if(saved[actuel]==0 && !nodes[actuel].empty()){
        QMessageBox::StandardButton reply;
        reply=QMessageBox::warning(this,"Enregistrement","Votre graphe n'est pas enrgistrer.Veuillez-vous l'enregistrer ?",
                                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
       if(reply==QMessageBox::Yes) save();
       if(reply==QMessageBox::Cancel) vider=0;
    }
    if(vider==1 && !nodes[actuel].empty()){
        for(int j=0;j<graphes[actuel]->noeuds.list.size();j++){
            QLinkedList<Edge*>::iterator it_ed=graphes[actuel]->lsadj[j]->ed.begin();
            while(it_ed!=graphes[actuel]->lsadj[j]->ed.end()){
                scenes[actuel]->removeItem(*it_ed);
             it_ed++;
            }
        }
        for(int j=0;j<graphes[actuel]->noeuds.list.size();j++){
            graphes[actuel]->lsadj[j]->ed.clear();
            graphes[actuel]->lsadj[j]->poid.clear();
            graphes[actuel]->lsadj[j]->ele->list.clear();
        }
        for(int j=0;j<graphes[actuel]->noeuds.list.size();j++){
            scenes[actuel]->removeItem(nodes[actuel][j]);
        }
        nodes[actuel].clear();
        labels[actuel].clear();
        graphes[actuel]->noeuds.list.clear();
        Oriented[actuel]=false;
        graphes[actuel]=NULL;
        li[actuel]=0;
        loaded[actuel]=0;
    }
}

void MainWindow::ajouter_tab()
{
    ui->tabWidget->setStyleSheet("background-color:white;"
                                 "border-radius:0px;");
    New_j1++;
    graphes.resize(New_j1);
    scenes.resize(New_j1);
    li.resize(New_j1);
    fois.resize(New_j1);
    saved.resize(New_j1);
    loaded.resize(New_j1);
    nodes.resize(New_j1);
    labels.resize(New_j1);
    Oriented.resize(New_j1);
    path.resize(New_j1);
    QGraphicsView *view=new QGraphicsView();
    ui->tabWidget->addTab(view,"Tab "+QString::number(New_j1)+" *");
    scenes[New_j1-1]=new QGraphicsScene();
    view->setScene(scenes[New_j1-1]);
    li[New_j1-1]=0;
    fois[New_j1-1]=0;
    saved[New_j1-1]=0;
    loaded[New_j1-1]=0;
    Oriented[New_j1-1]=false;
    ui->tabWidget->setCurrentIndex(New_j1-1);
}


// Menu---New

void MainWindow::on_actionNew_triggered()
{
    ajouter_tab();
}

///Enregistrement

void MainWindow::save()
{
    //Si le vecteur scenes est vide se bouton ne fonctionera pas.
    if(!scenes.empty()){
    if(loaded[actuel]==0){
        QString newPath = QFileDialog::getSaveFileName(this, trUtf8("Save TXT"),
            path[actuel], tr("TEXT files (*.txt)"));

        if (newPath.isEmpty())
            return;
        path[actuel] = newPath;
    }
    QFile file(path[actuel]);
          if(file.open(QIODevice::WriteOnly | QIODevice::Text))
          {
            QTextStream stream(&file);
            stream<<"Orienter = "<<Oriented[actuel]<<endl;
            for(int i = 0;i<graphes[actuel]->noeuds.list.size();i++){
                    QLinkedList<QString>::iterator it=graphes[actuel]->lsadj[i]->ele->list.begin();
                    QLinkedList<int>::iterator it_p=graphes[actuel]->lsadj[i]->poid.begin();
                    stream<<*it<<" "<<nodes[actuel][i]->pos().x()<<" "<<nodes[actuel][i]->pos().y()<<endl;
                    it++;
                    while(it!=graphes[actuel]->lsadj[i]->ele->list.end()){
                        stream<<*it<<"*"<<endl;
                        stream<<*it_p<<".."<<endl;
                        it++;
                        it_p++;
                    }

            }
            file.close();
            saved[actuel]=1;
            loaded[actuel]=1;
          }
          QFileInfo f(file);
          path[actuel] = f.baseName()+".txt";
          ui->tabWidget->setTabText(actuel, path[actuel]);
    }//if(!scenes.empty()){
}


void MainWindow::on_actionSave_triggered()
{
    if(!scenes.empty()) save();
}


///Chargement

void MainWindow::on_actionLoad_triggered()
{
    ajouter_tab();

    if(!nodes[actuel].empty()) fermer();
    QString newPath = QFileDialog::getOpenFileName(this, trUtf8("Open TXT"),
                                                   path[actuel], tr("TEXT files (*.txt)"));
    if (newPath.isEmpty())
        return;

    path[actuel] = newPath;
    QString dest;
    QString src;
    int d=0;
    int c=0;
    QString line;
    QString copy;
    QFile file(path[actuel]);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line=stream.readLine();
            if(line.contains("=")){
                QRegularExpression rx("\\d+");
                QRegularExpressionMatchIterator i = rx.globalMatch(line);
                while (i.hasNext()) {
                      QRegularExpressionMatch match = i.next();
                      Oriented[actuel]=match.captured(0).toInt();
                }
                graphes[actuel]=new Graphe(Oriented[actuel]);
            }
            if(!line.contains(".") && !line.contains("*") && !line.contains("=")){
                labels[actuel].resize(li[actuel]+1);
                nodes[actuel].resize(li[actuel]+1);
                //compter le nombre des espaces
                foreach(QChar cha, line){
                    if(cha.isSpace()) d++;
                }
                //cette valeur indique le nombre des espaces
                c=d;
                //Parcourir la line et copier uniquement les lettres avec des espaces
                d=0;
                foreach(QChar cha, line){
                    if(cha.isSpace()) d++;
                    if((cha=="'" || cha.isNumber() || (cha.isLetter() || cha.isSpace())) && d<c-1){
                         copy.append(cha);
                    }
                }
                nodes[actuel][li[actuel]]=new square(copy);
                nodes[actuel][li[actuel]]->is_oriented(Oriented[actuel]);
                labels[actuel][li[actuel]] = new QGraphicsTextItem(nodes[actuel][li[actuel]]);
                scenes[actuel]->addItem(nodes[actuel][li[actuel]]);
                graphes[actuel]->ajouter_noeud(copy);
                //Au-dessous on va copier uniquement la valeur des abscisses
                d=0;
                copy.clear();
                foreach(QChar cha, line){
                    if(cha.isSpace()) d++;
                    if(d==c-1){
                        if(cha.isNumber() || cha=="-"){
                            copy.append(cha);
                        }
                    }
                }
                nodes[actuel][li[actuel]]->setX(copy.toInt());
                //On va copier uniquement la valeur des ordonnées
                copy.clear();
                d=0;
                foreach(QChar cha, line){
                    if(cha.isSpace()) d++;
                    if(d==c){
                        if(cha.isNumber() || cha=="-"){
                              copy.append(cha);
                        }
                    }
                }
                nodes[actuel][li[actuel]]->setY(copy.toInt());
                li[actuel]++;

            }

            d=0;
            copy.clear();
        }

    }
    d=0;
    QFile file1(path[actuel]);
    if (file1.open(QIODevice::ReadWrite | QIODevice::Text)){
        QTextStream stream1(&file1);
        while (!stream1.atEnd()){
            line=stream1.readLine();
            if(line.contains("=")){
            }
            if(!line.contains("..") && !line.contains("*") && !line.contains("=")){
                foreach(QChar cha, line){
                    if(cha.isSpace()) d++;
                }
                //cette valeur indique le nombre des espaces
                c=d;
                d=0;
                foreach(QChar cha, line){
                    if(cha.isSpace()) d++;
                    if((cha=="'" || cha.isNumber() || (cha.isLetter() || cha.isSpace())) && d<c-1){
                         copy.append(cha);
                    }
                }
                src=copy;
             }

             if(line.contains("*")){
                copy.clear();
                QRegularExpression rx("[A-Za-zà-ÿÀ-Ÿ'\\s0-9]");
                QRegularExpressionMatchIterator i = rx.globalMatch(line);
                while (i.hasNext()) {
                      QRegularExpressionMatch match = i.next();
                      copy.append(match.captured(0));
                }
                dest=copy;
             }

             if(line.contains("..")){
                 QRegularExpression rx("-?\\d+");
                 QRegularExpressionMatchIterator i = rx.globalMatch(line);
                 while (i.hasNext()) {
                       QRegularExpressionMatch match = i.next();
                       if(graphes[actuel]->lsadj[graphes[actuel]->get_indice(dest)]->ele->list.contains(src) && !Oriented[actuel]){

                       }else{
                           if(graphes[actuel]->lsadj[graphes[actuel]->get_indice(dest)]->ele->list.contains(src) && Oriented[actuel]){
                               Edge *D=new Edge(nodes[actuel][graphes[actuel]->get_indice(src)],nodes[actuel][graphes[actuel]->get_indice(dest)],match.captured(0).toInt());
                               D->darrow = true ;
                               graphes[actuel]->lsadj[graphes[actuel]->get_indice(src)]->ed.append(D);
                                scenes[actuel]->addItem(D);
                            }else{
                                 Edge *D=new Edge(nodes[actuel][graphes[actuel]->get_indice(src)],nodes[actuel][graphes[actuel]->get_indice(dest)],match.captured(0).toInt());
                                 graphes[actuel]->lsadj[graphes[actuel]->get_indice(src)]->ed.prepend(D);
                                 if(!Oriented[actuel]) graphes[actuel]->lsadj[graphes[actuel]->get_indice(dest)]->ed.prepend(D);
                                 scenes[actuel]->addItem(D);

                                 }
                            graphes[actuel]->ajouter_arete(src,dest,match.captured(0).toInt());
                       }

                 }//while(i.hasNext())
             }//if(line.contains("..")
                d=0;
                copy.clear();
        }//while (!stream1.atEnd())
    }//if (file1.open(QIODevice::ReadWrite | QIODevice::Text))*/
    loaded[actuel]=1;
    saved[actuel]=1;
    QFileInfo f(file);
    path[actuel] = f.baseName()+".txt";
    ui->tabWidget->setTabText(actuel, path[actuel]);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!scenes.empty()){
        if(saved[actuel]==0 && !nodes[actuel].empty()){
            QMessageBox::StandardButton reply;
            reply=QMessageBox::warning(this,"Enregistrement","Votre graphe n'est pas enrgistrer.Veuillez-vous l'enregistrer ?",
                                        QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
           if(reply==QMessageBox::Yes){ save(); fermer(); closeEvent(event);}
           if(reply==QMessageBox::No){ saved[actuel]=1; fermer(); closeEvent(event);}
           if(reply==QMessageBox::Cancel) event->ignore();
        }
    }
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    actuel=index;
   // qDebug()<<index;
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    int supprimer=1;
    if(saved[index]==0){
        QMessageBox::StandardButton reply;
        reply=QMessageBox::warning(this,"Enregistrement","Votre graphe n'est pas enrgistrer.Veuillez-vous l'enregistrer ?",
                                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if(reply==QMessageBox::Yes) save();
        if(reply==QMessageBox::Cancel) supprimer=0;
     }
    if(supprimer==1){
        graphes.removeAt(index);
        scenes.removeAt(index);
        li.removeAt(index);
        fois.removeAt(index);
        saved.removeAt(index);
        loaded.removeAt(index);
        if(!nodes[index].empty()){
            nodes.removeAt(index);
            labels.removeAt(index);
        }
        path.removeAt(index);
        ui->tabWidget->removeTab(index);
        New_j1--;
    }
    if(scenes.empty()){
        ui->tabWidget->setStyleSheet("background-image:url(:/icons/icons/12.jpeg);"
                                     "background-repeat:none;"
                                     "background-color:#000918;"
                                     "border-style:solid;"
                                     "border-width:1px;"
                                     "border-color:black;");
    }

}


