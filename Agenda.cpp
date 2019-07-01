# AGENDA_CRUD

// <><><> Agenda para marcação de atendimento médico mensal <><><>  

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <vector>

using namespace std;

#define numdias 31
#define numhoras 10
#define numcaracter 40

int I, J, K;
int DIA, HORA;
string NOME;
bool INICIADO = false;
bool TESTE;


// Posicionar cursor nos limites 80 x 24

void position(int LINHA, int COLUNA) {
    if (COLUNA >= 1 and COLUNA <= 80 and LINHA >= 1 and LINHA <= 24) {
        HANDLE TELA;
        COORD POS;
        TELA = GetStdHandle(STD_OUTPUT_HANDLE);
        POS.X = COLUNA - 1;
        POS.Y = LINHA - 1;
        SetConsoleCursorPosition(TELA, POS);
    }
}

// Limpar tela

void limpa(void) {
    HANDLE TELA;
    DWORD ESCRITA = 0;
    COORD POS;
    TELA = GetStdHandle(STD_OUTPUT_HANDLE);
    POS.X = 0;
    POS.Y = 0;
    FillConsoleOutputCharacter(TELA, 32, 100 * 100, POS, &ESCRITA);
}


// Limpar linha a partir da posicao do cursor

void clearline(void) {
    HANDLE TELA;
    COORD POS;
    CONSOLE_SCREEN_BUFFER_INFO VIDEO;
    DWORD ESCRITA = 0;
    TELA = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(TELA, &VIDEO);
    POS.Y = VIDEO.dwCursorPosition.Y;
    POS.X = VIDEO.dwCursorPosition.X;
    FillConsoleOutputCharacter(TELA, 32, 80 - POS.X, POS, &ESCRITA);
}


// cria linhas
void tracalinha(string tipo) {
    limpa();
    position(1, 1);
    for (I = 0; I <= 79; I++)
        cout << "-";
    cout << endl;
    position(2, 26);
    cout << "*** AGENDA PARA MARCACAO DE ATENDIMENTO ***" << endl;
    position(3, 33 );
    cout << tipo;
    cout << endl;
    position(4, 1 );
    for (I = 0; I <= 79; I++)
        cout << "-";
}

//tela do menu inicial

void textomenu(void)
{
    limpa( );
    string tipo;
    tracalinha(tipo);
    position(8,26);
    cout << "\t\tMENU PRINCIPAL\n\n";
    position( 10,26);
    cout << "MARCAR ATENDIMENTO ................: [1]";
    position(12,26);
    cout << "DESMARCAR ATENDIMENTO .............: [2]";
    position(14,26);
    cout << "LISTAR MARCACOES DO DIA ...........: [3]";
    position(16,26);
    cout << "PESQUISAR HORARIO DO CLIENTE ......: [4]";
    position(18,26);
    cout << "MAPA DE HORARIO LIVRE .............: [5]";
	position (20,26);
	cout << "SAIR ..............................: [6]";
    position(24,26);
}

struct tiponome
{
   bool preenchido;
   string NOME;

};
//dias e horas
tiponome agenda[numdias][numhoras];


void marcaratendimento(void)
{
    limpa( );
    string tipo;
    tracalinha(tipo);
    position(8,26);
    cout << "\t\tMARCAR ATENDIMENTO";
    position(8,26);
    position(11,17);
    clearline();
    position(12,17);
    clearline();
    position(13,26);
    clearline();
    position(14,17);
    clearline();
    position(15,17);
    clearline();
    position(10, 26);
	cout << "INFORME O DIA: ";
    fflush(stdin);
	cin >> DIA;
	while (not(DIA >= 1 && DIA <= 31))
	{
	    position(19, 26);
		cout << "VOCE ENTROU UM DIA INVALIDO! \n\n ENTRE UM DIA VALIDO: ";
		limpa();
		fflush(stdin);
		cin >> DIA;
		clearline();
	}

    position(11,26);
    cout << "INFORME A HORA: ";
    fflush(stdin);
	cin >> HORA;

	while (not(HORA >= 8 && HORA <= 17)){

        position(20,26);
		cout << "\n\n\n\n\n\n\n\nVOCE ENTROU UMA HORA INVALIDA! \n\n ENTRE UMA HORA VALIDA: ";
		clearline();
		fflush(stdin);
		cin >> HORA;
	}
	if (agenda[DIA - 1][HORA].preenchido){
        position(19,26);
		cout << "\n\n\n\n\n\n\nESTA HORA ESTA OCUPADA! ";
	}
	else{
        position(12,26);

		cout << "INFORME O NOME: ";
		fflush(stdin);
		cin >> NOME;
		agenda[DIA - 1][HORA - 8].NOME = NOME;
		agenda[DIA - 1][HORA - 8].preenchido = true;
		position(19,26);
		cout << "\n\n\n\n\n\n\nSUCESSO HORARIO AGENDADO! ";
		cout << "Tecle <Enter> para ir ao MENU... ";
        cin.get();
        textomenu();

	}
}

void desmarcar(void){
    limpa( );
    string tipo;
    tracalinha(tipo);
    position(8,26);
    cout << "\t\tDESMARCAR ATENDIMENTO";
    position(8,26);
    position(11,17);
    clearline();
    position(12,17);
    clearline();
    position(13,26);
    clearline();
    position(14,17);
    clearline();
    position(15,17);
    clearline();
    position(10, 26);
	cout << "INFORME O DIA: ";
	cin >> DIA;
	while (not(DIA >= 1 && DIA <= 31))
	{
		cout << "VOCE ENTROU UM DIA INVALIDO! \n\n ENTRE UM DIA VALIDO: ";
		clearline();
		cin >> DIA;
	}
    position(11,26);
    cout << "INFORME A HORA: ";
	cin >> HORA;

	while (not(HORA >= 8 && HORA <= 17)){


		cout << "VOCE ENTROU UMA HORA INVALIDA! \n\n ENTRE UMA HORA VALIDA: ";
		clearline();
		cin >> HORA;
	}
	if (not(agenda[DIA - 1][HORA - 8].preenchido)){
		cout << "ESTA HORA NAO POSSUI AGENDAMENTO! ";
		return;
	}
	else{

		agenda[DIA - 1][HORA - 8].preenchido = false;
		position(19,26);
		cout << "\\n\n\n\n\n\n\nSUCESSO HORARIO DESMARCADO! ";
		fflush(stdin);
		cout << "Tecle <Enter> para ir ao MENU... ";
        cin.get();
        textomenu();
	}

}
// verifica os cadastros do dia
void listardia(void)
{
     limpa( );
    string tipo;
    tracalinha(tipo);
    position(8,26);
    cout << "\t\tCLIENTES DO DIA";
    position(11,26);
	cout << "\t\tINFORME O DIA: ";
	fflush(stdin);
	cin >> DIA;
	while (not(DIA >= 1 && DIA <= 31))
	{
		cout << "VOCE ENTROU UM DIA INVALIDO! \n\n ENTRE UM DIA VALIDO: ";
		clearline();
		cin >> DIA;
	}
	position(14,26);
    cout << "\t\tLISTAGEM DE CLIENTES\n";
    int linha = 15;
	for (I = 0; I < numhoras; I++){
		if (agenda[DIA - 1][I].preenchido){
        position(linha,26);
		cout << "\t\tHORA   " << I+8 << " : \t" << agenda[DIA - 1][I].NOME << "\n";
		linha++;
		}
	}
	cout << endl;
    fflush(stdin);
    position(19,26);
    cout << "\n\n\n\n\n\n\n\nTecle <Enter> para ir ao MENU... ";
    cin.get();
    textomenu();
}

void pesquisanome(void)
{
    fflush(stdin);
    string tipo;
    string nome1;
    tracalinha(tipo);
    position(8,26);
    cout << "\t\tHORARIOS DO CLIENTE";
    position(11,26);
	cout << "\n\tINFORME O NOME: ";
	fflush(stdin);
	cin >> NOME;
    fflush(stdin);
    bool encontrado = false;
	for (I = 0; I < numdias; I++){
		for (J = 0 ; J < numhoras; J++){
			if (agenda[I][J].preenchido && agenda[I][J].NOME == NOME){
                cout << " DIA " << I+1 << " AS " << J+8 << "   HORAS ---- Cliente:\t" << NOME << endl;
                encontrado = true;
			}
		}
	}
	if(!encontrado)
        cout << "\n\nNenhum registro encontrado\n";
	cout << "\n\n\n\n\n\n\n\nTecle <Enter> para ir ao MENU... ";
    cin.get();
	return;
}

void mostrartudo(void)
{
	cout << "DIA:    ";
	for (I = 0; I < numdias; I++){
		if (I < 10)
			cout << " ";
		cout << I+1 << " ";
	}

	cout << "\n";
	cout << "HORARIO\n";
	for (I = 0; I < numhoras; I++)
	{

		if (I + 8 < 18 ){
			cout << " " << I+8 << "      ";
	}else{
		cout << I+8 << "       ";
	}fflush(stdin);
		for (J = 0; J < numdias; J++)
		{
			if (agenda[J][I].preenchido){
				cout << " * ";
			}
			else{
				cout << " . ";
			}
		}
		cout << "\n";
    }
		fflush(stdin);
		cout << "Tecle <Enter> para ir ao MENU... ";
        cin.get();
        textomenu();
}

void salvar(void){
    ofstream arq;

    arq.open("saveagenda.txt");

    for (int dia = 0; dia < 31; dia++){
        for(int hora = 0; hora < 10; hora++){
            string linha;
            ostringstream temp;
            temp << (dia+1);
            linha = temp.str()+";";
            ostringstream temp2;
            temp2 << (hora+8);
            linha += temp2.str()+";";
            linha += agenda[dia][hora].NOME+=";";
            linha += agenda[dia][hora].preenchido == true ? "1\n" : "0\n";
            arq << linha;
        }
	}

    arq.close();
}

vector<string> split(const string &texto, char caractere){
    vector<string> result;
    stringstream ss (texto);
    string item;

    while (getline (ss, item, caractere)) {
        result.push_back (item);
    }

    return result;
}

bool abrir(void){
    ifstream arq;
    string line;
    arq.open("saveagenda.txt");

    if(arq.is_open()){
        while (getline (arq,line)) //enquanto end of file for false continua
        {
                                 //e não binário(ios::bin) pega cada linha
            vector<string> resLine = split(line, ';');
            stringstream diaS(resLine[0].c_str());
            int dia, hora, preenchido;
            diaS >> dia;
            stringstream horaS(resLine[1].c_str());
            horaS >> hora;
            stringstream preS(resLine[3].c_str());
            preS >> preenchido;
            agenda[dia-1][hora-8].NOME = resLine[2].c_str();
            if(preenchido == 1)
                agenda[dia-1][hora-8].preenchido = true;
            else
                agenda[dia-1][hora-8].preenchido = false;
        }
        arq.close();
        return true;
    }else{
        return false;
    }
}


int main(void){

	char opcao[2];
	bool abriu = abrir();



	if(abriu == false){
        for (int dia = 0; dia < 31; dia++){
            for(int hora = 0; hora < 10; hora++){
                agenda[dia][hora].NOME = "";
                agenda[dia][hora].preenchido = false;
            }
        }
	}

	do {
		textomenu();
		cin >> opcao; cin.ignore(80,'\n');
		limpa();
		switch(atoi(opcao))
		{
			case 1:
				marcaratendimento();
				break;
			case 2:
				desmarcar();
				break;
			case 3:
				listardia();
				break;
			case 4:
				pesquisanome();
				break;
			case 5:
				mostrartudo();
				break;
			case 6:{
			    salvar();
			    exit(0);
			}
			    break;
			default:
				cout << "OPCAO INVALIDA!\n\n\n";
		}

	}while(atoi(opcao)!=6);
	return 0;
}
