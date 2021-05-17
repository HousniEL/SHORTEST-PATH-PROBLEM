#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include <QRegularExpressionMatchIterator>
#include <QFile>
#include <QFileInfo>
#include <QCloseEvent>
#include <QFileDialog>
#include "graphe.h"
#include "square.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void initilaise();
    void save();
    void fermer();
    void ajouter_tab();
    QVector<int> saved;
    QVector<int> loaded;
    ~MainWindow();


private slots:
    void on_Generer_Graphe_clicked();

    void on_Ajouter_Noeud_clicked();

    void on_Ajouter_Arete_clicked();

    void on_Supprimer_Noeud_clicked();

    void on_Supprimer_Arete_clicked();

    void on_DIJKSTRA_clicked();

    void on_Floyd_Warshall_clicked();

    void on_Bellman_clicked();

    void on_Johnson_clicked();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_tabCloseRequested(int index);


protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    int actuel;
    QGraphicsLineItem *line;
    QVector<bool> Oriented;
    QVector<QVector<square*>> nodes;
    QVector<QGraphicsScene*> scenes;
    QVector<int> li;
    QVector<int> fois;
    QVector<Graphe*> graphes;

    QVector<QVector<QGraphicsTextItem*>> labels;
    QVector<QString> path;

};
#endif // MAINWINDOW_H
