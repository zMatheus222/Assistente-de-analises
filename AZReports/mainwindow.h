#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

    //função que irá criar a tabela para exibição na tela.
    void create_table(vector<vector<vector<QString>>> triple_vector);

    //variavel que armazena o item digitado para pesquisa
    QString search_text;

    //função que irá filtrar os itens da tabela
    void filter_itens(QString received_item);

    QString clicked_item;

public slots:

    void on_BtnPreviousTab_clicked();
    void on_BtnNextTab_clicked();
    void on_BtnSearch_clicked();
    void on_BtnAction_clicked();

    //função para pegar a coluna clicada na tabela
    void on_VMware_Table_Show_cellClicked(int row, int column);

private slots:

    void on_Unit_Table_Show_cellClicked(int row, int column);

    void on_Server_Table_Show_cellClicked(int row, int column);

private:

};
#endif // MAINWINDOW_H
