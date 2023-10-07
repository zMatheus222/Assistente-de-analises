#ifndef DISPLAY_LOGIC_H
#define DISPLAY_LOGIC_H

#include <QString>
#include <vector>
#include <regex>

using namespace std;

class ItemType{

public:

    QString item_type;
    QString belong_machine;
    QString host_name;
    QString container_name;
    QString ip;
    QString port;
    QString local_abr;
    QString local_full;
    QString description;

    //vector que salva as informações de um item especifico
    vector<QString> item_list;

    //vector que salva todos os itens da wiki
    vector<vector<vector<QString>>> full_item_list;

    //as regex comparativas da wiki
    regex rgx_unit;
    regex rgx_vmware;
    regex rgx_servidor;
    regex rgx_machine;

    //smatch que armazena as capturas de regex entre ()
    smatch smatch_received_item;

    //smatch exclusiva para coletar numero da maquina
    smatch smatch_machine;

    //inicializador das variaveis regex.
    void rgx();
    void wait(int time);

    //função de consulta na wiki
    void extracted(vector<QString> &actual_vector);
    vector<vector<vector<QString>>> consult_on_wiki();

private:

};


#endif // DISPLAY_LOGIC_H
