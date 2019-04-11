#include <stdio.h>
#include <stdlib.h>

#define TAMANHOVETOR 12

int menu();
int FuncaoHashing(int num);
void InserirHash(struct Tabela* TabelaHash, int num, int pos);
void MostrarHash(struct Tabela* TabelaHash);
void RemoverHash(struct Tabela* TabelaHash, int num, int pos);

struct HashLista
{
	int chave;
	HashLista *prox;
};

struct Tabela
{
	int Tamanho;
	struct HashLista** ListaChave;
};

int main()
{
	int op, c, num, pos;
	Tabela* TabelaHash = (struct Tabela *)malloc(sizeof(struct Tabela));
	TabelaHash->Tamanho = TAMANHOVETOR;
	TabelaHash->ListaChave = (struct HashLista **)malloc(TAMANHOVETOR * sizeof(struct HashLista*));

	for (int i = 0; i < TAMANHOVETOR; i++)
		TabelaHash->ListaChave[i] = NULL;

	while (1)
	{
		op = menu();
		switch (op)
		{
		case 1: //inserir
			printf("Digite o numero desejado: ");
			scanf_s("%d", &num);
			while ((c = getchar()) != '\n' && c != EOF) {} // sempre limpe o buffer do teclado.
			pos = FuncaoHashing(num);
			printf("Inserindo na posicao %d da tabela...\n", pos);
			system("pause");
			InserirHash(TabelaHash, num, pos);
			break;
		case 2: //remover
			printf("Digite o numero a ser removido: ");
			scanf_s("%d", &num);
			while ((c = getchar()) != '\n' && c != EOF) {} // sempre limpe o buffer do teclado.
			pos = FuncaoHashing(num);
			printf("Removendo na posicao %d da tabela...\n", pos);
			system("pause");
			RemoverHash(TabelaHash, num, pos);
			break;
		case 3: //buscar

			break;
		case 4: //mostrar
			MostrarHash(TabelaHash);
			system("pause");
			break;
		case 5:
			return 0;
			break;
		default:
			printf("Invalido\n");
			break;
		}
	}
	return 0;
}

int menu() {
	int op, c;
	system("Cls");

	printf("1. Inserir na Hash\n");
	printf("2. Remover da Hash\n");
	printf("3. Buscar na Hash\n");
	printf("4. Mostrar a Hash\n");
	printf("5. Sair\n");
	printf("Digite sua escolha: ");

	scanf_s("%d", &op);
	while ((c = getchar()) != '\n' && c != EOF) {} // sempre limpe o buffer do teclado.

	system("Cls");
	return op;
}

int FuncaoHashing(int num)
{
	return (num % TAMANHOVETOR); //Método da Divisão
}

void InserirHash(struct Tabela* TabelaHash, int num, int pos)
{
	HashLista *NovoElemento;
	NovoElemento = (struct HashLista *)malloc(sizeof(struct HashLista));
	NovoElemento->chave = num;
	NovoElemento->prox = NULL;

	NovoElemento->prox = TabelaHash->ListaChave[pos];
	TabelaHash->ListaChave[pos] = NovoElemento;
}

void RemoverHash(struct Tabela* TabelaHash, int num, int pos)
{
	HashLista *ElementoVarredura;
	ElementoVarredura = (struct HashLista *)malloc(sizeof(struct HashLista));
	ElementoVarredura = TabelaHash->ListaChave[pos];

	HashLista *Auxiliar;
	Auxiliar = (struct HashLista *)malloc(sizeof(struct HashLista));

	if (TabelaHash->ListaChave[pos]->chave == num)
	{
		TabelaHash->ListaChave[pos] = TabelaHash->ListaChave[pos]->prox;
		free(ElementoVarredura);
	}
	else
	{
		while (ElementoVarredura->chave != num)
		{
			Auxiliar = ElementoVarredura; //Mantem o anterior
			ElementoVarredura = ElementoVarredura->prox;
		}	
		Auxiliar->prox = ElementoVarredura->prox;
		free(ElementoVarredura);
	}
}

void MostrarHash(struct Tabela* TabelaHash)
{
	int v;
	for (v = 0; v < TabelaHash->Tamanho; v++)
	{
		struct HashLista* ElementoVarredura = TabelaHash->ListaChave[v];
		printf("\n Lista de chaves por posicao %d:\n ", v);
		while (ElementoVarredura != NULL)
		{
			printf("%d -> ", ElementoVarredura->chave);
			ElementoVarredura = ElementoVarredura->prox;
		}
		printf("\n");
	}
}