/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *BtnPreviousTab;
    QPushButton *BtnNextTab;
    QTextEdit *ItemSearch;
    QPushButton *BtnSearch;
    QPushButton *BtnAction;
    QTabWidget *Itens_tabWidget;
    QWidget *tab;
    QTableWidget *Full_Table_Show;
    QWidget *tab_2;
    QTableWidget *Unit_Table_Show;
    QWidget *tab_3;
    QTableWidget *VMware_Table_Show;
    QWidget *tab_4;
    QTableWidget *Server_Table_Show;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(799, 785);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        BtnPreviousTab = new QPushButton(centralwidget);
        BtnPreviousTab->setObjectName("BtnPreviousTab");
        BtnPreviousTab->setGeometry(QRect(20, 610, 191, 41));
        BtnNextTab = new QPushButton(centralwidget);
        BtnNextTab->setObjectName("BtnNextTab");
        BtnNextTab->setGeometry(QRect(580, 610, 191, 41));
        ItemSearch = new QTextEdit(centralwidget);
        ItemSearch->setObjectName("ItemSearch");
        ItemSearch->setGeometry(QRect(485, 50, 241, 31));
        BtnSearch = new QPushButton(centralwidget);
        BtnSearch->setObjectName("BtnSearch");
        BtnSearch->setGeometry(QRect(730, 50, 41, 31));
        BtnAction = new QPushButton(centralwidget);
        BtnAction->setObjectName("BtnAction");
        BtnAction->setGeometry(QRect(300, 610, 191, 41));
        Itens_tabWidget = new QTabWidget(centralwidget);
        Itens_tabWidget->setObjectName("Itens_tabWidget");
        Itens_tabWidget->setGeometry(QRect(20, 60, 751, 401));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Itens_tabWidget->sizePolicy().hasHeightForWidth());
        Itens_tabWidget->setSizePolicy(sizePolicy);
        Itens_tabWidget->setTabPosition(QTabWidget::North);
        Itens_tabWidget->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName("tab");
        Full_Table_Show = new QTableWidget(tab);
        Full_Table_Show->setObjectName("Full_Table_Show");
        Full_Table_Show->setGeometry(QRect(10, 10, 721, 351));
        Itens_tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        Unit_Table_Show = new QTableWidget(tab_2);
        Unit_Table_Show->setObjectName("Unit_Table_Show");
        Unit_Table_Show->setGeometry(QRect(10, 10, 731, 351));
        Itens_tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        VMware_Table_Show = new QTableWidget(tab_3);
        VMware_Table_Show->setObjectName("VMware_Table_Show");
        VMware_Table_Show->setGeometry(QRect(10, 10, 721, 351));
        Itens_tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        Server_Table_Show = new QTableWidget(tab_4);
        Server_Table_Show->setObjectName("Server_Table_Show");
        Server_Table_Show->setGeometry(QRect(10, 10, 721, 351));
        Itens_tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralwidget);
        Itens_tabWidget->raise();
        BtnPreviousTab->raise();
        BtnNextTab->raise();
        ItemSearch->raise();
        BtnSearch->raise();
        BtnAction->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 799, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        Itens_tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        BtnPreviousTab->setText(QCoreApplication::translate("MainWindow", "Tabela Anterior", nullptr));
        BtnNextTab->setText(QCoreApplication::translate("MainWindow", "Pr\303\263xima Tabela", nullptr));
        BtnSearch->setText(QString());
        BtnAction->setText(QCoreApplication::translate("MainWindow", "Realizar A\303\247\303\243o", nullptr));
        Itens_tabWidget->setTabText(Itens_tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Todos os itens", nullptr));
        Itens_tabWidget->setTabText(Itens_tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Unidades", nullptr));
        Itens_tabWidget->setTabText(Itens_tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "VMWares", nullptr));
        Itens_tabWidget->setTabText(Itens_tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Servidores", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
