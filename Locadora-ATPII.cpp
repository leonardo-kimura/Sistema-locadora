<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>

/*

---------Trabalho feito por-----------
262516217 - Gabriel Ribeiro de Souza
---------------------------------------
262516950 - Leonardo Yukio Kimura
---------------------------------------
262516314� - Luis Antonio Moreira Giolo
----------------------------------------

*/

// ----- TABELAS -----

struct TpCliente
{
	char CPF[15],Nome[120], Telefone[14] ;
	int Status;
};
		
struct TpCarro
{
	int CodCar,Status;
	char Modelo[30], Categoria[30];
	float PrecoDia;
};

struct TpLocacao{
	char CPF[15];
	int CodCar, QtdDias, Status;
	float ValorLoc;
};

// ----- INTERFACE -----
void Moldura(int CI, int LI, int CF, int LF, int CorBorda, int CorFundo);
void LimpaJanela(int CI, int LI, int CF, int LF, int CorFundo);


// ---- CRIAR ARQUIVOS ----

void CriarArquivos();

// ----- MENUS -----

char MenuPrincipal();
char MenuCadastros();
char MenuRelatorios();
char MenuOrganizacao();

// ----- BUSCAS -----

int BuscaExaustivaCliente(FILE *PtrArq, char auxCPF[15]);
int BuscaExaustivaCarro(FILE *PtrArq, int auxCod);
int BuscaExaustivaLocacao(FILE *PtrArq, char auxCPF[15], int auxCod);
int BuscaSentinelaCliente(char auxCPF[15]);
int BuscaSeqIndexCPF(char auxCPF[15]);
int BuscaBinariaCarro(int auxCod);
int BuscaBinariaLocacaoCPF(char auxCPF[15]);
int ContarLocacoesCliente(char auxCPF[15]);

// ----- ORDENA��O -----

void InsertionSortClientesArquivo();
void SelectionSortCarrosArquivo();
void BubbleSortCarrosModeloArquivo();
void BubbleSortLocacoesCPFArquivo();

// -----  CLIENTES -----
void CADCliente();

void ALTCliente();
void EXClienteLogica();
void RELACliente();

// ----- CARROS -----

void CADCarro();
void ALTCarro();
void EXCarroLogica();
void RELACarro();

// ----- LOCA��ES -----

void CADLoc();
void ALTLoc();
void EXCLocLogica();
void RELALoc();

// ----- RELAT�RIOS -----

void RelatorioClientesMais3Locacoes();
void RelatorioCarrosPorCategoria();
void RelatorioLocacoesAcimaValor();
void RelatorioCompletoCliente();

// ----- EXCLUS�ES F�SICAS -----
void ExclusaoFisicaClientes();
void ExclusaoFisicaCarros();
void ExclusaoFisicaLocacoes();


// -----MOLDURA -----
void Moldura(int CI, int LI, int CF, int LF, int CorBorda, int CorFundo)
{
	int i;
	textbackground(0);
	textcolor(CorBorda);
	
	gotoxy(CI,LI); printf("%c",201);
	gotoxy(CF,LI); printf("%c",187);
	gotoxy(CI,LF); printf("%c",200);
	gotoxy(CF,LF); printf("%c",188);
	
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI); printf("%c",205);
		gotoxy(i,LF); printf("%c",205);
	}
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i); printf("%c",186);
		gotoxy(CF,i); printf("%c",186);
	}
	
	textbackground(0);
	for(i=LI+1; i<LF; i++)
	{
		for(int j=CI+1; j<CF; j++)
		{
			gotoxy(j, i); printf(" ");
		}
	}
	textbackground(0);
	textcolor(7);
}

void LimpaJanela(int CI, int LI, int CF, int LF, int CorFundo)
{
	int i, j;
	for(i=LI+1; i<LF; i++)
	{
		for(j=CI+1; j<CF; j++)
		{
			gotoxy(j, i); printf(" ");
		}
	}
}

// ----- CRIAR ARQUIVOS -----

void CriarArquivos(){
	FILE *PtrArq;
	
	PtrArq = fopen("Clientes.dat", "ab");
	if(PtrArq != NULL) fclose(PtrArq);
	
	PtrArq = fopen("Carros.dat", "ab");
	if(PtrArq != NULL) fclose(PtrArq);
	
	PtrArq = fopen("Locacoes.dat", "ab");
	if(PtrArq != NULL) fclose(PtrArq);
}

// ----- BUSCAS -----

int BuscaExaustivaCliente(FILE *PtrArq, char auxCPF[15]) {
	TpCliente RC;
	int Pos = -1;
	int Achou = 0;
	
	rewind(PtrArq);
	fread(&RC, sizeof(TpCliente), 1, PtrArq);
	
	while(!feof(PtrArq) && Achou == 0)
	{
		if(strcmp(RC.CPF, auxCPF) == 0 && RC.Status == 1)
		{
			Pos = ftell(PtrArq) - sizeof(TpCliente);
			Achou = 1;
		}
		else
		{
			fread(&RC, sizeof(TpCliente), 1, PtrArq);
		}
	}
	
	return Pos;
}

int BuscaExaustivaCarro(FILE *PtrArq, int auxCod) {
	TpCarro RC;
	int Pos = -1, Achou = 0;
	
	rewind(PtrArq);
	fread(&RC, sizeof(TpCarro), 1, PtrArq);
	
	while(!feof(PtrArq) && Achou == 0) {
	 	if(RC.CodCar == auxCod && RC.Status == 1) {
	 	 	Pos = ftell(PtrArq) - sizeof(TpCarro);
			Achou = 1;
	 	}
		else
		{
	 		fread(&RC, sizeof(TpCarro), 1, PtrArq);
		}
	}
	return Pos;
}

int BuscaExaustivaLocacao(FILE *PtrArq, char auxCPF[15], int auxCod) {
	TpLocacao RL;
	int Pos = -1;
	int Achou = 0;
	
	rewind(PtrArq);
	fread(&RL, sizeof(TpLocacao), 1, PtrArq);
	
	while(!feof(PtrArq) && Achou == 0) {
	 	if(strcmp(RL.CPF, auxCPF) == 0 && RL.CodCar == auxCod && RL.Status == 1) {
	 	 	Pos = ftell(PtrArq) - sizeof(TpLocacao);
			Achou = 1;
	 	}
		else
		{
	 		fread(&RL, sizeof(TpLocacao), 1, PtrArq);
		}
	}
	return Pos;
}

int BuscaSentinelaCliente(char auxCPF[15]) {
	FILE *PtrArq;
	FILE *PtrSent;
	TpCliente RC;
	
	int ContRegistros = 0;
	int i = 0;
	int PosFinal = -1;

	PtrArq = fopen("Clientes.dat", "rb");
	PtrSent = fopen("TempSentinela.dat", "wb");

	fread(&RC, sizeof(TpCliente), 1, PtrArq);
	while (!feof(PtrArq)) {
	 	if (RC.Status == 1) {
	 	 	fwrite(&RC, sizeof(TpCliente), 1, PtrSent);
	 	 	ContRegistros++;
	 	}
	 	fread(&RC, sizeof(TpCliente), 1, PtrArq);
	}
	fclose(PtrArq);

	strcpy(RC.CPF, auxCPF);
	RC.Status = 1;
	strcpy(RC.Nome, "SENTINELA");
	strcpy(RC.Telefone, "SENTINELA");
	
	fwrite(&RC, sizeof(TpCliente), 1, PtrSent);
	fclose(PtrSent);

	PtrSent = fopen("TempSentinela.dat", "rb");
	
	rewind(PtrSent);
	fread(&RC, sizeof(TpCliente), 1, PtrSent);
	i = 1;

	while (strcmp(RC.CPF, auxCPF) != 0) {
	 	fread(&RC, sizeof(TpCliente), 1, PtrSent);
	 	i++;
	}
	
	if (i <= ContRegistros) {
	 	PosFinal = (i - 1) * sizeof(TpCliente);
	}

	fclose(PtrSent);

	remove("TempSentinela.dat");

	return PosFinal;
}

int BuscaSeqIndexCPF(FILE *Ptr, char auxCPF[15]){
	TpCliente RC;
	int Pos = -1;
	
	FILE *PtrArq = fopen("Clientes.dat", "rb");
	
	rewind(PtrArq);
	fread(&RC,sizeof(TpCliente),1,PtrArq);
	
	while(!feof(PtrArq) && strcmp(RC.CPF, auxCPF) < 0)
	{
		fread(&RC,sizeof(TpCliente),1,PtrArq);
	}
	
	if(!feof(PtrArq) && strcmp(RC.CPF, auxCPF) == 0 && RC.Status == 1)
	{
		Pos = ftell(PtrArq) - sizeof(TpCliente);
	}
	
	fclose(PtrArq);
	return Pos;	
}

int BuscaBinariaCarro(int auxCod){
	TpCarro RC;
	int inicio, meio, fim;
	int Achou = 0;
	int Pos = -1;
	
	FILE *PtrArq = fopen("Carros.dat", "rb");
	
	inicio = 0;
	fseek(PtrArq, 0, SEEK_END);
	fim = (ftell(PtrArq) / sizeof(TpCarro)) - 1;
	
	while (inicio <= fim && Achou == 0) {
	 	meio = (inicio + fim) / 2;

	 	fseek(PtrArq, meio * sizeof(TpCarro), SEEK_SET);
	 	fread(&RC, sizeof(TpCarro), 1, PtrArq);

	 	if (RC.CodCar == auxCod) {
	 	 	if(RC.Status == 1)
	 	 	{
	 	 	 	Achou = 1;
				Pos = meio * sizeof(TpCarro);
			}
			else
			{
				inicio = fim + 1;
			}
	 	} else if (RC.CodCar < auxCod) {
	 	 	inicio = meio + 1;
	 	} else {
	 	 	fim = meio - 1;
	 	}
	}
	
	fclose(PtrArq);
	return Pos;
}

int BuscaBinariaLocacaoCPF(char auxCPF[15]){
	TpLocacao RL;
	int inicio, meio, fim;
	int Achou = 0;
	int Pos = -1;
	int comp;
	
	FILE *PtrArq = fopen("Locacoes.dat", "rb");
	
	inicio = 0;
	fseek(PtrArq, 0, SEEK_END);
	fim = (ftell(PtrArq) / sizeof(TpLocacao)) - 1;
	
	while (inicio <= fim && Achou == 0) {
	 	meio = (inicio + fim) / 2;

	 	fseek(PtrArq, meio * sizeof(TpLocacao), SEEK_SET);
	 	fread(&RL, sizeof(TpLocacao), 1, PtrArq);

	 	if(RL.Status == 1)
	 	{
	 	 	comp = strcmp(RL.CPF, auxCPF);
	 	 	
	 	 	if (comp == 0) {
	 	 	 	Achou = 1;
	 	 	 	Pos = meio * sizeof(TpLocacao);
	 	 	} else if (comp < 0) { 
	 	 	 	inicio = meio + 1;
	 	 	} else { 
	 	 	 	fim = meio - 1;
	 	 	}
	 	}
	 	else
	 	{
	 	 	comp = strcmp(RL.CPF, auxCPF);
	 	 	if (comp < 0) {
	 	 	 	inicio = meio + 1;
	 	 	} else {
	 	 	 	fim = meio - 1;
	 	 	}
	 	}
	}
	
	fclose(PtrArq);
	return Pos;
}

int ContarLocacoesCliente(char auxCPF[15])
{
	TpLocacao Loc;
	int Cont = 0;
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");
	

	fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	while(!feof(PtrLoc))
	{
	 	if(Loc.Status == 1 && strcmp(Loc.CPF, auxCPF) == 0)
	 	{
			Cont++;
	 	}
		fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	}
	fclose(PtrLoc);
	return Cont;
}


// ----- ORDENA��O -----

void InsertionSortClientesArquivo()
{
	FILE *PtrArq = fopen("Clientes.dat", "rb+");

	int Tam;
	fseek(PtrArq, 0, SEEK_END);
	Tam = ftell(PtrArq) / sizeof(TpCliente);
	
	if (Tam <= 1)
	{
		fclose(PtrArq);
		return;
	}

	int i, j;
	TpCliente Aux, Rj;

	for (i = 1; i < Tam; i++)
	{
		fseek(PtrArq, i * sizeof(TpCliente), SEEK_SET);
		fread(&Aux, sizeof(TpCliente), 1, PtrArq);
		
		j = i - 1;

		fseek(PtrArq, j * sizeof(TpCliente), SEEK_SET);
		fread(&Rj, sizeof(TpCliente), 1, PtrArq);

		while (j >= 0 && strcmp(Aux.CPF, Rj.CPF) < 0)
		{
			fseek(PtrArq, (j + 1) * sizeof(TpCliente), SEEK_SET);
			fwrite(&Rj, sizeof(TpCliente), 1, PtrArq);
			
			j--;
			
			if (j >= 0)
			{
				fseek(PtrArq, j * sizeof(TpCliente), SEEK_SET);
				fread(&Rj, sizeof(TpCliente), 1, PtrArq);
			}
		}
		
		fseek(PtrArq, (j + 1) * sizeof(TpCliente), SEEK_SET);
		fwrite(&Aux, sizeof(TpCliente), 1, PtrArq);
	}

	fclose(PtrArq);
}

void SelectionSortCarrosArquivo()
{
	FILE *PtrArq = fopen("Carros.dat", "rb+");

	int Tam, i,j,min;
	TpCarro Ri, Rj, Rmin;
	fseek(PtrArq, 0, SEEK_END);
	Tam = ftell(PtrArq) / sizeof(TpCarro);

	if (Tam <= 1)
	{
		fclose(PtrArq);
		gotoxy(3, 23); printf("Ordenado.");
		getch();
		return;
	}


	for (i = 0; i < Tam - 1; i++)
	{
		min = i;
		
		fseek(PtrArq, min * sizeof(TpCarro), SEEK_SET);
		fread(&Rmin, sizeof(TpCarro), 1, PtrArq);

		for (j = i + 1; j < Tam; j++)
		{
			fseek(PtrArq, j * sizeof(TpCarro), SEEK_SET);
			fread(&Rj, sizeof(TpCarro), 1, PtrArq);

			if (Rj.CodCar < Rmin.CodCar)
			{
				min = j;
				Rmin = Rj;
			}
		}

		if (i != min)
		{
			fseek(PtrArq, i * sizeof(TpCarro), SEEK_SET);
			fread(&Ri, sizeof(TpCarro), 1, PtrArq);

			fseek(PtrArq, min * sizeof(TpCarro), SEEK_SET);
			fwrite(&Ri, sizeof(TpCarro), 1, PtrArq);
			
			fseek(PtrArq, i * sizeof(TpCarro), SEEK_SET);
			fwrite(&Rmin, sizeof(TpCarro), 1, PtrArq);
		}
	}

	fclose(PtrArq);
}

void BubbleSortCarrosModeloArquivo()
{
	FILE *PtrArq = fopen("Carros.dat", "rb+");

	TpCarro Rj, Rj1;
	int Tam, i,j, Trocou =1;
	fseek(PtrArq, 0, SEEK_END);
	Tam = ftell(PtrArq) / sizeof(TpCarro);

	if (Tam <= 1)
	{
		fclose(PtrArq);
		gotoxy(3, 23); printf("Nao e necessario ordenar (0 ou 1 carro).");
		getch();
		return;
	}


	for (i = 0; i < Tam - 1 && Trocou == 1; i++)
	{
		Trocou = 0;
		for (j = 0; j < Tam - 1 - i; j++)
		{
			fseek(PtrArq, j * sizeof(TpCarro), SEEK_SET);
			fread(&Rj, sizeof(TpCarro), 1, PtrArq);

			fseek(PtrArq, (j + 1) * sizeof(TpCarro), SEEK_SET);
			fread(&Rj1, sizeof(TpCarro), 1, PtrArq);
			
			if (stricmp(Rj.Modelo, Rj1.Modelo) > 0)
			{
				fseek(PtrArq, j * sizeof(TpCarro), SEEK_SET);
				fwrite(&Rj1, sizeof(TpCarro), 1, PtrArq);
				
				fseek(PtrArq, (j + 1) * sizeof(TpCarro), SEEK_SET);
				fwrite(&Rj, sizeof(TpCarro), 1, PtrArq);
				
				Trocou = 1;
			}
		}
	}
	
	fclose(PtrArq);
}

void BubbleSortLocacoesCPFArquivo()
{
	FILE *PtrArq = fopen("Locacoes.dat", "rb+");

	int Tam,i,j, Trocou = 1;
	TpLocacao Rj, Rj1;
	fseek(PtrArq, 0, SEEK_END);
	Tam = ftell(PtrArq) / sizeof(TpLocacao);

	if (Tam <= 1)
	{
		fclose(PtrArq);
		gotoxy(3, 23); printf("Nao e necessario ordenar (0 ou 1 locacao).");
		getch();
		return;
	}

	
	for (i = 0; i < Tam - 1 && Trocou == 1; i++)
	{
		Trocou = 0;
		for (j = 0; j < Tam - 1 - i; j++)
		{
			fseek(PtrArq, j * sizeof(TpLocacao), SEEK_SET);
			fread(&Rj, sizeof(TpLocacao), 1, PtrArq);

			fseek(PtrArq, (j + 1) * sizeof(TpLocacao), SEEK_SET);
			fread(&Rj1, sizeof(TpLocacao), 1, PtrArq);
			
			if (strcmp(Rj.CPF, Rj1.CPF) > 0)
			{
				fseek(PtrArq, j * sizeof(TpLocacao), SEEK_SET);
				fwrite(&Rj1, sizeof(TpLocacao), 1, PtrArq);
				
				fseek(PtrArq, (j + 1) * sizeof(TpLocacao), SEEK_SET);
				fwrite(&Rj, sizeof(TpLocacao), 1, PtrArq);
				
				Trocou = 1;
			}
		}
	}
	
	fclose(PtrArq);
}


// ----- CLIENTES -----

void CADCliente(void){
	TpCliente Cliente;
	int posCPF;
	char AuxCPF[15];
	char op = 'S';
	
	FILE *PtrArq = fopen("Clientes.dat", "ab+");

	while(toupper(op) == 'S')
	{
		Moldura(1, 1, 80, 25, 15, 0);
		gotoxy(30, 2); textcolor(9); printf("CADASTRO DE CLIENTES");
		
		LimpaJanela(1, 2, 80, 25, 0);
		gotoxy(3, 5); textcolor(9); printf("Digite o CPF (ENTER para Sair): "); textcolor(15);
		fflush(stdin);
		gets(AuxCPF);
		
		if(strcmp(AuxCPF, "") == 0)
		{
			op = 'N';
		}
		else
		{
			posCPF = BuscaExaustivaCliente(PtrArq,AuxCPF);
			
			if(posCPF == -1){
					strcpy(Cliente.CPF,AuxCPF);
					gotoxy(3, 7); textcolor(9); printf("%c Nome: ", 175); textcolor(15);
					fflush(stdin);
					gets(Cliente.Nome);
					gotoxy(3, 8); textcolor(9); printf("%c Telefone: ",175); textcolor(15);
					fflush(stdin);
					gets(Cliente.Telefone);
					Cliente.Status = 1;			
				
					fseek(PtrArq, 0, SEEK_END);
					fwrite(&Cliente,sizeof(TpCliente),1,PtrArq);
					
					fclose(PtrArq);
					InsertionSortClientesArquivo(); 
					PtrArq = fopen("Clientes.dat", "ab+");
					
					gotoxy(3, 23); textcolor(10); printf("Cliente cadastrado com sucesso!!");
					textcolor(15);
					getch();
				}
			else
			{
			 	gotoxy(3, 23); textcolor(12); printf("CPF ja cadastrado!");
			 	textcolor(15);
				getch();
			}
			
			if(toupper(op) == 'S')
			{
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(3, 5); printf("Deseja cadastrar outro? (S/N): ");
				op = getche();
			}
		}
	}
			
	fclose(PtrArq);
}

void ALTCliente(void) {
	TpCliente Cliente;
	char AuxCPF[15], NovoNome[120], NovoTel[14];
	int pos;
	
	FILE *PtrArq = fopen("Clientes.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(29, 2); textcolor(9); printf("ALTERACAO DE CLIENTES");
	
	gotoxy(3, 5); textcolor(9); printf("Digite o CPF do cliente a alterar: "); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	
	pos = BuscaSeqIndexCPF(PtrArq, AuxCPF);
		
	if(pos == -1) {
	 	gotoxy(3, 23);  textcolor(12); printf("Cliente nao encontrado ou inativo!"); textcolor(15); 
		getch();
	} else {
	 	fseek(PtrArq, pos, SEEK_SET);
	 	fread(&Cliente, sizeof(TpCliente), 1, PtrArq);
	 	
	 	gotoxy(3, 7); textcolor(9); printf("Dados Atuais:");
	 	gotoxy(3, 8);  textcolor(14);  printf("%c CPF: %s",175, Cliente.CPF); 
	 	gotoxy(3, 9); printf("%c Nome: %s", 175,Cliente.Nome);
	 	gotoxy(3, 10); printf("%c Telefone: %s", 175,Cliente.Telefone); textcolor(15);
	 	
	 	gotoxy(3, 13); printf("Digite os novos dados (ENTER para manter):");
	
		
	 	gotoxy(3, 15); textcolor(9); printf("%c Novo Nome: ",175); textcolor(15); 
	 	fflush(stdin);
	 	gets(NovoNome);
	 	
	 	gotoxy(3, 16); textcolor(9); printf("%c Novo Telefone: ",175); textcolor(15); 
	 	fflush(stdin);
	 	gets(NovoTel);
		
		if(strcmp(NovoNome, "") != 0)
			strcpy(Cliente.Nome, NovoNome);
			
		if(strcmp(NovoTel, "") != 0)
			strcpy(Cliente.Telefone, NovoTel);
	 	
	 	fseek(PtrArq, pos, SEEK_SET);
	 	fwrite(&Cliente, sizeof(TpCliente), 1, PtrArq);
	 	
	 	gotoxy(3, 23); textcolor(10); printf("Cliente alterado com sucesso!"); textcolor(15);
		getch();
	}
	
	fclose(PtrArq);
}

void EXClienteLogica(void) {
	TpCliente Cliente;
	char AuxCPF[15];
	int pos;
	char op;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");
	
	FILE *PtrArq = fopen("Clientes.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(29, 2); textcolor(9); printf("EXCLUIR CLIENTES");
	
	gotoxy(3, 5); textcolor(9); printf("Digite o CPF do cliente a excluir: "); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	
	pos = BuscaExaustivaCliente(PtrArq, AuxCPF);
	
	if(pos == -1) {
	 	gotoxy(3, 23); textcolor(12); printf("Cliente nao encontrado ou ja excluido!");
		getch();
	} else {
		
		int ContLoc = ContarLocacoesCliente(AuxCPF);
		
		if(ContLoc > 0)
		{
			gotoxy(3, 23); textcolor(12); printf("Cliente possui locacoes ativas e nao pode ser excluido!"); textcolor(15);
			getch();
		}
		else
		{
			fseek(PtrArq, pos, SEEK_SET);
			fread(&Cliente, sizeof(TpCliente), 1, PtrArq);
			
			gotoxy(3, 7); textcolor(9); printf("Dados do cliente:");
			gotoxy(3, 8); textcolor(14); printf("%c CPF: %s", 175,Cliente.CPF);
			gotoxy(3, 9); printf("%c Nome: %s",175, Cliente.Nome);
			gotoxy(3, 10);printf("%c Telefone: %s",175,Cliente.Telefone); textcolor(15);
			
			gotoxy(3, 12); printf("Tem certeza? (S/N): ");
			fflush(stdin);
			op = getche();
			
			if(toupper(op) == 'S') {
				Cliente.Status = 0;
				
				fseek(PtrArq, pos, SEEK_SET);
				fwrite(&Cliente, sizeof(TpCliente), 1, PtrArq);
				gotoxy(3, 23); textcolor(12); printf("Cliente excluido!"); textcolor(15);
				getch();
			} else {
				gotoxy(3, 23); textcolor(4); printf("Exclusao cancelada."); textcolor(15);
				getch();
			}
		}
	}
	fclose(PtrArq);
	fclose(PtrLoc);
}

void RELACliente(void){
	TpCliente Cliente;
	int Linha = 6;
	int Cont = 0;
	
	FILE *PtrArq = fopen("Clientes.dat", "rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(30, 2); textcolor(9); printf("RELATORIO DE CLIENTES"); textcolor(11);
	
	fread(&Cliente,sizeof(TpCliente),1,PtrArq);
	while(!feof(PtrArq)){
		
		if(Cliente.Status == 1){
			Cont++;
			if(Linha > 20)
			{
				gotoxy(25, 24); textcolor(7); printf("Pressione ENTER para continuar..."); textcolor(11);
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				Linha = 6;
			}
			gotoxy(3, Linha++); printf("%c CPF: %s",175, Cliente.CPF);
			gotoxy(3, Linha++); printf("%c Nome: %s",175, Cliente.Nome);
			gotoxy(3, Linha++); printf("%c Telefone: %s",175,Cliente.Telefone);
			gotoxy(3, Linha++); printf("                                      ");
			gotoxy(3, Linha++); printf("---------------------------------------");
		}	
		fread(&Cliente,sizeof(TpCliente),1,PtrArq);
	}
	fclose(PtrArq);
	
	if(Cont == 0)
	{
		gotoxy(3, 6); textcolor(12); printf("Nenhum cliente ativo cadastrado."); textcolor(15);
	}
	
	gotoxy(25, 24); textcolor(2); printf("Fim do Relatorio. Pressione ENTER.");  textcolor(15);
	getch();
}


// ----- CARROS -----

void CADCarro(){
	TpCarro Carro;
	int posCar;
	char op = 'S';
	
	FILE *PtrCarro = fopen("Carros.dat", "ab+");
	
	while(toupper(op) == 'S')
	{
		Moldura(1, 1, 80, 25, 15, 0);
		gotoxy(32, 2); textcolor(10); printf("CADASTRO DE CARROS");
		
		LimpaJanela(1, 2, 80, 25, 0);
		gotoxy(3, 5);  printf("Digite o CODIGO (0 para sair): "); textcolor(15);
		scanf("%d",&Carro.CodCar);
		
		if(Carro.CodCar == 0)
		{
			op = 'N';
		}
		else
		{
			posCar = BuscaExaustivaCarro(PtrCarro, Carro.CodCar);

			if(posCar == -1) {
				gotoxy(3, 7);textcolor(10); printf("%c Modelo: ",175); textcolor(15);
				fflush(stdin);
				gets(Carro.Modelo);
				
				gotoxy(3, 8);textcolor(10); printf("%c Categoria: ",175); textcolor(15);
				fflush(stdin);
				gets(Carro.Categoria);
				
				gotoxy(3, 9);textcolor(10); printf("Preco da Diaria: R$ "); textcolor(15);
				scanf("%f",&Carro.PrecoDia);
				
				Carro.Status = 1;
				
				fseek(PtrCarro, 0, SEEK_END);
				fwrite(&Carro, sizeof(TpCarro),1,PtrCarro);
				gotoxy(3, 23); textcolor(2); printf("Carro cadastrado com sucesso!"); textcolor(15);
				getch();
			} else {
				gotoxy(3, 23); textcolor(12); printf("Carro com este codigo ja existe!"); textcolor(15);
				getch();
			}
			
			if(toupper(op) == 'S')
			{
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(3, 5); printf("Deseja cadastrar outro? (S/N): ");
				op = getche();
			}
		}
	 }
	
	 fclose(PtrCarro);
}

void ALTCarro(void) {
	TpCarro Carro;
	int AuxCod, pos;
	char NovoMod[30], NovaCat[30];
	float NovoPreco = 0; 
	
	FILE *PtrArq = fopen("Carros.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(31, 2); textcolor(10); printf("ALTERACAO DE CARROS");
	
	gotoxy(3, 5); textcolor(10); printf("Digite o Codigo do carro a alterar: "); textcolor(15);
	scanf("%d", &AuxCod);
	
	pos = BuscaExaustivaCarro(PtrArq, AuxCod);
	
	if(pos == -1) {
	 	gotoxy(3, 23); printf("Carro nao encontrado ou inativo!");
		getch();
	} else {
	 	fseek(PtrArq, pos, SEEK_SET);
	 	fread(&Carro, sizeof(TpCarro), 1, PtrArq);
	 	
		gotoxy(3, 7); textcolor(10); printf("Dados Atuais:");
	 	gotoxy(3, 8);  textcolor(14); printf("%c Codigo: %d",175, Carro.CodCar);
	 	gotoxy(3, 9); printf("%c Modelo: %s",175, Carro.Modelo);
	 	gotoxy(3, 10); printf("%c Categoria: %s",175, Carro.Categoria);
	 	gotoxy(3, 11); printf("%c Preco/Dia: R$ %.2f",175,Carro.PrecoDia);
	 	
	 	gotoxy(3, 13); textcolor(15); printf("Digite os novos dados (ENTER para manter):");
		
	 	gotoxy(3, 15); textcolor(10);  printf("%c Novo Modelo: ",175); textcolor(15);
	 	fflush(stdin);
	 	gets(NovoMod);
	 	
	 	gotoxy(3, 16); textcolor(10); printf("%c Nova Categoria: ",175); textcolor(15);
	 	fflush(stdin);
	 	gets(NovaCat);
	 	
	 	gotoxy(3, 17); textcolor(10); printf("%c Novo Preco: R$ ",175); textcolor(15);
		scanf("%f", &NovoPreco);
		
		if(strcmp(NovoMod, "") != 0)
			strcpy(Carro.Modelo, NovoMod);
		
		if(strcmp(NovaCat, "") != 0)
			strcpy(Carro.Categoria, NovaCat);
			
		if(NovoPreco > 0)
		{
			Carro.PrecoDia = NovoPreco;
		}
	 	
	 	fseek(PtrArq, pos, SEEK_SET);
	 	fwrite(&Carro, sizeof(TpCarro), 1, PtrArq);
	 	
	 	gotoxy(3, 23); textcolor(2); printf("Carro alterado com sucesso!"); textcolor(15);
		getch();
	}
	
	fclose(PtrArq);
}

void EXCarroLogica(void) {
	TpCarro Carro;
	int AuxCod, pos;
	char confirma;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");
	
	FILE *PtrArq = fopen("Carros.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(30, 2); textcolor(10); printf("EXCLUIR CARROS");
	
	gotoxy(3, 5); textcolor(10); printf("Digite o Codigo do carro a excluir: "); textcolor(15);
	scanf("%d", &AuxCod);
	
	pos = BuscaExaustivaCarro(PtrArq, AuxCod);
	
	if(pos == -1) {
	 	gotoxy(3, 23); textcolor(12); printf("Carro nao encontrado ou ja excluido!"); textcolor(15);
		getch();
	} else {
		
		TpLocacao Loc;
		int AchouLoc = 0;
		rewind(PtrLoc);
		fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
		while(!feof(PtrLoc) && AchouLoc == 0)
		{
			if(Loc.CodCar == AuxCod && Loc.Status == 1)
			{
				AchouLoc = 1;
			}
			else
			{
				fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
			}
		}
		
		if(AchouLoc == 1)
		{
			gotoxy(3, 23);  textcolor(12);  printf("Carro esta em uma locacao ativa e nao pode ser excluido!");  textcolor(15); 
			getch();
		}
		else
		{
			fseek(PtrArq, pos, SEEK_SET);
			fread(&Carro, sizeof(TpCarro), 1, PtrArq);
			
			gotoxy(3, 7);  textcolor(10); printf("Dados do Carro:");textcolor(14);
			gotoxy(3, 8); printf("%c Codigo: %d", 175,Carro.CodCar);
			gotoxy(3, 9); printf("%c Modelo: %s",175,Carro.Modelo); 
			gotoxy(3, 10); printf("%c Preco Diaria: R$ %2.f",175,Carro.PrecoDia); textcolor(15);
			
			gotoxy(3, 12); printf("Tem certeza? (S/N): ");
			fflush(stdin);
			confirma = getche();
			
			if(toupper(confirma) == 'S') {
				Carro.Status = 0;
				
				fseek(PtrArq, pos, SEEK_SET);
				fwrite(&Carro, sizeof(TpCarro), 1, PtrArq);
				gotoxy(3, 23); textcolor(12); printf("Carro excluido "); textcolor(15);
				getch();
			} else {
				gotoxy(3, 23); textcolor(12); printf("Exclusao cancelada."); textcolor(15);
				getch();
			}
		}
	}
	fclose(PtrArq);
	fclose(PtrLoc);
}

void RELACarro(){
	TpCarro Carro;
	int Linha = 6;
	int Cont = 0;
	
	FILE *PtrCarro = fopen("Carros.dat","rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(31, 2); textcolor(10); printf("RELATORIO DE CARROS");

	fread(&Carro, sizeof(TpCarro),1,PtrCarro);
	while(!feof(PtrCarro)){
		if(Carro.Status == 1) {
			Cont++;
			if(Linha > 20)
			{
				gotoxy(25, 24); textcolor(7); printf("Pressione ENTER para continuar...");
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				Linha = 6;
			}
			textcolor(2);
	 	 	gotoxy(3, Linha++); printf("%c Codigo: %d",175,Carro.CodCar);
			gotoxy(3, Linha++); printf("%c Modelo: %s",175,Carro.Modelo);
			gotoxy(3, Linha++); printf("%c Categoria: %s",175,Carro.Categoria);
			gotoxy(3, Linha++); printf("%c Preco Diaria: R$ %.2f",175,Carro.PrecoDia);
			gotoxy(3, Linha++); printf("                                          ");
			gotoxy(3, Linha++); printf("---------------------------------------");
	 	}
		fread(&Carro, sizeof(TpCarro),1,PtrCarro);
	}
	fclose(PtrCarro);
	
	if(Cont == 0)
	{
		gotoxy(3, 6); textcolor(12); printf("Nenhum carro ativo cadastrado."); textcolor(15);
	}
	
	gotoxy(24, 24);  printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}


// -----  LOCA��ES -----

void CADLoc(void){
	TpCarro Car;
	TpLocacao Loc;
	int posCli, posCar;
	char Op = 'S';
	
	FILE *PtrCli = fopen("Clientes.dat", "rb");
	FILE *PtrCar = fopen("Carros.dat", "rb");
	FILE *PtrLoc = fopen("Locacoes.dat", "ab+");
	
	while(toupper(Op) == 'S')
	{
		Moldura(1, 1, 80, 25, 15, 0);
		gotoxy(30, 2); textcolor(13); printf("CADASTRO DE LOCACOES");
		
		LimpaJanela(1, 2, 80, 25, 0);
		gotoxy(3, 5);  printf("Digite o CPF do Cliente (ENTER p/ sair): "); textcolor(15);
		fflush(stdin);
		gets(Loc.CPF);
		
		if(strcmp(Loc.CPF, "") == 0)
		{
			Op = 'N';
		}
		else
		{
			posCli = BuscaExaustivaCliente(PtrCli, Loc.CPF);
			
			if(posCli == -1) {
				gotoxy(3, 23); textcolor(12); printf("Cliente nao encontrado ou inativo!"); textcolor(15);
				getch();
			}
			else {
				gotoxy(3, 7); textcolor(13); printf("%c Codigo do Carro: ",175); textcolor(15);
				scanf("%d", &Loc.CodCar);
				
				posCar = BuscaExaustivaCarro(PtrCar, Loc.CodCar);
				
				if(posCar == -1) {
					gotoxy(3, 23); textcolor(12); printf("Carro nao encontrado ou inativo!"); textcolor(15);
					getch();
				}
				else {
					int posLoc = BuscaExaustivaLocacao(PtrLoc, Loc.CPF, Loc.CodCar);
					
					if(posLoc != -1)
					{
						gotoxy(3, 23);textcolor(12); printf("Este cliente ja possui uma locacao ATIVA com este carro!"); textcolor(15);
						getch();
					}
					else
					{
						fseek(PtrCar, posCar, SEEK_SET);
						fread(&Car, sizeof(TpCarro), 1, PtrCar);
						
						gotoxy(3, 9); textcolor(10); printf("%c Carro: %s (R$ %.2f/dia)",175, Car.Modelo, Car.PrecoDia);
						
						gotoxy(3, 11); textcolor(13); printf("%c Quantidade de dias: ",175);textcolor(15);
						scanf("%d", &Loc.QtdDias); 	
			
						Loc.ValorLoc = Loc.QtdDias * Car.PrecoDia;
						Loc.Status = 1;
						
						fseek(PtrLoc, 0, SEEK_END);
						fwrite(&Loc, sizeof(TpLocacao), 1, PtrLoc);
						
						gotoxy(3, 13); printf("%c Valor Total: R$ %.2f",175, Loc.ValorLoc); 
						gotoxy(3, 23); textcolor(2); printf("%c Locacao registrada com sucesso!",175); textcolor(15);
						getch();
					}
				}
			}
			
			if(toupper(Op) == 'S')
			{
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(3, 5); printf("Deseja cadastrar outro? (S/N): ");
				Op = getche();
			}
		}
	}
	
	fclose(PtrCli);
	fclose(PtrCar);
	fclose(PtrLoc);
}

void ALTLoc(void){
	TpLocacao Loc;
	TpCarro Car;
	char AuxCPF[15];
	int AuxCod, posLoc, posCar, verif;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb+");
	FILE *PtrCar = fopen("Carros.dat", "rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(30, 2); textcolor(13); printf("ALTERACAO DE LOCACOES");
	
	gotoxy(3, 5); textcolor(13); printf("%c Digite o CPF da locacao: ",175); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	gotoxy(3, 6); textcolor(13); printf("%c Digite o Codigo do Carro: ",175); textcolor(15);
	scanf("%d", &AuxCod);
	
	posLoc = BuscaExaustivaLocacao(PtrLoc, AuxCPF, AuxCod);
	
	if(posLoc == -1) {
	 	gotoxy(3, 23); textcolor(12); printf("Locacao nao encontrada ou inativa!"); textcolor(15);
		getch();
	} else {
	 	fseek(PtrLoc, posLoc, SEEK_SET);
	 	fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
	 	
		gotoxy(3, 8); textcolor(10); printf("%c Dias Atuais: %d", 175,Loc.QtdDias); textcolor(15);
	 	gotoxy(3, 9); textcolor(10); printf("%c Valor Atual: R$ %.2f",175, Loc.ValorLoc); textcolor(13);
	 	
	 	gotoxy(3, 11); printf("%c Novo Codigo de Carro: ",175); textcolor(15);
		scanf("%d", &Loc.CodCar);
		
		posCar = BuscaExaustivaCarro(PtrCar, Loc.CodCar);
		
		if(posCar == -1)
		{
			gotoxy(3, 23); textcolor(12); printf("Novo carro nao encontrado! Alteracao cancelada."); textcolor(15);
			getch();
		}
		else
		{
			verif = BuscaExaustivaLocacao(PtrLoc, AuxCPF, Loc.CodCar);
			
			if(verif != -1 && verif != posLoc)
			{
				gotoxy(3, 23); textcolor(12); printf("Cliente ja possui locacao ativa com este carro!"); textcolor(15);
				getch();
			}
			else
			{
				fseek(PtrCar, posCar, SEEK_SET);
				fread(&Car, sizeof(TpCarro), 1, PtrCar);
				
				gotoxy(3, 13); textcolor(13); printf("%c Carro: %s (R$ %.2f/dia)",175, Car.Modelo, Car.PrecoDia); textcolor(15);
				
				gotoxy(3, 14); textcolor(13); printf("%c Nova Quantidade de Dias: ",175); textcolor(15);
				scanf("%d", &Loc.QtdDias);
				
				Loc.ValorLoc = Loc.QtdDias * Car.PrecoDia;
				gotoxy(3, 16); printf("%c Novo Valor: R$ %.2f",175, Loc.ValorLoc); textcolor(15);
				
				fseek(PtrLoc, posLoc, SEEK_SET);
				fwrite(&Loc, sizeof(TpLocacao), 1, PtrLoc);
				
				gotoxy(3, 23); textcolor(2); printf("Locacao alterada com sucesso!"); textcolor(15);
				getch();
			}
		}
	}
	
	fclose(PtrLoc);
	fclose(PtrCar);
}

void EXCLocLogica(void) {
	TpLocacao Loc;
	char AuxCPF[15];
	int AuxCod, pos;
	char confirma;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(29, 2); textcolor(13); printf("EXCLUSAO LOGICA LOCACAO");
	
	gotoxy(3, 5); textcolor(13); printf("%c Digite o CPF da locacao: ",175); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	gotoxy(3, 6); textcolor(13); printf("%c Digite o Codigo do Carro: ",175);textcolor(15);
	scanf("%d", &AuxCod);
	
	pos = BuscaExaustivaLocacao(PtrLoc, AuxCPF, AuxCod);
	
	if(pos == -1) {
	 	gotoxy(3, 23);textcolor(12); printf("Locacao nao encontrada ou ja excluida!"); textcolor(15);
		getch();
	} else {
	 	fseek(PtrLoc, pos, SEEK_SET);
	 	fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
	 	gotoxy(3, 8);textcolor(13); printf("%c Dados Locacao",175); textcolor(14);
		gotoxy(3, 9); printf("%c Cliente: %s", 175,Loc.CPF);
	 	gotoxy(3, 10); printf("%c Carro: %d",175, Loc.CodCar);
		gotoxy(3, 11); printf("%c Valor: R$ %.2f",175, Loc.ValorLoc); textcolor(15);
	 	
	 	gotoxy(3, 13); printf("Tem certeza? (S/N): ");
	 	fflush(stdin);
	 	confirma = getche();
	 	
	 	if(toupper(confirma) == 'S') {
	 	 	Loc.Status = 0;
	 	 	
	 	 	fseek(PtrLoc, pos, SEEK_SET);
	 	 	fwrite(&Loc, sizeof(TpLocacao), 1, PtrLoc);
	 	 	gotoxy(3, 23); textcolor(10); printf("Locacao excluida!"); textcolor(15);
			getch();
	 	} else {
	 	 	gotoxy(3, 23); textcolor(12); printf("Exclusao cancelada."); textcolor(15);
			getch();
	 	}
	}
	fclose(PtrLoc);
}

void RELALoc(void){
	TpLocacao Loc;
	int Linha = 6;
	int Cont = 0;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");

	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(30, 2); textcolor(13); printf("RELATORIO DE LOCACOES"); 
	
	fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	while(!feof(PtrLoc))
	{
	 	if(Loc.Status == 1)
	 	{
			Cont++;
			if(Linha > 20)
			{
				gotoxy(25, 24);  textcolor(7); printf("Pressione ENTER para continuar..."); textcolor(13);
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				Linha = 6;
			}
			gotoxy(3, Linha++); printf("%c CPF: %s",175, Loc.CPF);
			gotoxy(3, Linha++); printf("%c Codigo Carro: %d",175,Loc.CodCar);
			gotoxy(3, Linha++); printf("%c Quantidade dias: %d",175,Loc.QtdDias);
			gotoxy(3, Linha++); printf("%c Valor Locacao: R$ %.2f",175,Loc.ValorLoc);
			gotoxy(3, Linha++); printf("                                     ");
			gotoxy(3, Linha++); printf("---------------------------------------");
	 	}
		fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	}
	
	fclose(PtrLoc);
	
	if(Cont == 0)
	{
		gotoxy(3, 6); textcolor(12); printf("Nenhuma locacao ativa cadastrada."); textcolor(15);
	}
	
	gotoxy(24, 24); textcolor(2);printf("Fim do Relatorio. Pressione ENTER.");textcolor(15);
	getch();
}


// ----- RELAT�RIOS -----

void RelatorioClientesMais3Locacoes()
{
	TpCliente Cliente;
	int Linha = 6;
	int ContLoc;
	int Achou = 0;
	
	FILE *PtrCli = fopen("Clientes.dat", "rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(24, 2); textcolor(14); printf("CLIENTES COM MAIS DE 3 LOCACOES");
	
	fread(&Cliente,sizeof(TpCliente),1,PtrCli);
	while(!feof(PtrCli)){
		
		if(Cliente.Status == 1){
			ContLoc = ContarLocacoesCliente(Cliente.CPF);
			if(ContLoc > 3)
			{
				Achou = 1;
				if(Linha > 20)
				{
					gotoxy(25, 24); printf("Pressione ENTER para continuar...");
					getch();
					LimpaJanela(1, 2, 80, 25, 0);
					Linha = 6;
				}
				gotoxy(3, Linha++); printf("CPF: %s",Cliente.CPF);
				gotoxy(3, Linha++); printf("Nome: %s",Cliente.Nome);
				gotoxy(3, Linha++); printf("Telefone: %s",Cliente.Telefone);
				gotoxy(3, Linha++); printf("Total de Locacoes: %d",ContLoc);
				gotoxy(3, Linha++); printf("---------------------------------------");
			}
		}	
		fread(&Cliente,sizeof(TpCliente),1,PtrCli);
	}
	fclose(PtrCli);
	
	if(Achou == 0)
	{
		gotoxy(3, 6); printf("Nenhum cliente encontrado com mais de 3 locacoes.");
	}
	
	gotoxy(25, 24); printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}

void RelatorioCarrosPorCategoria()
{
	TpCarro Carro;
	char Categoria[30];
	int Linha = 8;
	int Achou = 0;
	
	FILE *PtrCarro = fopen("Carros.dat","rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(28, 2); textcolor(14); printf("RELATORIO POR CATEGORIA");
	
	gotoxy(3, 5); textcolor(15); printf("Digite a Categoria a buscar: ");
	fflush(stdin);
	gets(Categoria);
	
	LimpaJanela(1, 2, 80, 25, 0);
	gotoxy(28, 2); textcolor(14); printf("RELATORIO POR CATEGORIA: %s", Categoria);
	
	fread(&Carro, sizeof(TpCarro),1,PtrCarro);
	while(!feof(PtrCarro)){
		if(Carro.Status == 1 && stricmp(Carro.Categoria, Categoria) == 0) {
			Achou = 1;
			if(Linha > 20)
			{
				gotoxy(25, 24); printf("Pressione ENTER para continuar...");
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(28, 2); textcolor(14); printf("RELATORIO POR CATEGORIA: %s", Categoria);
				Linha = 6;
			}
	 	 	gotoxy(3, Linha++); printf("CODIGO: %d",Carro.CodCar);
			gotoxy(3, Linha++); printf("MODELO: %s",Carro.Modelo);
			gotoxy(3, Linha++); printf("CATEGORIA: %s",Carro.Categoria);
			gotoxy(3, Linha++); printf("PRECO DIARIA: R$ %.2f",Carro.PrecoDia);
			gotoxy(3, Linha++); printf("---------------------------------------");
	 	}
		fread(&Carro, sizeof(TpCarro),1,PtrCarro);
	}
	fclose(PtrCarro);
	
	if(Achou == 0)
	{
		gotoxy(3, 6); printf("Nenhum carro encontrado para esta categoria.");
	}
	
	gotoxy(25, 24); printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}

void RelatorioLocacoesAcimaValor()
{
	TpLocacao Loc;
	float ValorLimite;
	int Linha = 8;
	int Achou = 0;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");

	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(26, 2); textcolor(14); printf("LOCACOES COM VALOR ACIMA DE");
	
	gotoxy(3, 5); textcolor(15); printf("Digite o Valor minimo: R$ ");
	scanf("%f", &ValorLimite);
	
	LimpaJanela(1, 2, 80, 25, 0);
	gotoxy(26, 2); textcolor(14); printf("LOCACOES COM VALOR ACIMA DE R$ %.2f", ValorLimite);

	fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	while(!feof(PtrLoc))
	{
	 	if(Loc.Status == 1 && Loc.ValorLoc > ValorLimite)
	 	{
			Achou = 1;
			if(Linha > 20)
			{
				gotoxy(25, 24); printf("Pressione ENTER para continuar...");
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(26, 2); textcolor(14); printf("LOCACOES COM VALOR ACIMA DE R$ %.2f", ValorLimite);
				Linha = 6;
			}
			gotoxy(3, Linha++); printf("CPF: %s",Loc.CPF);
			gotoxy(3, Linha++); printf("Codigo Carro: %d",Loc.CodCar);
			gotoxy(3, Linha++); printf("Quantidade dias: %d",Loc.QtdDias);
			gotoxy(3, Linha++); printf("Valor Locacao: R$ %.2f",Loc.ValorLoc);
			gotoxy(3, Linha++); printf("---------------------------------------");
	 	}
		fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	}
	fclose(PtrLoc);
	
	if(Achou == 0)
	{
		gotoxy(3, 6); printf("Nenhuma locacao encontrada acima deste valor.");
	}
	
	gotoxy(25, 24); printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}

void RelatorioCompletoCliente()
{
	char AuxCPF[15];
	TpCliente Cliente;
	TpLocacao Loc;
	TpCarro Carro;
	int posCli, Linha, AchouLoc = 0;
	
	FILE *PtrCli = fopen("Clientes.dat", "rb");
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");
	FILE *PtrCar = fopen("Carros.dat", "rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(26, 2); textcolor(14); printf("RELATORIO COMPLETO POR CLIENTE");
	
	gotoxy(3, 5); textcolor(15); printf("Digite o CPF do Cliente: ");
	fflush(stdin);
	gets(AuxCPF);
	
	posCli = BuscaExaustivaCliente(PtrCli, AuxCPF);
	
	if(posCli == -1)
	{
		gotoxy(3, 23); printf("Cliente nao encontrado ou inativo!");
		getch();
	}
	else
	{
		LimpaJanela(1, 2, 80, 25, 0);
		gotoxy(26, 2); textcolor(14); printf("RELATORIO COMPLETO POR CLIENTE");
		
		fseek(PtrCli, posCli, SEEK_SET);
		fread(&Cliente, sizeof(TpCliente), 1, PtrCli);
		
		Linha = 5;
		gotoxy(3, Linha++); printf("Cliente: %s", Cliente.Nome);
		gotoxy(3, Linha++); printf("Telefone: %s", Cliente.Telefone);
		gotoxy(3, Linha++); printf("---------------------------------------");
		
		rewind(PtrLoc);
		fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
		while(!feof(PtrLoc))
		{
			if(Loc.Status == 1 && strcmp(Loc.CPF, AuxCPF) == 0)
			{
				AchouLoc = 1;
				if(Linha > 20)
				{
					gotoxy(25, 24); printf("Pressione ENTER para continuar...");
					getch();
					LimpaJanela(1, 2, 80, 25, 0);
					gotoxy(26, 2); textcolor(14); printf("RELATORIO COMPLETO POR CLIENTE");
					Linha = 5;
				}
				
				gotoxy(3, Linha++); printf("Locacao - Dias: %d - Valor: R$ %.2f", Loc.QtdDias, Loc.ValorLoc);
				
				int posCar = BuscaExaustivaCarro(PtrCar, Loc.CodCar);
				if(posCar != -1)
				{
					fseek(PtrCar, posCar, SEEK_SET);
					fread(&Carro, sizeof(TpCarro), 1, PtrCar);
					gotoxy(3, Linha++); printf("Carro: %s (%s)", Carro.Modelo, Carro.Categoria);
				}
				else
				{
					gotoxy(5, Linha++); printf("Carro: [Cod %d Nao Encontrado]", Loc.CodCar);
				}
				gotoxy(3, Linha++); printf("---------------------------------------");
			}
			fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
		}
		
		if(AchouLoc == 0)
		{
			gotoxy(3, Linha++); printf("Nenhuma locacao ativa encontrada para este cliente.");
		}
	}
	
	fclose(PtrCli);
	fclose(PtrLoc);
	fclose(PtrCar);
	gotoxy(25, 24); printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}


// ----- FUN��ES - ORGANIZA��O DE ARQUIVOS -----

void ExclusaoFisicaClientes()
{
	FILE *PtrArq = fopen("Clientes.dat", "rb");
	FILE *PtrTemp = fopen("TempCli.dat", "wb");
	TpCliente Cliente;
	int Cont = 0;
	
	fread(&Cliente, sizeof(TpCliente), 1, PtrArq);
	while(!feof(PtrArq))
	{
		if(Cliente.Status == 1)
		{
			fwrite(&Cliente, sizeof(TpCliente), 1, PtrTemp);
			Cont++;
		}
		fread(&Cliente, sizeof(TpCliente), 1, PtrArq);
	}
	
	fclose(PtrArq);
	fclose(PtrTemp);
	
	remove("Clientes.dat");
	rename("TempCli.dat", "Clientes.dat");
	
	gotoxy(3, 23);printf("Exclusao Fisica de Clientes Concluida! %d registros mantidos.", Cont);
	getch();
}

void ExclusaoFisicaCarros()
{
	FILE *PtrArq = fopen("Carros.dat", "rb");
	FILE *PtrTemp = fopen("TempCar.dat", "wb");
	TpCarro Carro;
	int Cont = 0;
	
	fread(&Carro, sizeof(TpCarro), 1, PtrArq);
	while(!feof(PtrArq))
	{
		if(Carro.Status == 1)
		{
			fwrite(&Carro, sizeof(TpCarro), 1, PtrTemp);
			Cont++;
		}
		fread(&Carro, sizeof(TpCarro), 1, PtrArq);
	}
	
	fclose(PtrArq);
	fclose(PtrTemp);
	
	remove("Carros.dat");
	rename("TempCar.dat", "Carros.dat");
	
	gotoxy(3, 23); printf("Exclusao Fisica de Carros Concluida! %d registros mantidos.", Cont);
	getch();
}

void ExclusaoFisicaLocacoes()
{
	FILE *PtrArq = fopen("Locacoes.dat", "rb");
	FILE *PtrTemp = fopen("TempLoc.dat", "wb");
	TpLocacao Loc;
	int Cont = 0;
	
	fread(&Loc, sizeof(TpLocacao), 1, PtrArq);
	while(!feof(PtrArq))
	{
		if(Loc.Status == 1)
		{
			fwrite(&Loc, sizeof(TpLocacao), 1, PtrTemp);
			Cont++;
		}
		fread(&Loc, sizeof(TpLocacao), 1, PtrArq);
	}
	
	fclose(PtrArq);
	fclose(PtrTemp);
	
	remove("Locacoes.dat");
	rename("TempLoc.dat", "Locacoes.dat");
	
	gotoxy(3, 23); 	printf("Exclusao Fisica de Locacoes Concluida! %d registros mantidos.", Cont);
	getch();
}


// ----- MENUS -----

char MenuPrincipal()
{
	Moldura(1, 1, 80, 25, 15, 0);
	Moldura(25, 2, 55, 4, 14, 0);
	gotoxy(30, 3); textcolor(15); printf("  LOCADORA DE CARROS");
	
	textbackground(0);
	textcolor(7);
	
	gotoxy(28, 7); printf("[ 1 ] Gerenciar Cadastros");
	gotoxy(28, 9); printf("[ 2 ] Relatorios Especiais");
	gotoxy(28, 11); printf("[ 3 ] Organizar Arquivos");
	
	gotoxy(28, 15); printf("[ESC] Sair do Programa");
	
	gotoxy(28, 18); printf("Escolha uma opcao: ");
	
	return getche();
}

char MenuCadastros()
{
	Moldura(1, 1, 80, 25, 15, 0);
	Moldura(25, 2, 55, 4, 14, 0);
	gotoxy(30, 3); textcolor(15); printf("  GERENCIAR CADASTROS");
	
	textbackground(0);
	textcolor(7);
	
	// Clientes
	gotoxy(5, 7); textcolor(11); printf("--- CLIENTES ---");
	gotoxy(5, 9); textcolor(7); printf("[A] Cadastrar Cliente");
	gotoxy(5, 10); printf("[B] Alterar Cliente");
	gotoxy(5, 11); printf("[C] Excluir Cliente");
	gotoxy(5, 12); printf("[D] Relatorio Clientes");
	
	// Carros
	gotoxy(30, 7); textcolor(10); printf("--- CARROS ---");
	gotoxy(30, 9); textcolor(7); printf("[E] Cadastrar Carro");
	gotoxy(30, 10); printf("[F] Alterar Carro");
	gotoxy(30, 11); printf("[G] Excluir Carro");
	gotoxy(30, 12); printf("[H] Relatorio Carros");
	
	// Loca��es
	gotoxy(55, 7); textcolor(13); printf("--- LOCACOES ---");
	gotoxy(55, 9); textcolor(7); printf("[I] Cadastrar Locacao");
	gotoxy(55, 10); printf("[J] Alterar Locacao");
	gotoxy(55, 11); printf("[K] Excluir Locacao");
	gotoxy(55, 12); printf("[L] Relatorio Locacoes");
	
	gotoxy(3, 20); printf("[ESC] Voltar ao Menu Principal");
	
	gotoxy(3, 22); printf("Escolha uma opcao: ");
	
	return getche();
}

char MenuRelatorios()
{
	Moldura(1, 1, 80, 25, 15, 0);
	Moldura(25, 2, 55, 4, 14, 0);
	gotoxy(30, 3); textcolor(15); printf("RELATORIOS ESPECIAIS");
	
	textbackground(0);
	textcolor(7);
	
	gotoxy(20, 8); printf("[1] Listar Clientes com mais de 3 Locacoes");
	gotoxy(20, 10); printf("[2] Listar Carros por Categoria");
	gotoxy(20, 12); printf("[3] Listar Locacoes Acima de um Valor");
	gotoxy(20, 14); printf("[4] Relatorio Completo por Cliente");
	
	gotoxy(20, 18); printf("[ESC] Voltar ao Menu Principal");
	
	gotoxy(20, 20); printf("Escolha uma opcao: ");
	
	return getche();
}

char MenuOrganizacao()
{
	Moldura(1, 1, 80, 25, 15, 0);
	Moldura(25, 2, 55, 4, 14, 0);
	gotoxy(30, 3); textcolor(15); printf("ORGANIZAR ARQUIVOS");
	
	textbackground(0);
	textcolor(7);
	
	gotoxy(5, 7); textcolor(11); printf("--- ORDENACAO ---");
	gotoxy(5, 9); textcolor(7); printf("[1] Clientes por CPF (Insertion Sort)");
	gotoxy(5, 10); printf("[2] Carros por Codigo (Selection Sort)");
	gotoxy(5, 11); printf("[3] Carros por Modelo (Bubble Sort)");
	gotoxy(5, 12); printf("[0] Locacoes por CPF (Bubble Sort)");
	
	gotoxy(45, 7); textcolor(12); printf("--- EXCLUSAO FISICA ---");
	gotoxy(45, 9); textcolor(7); printf("[4] Limpar Clientes Inativos");
	gotoxy(45, 10); printf("[5] Limpar Carros Inativos");
	gotoxy(45, 11); printf("[6] Limpar Locacoes Inativas");

	

	
	gotoxy(3, 21); printf("[ESC] Voltar ao Menu Principal");
	
	gotoxy(3, 23); printf("Escolha uma opcao: ");
	
	return getche();
}

// ----- FUN��O PRINCIPAL -----
int main(void)
{
	char op, sub_op;
	char AuxCPF[15];
	int AuxCod;
	
	CriarArquivos();
	clrscr();
	
	op = ' ';
	while(op != 27)
	{
		clrscr();
		op = MenuPrincipal();
		
		switch(op)
		{
			case '1':
				sub_op = ' ';
				while(sub_op != 27)
				{
					clrscr();
					sub_op = MenuCadastros();
					switch(toupper(sub_op))
					{
						case 'A': CADCliente(); break;
						case 'B': ALTCliente(); break;
						case 'C': EXClienteLogica(); break;
						case 'D': RELACliente(); break;
						case 'E': CADCarro(); break;
						case 'F': ALTCarro(); break;
						case 'G': EXCarroLogica(); break;
						case 'H': RELACarro(); break;
						case 'I': CADLoc(); break;
						case 'J': ALTLoc(); break;
						case 'K': EXCLocLogica(); break;
						case 'L': RELALoc(); break;
					}
				}
				break;
			
			case '2':
				sub_op = ' ';
				while(sub_op != 27)
				{
					clrscr();
					sub_op = MenuRelatorios();
					switch(sub_op)
					{
						case '1': RelatorioClientesMais3Locacoes(); break;
						case '2': RelatorioCarrosPorCategoria(); break;
						case '3': RelatorioLocacoesAcimaValor(); break;
						case '4': RelatorioCompletoCliente(); break;
					}
				}
				break;
			
			case '3':
				sub_op = ' ';
				while(sub_op != 27)
				{
					clrscr();
					sub_op = MenuOrganizacao();
					switch(toupper(sub_op))
					{
						case '1': 
					
							InsertionSortClientesArquivo(); 
							gotoxy(3, 23); printf("Clientes ordenados por CPF!                 ");
							getch();
							break;
						case '2': 
						
							SelectionSortCarrosArquivo(); 
							gotoxy(3, 23); printf("Carros Ordenados!                 ");
							getch();
							break;
						case '3': 
					
							BubbleSortCarrosModeloArquivo(); 
							gotoxy(3, 23); printf("Carros ordenados por Modelo!                ");
							getch();
							break;
						case '4': ExclusaoFisicaClientes(); break;
						case '5': ExclusaoFisicaCarros(); break;
						case '6': ExclusaoFisicaLocacoes(); break;
						case '0': 
							gotoxy(3, 23); printf("Iniciando ordenacao de Locacoes. Aguarde...");
							BubbleSortLocacoesCPFArquivo(); 
							gotoxy(3, 23); printf("Locacoes ordenadas por CPF!                 ");
							getch();
							break;			
				
					}
				}
			break;
				
		}
	}
	
	clrscr();
	gotoxy(35, 12); textcolor(15); printf("Saindo...");
	getch();
	return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>

/*

---------Trabalho feito por-----------
262516217 - Gabriel Ribeiro de Souza
---------------------------------------
262516950 - Leonardo Yukio Kimura
---------------------------------------
262516314� - Luis Antonio Moreira Giolo
----------------------------------------

*/

// ----- TABELAS -----

struct TpCliente
{
	char CPF[15],Nome[120], Telefone[14] ;
	int Status;
};
		
struct TpCarro
{
	int CodCar,Status;
	char Modelo[30], Categoria[30];
	float PrecoDia;
};

struct TpLocacao{
	char CPF[15];
	int CodCar, QtdDias, Status;
	float ValorLoc;
};

// ----- INTERFACE -----
void Moldura(int CI, int LI, int CF, int LF, int CorBorda, int CorFundo);
void LimpaJanela(int CI, int LI, int CF, int LF, int CorFundo);


// ---- CRIAR ARQUIVOS ----

void CriarArquivos();

// ----- MENUS -----

char MenuPrincipal();
char MenuCadastros();
char MenuRelatorios();
char MenuOrganizacao();

// ----- BUSCAS -----

int BuscaExaustivaCliente(FILE *PtrArq, char auxCPF[15]);
int BuscaExaustivaCarro(FILE *PtrArq, int auxCod);
int BuscaExaustivaLocacao(FILE *PtrArq, char auxCPF[15], int auxCod);
int BuscaSentinelaCliente(char auxCPF[15]);
int BuscaSeqIndexCPF(char auxCPF[15]);
int BuscaBinariaCarro(int auxCod);
int BuscaBinariaLocacaoCPF(char auxCPF[15]);
int ContarLocacoesCliente(char auxCPF[15]);

// ----- ORDENA��O -----

void InsertionSortClientesArquivo();
void SelectionSortCarrosArquivo();
void BubbleSortCarrosModeloArquivo();
void BubbleSortLocacoesCPFArquivo();

// -----  CLIENTES -----
void CADCliente();

void ALTCliente();
void EXClienteLogica();
void RELACliente();

// ----- CARROS -----

void CADCarro();
void ALTCarro();
void EXCarroLogica();
void RELACarro();

// ----- LOCA��ES -----

void CADLoc();
void ALTLoc();
void EXCLocLogica();
void RELALoc();

// ----- RELAT�RIOS -----

void RelatorioClientesMais3Locacoes();
void RelatorioCarrosPorCategoria();
void RelatorioLocacoesAcimaValor();
void RelatorioCompletoCliente();

// ----- EXCLUS�ES F�SICAS -----
void ExclusaoFisicaClientes();
void ExclusaoFisicaCarros();
void ExclusaoFisicaLocacoes();


// -----MOLDURA -----
void Moldura(int CI, int LI, int CF, int LF, int CorBorda, int CorFundo)
{
	int i;
	textbackground(0);
	textcolor(CorBorda);
	
	gotoxy(CI,LI); printf("%c",201);
	gotoxy(CF,LI); printf("%c",187);
	gotoxy(CI,LF); printf("%c",200);
	gotoxy(CF,LF); printf("%c",188);
	
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI); printf("%c",205);
		gotoxy(i,LF); printf("%c",205);
	}
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i); printf("%c",186);
		gotoxy(CF,i); printf("%c",186);
	}
	
	textbackground(0);
	for(i=LI+1; i<LF; i++)
	{
		for(int j=CI+1; j<CF; j++)
		{
			gotoxy(j, i); printf(" ");
		}
	}
	textbackground(0);
	textcolor(7);
}

void LimpaJanela(int CI, int LI, int CF, int LF, int CorFundo)
{
	int i, j;
	for(i=LI+1; i<LF; i++)
	{
		for(j=CI+1; j<CF; j++)
		{
			gotoxy(j, i); printf(" ");
		}
	}
}

// ----- CRIAR ARQUIVOS -----

void CriarArquivos(){
	FILE *PtrArq;
	
	PtrArq = fopen("Clientes.dat", "ab");
	if(PtrArq != NULL) fclose(PtrArq);
	
	PtrArq = fopen("Carros.dat", "ab");
	if(PtrArq != NULL) fclose(PtrArq);
	
	PtrArq = fopen("Locacoes.dat", "ab");
	if(PtrArq != NULL) fclose(PtrArq);
}

// ----- BUSCAS -----

int BuscaExaustivaCliente(FILE *PtrArq, char auxCPF[15]) {
	TpCliente RC;
	int Pos = -1;
	int Achou = 0;
	
	rewind(PtrArq);
	fread(&RC, sizeof(TpCliente), 1, PtrArq);
	
	while(!feof(PtrArq) && Achou == 0)
	{
		if(strcmp(RC.CPF, auxCPF) == 0 && RC.Status == 1)
		{
			Pos = ftell(PtrArq) - sizeof(TpCliente);
			Achou = 1;
		}
		else
		{
			fread(&RC, sizeof(TpCliente), 1, PtrArq);
		}
	}
	
	return Pos;
}

int BuscaExaustivaCarro(FILE *PtrArq, int auxCod) {
	TpCarro RC;
	int Pos = -1, Achou = 0;
	
	rewind(PtrArq);
	fread(&RC, sizeof(TpCarro), 1, PtrArq);
	
	while(!feof(PtrArq) && Achou == 0) {
	 	if(RC.CodCar == auxCod && RC.Status == 1) {
	 	 	Pos = ftell(PtrArq) - sizeof(TpCarro);
			Achou = 1;
	 	}
		else
		{
	 		fread(&RC, sizeof(TpCarro), 1, PtrArq);
		}
	}
	return Pos;
}

int BuscaExaustivaLocacao(FILE *PtrArq, char auxCPF[15], int auxCod) {
	TpLocacao RL;
	int Pos = -1;
	int Achou = 0;
	
	rewind(PtrArq);
	fread(&RL, sizeof(TpLocacao), 1, PtrArq);
	
	while(!feof(PtrArq) && Achou == 0) {
	 	if(strcmp(RL.CPF, auxCPF) == 0 && RL.CodCar == auxCod && RL.Status == 1) {
	 	 	Pos = ftell(PtrArq) - sizeof(TpLocacao);
			Achou = 1;
	 	}
		else
		{
	 		fread(&RL, sizeof(TpLocacao), 1, PtrArq);
		}
	}
	return Pos;
}

int BuscaSentinelaCliente(char auxCPF[15]) {
	FILE *PtrArq;
	FILE *PtrSent;
	TpCliente RC;
	
	int ContRegistros = 0;
	int i = 0;
	int PosFinal = -1;

	PtrArq = fopen("Clientes.dat", "rb");
	PtrSent = fopen("TempSentinela.dat", "wb");

	fread(&RC, sizeof(TpCliente), 1, PtrArq);
	while (!feof(PtrArq)) {
	 	if (RC.Status == 1) {
	 	 	fwrite(&RC, sizeof(TpCliente), 1, PtrSent);
	 	 	ContRegistros++;
	 	}
	 	fread(&RC, sizeof(TpCliente), 1, PtrArq);
	}
	fclose(PtrArq);

	strcpy(RC.CPF, auxCPF);
	RC.Status = 1;
	strcpy(RC.Nome, "SENTINELA");
	strcpy(RC.Telefone, "SENTINELA");
	
	fwrite(&RC, sizeof(TpCliente), 1, PtrSent);
	fclose(PtrSent);

	PtrSent = fopen("TempSentinela.dat", "rb");
	
	rewind(PtrSent);
	fread(&RC, sizeof(TpCliente), 1, PtrSent);
	i = 1;

	while (strcmp(RC.CPF, auxCPF) != 0) {
	 	fread(&RC, sizeof(TpCliente), 1, PtrSent);
	 	i++;
	}
	
	if (i <= ContRegistros) {
	 	PosFinal = (i - 1) * sizeof(TpCliente);
	}

	fclose(PtrSent);

	remove("TempSentinela.dat");

	return PosFinal;
}

int BuscaSeqIndexCPF(FILE *Ptr, char auxCPF[15]){
	TpCliente RC;
	int Pos = -1;
	
	FILE *PtrArq = fopen("Clientes.dat", "rb");
	
	rewind(PtrArq);
	fread(&RC,sizeof(TpCliente),1,PtrArq);
	
	while(!feof(PtrArq) && strcmp(RC.CPF, auxCPF) < 0)
	{
		fread(&RC,sizeof(TpCliente),1,PtrArq);
	}
	
	if(!feof(PtrArq) && strcmp(RC.CPF, auxCPF) == 0 && RC.Status == 1)
	{
		Pos = ftell(PtrArq) - sizeof(TpCliente);
	}
	
	fclose(PtrArq);
	return Pos;	
}

int BuscaBinariaCarro(int auxCod){
	TpCarro RC;
	int inicio, meio, fim;
	int Achou = 0;
	int Pos = -1;
	
	FILE *PtrArq = fopen("Carros.dat", "rb");
	
	inicio = 0;
	fseek(PtrArq, 0, SEEK_END);
	fim = (ftell(PtrArq) / sizeof(TpCarro)) - 1;
	
	while (inicio <= fim && Achou == 0) {
	 	meio = (inicio + fim) / 2;

	 	fseek(PtrArq, meio * sizeof(TpCarro), SEEK_SET);
	 	fread(&RC, sizeof(TpCarro), 1, PtrArq);

	 	if (RC.CodCar == auxCod) {
	 	 	if(RC.Status == 1)
	 	 	{
	 	 	 	Achou = 1;
				Pos = meio * sizeof(TpCarro);
			}
			else
			{
				inicio = fim + 1;
			}
	 	} else if (RC.CodCar < auxCod) {
	 	 	inicio = meio + 1;
	 	} else {
	 	 	fim = meio - 1;
	 	}
	}
	
	fclose(PtrArq);
	return Pos;
}

int BuscaBinariaLocacaoCPF(char auxCPF[15]){
	TpLocacao RL;
	int inicio, meio, fim;
	int Achou = 0;
	int Pos = -1;
	int comp;
	
	FILE *PtrArq = fopen("Locacoes.dat", "rb");
	
	inicio = 0;
	fseek(PtrArq, 0, SEEK_END);
	fim = (ftell(PtrArq) / sizeof(TpLocacao)) - 1;
	
	while (inicio <= fim && Achou == 0) {
	 	meio = (inicio + fim) / 2;

	 	fseek(PtrArq, meio * sizeof(TpLocacao), SEEK_SET);
	 	fread(&RL, sizeof(TpLocacao), 1, PtrArq);

	 	if(RL.Status == 1)
	 	{
	 	 	comp = strcmp(RL.CPF, auxCPF);
	 	 	
	 	 	if (comp == 0) {
	 	 	 	Achou = 1;
	 	 	 	Pos = meio * sizeof(TpLocacao);
	 	 	} else if (comp < 0) { 
	 	 	 	inicio = meio + 1;
	 	 	} else { 
	 	 	 	fim = meio - 1;
	 	 	}
	 	}
	 	else
	 	{
	 	 	comp = strcmp(RL.CPF, auxCPF);
	 	 	if (comp < 0) {
	 	 	 	inicio = meio + 1;
	 	 	} else {
	 	 	 	fim = meio - 1;
	 	 	}
	 	}
	}
	
	fclose(PtrArq);
	return Pos;
}

int ContarLocacoesCliente(char auxCPF[15])
{
	TpLocacao Loc;
	int Cont = 0;
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");
	

	fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	while(!feof(PtrLoc))
	{
	 	if(Loc.Status == 1 && strcmp(Loc.CPF, auxCPF) == 0)
	 	{
			Cont++;
	 	}
		fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	}
	fclose(PtrLoc);
	return Cont;
}


// ----- ORDENA��O -----

void InsertionSortClientesArquivo()
{
	FILE *PtrArq = fopen("Clientes.dat", "rb+");

	int Tam;
	fseek(PtrArq, 0, SEEK_END);
	Tam = ftell(PtrArq) / sizeof(TpCliente);
	
	if (Tam <= 1)
	{
		fclose(PtrArq);
		return;
	}

	int i, j;
	TpCliente Aux, Rj;

	for (i = 1; i < Tam; i++)
	{
		fseek(PtrArq, i * sizeof(TpCliente), SEEK_SET);
		fread(&Aux, sizeof(TpCliente), 1, PtrArq);
		
		j = i - 1;

		fseek(PtrArq, j * sizeof(TpCliente), SEEK_SET);
		fread(&Rj, sizeof(TpCliente), 1, PtrArq);

		while (j >= 0 && strcmp(Aux.CPF, Rj.CPF) < 0)
		{
			fseek(PtrArq, (j + 1) * sizeof(TpCliente), SEEK_SET);
			fwrite(&Rj, sizeof(TpCliente), 1, PtrArq);
			
			j--;
			
			if (j >= 0)
			{
				fseek(PtrArq, j * sizeof(TpCliente), SEEK_SET);
				fread(&Rj, sizeof(TpCliente), 1, PtrArq);
			}
		}
		
		fseek(PtrArq, (j + 1) * sizeof(TpCliente), SEEK_SET);
		fwrite(&Aux, sizeof(TpCliente), 1, PtrArq);
	}

	fclose(PtrArq);
}

void SelectionSortCarrosArquivo()
{
	FILE *PtrArq = fopen("Carros.dat", "rb+");

	int Tam, i,j,min;
	TpCarro Ri, Rj, Rmin;
	fseek(PtrArq, 0, SEEK_END);
	Tam = ftell(PtrArq) / sizeof(TpCarro);

	if (Tam <= 1)
	{
		fclose(PtrArq);
		gotoxy(3, 23); printf("Ordenado.");
		getch();
		return;
	}


	for (i = 0; i < Tam - 1; i++)
	{
		min = i;
		
		fseek(PtrArq, min * sizeof(TpCarro), SEEK_SET);
		fread(&Rmin, sizeof(TpCarro), 1, PtrArq);

		for (j = i + 1; j < Tam; j++)
		{
			fseek(PtrArq, j * sizeof(TpCarro), SEEK_SET);
			fread(&Rj, sizeof(TpCarro), 1, PtrArq);

			if (Rj.CodCar < Rmin.CodCar)
			{
				min = j;
				Rmin = Rj;
			}
		}

		if (i != min)
		{
			fseek(PtrArq, i * sizeof(TpCarro), SEEK_SET);
			fread(&Ri, sizeof(TpCarro), 1, PtrArq);

			fseek(PtrArq, min * sizeof(TpCarro), SEEK_SET);
			fwrite(&Ri, sizeof(TpCarro), 1, PtrArq);
			
			fseek(PtrArq, i * sizeof(TpCarro), SEEK_SET);
			fwrite(&Rmin, sizeof(TpCarro), 1, PtrArq);
		}
	}

	fclose(PtrArq);
}

void BubbleSortCarrosModeloArquivo()
{
	FILE *PtrArq = fopen("Carros.dat", "rb+");

	TpCarro Rj, Rj1;
	int Tam, i,j, Trocou =1;
	fseek(PtrArq, 0, SEEK_END);
	Tam = ftell(PtrArq) / sizeof(TpCarro);

	if (Tam <= 1)
	{
		fclose(PtrArq);
		gotoxy(3, 23); printf("Nao e necessario ordenar (0 ou 1 carro).");
		getch();
		return;
	}


	for (i = 0; i < Tam - 1 && Trocou == 1; i++)
	{
		Trocou = 0;
		for (j = 0; j < Tam - 1 - i; j++)
		{
			fseek(PtrArq, j * sizeof(TpCarro), SEEK_SET);
			fread(&Rj, sizeof(TpCarro), 1, PtrArq);

			fseek(PtrArq, (j + 1) * sizeof(TpCarro), SEEK_SET);
			fread(&Rj1, sizeof(TpCarro), 1, PtrArq);
			
			if (stricmp(Rj.Modelo, Rj1.Modelo) > 0)
			{
				fseek(PtrArq, j * sizeof(TpCarro), SEEK_SET);
				fwrite(&Rj1, sizeof(TpCarro), 1, PtrArq);
				
				fseek(PtrArq, (j + 1) * sizeof(TpCarro), SEEK_SET);
				fwrite(&Rj, sizeof(TpCarro), 1, PtrArq);
				
				Trocou = 1;
			}
		}
	}
	
	fclose(PtrArq);
}

void BubbleSortLocacoesCPFArquivo()
{
	FILE *PtrArq = fopen("Locacoes.dat", "rb+");

	int Tam,i,j, Trocou = 1;
	TpLocacao Rj, Rj1;
	fseek(PtrArq, 0, SEEK_END);
	Tam = ftell(PtrArq) / sizeof(TpLocacao);

	if (Tam <= 1)
	{
		fclose(PtrArq);
		gotoxy(3, 23); printf("Nao e necessario ordenar (0 ou 1 locacao).");
		getch();
		return;
	}

	
	for (i = 0; i < Tam - 1 && Trocou == 1; i++)
	{
		Trocou = 0;
		for (j = 0; j < Tam - 1 - i; j++)
		{
			fseek(PtrArq, j * sizeof(TpLocacao), SEEK_SET);
			fread(&Rj, sizeof(TpLocacao), 1, PtrArq);

			fseek(PtrArq, (j + 1) * sizeof(TpLocacao), SEEK_SET);
			fread(&Rj1, sizeof(TpLocacao), 1, PtrArq);
			
			if (strcmp(Rj.CPF, Rj1.CPF) > 0)
			{
				fseek(PtrArq, j * sizeof(TpLocacao), SEEK_SET);
				fwrite(&Rj1, sizeof(TpLocacao), 1, PtrArq);
				
				fseek(PtrArq, (j + 1) * sizeof(TpLocacao), SEEK_SET);
				fwrite(&Rj, sizeof(TpLocacao), 1, PtrArq);
				
				Trocou = 1;
			}
		}
	}
	
	fclose(PtrArq);
}


// ----- CLIENTES -----

void CADCliente(void){
	TpCliente Cliente;
	int posCPF;
	char AuxCPF[15];
	char op = 'S';
	
	FILE *PtrArq = fopen("Clientes.dat", "ab+");

	while(toupper(op) == 'S')
	{
		Moldura(1, 1, 80, 25, 15, 0);
		gotoxy(30, 2); textcolor(9); printf("CADASTRO DE CLIENTES");
		
		LimpaJanela(1, 2, 80, 25, 0);
		gotoxy(3, 5); textcolor(9); printf("Digite o CPF (ENTER para Sair): "); textcolor(15);
		fflush(stdin);
		gets(AuxCPF);
		
		if(strcmp(AuxCPF, "") == 0)
		{
			op = 'N';
		}
		else
		{
			posCPF = BuscaExaustivaCliente(PtrArq,AuxCPF);
			
			if(posCPF == -1){
					strcpy(Cliente.CPF,AuxCPF);
					gotoxy(3, 7); textcolor(9); printf("%c Nome: ", 175); textcolor(15);
					fflush(stdin);
					gets(Cliente.Nome);
					gotoxy(3, 8); textcolor(9); printf("%c Telefone: ",175); textcolor(15);
					fflush(stdin);
					gets(Cliente.Telefone);
					Cliente.Status = 1;			
				
					fseek(PtrArq, 0, SEEK_END);
					fwrite(&Cliente,sizeof(TpCliente),1,PtrArq);
					
					fclose(PtrArq);
					InsertionSortClientesArquivo(); 
					PtrArq = fopen("Clientes.dat", "ab+");
					
					gotoxy(3, 23); textcolor(10); printf("Cliente cadastrado com sucesso!!");
					textcolor(15);
					getch();
				}
			else
			{
			 	gotoxy(3, 23); textcolor(12); printf("CPF ja cadastrado!");
			 	textcolor(15);
				getch();
			}
			
			if(toupper(op) == 'S')
			{
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(3, 5); printf("Deseja cadastrar outro? (S/N): ");
				op = getche();
			}
		}
	}
			
	fclose(PtrArq);
}

void ALTCliente(void) {
	TpCliente Cliente;
	char AuxCPF[15], NovoNome[120], NovoTel[14];
	int pos;
	
	FILE *PtrArq = fopen("Clientes.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(29, 2); textcolor(9); printf("ALTERACAO DE CLIENTES");
	
	gotoxy(3, 5); textcolor(9); printf("Digite o CPF do cliente a alterar: "); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	
	pos = BuscaSeqIndexCPF(PtrArq, AuxCPF);
		
	if(pos == -1) {
	 	gotoxy(3, 23);  textcolor(12); printf("Cliente nao encontrado ou inativo!"); textcolor(15); 
		getch();
	} else {
	 	fseek(PtrArq, pos, SEEK_SET);
	 	fread(&Cliente, sizeof(TpCliente), 1, PtrArq);
	 	
	 	gotoxy(3, 7); textcolor(9); printf("Dados Atuais:");
	 	gotoxy(3, 8);  textcolor(14);  printf("%c CPF: %s",175, Cliente.CPF); 
	 	gotoxy(3, 9); printf("%c Nome: %s", 175,Cliente.Nome);
	 	gotoxy(3, 10); printf("%c Telefone: %s", 175,Cliente.Telefone); textcolor(15);
	 	
	 	gotoxy(3, 13); printf("Digite os novos dados (ENTER para manter):");
	
		
	 	gotoxy(3, 15); textcolor(9); printf("%c Novo Nome: ",175); textcolor(15); 
	 	fflush(stdin);
	 	gets(NovoNome);
	 	
	 	gotoxy(3, 16); textcolor(9); printf("%c Novo Telefone: ",175); textcolor(15); 
	 	fflush(stdin);
	 	gets(NovoTel);
		
		if(strcmp(NovoNome, "") != 0)
			strcpy(Cliente.Nome, NovoNome);
			
		if(strcmp(NovoTel, "") != 0)
			strcpy(Cliente.Telefone, NovoTel);
	 	
	 	fseek(PtrArq, pos, SEEK_SET);
	 	fwrite(&Cliente, sizeof(TpCliente), 1, PtrArq);
	 	
	 	gotoxy(3, 23); textcolor(10); printf("Cliente alterado com sucesso!"); textcolor(15);
		getch();
	}
	
	fclose(PtrArq);
}

void EXClienteLogica(void) {
	TpCliente Cliente;
	char AuxCPF[15];
	int pos;
	char op;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");
	
	FILE *PtrArq = fopen("Clientes.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(29, 2); textcolor(9); printf("EXCLUIR CLIENTES");
	
	gotoxy(3, 5); textcolor(9); printf("Digite o CPF do cliente a excluir: "); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	
	pos = BuscaExaustivaCliente(PtrArq, AuxCPF);
	
	if(pos == -1) {
	 	gotoxy(3, 23); textcolor(12); printf("Cliente nao encontrado ou ja excluido!");
		getch();
	} else {
		
		int ContLoc = ContarLocacoesCliente(AuxCPF);
		
		if(ContLoc > 0)
		{
			gotoxy(3, 23); textcolor(12); printf("Cliente possui locacoes ativas e nao pode ser excluido!"); textcolor(15);
			getch();
		}
		else
		{
			fseek(PtrArq, pos, SEEK_SET);
			fread(&Cliente, sizeof(TpCliente), 1, PtrArq);
			
			gotoxy(3, 7); textcolor(9); printf("Dados do cliente:");
			gotoxy(3, 8); textcolor(14); printf("%c CPF: %s", 175,Cliente.CPF);
			gotoxy(3, 9); printf("%c Nome: %s",175, Cliente.Nome);
			gotoxy(3, 10);printf("%c Telefone: %s",175,Cliente.Telefone); textcolor(15);
			
			gotoxy(3, 12); printf("Tem certeza? (S/N): ");
			fflush(stdin);
			op = getche();
			
			if(toupper(op) == 'S') {
				Cliente.Status = 0;
				
				fseek(PtrArq, pos, SEEK_SET);
				fwrite(&Cliente, sizeof(TpCliente), 1, PtrArq);
				gotoxy(3, 23); textcolor(12); printf("Cliente excluido!"); textcolor(15);
				getch();
			} else {
				gotoxy(3, 23); textcolor(4); printf("Exclusao cancelada."); textcolor(15);
				getch();
			}
		}
	}
	fclose(PtrArq);
	fclose(PtrLoc);
}

void RELACliente(void){
	TpCliente Cliente;
	int Linha = 6;
	int Cont = 0;
	
	FILE *PtrArq = fopen("Clientes.dat", "rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(30, 2); textcolor(9); printf("RELATORIO DE CLIENTES"); textcolor(11);
	
	fread(&Cliente,sizeof(TpCliente),1,PtrArq);
	while(!feof(PtrArq)){
		
		if(Cliente.Status == 1){
			Cont++;
			if(Linha > 20)
			{
				gotoxy(25, 24); textcolor(7); printf("Pressione ENTER para continuar..."); textcolor(11);
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				Linha = 6;
			}
			gotoxy(3, Linha++); printf("%c CPF: %s",175, Cliente.CPF);
			gotoxy(3, Linha++); printf("%c Nome: %s",175, Cliente.Nome);
			gotoxy(3, Linha++); printf("%c Telefone: %s",175,Cliente.Telefone);
			gotoxy(3, Linha++); printf("                                      ");
			gotoxy(3, Linha++); printf("---------------------------------------");
		}	
		fread(&Cliente,sizeof(TpCliente),1,PtrArq);
	}
	fclose(PtrArq);
	
	if(Cont == 0)
	{
		gotoxy(3, 6); textcolor(12); printf("Nenhum cliente ativo cadastrado."); textcolor(15);
	}
	
	gotoxy(25, 24); textcolor(2); printf("Fim do Relatorio. Pressione ENTER.");  textcolor(15);
	getch();
}


// ----- CARROS -----

void CADCarro(){
	TpCarro Carro;
	int posCar;
	char op = 'S';
	
	FILE *PtrCarro = fopen("Carros.dat", "ab+");
	
	while(toupper(op) == 'S')
	{
		Moldura(1, 1, 80, 25, 15, 0);
		gotoxy(32, 2); textcolor(10); printf("CADASTRO DE CARROS");
		
		LimpaJanela(1, 2, 80, 25, 0);
		gotoxy(3, 5);  printf("Digite o CODIGO (0 para sair): "); textcolor(15);
		scanf("%d",&Carro.CodCar);
		
		if(Carro.CodCar == 0)
		{
			op = 'N';
		}
		else
		{
			posCar = BuscaExaustivaCarro(PtrCarro, Carro.CodCar);

			if(posCar == -1) {
				gotoxy(3, 7);textcolor(10); printf("%c Modelo: ",175); textcolor(15);
				fflush(stdin);
				gets(Carro.Modelo);
				
				gotoxy(3, 8);textcolor(10); printf("%c Categoria: ",175); textcolor(15);
				fflush(stdin);
				gets(Carro.Categoria);
				
				gotoxy(3, 9);textcolor(10); printf("Preco da Diaria: R$ "); textcolor(15);
				scanf("%f",&Carro.PrecoDia);
				
				Carro.Status = 1;
				
				fseek(PtrCarro, 0, SEEK_END);
				fwrite(&Carro, sizeof(TpCarro),1,PtrCarro);
				gotoxy(3, 23); textcolor(2); printf("Carro cadastrado com sucesso!"); textcolor(15);
				getch();
			} else {
				gotoxy(3, 23); textcolor(12); printf("Carro com este codigo ja existe!"); textcolor(15);
				getch();
			}
			
			if(toupper(op) == 'S')
			{
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(3, 5); printf("Deseja cadastrar outro? (S/N): ");
				op = getche();
			}
		}
	 }
	
	 fclose(PtrCarro);
}

void ALTCarro(void) {
	TpCarro Carro;
	int AuxCod, pos;
	char NovoMod[30], NovaCat[30];
	float NovoPreco = 0; 
	
	FILE *PtrArq = fopen("Carros.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(31, 2); textcolor(10); printf("ALTERACAO DE CARROS");
	
	gotoxy(3, 5); textcolor(10); printf("Digite o Codigo do carro a alterar: "); textcolor(15);
	scanf("%d", &AuxCod);
	
	pos = BuscaExaustivaCarro(PtrArq, AuxCod);
	
	if(pos == -1) {
	 	gotoxy(3, 23); printf("Carro nao encontrado ou inativo!");
		getch();
	} else {
	 	fseek(PtrArq, pos, SEEK_SET);
	 	fread(&Carro, sizeof(TpCarro), 1, PtrArq);
	 	
		gotoxy(3, 7); textcolor(10); printf("Dados Atuais:");
	 	gotoxy(3, 8);  textcolor(14); printf("%c Codigo: %d",175, Carro.CodCar);
	 	gotoxy(3, 9); printf("%c Modelo: %s",175, Carro.Modelo);
	 	gotoxy(3, 10); printf("%c Categoria: %s",175, Carro.Categoria);
	 	gotoxy(3, 11); printf("%c Preco/Dia: R$ %.2f",175,Carro.PrecoDia);
	 	
	 	gotoxy(3, 13); textcolor(15); printf("Digite os novos dados (ENTER para manter):");
		
	 	gotoxy(3, 15); textcolor(10);  printf("%c Novo Modelo: ",175); textcolor(15);
	 	fflush(stdin);
	 	gets(NovoMod);
	 	
	 	gotoxy(3, 16); textcolor(10); printf("%c Nova Categoria: ",175); textcolor(15);
	 	fflush(stdin);
	 	gets(NovaCat);
	 	
	 	gotoxy(3, 17); textcolor(10); printf("%c Novo Preco: R$ ",175); textcolor(15);
		scanf("%f", &NovoPreco);
		
		if(strcmp(NovoMod, "") != 0)
			strcpy(Carro.Modelo, NovoMod);
		
		if(strcmp(NovaCat, "") != 0)
			strcpy(Carro.Categoria, NovaCat);
			
		if(NovoPreco > 0)
		{
			Carro.PrecoDia = NovoPreco;
		}
	 	
	 	fseek(PtrArq, pos, SEEK_SET);
	 	fwrite(&Carro, sizeof(TpCarro), 1, PtrArq);
	 	
	 	gotoxy(3, 23); textcolor(2); printf("Carro alterado com sucesso!"); textcolor(15);
		getch();
	}
	
	fclose(PtrArq);
}

void EXCarroLogica(void) {
	TpCarro Carro;
	int AuxCod, pos;
	char confirma;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");
	
	FILE *PtrArq = fopen("Carros.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(30, 2); textcolor(10); printf("EXCLUIR CARROS");
	
	gotoxy(3, 5); textcolor(10); printf("Digite o Codigo do carro a excluir: "); textcolor(15);
	scanf("%d", &AuxCod);
	
	pos = BuscaExaustivaCarro(PtrArq, AuxCod);
	
	if(pos == -1) {
	 	gotoxy(3, 23); textcolor(12); printf("Carro nao encontrado ou ja excluido!"); textcolor(15);
		getch();
	} else {
		
		TpLocacao Loc;
		int AchouLoc = 0;
		rewind(PtrLoc);
		fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
		while(!feof(PtrLoc) && AchouLoc == 0)
		{
			if(Loc.CodCar == AuxCod && Loc.Status == 1)
			{
				AchouLoc = 1;
			}
			else
			{
				fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
			}
		}
		
		if(AchouLoc == 1)
		{
			gotoxy(3, 23);  textcolor(12);  printf("Carro esta em uma locacao ativa e nao pode ser excluido!");  textcolor(15); 
			getch();
		}
		else
		{
			fseek(PtrArq, pos, SEEK_SET);
			fread(&Carro, sizeof(TpCarro), 1, PtrArq);
			
			gotoxy(3, 7);  textcolor(10); printf("Dados do Carro:");textcolor(14);
			gotoxy(3, 8); printf("%c Codigo: %d", 175,Carro.CodCar);
			gotoxy(3, 9); printf("%c Modelo: %s",175,Carro.Modelo); 
			gotoxy(3, 10); printf("%c Preco Diaria: R$ %2.f",175,Carro.PrecoDia); textcolor(15);
			
			gotoxy(3, 12); printf("Tem certeza? (S/N): ");
			fflush(stdin);
			confirma = getche();
			
			if(toupper(confirma) == 'S') {
				Carro.Status = 0;
				
				fseek(PtrArq, pos, SEEK_SET);
				fwrite(&Carro, sizeof(TpCarro), 1, PtrArq);
				gotoxy(3, 23); textcolor(12); printf("Carro excluido "); textcolor(15);
				getch();
			} else {
				gotoxy(3, 23); textcolor(12); printf("Exclusao cancelada."); textcolor(15);
				getch();
			}
		}
	}
	fclose(PtrArq);
	fclose(PtrLoc);
}

void RELACarro(){
	TpCarro Carro;
	int Linha = 6;
	int Cont = 0;
	
	FILE *PtrCarro = fopen("Carros.dat","rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(31, 2); textcolor(10); printf("RELATORIO DE CARROS");

	fread(&Carro, sizeof(TpCarro),1,PtrCarro);
	while(!feof(PtrCarro)){
		if(Carro.Status == 1) {
			Cont++;
			if(Linha > 20)
			{
				gotoxy(25, 24); textcolor(7); printf("Pressione ENTER para continuar...");
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				Linha = 6;
			}
			textcolor(2);
	 	 	gotoxy(3, Linha++); printf("%c Codigo: %d",175,Carro.CodCar);
			gotoxy(3, Linha++); printf("%c Modelo: %s",175,Carro.Modelo);
			gotoxy(3, Linha++); printf("%c Categoria: %s",175,Carro.Categoria);
			gotoxy(3, Linha++); printf("%c Preco Diaria: R$ %.2f",175,Carro.PrecoDia);
			gotoxy(3, Linha++); printf("                                          ");
			gotoxy(3, Linha++); printf("---------------------------------------");
	 	}
		fread(&Carro, sizeof(TpCarro),1,PtrCarro);
	}
	fclose(PtrCarro);
	
	if(Cont == 0)
	{
		gotoxy(3, 6); textcolor(12); printf("Nenhum carro ativo cadastrado."); textcolor(15);
	}
	
	gotoxy(24, 24);  printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}


// -----  LOCA��ES -----

void CADLoc(void){
	TpCarro Car;
	TpLocacao Loc;
	int posCli, posCar;
	char Op = 'S';
	
	FILE *PtrCli = fopen("Clientes.dat", "rb");
	FILE *PtrCar = fopen("Carros.dat", "rb");
	FILE *PtrLoc = fopen("Locacoes.dat", "ab+");
	
	while(toupper(Op) == 'S')
	{
		Moldura(1, 1, 80, 25, 15, 0);
		gotoxy(30, 2); textcolor(13); printf("CADASTRO DE LOCACOES");
		
		LimpaJanela(1, 2, 80, 25, 0);
		gotoxy(3, 5);  printf("Digite o CPF do Cliente (ENTER p/ sair): "); textcolor(15);
		fflush(stdin);
		gets(Loc.CPF);
		
		if(strcmp(Loc.CPF, "") == 0)
		{
			Op = 'N';
		}
		else
		{
			posCli = BuscaExaustivaCliente(PtrCli, Loc.CPF);
			
			if(posCli == -1) {
				gotoxy(3, 23); textcolor(12); printf("Cliente nao encontrado ou inativo!"); textcolor(15);
				getch();
			}
			else {
				gotoxy(3, 7); textcolor(13); printf("%c Codigo do Carro: ",175); textcolor(15);
				scanf("%d", &Loc.CodCar);
				
				posCar = BuscaExaustivaCarro(PtrCar, Loc.CodCar);
				
				if(posCar == -1) {
					gotoxy(3, 23); textcolor(12); printf("Carro nao encontrado ou inativo!"); textcolor(15);
					getch();
				}
				else {
					int posLoc = BuscaExaustivaLocacao(PtrLoc, Loc.CPF, Loc.CodCar);
					
					if(posLoc != -1)
					{
						gotoxy(3, 23);textcolor(12); printf("Este cliente ja possui uma locacao ATIVA com este carro!"); textcolor(15);
						getch();
					}
					else
					{
						fseek(PtrCar, posCar, SEEK_SET);
						fread(&Car, sizeof(TpCarro), 1, PtrCar);
						
						gotoxy(3, 9); textcolor(10); printf("%c Carro: %s (R$ %.2f/dia)",175, Car.Modelo, Car.PrecoDia);
						
						gotoxy(3, 11); textcolor(13); printf("%c Quantidade de dias: ",175);textcolor(15);
						scanf("%d", &Loc.QtdDias); 	
			
						Loc.ValorLoc = Loc.QtdDias * Car.PrecoDia;
						Loc.Status = 1;
						
						fseek(PtrLoc, 0, SEEK_END);
						fwrite(&Loc, sizeof(TpLocacao), 1, PtrLoc);
						
						gotoxy(3, 13); printf("%c Valor Total: R$ %.2f",175, Loc.ValorLoc); 
						gotoxy(3, 23); textcolor(2); printf("%c Locacao registrada com sucesso!",175); textcolor(15);
						getch();
					}
				}
			}
			
			if(toupper(Op) == 'S')
			{
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(3, 5); printf("Deseja cadastrar outro? (S/N): ");
				Op = getche();
			}
		}
	}
	
	fclose(PtrCli);
	fclose(PtrCar);
	fclose(PtrLoc);
}

void ALTLoc(void){
	TpLocacao Loc;
	TpCarro Car;
	char AuxCPF[15];
	int AuxCod, posLoc, posCar, verif;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb+");
	FILE *PtrCar = fopen("Carros.dat", "rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(30, 2); textcolor(13); printf("ALTERACAO DE LOCACOES");
	
	gotoxy(3, 5); textcolor(13); printf("%c Digite o CPF da locacao: ",175); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	gotoxy(3, 6); textcolor(13); printf("%c Digite o Codigo do Carro: ",175); textcolor(15);
	scanf("%d", &AuxCod);
	
	posLoc = BuscaExaustivaLocacao(PtrLoc, AuxCPF, AuxCod);
	
	if(posLoc == -1) {
	 	gotoxy(3, 23); textcolor(12); printf("Locacao nao encontrada ou inativa!"); textcolor(15);
		getch();
	} else {
	 	fseek(PtrLoc, posLoc, SEEK_SET);
	 	fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
	 	
		gotoxy(3, 8); textcolor(10); printf("%c Dias Atuais: %d", 175,Loc.QtdDias); textcolor(15);
	 	gotoxy(3, 9); textcolor(10); printf("%c Valor Atual: R$ %.2f",175, Loc.ValorLoc); textcolor(13);
	 	
	 	gotoxy(3, 11); printf("%c Novo Codigo de Carro: ",175); textcolor(15);
		scanf("%d", &Loc.CodCar);
		
		posCar = BuscaExaustivaCarro(PtrCar, Loc.CodCar);
		
		if(posCar == -1)
		{
			gotoxy(3, 23); textcolor(12); printf("Novo carro nao encontrado! Alteracao cancelada."); textcolor(15);
			getch();
		}
		else
		{
			verif = BuscaExaustivaLocacao(PtrLoc, AuxCPF, Loc.CodCar);
			
			if(verif != -1 && verif != posLoc)
			{
				gotoxy(3, 23); textcolor(12); printf("Cliente ja possui locacao ativa com este carro!"); textcolor(15);
				getch();
			}
			else
			{
				fseek(PtrCar, posCar, SEEK_SET);
				fread(&Car, sizeof(TpCarro), 1, PtrCar);
				
				gotoxy(3, 13); textcolor(13); printf("%c Carro: %s (R$ %.2f/dia)",175, Car.Modelo, Car.PrecoDia); textcolor(15);
				
				gotoxy(3, 14); textcolor(13); printf("%c Nova Quantidade de Dias: ",175); textcolor(15);
				scanf("%d", &Loc.QtdDias);
				
				Loc.ValorLoc = Loc.QtdDias * Car.PrecoDia;
				gotoxy(3, 16); printf("%c Novo Valor: R$ %.2f",175, Loc.ValorLoc); textcolor(15);
				
				fseek(PtrLoc, posLoc, SEEK_SET);
				fwrite(&Loc, sizeof(TpLocacao), 1, PtrLoc);
				
				gotoxy(3, 23); textcolor(2); printf("Locacao alterada com sucesso!"); textcolor(15);
				getch();
			}
		}
	}
	
	fclose(PtrLoc);
	fclose(PtrCar);
}

void EXCLocLogica(void) {
	TpLocacao Loc;
	char AuxCPF[15];
	int AuxCod, pos;
	char confirma;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb+");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(29, 2); textcolor(13); printf("EXCLUSAO LOGICA LOCACAO");
	
	gotoxy(3, 5); textcolor(13); printf("%c Digite o CPF da locacao: ",175); textcolor(15);
	fflush(stdin);
	gets(AuxCPF);
	gotoxy(3, 6); textcolor(13); printf("%c Digite o Codigo do Carro: ",175);textcolor(15);
	scanf("%d", &AuxCod);
	
	pos = BuscaExaustivaLocacao(PtrLoc, AuxCPF, AuxCod);
	
	if(pos == -1) {
	 	gotoxy(3, 23);textcolor(12); printf("Locacao nao encontrada ou ja excluida!"); textcolor(15);
		getch();
	} else {
	 	fseek(PtrLoc, pos, SEEK_SET);
	 	fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
	 	gotoxy(3, 8);textcolor(13); printf("%c Dados Locacao",175); textcolor(14);
		gotoxy(3, 9); printf("%c Cliente: %s", 175,Loc.CPF);
	 	gotoxy(3, 10); printf("%c Carro: %d",175, Loc.CodCar);
		gotoxy(3, 11); printf("%c Valor: R$ %.2f",175, Loc.ValorLoc); textcolor(15);
	 	
	 	gotoxy(3, 13); printf("Tem certeza? (S/N): ");
	 	fflush(stdin);
	 	confirma = getche();
	 	
	 	if(toupper(confirma) == 'S') {
	 	 	Loc.Status = 0;
	 	 	
	 	 	fseek(PtrLoc, pos, SEEK_SET);
	 	 	fwrite(&Loc, sizeof(TpLocacao), 1, PtrLoc);
	 	 	gotoxy(3, 23); textcolor(10); printf("Locacao excluida!"); textcolor(15);
			getch();
	 	} else {
	 	 	gotoxy(3, 23); textcolor(12); printf("Exclusao cancelada."); textcolor(15);
			getch();
	 	}
	}
	fclose(PtrLoc);
}

void RELALoc(void){
	TpLocacao Loc;
	int Linha = 6;
	int Cont = 0;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");

	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(30, 2); textcolor(13); printf("RELATORIO DE LOCACOES"); 
	
	fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	while(!feof(PtrLoc))
	{
	 	if(Loc.Status == 1)
	 	{
			Cont++;
			if(Linha > 20)
			{
				gotoxy(25, 24);  textcolor(7); printf("Pressione ENTER para continuar..."); textcolor(13);
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				Linha = 6;
			}
			gotoxy(3, Linha++); printf("%c CPF: %s",175, Loc.CPF);
			gotoxy(3, Linha++); printf("%c Codigo Carro: %d",175,Loc.CodCar);
			gotoxy(3, Linha++); printf("%c Quantidade dias: %d",175,Loc.QtdDias);
			gotoxy(3, Linha++); printf("%c Valor Locacao: R$ %.2f",175,Loc.ValorLoc);
			gotoxy(3, Linha++); printf("                                     ");
			gotoxy(3, Linha++); printf("---------------------------------------");
	 	}
		fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	}
	
	fclose(PtrLoc);
	
	if(Cont == 0)
	{
		gotoxy(3, 6); textcolor(12); printf("Nenhuma locacao ativa cadastrada."); textcolor(15);
	}
	
	gotoxy(24, 24); textcolor(2);printf("Fim do Relatorio. Pressione ENTER.");textcolor(15);
	getch();
}


// ----- RELAT�RIOS -----

void RelatorioClientesMais3Locacoes()
{
	TpCliente Cliente;
	int Linha = 6;
	int ContLoc;
	int Achou = 0;
	
	FILE *PtrCli = fopen("Clientes.dat", "rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(24, 2); textcolor(14); printf("CLIENTES COM MAIS DE 3 LOCACOES");
	
	fread(&Cliente,sizeof(TpCliente),1,PtrCli);
	while(!feof(PtrCli)){
		
		if(Cliente.Status == 1){
			ContLoc = ContarLocacoesCliente(Cliente.CPF);
			if(ContLoc > 3)
			{
				Achou = 1;
				if(Linha > 20)
				{
					gotoxy(25, 24); printf("Pressione ENTER para continuar...");
					getch();
					LimpaJanela(1, 2, 80, 25, 0);
					Linha = 6;
				}
				gotoxy(3, Linha++); printf("CPF: %s",Cliente.CPF);
				gotoxy(3, Linha++); printf("Nome: %s",Cliente.Nome);
				gotoxy(3, Linha++); printf("Telefone: %s",Cliente.Telefone);
				gotoxy(3, Linha++); printf("Total de Locacoes: %d",ContLoc);
				gotoxy(3, Linha++); printf("---------------------------------------");
			}
		}	
		fread(&Cliente,sizeof(TpCliente),1,PtrCli);
	}
	fclose(PtrCli);
	
	if(Achou == 0)
	{
		gotoxy(3, 6); printf("Nenhum cliente encontrado com mais de 3 locacoes.");
	}
	
	gotoxy(25, 24); printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}

void RelatorioCarrosPorCategoria()
{
	TpCarro Carro;
	char Categoria[30];
	int Linha = 8;
	int Achou = 0;
	
	FILE *PtrCarro = fopen("Carros.dat","rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(28, 2); textcolor(14); printf("RELATORIO POR CATEGORIA");
	
	gotoxy(3, 5); textcolor(15); printf("Digite a Categoria a buscar: ");
	fflush(stdin);
	gets(Categoria);
	
	LimpaJanela(1, 2, 80, 25, 0);
	gotoxy(28, 2); textcolor(14); printf("RELATORIO POR CATEGORIA: %s", Categoria);
	
	fread(&Carro, sizeof(TpCarro),1,PtrCarro);
	while(!feof(PtrCarro)){
		if(Carro.Status == 1 && stricmp(Carro.Categoria, Categoria) == 0) {
			Achou = 1;
			if(Linha > 20)
			{
				gotoxy(25, 24); printf("Pressione ENTER para continuar...");
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(28, 2); textcolor(14); printf("RELATORIO POR CATEGORIA: %s", Categoria);
				Linha = 6;
			}
	 	 	gotoxy(3, Linha++); printf("CODIGO: %d",Carro.CodCar);
			gotoxy(3, Linha++); printf("MODELO: %s",Carro.Modelo);
			gotoxy(3, Linha++); printf("CATEGORIA: %s",Carro.Categoria);
			gotoxy(3, Linha++); printf("PRECO DIARIA: R$ %.2f",Carro.PrecoDia);
			gotoxy(3, Linha++); printf("---------------------------------------");
	 	}
		fread(&Carro, sizeof(TpCarro),1,PtrCarro);
	}
	fclose(PtrCarro);
	
	if(Achou == 0)
	{
		gotoxy(3, 6); printf("Nenhum carro encontrado para esta categoria.");
	}
	
	gotoxy(25, 24); printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}

void RelatorioLocacoesAcimaValor()
{
	TpLocacao Loc;
	float ValorLimite;
	int Linha = 8;
	int Achou = 0;
	
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");

	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(26, 2); textcolor(14); printf("LOCACOES COM VALOR ACIMA DE");
	
	gotoxy(3, 5); textcolor(15); printf("Digite o Valor minimo: R$ ");
	scanf("%f", &ValorLimite);
	
	LimpaJanela(1, 2, 80, 25, 0);
	gotoxy(26, 2); textcolor(14); printf("LOCACOES COM VALOR ACIMA DE R$ %.2f", ValorLimite);

	fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	while(!feof(PtrLoc))
	{
	 	if(Loc.Status == 1 && Loc.ValorLoc > ValorLimite)
	 	{
			Achou = 1;
			if(Linha > 20)
			{
				gotoxy(25, 24); printf("Pressione ENTER para continuar...");
				getch();
				LimpaJanela(1, 2, 80, 25, 0);
				gotoxy(26, 2); textcolor(14); printf("LOCACOES COM VALOR ACIMA DE R$ %.2f", ValorLimite);
				Linha = 6;
			}
			gotoxy(3, Linha++); printf("CPF: %s",Loc.CPF);
			gotoxy(3, Linha++); printf("Codigo Carro: %d",Loc.CodCar);
			gotoxy(3, Linha++); printf("Quantidade dias: %d",Loc.QtdDias);
			gotoxy(3, Linha++); printf("Valor Locacao: R$ %.2f",Loc.ValorLoc);
			gotoxy(3, Linha++); printf("---------------------------------------");
	 	}
		fread(&Loc,sizeof(TpLocacao),1,PtrLoc);
	}
	fclose(PtrLoc);
	
	if(Achou == 0)
	{
		gotoxy(3, 6); printf("Nenhuma locacao encontrada acima deste valor.");
	}
	
	gotoxy(25, 24); printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}

void RelatorioCompletoCliente()
{
	char AuxCPF[15];
	TpCliente Cliente;
	TpLocacao Loc;
	TpCarro Carro;
	int posCli, Linha, AchouLoc = 0;
	
	FILE *PtrCli = fopen("Clientes.dat", "rb");
	FILE *PtrLoc = fopen("Locacoes.dat", "rb");
	FILE *PtrCar = fopen("Carros.dat", "rb");
	
	Moldura(1, 1, 80, 25, 15, 0);
	gotoxy(26, 2); textcolor(14); printf("RELATORIO COMPLETO POR CLIENTE");
	
	gotoxy(3, 5); textcolor(15); printf("Digite o CPF do Cliente: ");
	fflush(stdin);
	gets(AuxCPF);
	
	posCli = BuscaExaustivaCliente(PtrCli, AuxCPF);
	
	if(posCli == -1)
	{
		gotoxy(3, 23); printf("Cliente nao encontrado ou inativo!");
		getch();
	}
	else
	{
		LimpaJanela(1, 2, 80, 25, 0);
		gotoxy(26, 2); textcolor(14); printf("RELATORIO COMPLETO POR CLIENTE");
		
		fseek(PtrCli, posCli, SEEK_SET);
		fread(&Cliente, sizeof(TpCliente), 1, PtrCli);
		
		Linha = 5;
		gotoxy(3, Linha++); printf("Cliente: %s", Cliente.Nome);
		gotoxy(3, Linha++); printf("Telefone: %s", Cliente.Telefone);
		gotoxy(3, Linha++); printf("---------------------------------------");
		
		rewind(PtrLoc);
		fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
		while(!feof(PtrLoc))
		{
			if(Loc.Status == 1 && strcmp(Loc.CPF, AuxCPF) == 0)
			{
				AchouLoc = 1;
				if(Linha > 20)
				{
					gotoxy(25, 24); printf("Pressione ENTER para continuar...");
					getch();
					LimpaJanela(1, 2, 80, 25, 0);
					gotoxy(26, 2); textcolor(14); printf("RELATORIO COMPLETO POR CLIENTE");
					Linha = 5;
				}
				
				gotoxy(3, Linha++); printf("Locacao - Dias: %d - Valor: R$ %.2f", Loc.QtdDias, Loc.ValorLoc);
				
				int posCar = BuscaExaustivaCarro(PtrCar, Loc.CodCar);
				if(posCar != -1)
				{
					fseek(PtrCar, posCar, SEEK_SET);
					fread(&Carro, sizeof(TpCarro), 1, PtrCar);
					gotoxy(3, Linha++); printf("Carro: %s (%s)", Carro.Modelo, Carro.Categoria);
				}
				else
				{
					gotoxy(5, Linha++); printf("Carro: [Cod %d Nao Encontrado]", Loc.CodCar);
				}
				gotoxy(3, Linha++); printf("---------------------------------------");
			}
			fread(&Loc, sizeof(TpLocacao), 1, PtrLoc);
		}
		
		if(AchouLoc == 0)
		{
			gotoxy(3, Linha++); printf("Nenhuma locacao ativa encontrada para este cliente.");
		}
	}
	
	fclose(PtrCli);
	fclose(PtrLoc);
	fclose(PtrCar);
	gotoxy(25, 24); printf("Fim do Relatorio. Pressione ENTER.");
	getch();
}


// ----- FUN��ES - ORGANIZA��O DE ARQUIVOS -----

void ExclusaoFisicaClientes()
{
	FILE *PtrArq = fopen("Clientes.dat", "rb");
	FILE *PtrTemp = fopen("TempCli.dat", "wb");
	TpCliente Cliente;
	int Cont = 0;
	
	fread(&Cliente, sizeof(TpCliente), 1, PtrArq);
	while(!feof(PtrArq))
	{
		if(Cliente.Status == 1)
		{
			fwrite(&Cliente, sizeof(TpCliente), 1, PtrTemp);
			Cont++;
		}
		fread(&Cliente, sizeof(TpCliente), 1, PtrArq);
	}
	
	fclose(PtrArq);
	fclose(PtrTemp);
	
	remove("Clientes.dat");
	rename("TempCli.dat", "Clientes.dat");
	
	gotoxy(3, 23);printf("Exclusao Fisica de Clientes Concluida! %d registros mantidos.", Cont);
	getch();
}

void ExclusaoFisicaCarros()
{
	FILE *PtrArq = fopen("Carros.dat", "rb");
	FILE *PtrTemp = fopen("TempCar.dat", "wb");
	TpCarro Carro;
	int Cont = 0;
	
	fread(&Carro, sizeof(TpCarro), 1, PtrArq);
	while(!feof(PtrArq))
	{
		if(Carro.Status == 1)
		{
			fwrite(&Carro, sizeof(TpCarro), 1, PtrTemp);
			Cont++;
		}
		fread(&Carro, sizeof(TpCarro), 1, PtrArq);
	}
	
	fclose(PtrArq);
	fclose(PtrTemp);
	
	remove("Carros.dat");
	rename("TempCar.dat", "Carros.dat");
	
	gotoxy(3, 23); printf("Exclusao Fisica de Carros Concluida! %d registros mantidos.", Cont);
	getch();
}

void ExclusaoFisicaLocacoes()
{
	FILE *PtrArq = fopen("Locacoes.dat", "rb");
	FILE *PtrTemp = fopen("TempLoc.dat", "wb");
	TpLocacao Loc;
	int Cont = 0;
	
	fread(&Loc, sizeof(TpLocacao), 1, PtrArq);
	while(!feof(PtrArq))
	{
		if(Loc.Status == 1)
		{
			fwrite(&Loc, sizeof(TpLocacao), 1, PtrTemp);
			Cont++;
		}
		fread(&Loc, sizeof(TpLocacao), 1, PtrArq);
	}
	
	fclose(PtrArq);
	fclose(PtrTemp);
	
	remove("Locacoes.dat");
	rename("TempLoc.dat", "Locacoes.dat");
	
	gotoxy(3, 23); 	printf("Exclusao Fisica de Locacoes Concluida! %d registros mantidos.", Cont);
	getch();
}


// ----- MENUS -----

char MenuPrincipal()
{
	Moldura(1, 1, 80, 25, 15, 0);
	Moldura(25, 2, 55, 4, 14, 0);
	gotoxy(30, 3); textcolor(15); printf("  LOCADORA DE CARROS");
	
	textbackground(0);
	textcolor(7);
	
	gotoxy(28, 7); printf("[ 1 ] Gerenciar Cadastros");
	gotoxy(28, 9); printf("[ 2 ] Relatorios Especiais");
	gotoxy(28, 11); printf("[ 3 ] Organizar Arquivos");
	
	gotoxy(28, 15); printf("[ESC] Sair do Programa");
	
	gotoxy(28, 18); printf("Escolha uma opcao: ");
	
	return getche();
}

char MenuCadastros()
{
	Moldura(1, 1, 80, 25, 15, 0);
	Moldura(25, 2, 55, 4, 14, 0);
	gotoxy(30, 3); textcolor(15); printf("  GERENCIAR CADASTROS");
	
	textbackground(0);
	textcolor(7);
	
	// Clientes
	gotoxy(5, 7); textcolor(11); printf("--- CLIENTES ---");
	gotoxy(5, 9); textcolor(7); printf("[A] Cadastrar Cliente");
	gotoxy(5, 10); printf("[B] Alterar Cliente");
	gotoxy(5, 11); printf("[C] Excluir Cliente");
	gotoxy(5, 12); printf("[D] Relatorio Clientes");
	
	// Carros
	gotoxy(30, 7); textcolor(10); printf("--- CARROS ---");
	gotoxy(30, 9); textcolor(7); printf("[E] Cadastrar Carro");
	gotoxy(30, 10); printf("[F] Alterar Carro");
	gotoxy(30, 11); printf("[G] Excluir Carro");
	gotoxy(30, 12); printf("[H] Relatorio Carros");
	
	// Loca��es
	gotoxy(55, 7); textcolor(13); printf("--- LOCACOES ---");
	gotoxy(55, 9); textcolor(7); printf("[I] Cadastrar Locacao");
	gotoxy(55, 10); printf("[J] Alterar Locacao");
	gotoxy(55, 11); printf("[K] Excluir Locacao");
	gotoxy(55, 12); printf("[L] Relatorio Locacoes");
	
	gotoxy(3, 20); printf("[ESC] Voltar ao Menu Principal");
	
	gotoxy(3, 22); printf("Escolha uma opcao: ");
	
	return getche();
}

char MenuRelatorios()
{
	Moldura(1, 1, 80, 25, 15, 0);
	Moldura(25, 2, 55, 4, 14, 0);
	gotoxy(30, 3); textcolor(15); printf("RELATORIOS ESPECIAIS");
	
	textbackground(0);
	textcolor(7);
	
	gotoxy(20, 8); printf("[1] Listar Clientes com mais de 3 Locacoes");
	gotoxy(20, 10); printf("[2] Listar Carros por Categoria");
	gotoxy(20, 12); printf("[3] Listar Locacoes Acima de um Valor");
	gotoxy(20, 14); printf("[4] Relatorio Completo por Cliente");
	
	gotoxy(20, 18); printf("[ESC] Voltar ao Menu Principal");
	
	gotoxy(20, 20); printf("Escolha uma opcao: ");
	
	return getche();
}

char MenuOrganizacao()
{
	Moldura(1, 1, 80, 25, 15, 0);
	Moldura(25, 2, 55, 4, 14, 0);
	gotoxy(30, 3); textcolor(15); printf("ORGANIZAR ARQUIVOS");
	
	textbackground(0);
	textcolor(7);
	
	gotoxy(5, 7); textcolor(11); printf("--- ORDENACAO ---");
	gotoxy(5, 9); textcolor(7); printf("[1] Clientes por CPF (Insertion Sort)");
	gotoxy(5, 10); printf("[2] Carros por Codigo (Selection Sort)");
	gotoxy(5, 11); printf("[3] Carros por Modelo (Bubble Sort)");
	gotoxy(5, 12); printf("[0] Locacoes por CPF (Bubble Sort)");
	
	gotoxy(45, 7); textcolor(12); printf("--- EXCLUSAO FISICA ---");
	gotoxy(45, 9); textcolor(7); printf("[4] Limpar Clientes Inativos");
	gotoxy(45, 10); printf("[5] Limpar Carros Inativos");
	gotoxy(45, 11); printf("[6] Limpar Locacoes Inativas");

	

	
	gotoxy(3, 21); printf("[ESC] Voltar ao Menu Principal");
	
	gotoxy(3, 23); printf("Escolha uma opcao: ");
	
	return getche();
}

// ----- FUN��O PRINCIPAL -----
int main(void)
{
	char op, sub_op;
	char AuxCPF[15];
	int AuxCod;
	
	CriarArquivos();
	clrscr();
	
	op = ' ';
	while(op != 27)
	{
		clrscr();
		op = MenuPrincipal();
		
		switch(op)
		{
			case '1':
				sub_op = ' ';
				while(sub_op != 27)
				{
					clrscr();
					sub_op = MenuCadastros();
					switch(toupper(sub_op))
					{
						case 'A': CADCliente(); break;
						case 'B': ALTCliente(); break;
						case 'C': EXClienteLogica(); break;
						case 'D': RELACliente(); break;
						case 'E': CADCarro(); break;
						case 'F': ALTCarro(); break;
						case 'G': EXCarroLogica(); break;
						case 'H': RELACarro(); break;
						case 'I': CADLoc(); break;
						case 'J': ALTLoc(); break;
						case 'K': EXCLocLogica(); break;
						case 'L': RELALoc(); break;
					}
				}
				break;
			
			case '2':
				sub_op = ' ';
				while(sub_op != 27)
				{
					clrscr();
					sub_op = MenuRelatorios();
					switch(sub_op)
					{
						case '1': RelatorioClientesMais3Locacoes(); break;
						case '2': RelatorioCarrosPorCategoria(); break;
						case '3': RelatorioLocacoesAcimaValor(); break;
						case '4': RelatorioCompletoCliente(); break;
					}
				}
				break;
			
			case '3':
				sub_op = ' ';
				while(sub_op != 27)
				{
					clrscr();
					sub_op = MenuOrganizacao();
					switch(toupper(sub_op))
					{
						case '1': 
					
							InsertionSortClientesArquivo(); 
							gotoxy(3, 23); printf("Clientes ordenados por CPF!                 ");
							getch();
							break;
						case '2': 
						
							SelectionSortCarrosArquivo(); 
							gotoxy(3, 23); printf("Carros Ordenados!                 ");
							getch();
							break;
						case '3': 
					
							BubbleSortCarrosModeloArquivo(); 
							gotoxy(3, 23); printf("Carros ordenados por Modelo!                ");
							getch();
							break;
						case '4': ExclusaoFisicaClientes(); break;
						case '5': ExclusaoFisicaCarros(); break;
						case '6': ExclusaoFisicaLocacoes(); break;
						case '0': 
							gotoxy(3, 23); printf("Iniciando ordenacao de Locacoes. Aguarde...");
							BubbleSortLocacoesCPFArquivo(); 
							gotoxy(3, 23); printf("Locacoes ordenadas por CPF!                 ");
							getch();
							break;			
				
					}
				}
			break;
				
		}
	}
	
	clrscr();
	gotoxy(35, 12); textcolor(15); printf("Saindo...");
	getch();
	return 0;
}
>>>>>>> ec4ef433c94451c8299f5c75978c02b7fdc56e6d
