<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>

/*
	Este programa cria os arquivos .dat com dados de exemplo
	para testar o sistema da Locadora.
*/

// ----- ESTRUTURAS (copiadas do seu código) -----
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

int main() {
	FILE *PtrArq;
	
	// ----- GERAR CLIENTES.DAT -----
	PtrArq = fopen("Clientes.dat", "wb"); 
	if(PtrArq == NULL) {
		printf("Erro ao criar Clientes.dat\n");
		return 1;
	}
	
	struct TpCliente Clientes[] = {
		{"111.111.111-11", "Ana Silva", "1111-1111", 1},
		{"333.333.333-33", "Carla Dias (4 Loc)", "3333-3333", 1}, 
		{"222.222.222-22", "Bruno Costa", "2222-2222", 1},
		{"555.555.555-55", "Elisa Fernandes", "5555-5555", 1},
		{"444.444.444-44", "Daniel Moreira (Inativo)", "4444-4444", 0} 
	};
	
	
	fwrite(Clientes, sizeof(struct TpCliente), 5, PtrArq);
	fclose(PtrArq);
	printf("Arquivo 'Clientes.dat' gerado com 5 registros.\n");

	// ----- GERAR CARROS.DAT -----
	PtrArq = fopen("Carros.dat", "wb");
	if(PtrArq == NULL) {
		printf("Erro ao criar Carros.dat\n");
		return 1;
	}
	
	struct TpCarro Carros[] = {
		{101, 1, "Gol", "Popular", 70.00},
		{201, 1, "Corolla", "Sedan", 150.00},
		{102, 1, "Mobi", "Popular", 65.00},
		{301, 0, "Uno (Inativo)", "Popular", 50.00}, 
		{202, 1, "Civic", "Sedan", 155.00}
	};
	
	fwrite(Carros, sizeof(struct TpCarro), 5, PtrArq);
	fclose(PtrArq);
	printf("Arquivo 'Carros.dat' gerado com 5 registros.\n");

	// ----- GERAR LOCACOES.DAT -----
	PtrArq = fopen("Locacoes.dat", "wb");
	if(PtrArq == NULL) {
		printf("Erro ao criar Locacoes.dat\n");
		return 1;
	}
	
	struct TpLocacao Locacoes[] = {
		{"333.333.333-33", 101, 3, 1, 210.00},
		{"333.333.333-33", 102, 5, 1, 325.00}, 
		{"333.333.333-33", 201, 2, 1, 300.00}, 
		{"333.333.333-33", 202, 1, 1, 155.00}, 
		
		{"111.111.111-11", 101, 7, 1, 490.00}, 
		{"222.222.222-22", 202, 3, 1, 465.00}, 
		{"111.111.111-11", 201, 1, 0, 150.00}  
	};
	
	fwrite(Locacoes, sizeof(struct TpLocacao), 7, PtrArq);
	fclose(PtrArq);
	printf("Arquivo 'Locacoes.dat' gerado com 7 registros.\n");

	printf("\nArquivos de teste gerados com sucesso!\n");
	printf("Pressione qualquer tecla para sair...\n");
	getch();
	
	return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>

/*
	Este programa cria os arquivos .dat com dados de exemplo
	para testar o sistema da Locadora.
*/

// ----- ESTRUTURAS (copiadas do seu código) -----
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

int main() {
	FILE *PtrArq;
	
	// ----- GERAR CLIENTES.DAT -----
	PtrArq = fopen("Clientes.dat", "wb"); 
	if(PtrArq == NULL) {
		printf("Erro ao criar Clientes.dat\n");
		return 1;
	}
	
	struct TpCliente Clientes[] = {
		{"111.111.111-11", "Ana Silva", "1111-1111", 1},
		{"333.333.333-33", "Carla Dias (4 Loc)", "3333-3333", 1}, 
		{"222.222.222-22", "Bruno Costa", "2222-2222", 1},
		{"555.555.555-55", "Elisa Fernandes", "5555-5555", 1},
		{"444.444.444-44", "Daniel Moreira (Inativo)", "4444-4444", 0} 
	};
	
	
	fwrite(Clientes, sizeof(struct TpCliente), 5, PtrArq);
	fclose(PtrArq);
	printf("Arquivo 'Clientes.dat' gerado com 5 registros.\n");

	// ----- GERAR CARROS.DAT -----
	PtrArq = fopen("Carros.dat", "wb");
	if(PtrArq == NULL) {
		printf("Erro ao criar Carros.dat\n");
		return 1;
	}
	
	struct TpCarro Carros[] = {
		{101, 1, "Gol", "Popular", 70.00},
		{201, 1, "Corolla", "Sedan", 150.00},
		{102, 1, "Mobi", "Popular", 65.00},
		{301, 0, "Uno (Inativo)", "Popular", 50.00}, 
		{202, 1, "Civic", "Sedan", 155.00}
	};
	
	fwrite(Carros, sizeof(struct TpCarro), 5, PtrArq);
	fclose(PtrArq);
	printf("Arquivo 'Carros.dat' gerado com 5 registros.\n");

	// ----- GERAR LOCACOES.DAT -----
	PtrArq = fopen("Locacoes.dat", "wb");
	if(PtrArq == NULL) {
		printf("Erro ao criar Locacoes.dat\n");
		return 1;
	}
	
	struct TpLocacao Locacoes[] = {
		{"333.333.333-33", 101, 3, 1, 210.00},
		{"333.333.333-33", 102, 5, 1, 325.00}, 
		{"333.333.333-33", 201, 2, 1, 300.00}, 
		{"333.333.333-33", 202, 1, 1, 155.00}, 
		
		{"111.111.111-11", 101, 7, 1, 490.00}, 
		{"222.222.222-22", 202, 3, 1, 465.00}, 
		{"111.111.111-11", 201, 1, 0, 150.00}  
	};
	
	fwrite(Locacoes, sizeof(struct TpLocacao), 7, PtrArq);
	fclose(PtrArq);
	printf("Arquivo 'Locacoes.dat' gerado com 7 registros.\n");

	printf("\nArquivos de teste gerados com sucesso!\n");
	printf("Pressione qualquer tecla para sair...\n");
	getch();
	
	return 0;
}
>>>>>>> ec4ef433c94451c8299f5c75978c02b7fdc56e6d
