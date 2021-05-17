/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionLoad;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QPushButton *Generer_Graphe;
    QPushButton *Ajouter_Noeud;
    QPushButton *Ajouter_Arete;
    QPushButton *Supprimer_Arete;
    QPushButton *Supprimer_Noeud;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Floyd_Warshall;
    QPushButton *DIJKSTRA;
    QPushButton *Bellman;
    QPushButton *Johnson;
    QTabWidget *tabWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1105, 610);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(" QGraphicsView\n"
"{\n"
"  border : 1px solid #ccc;\n"
"  background-color : #ddd;\n"
"}\n"
"\n"
" QPushButton\n"
"{\n"
"  width:135px;\n"
"  height:28px;\n"
"  background-color : #fff;\n"
"  color : #111;\n"
"  font-size: 12px;\n"
"  border-radius :20px;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"  background-color: #3EE793;\n"
"  color : black;\n"
"}\n"
"QTabWidget>QWidget{\n"
"color:black;\n"
"}\n"
"#MainWindow{\n"
"background-image:url(:/icons/icons/11.jpeg); \n"
"background-repeat:no-repeat;\n"
"background-color:#000918;\n"
"}\n"
"\n"
"\n"
"\n"
"QTabWidget>QWidget:hover{\n"
"background-color: #3EE793;\n"
"};\n"
"\n"
"\n"
"color :#000;\n"
"\n"
""));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/81-512.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        QFont font;
        font.setPointSize(11);
        actionNew->setFont(font);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/62124.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionSave->setFont(font);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/43-512.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon2);
        actionLoad->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, -1, -1, -1);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setStyleSheet(QString::fromUtf8("border:none;\n"
""));
        groupBox_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 9, 0, -1);
        Generer_Graphe = new QPushButton(groupBox_2);
        Generer_Graphe->setObjectName(QString::fromUtf8("Generer_Graphe"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Generer_Graphe->sizePolicy().hasHeightForWidth());
        Generer_Graphe->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Myanmar Text"));
        Generer_Graphe->setFont(font1);
        Generer_Graphe->setCursor(QCursor(Qt::PointingHandCursor));
        Generer_Graphe->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:white;\n"
"/*border-style:solid;\n"
"border-width:0.5px;\n"
"border-color:black;*/\n"
"border-radius:20px;\n"
"width:155px;\n"
"margin-left:0px;\n"
"\n"
"}\n"
"QPushButton:hover{\n"
"background-color:#3EE793;\n"
"color:black;\n"
"};"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/Groupe 114.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Generer_Graphe->setIcon(icon3);
        Generer_Graphe->setIconSize(QSize(34, 34));
        Generer_Graphe->setCheckable(false);
        Generer_Graphe->setChecked(false);
        Generer_Graphe->setAutoRepeatDelay(300);

        verticalLayout->addWidget(Generer_Graphe);

        Ajouter_Noeud = new QPushButton(groupBox_2);
        Ajouter_Noeud->setObjectName(QString::fromUtf8("Ajouter_Noeud"));
        sizePolicy2.setHeightForWidth(Ajouter_Noeud->sizePolicy().hasHeightForWidth());
        Ajouter_Noeud->setSizePolicy(sizePolicy2);
        Ajouter_Noeud->setFont(font1);
        Ajouter_Noeud->setCursor(QCursor(Qt::PointingHandCursor));
        Ajouter_Noeud->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:white;\n"
"/*border-style:solid;\n"
"border-width:0.5px;\n"
"border-color:black;*/\n"
"border-radius:20px;\n"
"width:155px;\n"
"margin-left:0px;\n"
"\n"
"}\n"
"QPushButton:hover{\n"
"background-color:#3EE793;\n"
"color:black;\n"
"};"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/Groupe 135.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Ajouter_Noeud->setIcon(icon4);
        Ajouter_Noeud->setIconSize(QSize(34, 34));

        verticalLayout->addWidget(Ajouter_Noeud);

        Ajouter_Arete = new QPushButton(groupBox_2);
        Ajouter_Arete->setObjectName(QString::fromUtf8("Ajouter_Arete"));
        sizePolicy2.setHeightForWidth(Ajouter_Arete->sizePolicy().hasHeightForWidth());
        Ajouter_Arete->setSizePolicy(sizePolicy2);
        Ajouter_Arete->setFont(font1);
        Ajouter_Arete->setCursor(QCursor(Qt::PointingHandCursor));
        Ajouter_Arete->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:white;\n"
"/*border-style:solid;\n"
"border-width:0.5px;\n"
"border-color:black;*/\n"
"border-radius:20px;\n"
"width:155px;\n"
"margin-left:0px;\n"
"\n"
"}\n"
"QPushButton:hover{\n"
"background-color:#3EE793;\n"
"color:black;\n"
"};"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/Groupe 167.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Ajouter_Arete->setIcon(icon5);
        Ajouter_Arete->setIconSize(QSize(32, 32));

        verticalLayout->addWidget(Ajouter_Arete);

        Supprimer_Arete = new QPushButton(groupBox_2);
        Supprimer_Arete->setObjectName(QString::fromUtf8("Supprimer_Arete"));
        sizePolicy2.setHeightForWidth(Supprimer_Arete->sizePolicy().hasHeightForWidth());
        Supprimer_Arete->setSizePolicy(sizePolicy2);
        Supprimer_Arete->setFont(font1);
        Supprimer_Arete->setCursor(QCursor(Qt::PointingHandCursor));
        Supprimer_Arete->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:white;\n"
"/*border-radius:20px;\n"
"border-style:solid;\n"
"border-width:0.5px;\n"
"border-color:black;*/\n"
"background-color:#E73E48;\n"
"color:white;\n"
"width:155px;\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(231,62,72,0.7);\n"
"color:black;\n"
"};"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/Groupe 162 (1).svg"), QSize(), QIcon::Normal, QIcon::Off);
        Supprimer_Arete->setIcon(icon6);
        Supprimer_Arete->setIconSize(QSize(32, 32));

        verticalLayout->addWidget(Supprimer_Arete);

        Supprimer_Noeud = new QPushButton(groupBox_2);
        Supprimer_Noeud->setObjectName(QString::fromUtf8("Supprimer_Noeud"));
        sizePolicy2.setHeightForWidth(Supprimer_Noeud->sizePolicy().hasHeightForWidth());
        Supprimer_Noeud->setSizePolicy(sizePolicy2);
        Supprimer_Noeud->setFont(font1);
        Supprimer_Noeud->setCursor(QCursor(Qt::PointingHandCursor));
        Supprimer_Noeud->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:white;\n"
"/*border-radius:20px;\n"
"border-style:solid;\n"
"border-width:0.5px;\n"
"border-color:black;*/\n"
"background-color:#E73E48;\n"
"color:white;\n"
"width:155px;\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(231,62,72,0.7);\n"
"color:black;\n"
"};"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/Groupe 134.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Supprimer_Noeud->setIcon(icon7);
        Supprimer_Noeud->setIconSize(QSize(34, 34));

        verticalLayout->addWidget(Supprimer_Noeud);


        verticalLayout_5->addWidget(groupBox_2);


        verticalLayout_6->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Palatino Linotype"));
        font2.setPointSize(14);
        lineEdit->setFont(font2);
        lineEdit->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit->setLayoutDirection(Qt::LeftToRight);
        lineEdit->setStyleSheet(QString::fromUtf8("border:none;\n"
"margin-bottom:7px;\n"
"background-color:transparent; \n"
"color: #fff;"));
        lineEdit->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        lineEdit->setReadOnly(true);

        verticalLayout_3->addWidget(lineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(5);
        sizePolicy4.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy4);
        groupBox_3->setStyleSheet(QString::fromUtf8("border:none;"));

        horizontalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy5(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(4);
        sizePolicy5.setVerticalStretch(5);
        sizePolicy5.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy5);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(85, 85, 85, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(0, 0, 0, 128));
        brush2.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush4(QColor(0, 0, 0, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        groupBox->setPalette(palette);
        groupBox->setContextMenuPolicy(Qt::NoContextMenu);
        groupBox->setStyleSheet(QString::fromUtf8("font: 12pt \"Mongolian Baiti\";\n"
"border:none;\n"
"Margin:0px 0px;\n"
""));
        groupBox->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        Floyd_Warshall = new QPushButton(groupBox);
        Floyd_Warshall->setObjectName(QString::fromUtf8("Floyd_Warshall"));
        sizePolicy2.setHeightForWidth(Floyd_Warshall->sizePolicy().hasHeightForWidth());
        Floyd_Warshall->setSizePolicy(sizePolicy2);
        Floyd_Warshall->setCursor(QCursor(Qt::PointingHandCursor));
        Floyd_Warshall->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:white;\n"
"color:black;\n"
"/*border-style:solid;\n"
"border-width:1px;\n"
"border-color:color;\n"
"border-top:none;*/\n"
"border-radius:20px;\n"
"border-bottom-left-radius:0px;\n"
"border-bottom-right-radius:0px;\n"
"/*margin-bottom:2px;*/\n"
"}\n"
"QPushButton:hover{\n"
"background-color:#566df9;\n"
"color : #ddd\n"
"};"));

        verticalLayout_2->addWidget(Floyd_Warshall);

        DIJKSTRA = new QPushButton(groupBox);
        DIJKSTRA->setObjectName(QString::fromUtf8("DIJKSTRA"));
        sizePolicy2.setHeightForWidth(DIJKSTRA->sizePolicy().hasHeightForWidth());
        DIJKSTRA->setSizePolicy(sizePolicy2);
        DIJKSTRA->setCursor(QCursor(Qt::PointingHandCursor));
        DIJKSTRA->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:white;\n"
"color:black;\n"
"/*border-style:solid;\n"
"border-width:1px;\n"
"border-color:color;\n"
"border-top:none;*/\n"
"border-radius:0px;\n"
"/*margin-bottom:2px;*/\n"
"}\n"
"QPushButton:hover{\n"
"background-color:#566df9;\n"
"color : #ddd\n"
"};"));

        verticalLayout_2->addWidget(DIJKSTRA);

        Bellman = new QPushButton(groupBox);
        Bellman->setObjectName(QString::fromUtf8("Bellman"));
        sizePolicy2.setHeightForWidth(Bellman->sizePolicy().hasHeightForWidth());
        Bellman->setSizePolicy(sizePolicy2);
        Bellman->setCursor(QCursor(Qt::PointingHandCursor));
        Bellman->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:white;\n"
"color:black;\n"
"/*border-style:solid;\n"
"border-width:1px;\n"
"border-color:color;\n"
"border-top:none;*/\n"
"border-radius:20px;\n"
"\n"
"border-radius:0px;\n"
"/*margin-bottom:2px;*/\n"
"}\n"
"QPushButton:hover{\n"
"background-color:#566df9;\n"
"color : #ddd\n"
"};"));

        verticalLayout_2->addWidget(Bellman);

        Johnson = new QPushButton(groupBox);
        Johnson->setObjectName(QString::fromUtf8("Johnson"));
        sizePolicy2.setHeightForWidth(Johnson->sizePolicy().hasHeightForWidth());
        Johnson->setSizePolicy(sizePolicy2);
        Johnson->setCursor(QCursor(Qt::PointingHandCursor));
        Johnson->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:white;\n"
"color:black;\n"
"/*border-style:solid;\n"
"border-width:1px;\n"
"border-color:color;\n"
"border-top:none;*/\n"
"border-radius:20px;\n"
"border-top-left-radius:0px;\n"
"border-top-right-radius:0px;\n"
"/*margin-bottom:2px;*/\n"
"}\n"
"QPushButton:hover{\n"
"background-color:#566df9;\n"
"color : #ddd\n"
"};"));

        verticalLayout_2->addWidget(Johnson);


        horizontalLayout->addWidget(groupBox);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_6->addLayout(verticalLayout_4);


        horizontalLayout_2->addLayout(verticalLayout_6);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(1);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy6);
        tabWidget->setStyleSheet(QString::fromUtf8("background-image:url(:/icons/icons/12.jpeg);\n"
"background-repeat:none;\n"
"background-color:#000918;\n"
"border-style:solid;\n"
"border-width:1px;\n"
"border-color:black;"));
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);

        horizontalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1105, 25));
        QFont font3;
        font3.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setWeight(50);
        menubar->setFont(font3);
        menubar->setCursor(QCursor(Qt::PointingHandCursor));
        menubar->setAutoFillBackground(false);
        menubar->setStyleSheet(QString::fromUtf8("background-color:white;"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setCursor(QCursor(Qt::PointingHandCursor));
        menuFile->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionLoad);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "   New", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "   Save", nullptr));
        actionLoad->setText(QCoreApplication::translate("MainWindow", "   Load", nullptr));
        groupBox_2->setTitle(QString());
        Generer_Graphe->setText(QCoreApplication::translate("MainWindow", "Generer un graphe", nullptr));
        Ajouter_Noeud->setText(QCoreApplication::translate("MainWindow", "Ajouter un noeud", nullptr));
        Ajouter_Arete->setText(QCoreApplication::translate("MainWindow", "Ajouter Ar\303\252te/Arc     ", nullptr));
        Supprimer_Arete->setText(QCoreApplication::translate("MainWindow", "Supprimer Ar\303\252te/Arc", nullptr));
        Supprimer_Noeud->setText(QCoreApplication::translate("MainWindow", "Supprimer  Noeud", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "Algorithme :", nullptr));
        groupBox_3->setTitle(QString());
        groupBox->setTitle(QString());
        Floyd_Warshall->setText(QCoreApplication::translate("MainWindow", "Floyd-Warshall", nullptr));
        DIJKSTRA->setText(QCoreApplication::translate("MainWindow", "Dijkstra", nullptr));
        Bellman->setText(QCoreApplication::translate("MainWindow", "Bellman-Ford", nullptr));
        Johnson->setText(QCoreApplication::translate("MainWindow", "Johnson", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
