#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "display_logic.h"
#include <regex>
#include <QTableWidgetItem>

//objeto global neste arquivo
ItemType *itemType = new ItemType;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //codigo que irá listar e identificar todos os itens com base na wiki, e colocar todos os valores
    //em um vector tridimencional que está declarado em ItemType::full_item_list
    itemType->consult_on_wiki();
    this->create_table(itemType->full_item_list);

    //

}

void MainWindow::create_table(vector<vector<vector<QString>>> triple_vector){

    int unit_column_size;
    int unit_line_size;

    int vmware_column_size;
    int vmware_line_size;

    int server_column_size;
    int server_line_size;

    //COLUMNS SÃO LINHAS VERTICAIS
    //ROWS SÃO LINHAS HORIZONTAIS

    //
    int tripleVector_pos = 0;
    for(const vector<vector<QString>>& actual_double_vector : triple_vector){

        int doubleVector_pos = 0;
        for(const vector<QString>& actual_vector : actual_double_vector){

            int string_pos = 0;
            for(const QString& actual_string : actual_vector){

                //condição se estivermos dentro das unidades [0] - (string_pos == 0) para ser executado apenas 1 vez.
                if((tripleVector_pos == 0)&&(string_pos == 0)){

                    //pega o tamanho do vector de um item e salva na variavel que sera usada para definir a quantidade de colunas verticais
                    unit_column_size = actual_vector.size();

                    //pega a quantidade de linhas horizontais do vector de vectors. (item inteiro)
                    unit_line_size = actual_double_vector.size();

                    //com base nas variaveis acima, definir tamanho das colunas e linhas para cada tipo
                    ui->Unit_Table_Show->setColumnCount(unit_column_size);
                    ui->Unit_Table_Show->setRowCount(unit_line_size);

                }

                //adicionar itens na QTableWidget
                if(tripleVector_pos == 0){
                    //adicionar item a item nas linhas das colunas
                    QTableWidgetItem *actual_obj = new QTableWidgetItem(actual_string);

                    //qDebug() << "doubleVector_pos:" << doubleVector_pos << "string_pos:" << string_pos << "actual_string:" << actual_string;
                    ui->Unit_Table_Show->setItem(doubleVector_pos, string_pos, actual_obj);
                }

                //condição se estivermos dentro das vmwares [0] - (string_pos == 0) para ser executado apenas 1 vez.
                if((tripleVector_pos == 1)&&(string_pos == 0)){

                    //pega o tamanho do vector de um item e salva na variavel que sera usada para definir a quantidade de colunas horizontais
                    vmware_column_size = actual_vector.size();

                    //pega a quantidade de linhas do vector de vectors. (item inteiro)
                    vmware_line_size = actual_double_vector.size();

                    //com base nas variaveis acima, definir tamanho das colunas e linhas para cada tipo
                    ui->VMware_Table_Show->setColumnCount(vmware_column_size);
                    ui->VMware_Table_Show->setRowCount(vmware_line_size);
                }

                //adicionar itens na QTableWidget
                if(tripleVector_pos == 1){
                    //adicionar item a item nas linhas das colunas
                    QTableWidgetItem *actual_obj = new QTableWidgetItem(actual_string);

                    //qDebug() << "doubleVector_pos:" << doubleVector_pos << "string_pos:" << string_pos << "actual_string:" << actual_string;
                    ui->VMware_Table_Show->setItem(doubleVector_pos, string_pos, actual_obj);
                }

                //condição se estivermos dentro dos servidores [0] - (string_pos == 0) para ser executado apenas 1 vez.
                if((tripleVector_pos == 2)&&(string_pos == 0)){


                    //pega o tamanho do vector de um item e salva na variavel que sera usada para definir a quantidade de colunas horizontais
                    server_column_size = actual_vector.size();

                    //pega a quantidade de linhas do vector de vectors. (item inteiro)
                    server_line_size = actual_double_vector.size();

                    //com base nas variaveis acima, definir tamanho das colunas e linhas para cada tipo
                    ui->Server_Table_Show->setColumnCount(server_column_size);
                    ui->Server_Table_Show->setRowCount(server_line_size);

                }

                //adicionar itens na QTableWidget
                if(tripleVector_pos == 2){
                    //adicionar item a item nas linhas das colunas
                    QTableWidgetItem *actual_obj = new QTableWidgetItem(actual_string);

                    //qDebug() << "doubleVector_pos:" << doubleVector_pos << "string_pos:" << string_pos << "actual_string:" << actual_string;
                    ui->Server_Table_Show->setItem(doubleVector_pos, string_pos, actual_obj);
                }

                string_pos++;
            }

            doubleVector_pos++;
        }

        tripleVector_pos++;
    }

    //design e aparencia -----------------------------------------

    int machine_size = 60;
    int port_size = 50;
    int hostname_row_size = 100;
    int containername_row_size = 140;
    int ip_row_size = 80;
    int abrev_size = 80;
    int full_loc_size = 200;

    //unidade

    QStringList unitheaderLabels;
    unitheaderLabels << "Hostname" << "IP" << "Localização";
    ui->Unit_Table_Show->setHorizontalHeaderLabels(unitheaderLabels);

    //mudar altura de uma row desejada
    ui->Unit_Table_Show->setRowHeight(0, 25);

    //mudar largura de uma row
    ui->Unit_Table_Show->setColumnWidth(0, hostname_row_size);
    ui->Unit_Table_Show->setColumnWidth(1, ip_row_size);
    ui->Unit_Table_Show->setColumnWidth(2, full_loc_size);

    //

    //vmwares

    QStringList vmwaresheaderLabels;
    vmwaresheaderLabels << "Maquina" << "Porta" << "Hostname" << "Container Name" << "Localização" << "IP";
    ui->VMware_Table_Show->setHorizontalHeaderLabels(vmwaresheaderLabels);

    //mudar altura de uma row desejada
    ui->VMware_Table_Show->setRowHeight(0, 25);

    ui->VMware_Table_Show->setColumnWidth(0, machine_size);
    ui->VMware_Table_Show->setColumnWidth(1, port_size);
    ui->VMware_Table_Show->setColumnWidth(2, hostname_row_size);
    ui->VMware_Table_Show->setColumnWidth(3, containername_row_size);
    ui->VMware_Table_Show->setColumnWidth(4, abrev_size);

    // ------------------------------------

    //setar tabelas visiveis no inicio
    ui->Unit_Table_Show->setVisible(true);
    ui->VMware_Table_Show->setVisible(true);
    ui->Server_Table_Show->setVisible(true);
    ui->Full_Table_Show->setVisible(true);

}

void MainWindow::filter_itens(QString received_item){

    //para comparação regex nao e possivel usar QString, então temos essa alternativa.
    string conv_received_item = received_item.toStdString();

    int un_rowSize = ui->Unit_Table_Show->rowCount();
    int un_columnSize = ui->Unit_Table_Show->columnCount();

    qDebug() << "pre::for int units" << "\n";

    for(int row = 0; row < un_rowSize; row++){

        bool hideRow = true;

        for(int column = 0; column < un_columnSize; column++){

            QTableWidgetItem *item = ui->Unit_Table_Show->item(row, column);

            qDebug() << "row:" << row << "| column:" << column << "item->text():" << item->text();

            if (item) {
                QString cellText = item->text();
                bool match = cellText.contains(received_item, Qt::CaseInsensitive);

                // Se qualquer célula na linha corresponder, não oculte a linha
                if (match) {
                    hideRow = false;
                    break; // Não é necessário verificar outras células na mesma linha
                }
            }

        }

        // Oculte a linha somente se nenhuma célula na linha corresponder
        ui->Unit_Table_Show->setRowHidden(row, hideRow);

    }


    int vmw_rowSize = ui->VMware_Table_Show->rowCount();
    int vmw_columnSize = ui->VMware_Table_Show->columnCount();

    qDebug() << "pre::for int vmwares" << "\n";

    for(int row = 0; row < vmw_rowSize; row++){

        bool hideRow = true;

        for(int column = 0; column < vmw_columnSize; column++){

            QTableWidgetItem *item = ui->VMware_Table_Show->item(row, column);

            qDebug() << "row:" << row << "| column:" << column << "item->text():" << item->text();

            if (item) {
                QString cellText = item->text();
                bool match = cellText.contains(received_item, Qt::CaseInsensitive);

                // Se qualquer célula na linha corresponder, não oculte a linha
                if (match) {
                    hideRow = false;
                    break; // Não é necessário verificar outras células na mesma linha
                }
            }

        }

        // Oculte a linha somente se nenhuma célula na linha corresponder
        ui->VMware_Table_Show->setRowHidden(row, hideRow);

    }

    int ser_rowSize = ui->Server_Table_Show->rowCount();
    int ser_columnSize = ui->Server_Table_Show->columnCount();

    qDebug() << "pre::for int vmwares" << "\n";

    for(int row = 0; row < ser_rowSize; row++){

        bool hideRow = true;

        for(int column = 0; column < ser_columnSize; column++){

            QTableWidgetItem *item = ui->Server_Table_Show->item(row, column);

            qDebug() << "row:" << row << "| column:" << column << "item->text():" << item->text();

            if (item) {
                QString cellText = item->text();
                bool match = cellText.contains(received_item, Qt::CaseInsensitive);

                // Se qualquer célula na linha corresponder, não oculte a linha
                if (match) {
                    hideRow = false;
                    break; // Não é necessário verificar outras células na mesma linha
                }
            }

        }

        // Oculte a linha somente se nenhuma célula na linha corresponder
        ui->Server_Table_Show->setRowHidden(row, hideRow);

    }

}

void MainWindow::on_BtnPreviousTab_clicked(){

    if(ui->Full_Table_Show->isVisible()){
        qDebug() << "full_table_show visible";
        ui->Full_Table_Show->setVisible(false);
        ui->Unit_Table_Show->setVisible(false);
        ui->VMware_Table_Show->setVisible(false);
        ui->Server_Table_Show->setVisible(true);
    }
    else if(ui->Unit_Table_Show->isVisible()){
        qDebug() << "unit_table_show visible";
        ui->Full_Table_Show->setVisible(true);
        ui->Unit_Table_Show->setVisible(false);
        ui->VMware_Table_Show->setVisible(false);
        ui->Server_Table_Show->setVisible(false);
    }
    else if(ui->VMware_Table_Show->isVisible()){
        qDebug() << "vmware_table_show visible";
        ui->Full_Table_Show->setVisible(false);
        ui->Unit_Table_Show->setVisible(true);
        ui->VMware_Table_Show->setVisible(false);
        ui->Server_Table_Show->setVisible(false);
    }

    else if(ui->Server_Table_Show->isVisible()){
        qDebug() << "server_table_show visible";
        ui->Full_Table_Show->setVisible(false);
        ui->Unit_Table_Show->setVisible(false);
        ui->VMware_Table_Show->setVisible(true);
        ui->Server_Table_Show->setVisible(false);
    }

}

void MainWindow::on_BtnNextTab_clicked(){

    if(ui->Full_Table_Show->isVisible()){
        qDebug() << "full_table_show visible";
        ui->Full_Table_Show->setVisible(false);
        ui->Unit_Table_Show->setVisible(true);
        ui->VMware_Table_Show->setVisible(false);
        ui->Server_Table_Show->setVisible(false);
    }
    else if(ui->Unit_Table_Show->isVisible()){
        qDebug() << "unit_table_show visible";
        ui->Full_Table_Show->setVisible(false);
        ui->Unit_Table_Show->setVisible(false);
        ui->VMware_Table_Show->setVisible(true);
        ui->Server_Table_Show->setVisible(false);
    }
    else if(ui->VMware_Table_Show->isVisible()){
        qDebug() << "vmware_table_show visible";
        ui->Full_Table_Show->setVisible(false);
        ui->Unit_Table_Show->setVisible(false);
        ui->VMware_Table_Show->setVisible(false);
        ui->Server_Table_Show->setVisible(true);
    }

    else if(ui->Server_Table_Show->isVisible()){
        qDebug() << "server_table_show visible";
        ui->Full_Table_Show->setVisible(true);
        ui->Unit_Table_Show->setVisible(false);
        ui->VMware_Table_Show->setVisible(false);
        ui->Server_Table_Show->setVisible(false);
    }

}

void MainWindow::on_BtnSearch_clicked(){

    //pegar o texto digitado no campo e tirar espaços extras
    search_text = ui->ItemSearch->toPlainText().trimmed();

    this->filter_itens(search_text);


}

void MainWindow::on_BtnAction_clicked(){

    qDebug() << "O item que está clicado no momento é:" << this->clicked_item;



}

MainWindow::~MainWindow(){

    delete ui;
}

void MainWindow::on_VMware_Table_Show_cellClicked(int row, int column){

    QTableWidgetItem *selectedItem = ui->VMware_Table_Show->item(row, column);

    if(selectedItem != nullptr){
        this->clicked_item = selectedItem->text();
        qDebug() << "clicked_item:" << clicked_item;
    }

}


void MainWindow::on_Unit_Table_Show_cellClicked(int row, int column){

    QTableWidgetItem *selectedItem = ui->Unit_Table_Show->item(row, column);

    if(selectedItem != nullptr){
        this->clicked_item = selectedItem->text();
        qDebug() << "clicked_item:" << clicked_item;
    }

}

void MainWindow::on_Server_Table_Show_cellClicked(int row, int column){

    QTableWidgetItem *selectedItem = ui->Server_Table_Show->item(row, column);

    if(selectedItem != nullptr){
        this->clicked_item = selectedItem->text();
        qDebug() << "clicked_item:" << clicked_item;
    }

}

