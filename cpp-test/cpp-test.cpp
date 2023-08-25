#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

void wait(int milisseconds) {
    this_thread::sleep_for(chrono::milliseconds(milisseconds));
}

void pos_resposta(string var) {
    cout << "Sua resposta foi: " << var << endl;
    wait(1000);
}

void assistente(string solicitante, string envolvido, int s_principal, int s_intrinseca, int max_si, int etapa, string momento_incidente, string reincidencia) {

    ofstream output_file("texto_discord.txt");

    if (!output_file) {
        cout << "Nao foi possivel localizar o arquivo de saida." << endl;
        exit(0);
    }

    string reincidencia_txt;
    vector<int> sit_intrinseca_segundos = { 0,0,5,10,10,15,20,25,30,50 };
    vector<int> sit_intrinseca_tempo = { 0,0,5,10,10,15,20,25,30,50 };
    vector<string> outras_punicoes = { "Drive Through","Qualy Ban","Stop and Go" };

    int punicao_segundos;
    int punicao_tempo;

    for (int i = 0; i <= max_si; i++) {
        if(s_intrinseca == i){
            punicao_segundos = sit_intrinseca_segundos[i];
            punicao_tempo = sit_intrinseca_tempo[i];
        }
        else if(s_intrinseca == i && reincidencia == "S") {
            punicao_segundos = sit_intrinseca_segundos[i] * 2;
            punicao_tempo = sit_intrinseca_tempo[i] * 2;
        }
    }

    if (reincidencia == "S") {
        reincidencia_txt = "Sim";
    }
    else {
        reincidencia_txt = "Nao";
    }

    output_file << "Incidente entre " << solicitante << " e " << envolvido << "\nResumo: Piloto X bate no y o fazendo rodar" << "\nMomento do incidente: " << etapa << "º Etapa - Minuto: " << momento_incidente <<
        "\nResultado: Punicao para " << envolvido << ": Foi reincidencia? " << reincidencia_txt << ". " <<"Situacao Principal: ("
        << s_principal << ") - Situacao Intrinseca " << "(" << s_intrinseca << ") " << " (+" << punicao_segundos <<
        ") segundos adicionados ao fim da prova (-" << punicao_tempo << ") pontos na tabela de pontuacao";
   
    /*output_file.flush();*/
    output_file.close();
}

int main(){

    string solicitante;
    string envolvido;
    string momento_incidente;
    string reincidencia = "N";
    int etapa;
    

    string quest_assistente = "N";
    int max_sp = 5;
    int max_si = 10;
    int s_principal;
    int s_intrinseca;

    cout << "*****************************\n";
    cout << "***Gerenciador de analises***\n";
    cout << "*****************************\n\n";

    cout << "Qual o nome do solicitante?\n\nPreencha Nome.Sobrenome\n";
    cin >> solicitante;
    pos_resposta(solicitante);
    
    cout << "\nQual o nome do acusado(s)? Preencha Nome.Sobrenome\n";
    cin >> envolvido;
    pos_resposta(envolvido);

    cout << "\nQual foi a etapa do ocorrido? (Responda com 1,2,3...)\n";
    cin >> etapa;
    pos_resposta(to_string(etapa));

    cout << "\nQual foi o momento do incidente? ('Minuto' & 'Segundos')\n";
    cin >> momento_incidente;
    pos_resposta(momento_incidente);

    cout << "\nEsta analise se configura como uma reincidencia?\n";
    cin >> reincidencia;
    pos_resposta(reincidencia);

    cout << "\nDeseja iniciar o assistente de analise? (S/N)\n";
    cin >> quest_assistente;
    pos_resposta(quest_assistente);

    if (quest_assistente == "S") {
        assistente(solicitante, envolvido,0,0,max_si,etapa,momento_incidente,reincidencia);
    }
    else {
        cout << "Digite a situacao principal: (1 a " << max_sp << ")\n";
        cin >> s_principal;
        pos_resposta(to_string(s_principal));

        cout << "Digite a situacao intrinseca: (1 a " << max_si << ")\n";
        cin >> s_intrinseca;
        pos_resposta(to_string(s_intrinseca));

        assistente(solicitante, envolvido, s_principal, s_intrinseca, max_si, etapa, momento_incidente, reincidencia);
    }
    
}