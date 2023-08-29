#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <regex>

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
    wait(300);
    if (etapa == "") {
        cout << "Sua resposta foi: " << var << endl;
    }
    else {
        cout << "Sua resposta foi: " << etapa << endl;
    }
}

void assistente(string solicitante, string envolvido, int s_principal, int s_intrinseca, int max_si, int etapa, string momento_incidente, int reincidencia, string nomes_etapas) {

    ofstream output_txt("texto_discord.txt", ios::app);
    ifstream input_txt("texto_discord.txt");

    input_txt.seekg(0, ios::end);
    string if_need_endl;
    if(input_txt.tellg() == 0){
        cout << "\nO arquivo ainda não possúi análises registradas." << endl;
    }
    else{
        cout << "\nO arquivo possui analises ja registradas" << endl;
        if_need_endl = "\n\n";
    }

    string reincidencia_txt;

    vector<int> sit_intrinseca_segundos = {0,0,5,5,10,10,15,20,25,30};
    vector<int> sit_intrinseca_pontos =   {0,0,0,0,0,10,15,20,25,30,50};

    vector<string> outras_punicoes = { "Drive Through","Qualy Ban","Stop and Go" };

    int punicao_segundos;
    int punicao_pontos;

    for (int i = 1; i <= max_si; i++) {
        if (s_intrinseca == i) {
            punicao_segundos = sit_intrinseca_segundos[i -1];
            punicao_pontos = sit_intrinseca_pontos[i -1];
            if(reincidencia == 1){
                punicao_segundos = sit_intrinseca_segundos[i -1] * 2;
                punicao_pontos = sit_intrinseca_pontos[i -1] * 2;
            }
        }
    }

    if (reincidencia == 1) {
        reincidencia_txt = "Sim";
    }
    else {
        reincidencia_txt = "Nao";
    }

    vector<string> resumos_principais;

    resumos_principais.push_back("Piloto " + envolvido + " toca a traseira de " + solicitante);
    resumos_principais.push_back("Piloto " + envolvido + " não deixa espaço mínimo de 1 carro a " + solicitante);
    resumos_principais.push_back("Colisao porta com porta causada pelo piloto " + envolvido);
    resumos_principais.push_back("Piloto " + envolvido + " permaneceu no circuito com carro danificado, gerando incidente.");
    resumos_principais.push_back("Piloto " + envolvido + " retorna a pista de forma perigosa causando incidente");
    resumos_principais.push_back("Piloto " + envolvido + " Passou dos limites de pista (linha branca ou zebra).");
    resumos_principais.push_back("Incidente de corrida. (Sem punição).");

    vector<string> resumos_intrinsecos = {
        " porem não ganhou vantagem",
        " não causou nenhum prejuizo como danos consideráveis ou perca de posições.",
        " e ganhou vantagem.",
        " e causou perda considerável de tempo (0.7s ou mais).",
        " o fazendo rodar, porém sem danos consideráveis ou perder posições.",
        " e causou perda de posições porém o oponente não rodou ou sofreu danos.",
        " o oponente rodou sem sofrer danos consideráveis porém houve perda de posições.",
        " o fazendo rodar e sofrer danos consideráveis.",
        " o fazendo rodar e sofrer danos graves",
        " causou strike inevitável.",
        " causou strike evitavel.",
        " incidente ocorreu devido a BUG / Erro."
    };

    int n_princip;

    switch (s_principal) {
    case 1:
        n_princip = 0;
        break;
    case 2:
        n_princip = 1;
        break;
    case 3:
        n_princip = 2;
        break;
    case 4:
        n_princip = 3;
        break;
    case 5:
        n_princip = 4;
        break;
    case 6:
        n_princip = 5;
        break;
    case 7:
        n_princip = 6;
        break;
    case 8:
        n_princip = 7;
        break;
    default:
        n_princip = -1;
        break;
    }

    int n_intrinsec;
    switch (s_intrinseca) {
    case 1:
        n_intrinsec = 0;
        break;
    case 2:
        n_intrinsec = 1;
        break;
    case 3:
        n_intrinsec = 2;
        break;
    case 4:
        n_intrinsec = 3;
        break;
    case 5:
        n_intrinsec = 4;
        break;
    case 6:
        n_intrinsec = 5;
        break;
    case 7:
        n_intrinsec = 6;
        break;
    case 8:
        n_intrinsec = 7;
        break;
    case 9:
        n_intrinsec = 8;
        break;
    case 10:
        n_intrinsec = 9;
        break;
    case 11:
        n_intrinsec = 10;
        break;
    case 12:
        n_intrinsec = 11;
        break;
    default:
        n_intrinsec = -1;
        break;
    }

    cout << "A punicao para este incidente e de +" << punicao_segundos << "segundos, -" << punicao_pontos << " pontos na tabela." << endl;

    if ((n_princip != -1) && (n_intrinsec != -1)) {

        output_txt << if_need_endl << "> Incidente entre **" << solicitante << "** e **" << envolvido << "**\n> Resumo: " << resumos_principais[n_princip] << resumos_intrinsecos[n_intrinsec] << "\n> \n> Momento do incidente: **" << etapa << "º Etapa (" << nomes_etapas << ")** - Minuto: " << momento_incidente <<
        "\n> \n> **Resultado:** Punicao para " << envolvido << ": Foi reincidencia? " << reincidencia_txt << ". " << "Situacao Principal: ("
        << s_principal << ") - Situacao Intrinseca " << "(" << s_intrinseca << ") " << " (+" << punicao_segundos <<
        ") segundos adicionados ao fim da prova (-" << punicao_pontos << ") pontos na tabela de pontuacao";

        cout << "\nSeu resumo de analises foi exportado para o arquivo .txt" << endl;
    }
    else {
        cout << "Não foi possível exportar as informações para o txt." << endl;
        cout << "\ns_principal: " << s_principal << "\ns_intrinseca: " << s_intrinseca << "\nn_princip: " << n_princip << "\nn_intrinsec: " << n_intrinsec << endl;
        output_txt.close();
        exit(0);
    }

    output_txt.close();
}

bool validar_solicit_regex(string& solicitante) {
    regex solicit_regex("^([A-Za-z]+)\\s([A-Za-z]+)(\\s[A-Za-z]+)?$");
    return regex_match(solicitante, solicit_regex);
}

bool validar_time_regex(string& time) {
    regex solicit_regex("([0-9][0-9]):([0-5][0-9])");
    return regex_match(time, solicit_regex);
}

int main() {

    string solicitante;
    string envolvido;
    string momento_incidente;
    int reincidencia = 0;
    int etapa;


    int max_sp = 5;
    int max_si = 10;
    int s_principal;
    int s_intrinseca;

    vector<string> nomes_etapas = { "Hungaroring","Circuit of the Americas","Misano","Laguna Seca","Paul Ricard", "Registrar etapa"};

    vector<string> situacoes_principais = {
        "",
        "Toque na traseira que provoque a perda da tração no oponente.",
        "Não deixar espaço mínimo de um carro (linha branca ou zebra como referência)",
        "Referente a batidas laterais (porta com porta)",
        "Permanecer em pista com o carro danificado",
        "Retornar a pista de forma perigosa",
        "Passou dos limites de pista (linha branca ou zebra, linha dos boxes)",
        "Nenhuma das opcoes listadas"
    };

    vector<string> situacoes_intrinsecas = {
        "",
        "não ganhou vantagem: Sem punição",
        "Não causou nenhum prejuizo como danos consideráveis ao veiculo do oponente: Sem punição.",
        "ganhou vantagem: +5 segundos",
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

    /*Area de perguntas / respostas e validação das respostas*/

    cout << "***********************************\n";
    cout << "***** Gerenciador de analises *****\n";
    cout << "***********************************\n\n";

    while (true) {
        cout << "Qual o nome do solicitante?\n\nPreencha Nome Sobrenome\n";
        getline(cin, solicitante);
        pos_resposta(solicitante, "");
        if (!validar_solicit_regex(solicitante)) {
            printf("\nResposta invalida, Verifique se seguiu o formato: 'Nome' 'Sobrenome' e tente novamente.\n");
        }
        else {
            break;
        }
        cout << validar_solicit_regex(solicitante) << endl;
    }

    while (true) {
        cout << "\nQual o nome do acusado(s)? Preencha 'Nome' 'Sobrenome'\n";
        getline(cin, envolvido);
        pos_resposta(envolvido, "");
        if (!validar_solicit_regex(envolvido)) {
            printf("\nResposta invalida, Verifique se seguiu o formato: 'Nome' 'Sobrenome' e tente novamente.\n");
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "\nQual foi a etapa do ocorrido? (Responda com 1,2,3...)\n";
        for (int i = 0; i < nomes_etapas.size(); i++) {
            cout << "[" << i + 1 << "] " << nomes_etapas[i] << endl;
        }

        cin >> etapa;
        etapa--;
        pos_resposta(nomes_etapas[etapa],"");

        cin.ignore(); /*Quando você lê uma variável com cin, ele deixa uma quebra de linha pendente no buffer de entrada após a leitura de um valor, para descartar a quebra de linha pendente.*/

        /*Dar opção de adicionar uma etapa a mais*/
        string nova_etapa;

        if(etapa == nomes_etapas.size() -1){
            cout << "\nDigite o nome da etapa:\n";
            getline(cin, nova_etapa);
            pos_resposta("",nova_etapa);
            nomes_etapas.push_back(nova_etapa);

            cout << "Ela se refere a qual etapa?" << endl;
            for(int i = 1; i < nomes_etapas.size(); i++){
                cout << "[" << i << "º] " << "Etapa" << endl;
            }
            cin >> etapa;
            pos_resposta("",to_string(etapa));
        }

        if ((etapa > nomes_etapas.size()) && (etapa <= 0)) {
            printf("\nResposta invalida, Verifique se sua resposta contem um dos numeros especificados na lista.\n");
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "\nQual foi o momento do incidente? ('Minuto':'Segundos')\n";
        cin >> momento_incidente;
        pos_resposta(momento_incidente, "");
        if (!validar_time_regex(momento_incidente)) {
            printf("\nResposta invalida, Verifique se ela tem o formato MM:SS exemplo: '20:30'\n");
        }
        else {
            break;
        }
    }
    
    while (true) {
        cout << "\nEsta analise se configura como uma reincidencia?\n[1] Sim\n[2] Nao\n";
        cin >> reincidencia;
        pos_resposta(to_string(reincidencia), "");
        if ((reincidencia != 1) && (reincidencia != 2)) {
            printf("\nResposta invalida, Verifique se ela tem 1 ou 2\n");
        }
        else {
            break;
        }
    }
    
    while (true) {
        cout << "Escolha uma das situacoes principais abaixo:\n" << endl;
        for (int i = 1; i < situacoes_principais.size(); i++) {
            cout << "[" << i << "] " << situacoes_principais[i] << endl;
        }
        cin >> s_principal;
        pos_resposta(to_string(s_principal), "");
        if ((s_principal <= 0) && (s_principal > situacoes_principais.size())) {
            printf("\nResposta invalida, Verifique se sua resposta contem um dos numeros especificados na lista.\n");
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Agora escolha uma situacao intrinseca abaixo:\n" << endl;
        for (int i = 1; i < situacoes_intrinsecas.size(); i++) {
            cout << "[" << i << "] " << situacoes_intrinsecas[i] << endl;
        }
        cin >> s_intrinseca;
        pos_resposta(to_string(s_intrinseca), "");
        if ((s_intrinseca <= 0) && (s_intrinseca >= situacoes_intrinsecas.size())) {
            printf("\nResposta invalida, Verifique se sua resposta contem um dos numeros especificados na lista.\n");
        }
        else {
            break;
        }
    }

    cout << "\ns_principal: " << s_principal << "\ns_intrinseca: " << s_intrinseca << endl;

    assistente(solicitante, envolvido, s_principal, s_intrinseca, max_si, etapa, momento_incidente, reincidencia, nomes_etapas[etapa +1]);
}
