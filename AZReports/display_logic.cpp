#include "display_logic.h"
#include <vector>
#include <fstream>
#include <QString>
#include <QTableView>
#include <regex>
#include <thread>
#include <chrono>

using namespace std;

void log_vectors(vector<vector<vector<QString>>> triple_vector){

    qDebug() << "triple_vector show";
    int counta = 0;
    for(vector<vector<QString>>& actual_vector_of_vectors : triple_vector){
        int countb = 0;
        for(vector<QString> actual_vector : actual_vector_of_vectors){
            int countc = 0;
            for(QString& line : actual_vector){


                qDebug() << counta << " | " << countb << " | " << countc << " > line:" << line;

                countc++;
            }
            countb++;
        }
        counta++;
    }
}

void ItemType::wait(int time){
    qDebug() << "pause...";
    this_thread::sleep_for(chrono::seconds(time));
}

//função para inicializar atribuindo valores as variaives de regex que podem ser usadas em outros casos.
void ItemType::rgx(){

    qDebug() << "inicializando lista de regex...";

    rgx_unit = regex("([A-Za-z]+[0-9]+[A-Za-z]+)(?:\\t+)?\\s?([0-9]+.[0-9]+.[0-9]+.[0-9]+)(?:\\t+)?\\s?([A-Za-zÃ-Õ-Á-Ú-. ]+)");
    rgx_vmware = regex("([0-9]+)\t+([A-Za-z]+[0-9]+[A-Za-z]+)\t([A-Za-z_0-9]+)\t([A-Za-z]+)\t([0-9]+.[0-9]+.[0-9]+.[0-9]+)");
    rgx_servidor = regex("([0-9]+.[0-9]+.[0-9]+.[0-9]+)\t([A-Za-z]+[0-9]+[A-Za-z]+)\t([A-Za-z-á-ú-Á-Ú ,\\/\(\\)]+)(?:\t([a-zA-Z0-9 \\/]+))?");
    rgx_machine = regex(".*quina\\s([7]\\d+)");

}

vector<string> txt_vetorize(string file_path){

    vector<string> vetorized_list;

    //converter para string normal e passar ao ifstream (que não aceita QString)
    ifstream txt_file(file_path);

    if(txt_file.is_open()){
        qDebug() << "Arquivo " << file_path << " foi aberto com sucesso!";
        string actual_line;
        while(getline(txt_file, actual_line)){
            vetorized_list.push_back(actual_line);
        }
    }
    else{
        qDebug() << "Arquivo: " << file_path << " não foi aberto.";
    }

    txt_file.close();

    return vetorized_list;
}

vector<vector<vector<QString>>> ItemType::consult_on_wiki(){

    qDebug() << "entered::consult_on_wiki";

    int count;
    ItemType *itemType = new ItemType;

    vector<QString> temporary_vector;
    vector<vector<QString>> temporary_vector_of_vectors;

    //variavel que armazena numero da maquina, é estatica para sempre manter seu valor
    static string machine_number;

    //vector que irá guardar tudo do item, o vetor 0 (unidades) vetor 1 (vmwares) vetor 2 (servidores)
    //vector<vector<QString>> full_item_list;

    //funções que terão todos os itens da wiki
    vector<string> vetorized_units = txt_vetorize(CURRENT_SOURCE_DIR "/txt_files/wiki_units.txt");
    vector<string> vetorized_vmwares = txt_vetorize(CURRENT_SOURCE_DIR "/txt_files/wiki_vmwares.txt");
    vector<string> vetorized_servidores = txt_vetorize(CURRENT_SOURCE_DIR "/txt_files/wiki_serverlist.txt");

    qDebug() << "vetorized_units.size(): " << vetorized_units.size();
    qDebug() << "vetorized_vmwares.size(): " << vetorized_vmwares.size();
    qDebug() << "vetorized_servidores.size(): " << vetorized_servidores.size();

    //inicializar as regex
    itemType->rgx();

    //for que vai separar item a item da wiki para exibição
    for(const string& item : vetorized_units){

        //separação dos itens da linha com regex, exemplo de como ficara a smatch:
        /*
        [0] SRVPTH001APG	10.156.84.94	APARECIDA DE GOIANIA
        [1] SRVPTH001APG
        [2] 10.156.84.94
        [3] APARECIDA DE GOIANIA
        */

        bool unidade = regex_search(item,itemType->smatch_received_item,itemType->rgx_unit);

        //qDebug() << "rgx_search::unit: " << unidade << " item: " << item;

        if(unidade == true){

            qDebug() << "Unidade detectada, prosseguindo...";

            //contar a quantidade de matches no smatch.
            size_t numMatches = itemType->smatch_received_item.size();

            //com base na quantidade de matches, salvar itens em um vector.//tem que começar por 1.
            for(int i = 1; i < numMatches; i++){

                QString conv_smatch_received_item = QString::fromStdString(itemType->smatch_received_item[i]);
                qDebug() << " | i: " << i << " | conv_smatch_received_item: " << conv_smatch_received_item;
                temporary_vector.push_back(conv_smatch_received_item);

            }

            temporary_vector_of_vectors.push_back(temporary_vector);
            temporary_vector.clear();

        }

    }

    full_item_list.push_back(temporary_vector_of_vectors);
    temporary_vector_of_vectors.clear();

    //for que vai separar item a item da wiki para exibição
    count = 0;
    for(const string& item : vetorized_vmwares){

        //separação dos itens da linha com regex, exemplo de como ficara a smatch:
        /*
        [0] 9200	srvhvm04apg	vmware_exporter_apg01	APG	10.156.84.52
        [1] 76 //observação a maquina só será adicionada ao vetor separadamente
        [2] 9200
        [3] srvhvm04apg
        [4] vmware_exporter_apg01
        [5] APG
        [6] 10.156.84.52
        */

        //caso a linha seja equivalente a maquina, salvar no smatch, precisamos do true
        //usamos um if true para não ter risco de machine number ser substituida no processo.

        bool vmware = regex_search(item,itemType->smatch_received_item,itemType->rgx_vmware);
        bool maquina = regex_search(item,itemType->smatch_machine,itemType->rgx_machine);

        string sma = itemType->smatch_machine[1];
        //qDebug() << "sma::item: " << item << "machine matched: " << sma;

        if((vmware == true)||(maquina == true)){

            qDebug() << "VMWare detectada, prosseguindo...";

            //contar a quantidade de matches no smatch.
            size_t numMatches = itemType->smatch_received_item.size();

            //se for linha da maquina, deixar salvo o numero da maquina se a linha que ta passando aqui for equivalente a da maquina
            if(maquina == true){
                qDebug() << "maquina == true";
                machine_number = itemType->smatch_machine[1];
            }

            //se não for linha da maquina, sempre adicionar o numero da maquina atual na linha 0, MAS pular caso for o primeiro item (para não duplicar)
            if(maquina == false){
                QString conv_machine_number = QString::fromStdString(machine_number);
                qDebug() << "temporary_vector push_back: " << conv_machine_number;
                temporary_vector.push_back(conv_machine_number);
            }

            //com base na quantidade de matches, salvar itens em um vector.
            for(int i = 1; i < numMatches; i++){
                //se não for maquina, então é o item que queremos, usamos vmware == true para evitar linhas indesejadas.
                QString conv_smatch_received_item = QString::fromStdString(itemType->smatch_received_item[i]);
                qDebug() << "temporary_vector push_back: " << conv_smatch_received_item;
                temporary_vector.push_back(conv_smatch_received_item);
            }
            //Se maquina for false OU vmware for false e maquina true
            if(maquina == false){
                temporary_vector_of_vectors.push_back(temporary_vector);
                temporary_vector.clear();
            }
        }
        count++;
    }

    full_item_list.push_back(temporary_vector_of_vectors);
    temporary_vector_of_vectors.clear();

    //for que vai separar item a item da wiki para exibição]
    for(const string& item : vetorized_servidores){

        //separação dos itens da linha com regex, exemplo de como ficara a smatch:
        /*
        [0] 10.156.5.75     SRVOBS003DCR	Docker Oracle, Loki
        [1] 10.156.5.75
        [2] SRVOBS003DCR
        [3] Docker Oracle, Loki
        */

        bool servidor = regex_search(item,itemType->smatch_received_item,itemType->rgx_servidor);

        if(servidor == true){
            qDebug() << "Servidor detectado, prosseguindo...";

            //contar a quantidade de matches no smatch.
            size_t numMatches = itemType->smatch_received_item.size();

            //com base na quantidade de matches, salvar itens em um vector.
            for(int i = 1; i < numMatches; i++){
                QString conv_smatch_received_item = QString::fromStdString(itemType->smatch_received_item[i]);
                temporary_vector.push_back(conv_smatch_received_item);
            }

            temporary_vector_of_vectors.push_back(temporary_vector);
            temporary_vector.clear();
        }

    }

    log_vectors(full_item_list);

    full_item_list.push_back(temporary_vector_of_vectors);
    temporary_vector_of_vectors.clear();


    return itemType->full_item_list;
}

