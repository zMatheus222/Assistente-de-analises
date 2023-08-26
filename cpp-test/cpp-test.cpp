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

void pos_resposta(string var, string etapa) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    wait(1000);
    if(etapa == ""){
        cout << "Sua resposta foi: " << var << endl;
    }
    else{
        cout << "Sua resposta foi: " << etapa << endl;
    }
    
}

void assistente(string solicitante, string envolvido, int s_principal, int s_intrinseca, int max_si, int etapa, string momento_incidente, int reincidencia) {

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
        else if(s_intrinseca == i && reincidencia == 1) {
            punicao_segundos = sit_intrinseca_segundos[i] * 2;
            punicao_tempo = sit_intrinseca_tempo[i] * 2;
        }
    }

    if (reincidencia == 1) {
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
    int reincidencia = 0;
    int etapa;
    

    string quest_assistente = "N";
    int max_sp = 5;
    int max_si = 10;
    int s_principal;
    int s_intrinseca;
    
    vector<string> etapas = {"","Hungaroring","Circuit of the Americas","Misano","Laguna Seca","Paul Ricard"};
    
    vector<string> situacoes_principais = {
        "",
        "Toque na traseira que provoque a perda da tração no oponente.",
        "Não deixar espaço mínimo de um carro (linha branca ou zebra como referência)",
        "Referente a batidas laterais (porta com porta)",
        "Permanecer em pista com o carro danificado",
        "Retornar a pista de forma perigosa",
        "Nenhuma das opcoes listadas"
    };
    
    vector<string> situacoes_intrinsecas = {
        "",
        "Não causou nenhum prejuizo como danos consideráveis ao veiculo do oponente: Sem punição.",
        "Causou perda considerável de tempo: (0.7s ou mais): +5 segundos",
        "Oponente rodou sem sofrer danos consideráveis ou perder posições: +10 segundos",
        "Causou perda de posições mas o oponente não rodou ou sofreu danos consideráveis: +10 segundos & -10 Pontos",
        "Oponente rodou sem sofrer danos consideráveis porém houve perda de posições: +15 segundos & -15 Pontos",
        "Oponente rodou e sofreu danos consideráveis no veículo): +20 segundos, -20 Pontos",
        "Oponente rodou e sofreu danos graves no veiculo: +25 segundos, -25 Pontos & DT na próxima etapa. caso o incidente tenha ocorrido na ultima etapa, o 'DT na próxima etapa' se tornará '-50 Pontos'",
        "Causou strike Inevitável (o piloto não teve o que fazer): +30 segundos, -30 Pontos & DT na próxima etapa, caso o incidente tenha ocorrido na ultima etapa, o 'DT na próxima etapa' se tornará '-50 Pontos'",
        "Causou strike evitavel (o piloto poderia ter evitado): DSQ da etapa, -50 Pontos & banimento da próxima etapa oficial que correr (inclui futuras temporadas)",
        "Qualquer item acima causado por BUG's será melhor avaliado pela direção, se o bug foi causado por problemas de conexão do piloto, ele não será absolvido de punição."
        "Nenhuma das situacoes listadas"
    };
        

    cout << "*****************************\n";
    cout << "***Gerenciador de analises***\n";
    cout << "*****************************\n\n";

    cout << "Qual o nome do solicitante?\n\nPreencha Nome.Sobrenome\n";
    cin >> solicitante;
    pos_resposta(solicitante,"");
    
    cout << "\nQual o nome do acusado(s)? Preencha Nome.Sobrenome\n";
    cin >> envolvido;
    pos_resposta(envolvido,"");

    cout << "\nQual foi a etapa do ocorrido? (Responda com 1,2,3...)\n";
    for(int i = 1; i < etapas.size(); i++){
        cout << "[" << i << "] " << etapas[i] << endl;
    }
    cin >> etapa;
    pos_resposta(to_string(etapa),etapas[etapa]);

    cout << "\nQual foi o momento do incidente? ('Minuto':'Segundos')\n";
    cin >> momento_incidente;
    pos_resposta(momento_incidente,"");

    cout << "\nEsta analise se configura como uma reincidencia?\n[1] Sim\n[2] Nao\n";
    cin >> reincidencia;
    pos_resposta(to_string(reincidencia),"");

    cout << "\nDeseja iniciar o assistente de analise? (S/N)\n";
    cin >> quest_assistente;
    pos_resposta(quest_assistente,"");

    if (quest_assistente == "S") {
        cout << "Escolha uma das situacoes principais abaixo:\n" << endl;
        for(int i = 1; i < situacoes_principais.size(); i++){
            cout << "[" << i << "] " << situacoes_principais[i] << endl;
        }
        cin >> s_principal;
        
        cout << "Agora escolha uma situacao intrinseca abaixo:\n" << endl;
        for(int i = 1; i < situacoes_intrinsecas.size(); i++){
            cout << "[" << i << "] " << situacoes_intrinsecas[i] << endl;
        }
        cin >> s_intrinseca;
        
        assistente(solicitante, envolvido,0,0,max_si,etapa,momento_incidente,reincidencia);
    }
    else {
        cout << "Digite a situacao principal: (1 a " << max_sp << ")\n";
        cin >> s_principal;
        pos_resposta(to_string(s_principal),"");

        cout << "Digite a situacao intrinseca: (1 a " << max_si << ")\n";
        cin >> s_intrinseca;
        pos_resposta(to_string(s_intrinseca),"");

        assistente(solicitante, envolvido, s_principal, s_intrinseca, max_si, etapa, momento_incidente, reincidencia);
    }
    
}
