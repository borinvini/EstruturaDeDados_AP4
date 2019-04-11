#include <stdio.h>
#include <stdlib.h>

#define NUMERO_VERTICES 6

struct ListaDeVizinhos
{
	int vertice;
	ListaDeVizinhos* prox;
};

struct Grafo
{
	int TotalVertices;
	struct ListaDeVizinhos** ListaAdj; //Será um vetor do tamanho do numero de vértices
};

struct STACK //Pilha dos vértices a serem visitados
{
	int vertice;
	STACK *prox;
}*top = NULL;

struct Grafo* CriarGrafo(int vertices);
void AdicionarAresta(struct Grafo* Grafo, int origem, int destino);
void MostrarGrafo(struct Grafo* Grafo);
void BuscaProfundidade(Grafo* Vizinhos, int v, int marcado[]);
void push(int y);
void pop();

int main()
{
	int marcado[NUMERO_VERTICES] = { 0 };
	int origem;

	Grafo* GrafoTeste = CriarGrafo(NUMERO_VERTICES);
	AdicionarAresta(GrafoTeste, 0, 1);
	AdicionarAresta(GrafoTeste, 0, 2);
	AdicionarAresta(GrafoTeste, 1, 3);
	AdicionarAresta(GrafoTeste, 2, 3);
	AdicionarAresta(GrafoTeste, 3, 4);
	AdicionarAresta(GrafoTeste, 3, 5);

	printf("Escolha um vertice para iniciar a busca:\n");
	scanf_s("%d", &origem);

	MostrarGrafo(GrafoTeste);

	printf("\nVertices visitados do grafo, iniciando em V%d:\n", origem);
	BuscaProfundidade(GrafoTeste, origem, marcado);

	printf("\n");
	system("pause");
	return 0;
}

struct Grafo* CriarGrafo(int TotalVertices)
{
	Grafo* Grafo = (struct Grafo *)malloc(sizeof(struct Grafo));
	Grafo->TotalVertices = TotalVertices;
	Grafo->ListaAdj = (struct ListaDeVizinhos **)malloc(TotalVertices * sizeof(struct ListaDeVizinhos*));

	for (int i = 0; i < TotalVertices; i++)
		Grafo->ListaAdj[i] = NULL;

	return Grafo;
}

void AdicionarAresta(struct Grafo* Grafo, int origem, int destino)
{ //INSERÇÃO NO INICIO DA LISTA 
  // Adiciona uma aresta da origem para o  destino
	struct ListaDeVizinhos* NovoElemento = (struct ListaDeVizinhos *)malloc(sizeof(struct ListaDeVizinhos));
	NovoElemento->vertice = destino;
	NovoElemento->prox = NULL;

	NovoElemento->prox = Grafo->ListaAdj[origem];
	Grafo->ListaAdj[origem] = NovoElemento;

	// Adiciona uma aresta do destino para a origem
	NovoElemento = (struct ListaDeVizinhos *)malloc(sizeof(struct ListaDeVizinhos));
	NovoElemento->vertice = origem;
	NovoElemento->prox = NULL;

	NovoElemento->prox = Grafo->ListaAdj[destino];
	Grafo->ListaAdj[destino] = NovoElemento;
}

void MostrarGrafo(struct Grafo* Grafo)
{
	int v;
	for (v = 0; v < Grafo->TotalVertices; v++)
	{
		struct ListaDeVizinhos* ElementoVarredura = Grafo->ListaAdj[v];
		printf("\n Lista de adjacencias do vertice %d:\n ", v);
		while (ElementoVarredura != NULL)
		{
			printf("%d -> ", ElementoVarredura->vertice);
			ElementoVarredura = ElementoVarredura->prox;
		}
		printf("\n");
	}
}

void BuscaProfundidade(Grafo* Vizinhos, int v, int marcado[])
{
	int w;
	ListaDeVizinhos *ElementoVarredura;
	ElementoVarredura = (struct ListaDeVizinhos *)malloc(sizeof(struct ListaDeVizinhos));

	marcado[v] = 1;
	printf("V%d\t", v);
	push(v); //empilha
	ElementoVarredura = Vizinhos->ListaAdj[v];
	//if (ElementoVarredura == NULL) {
	//	return;
	//}
	while (ElementoVarredura != NULL) {
		w = ElementoVarredura->vertice;
		if (marcado[w] != 1)
		{
			BuscaProfundidade(Vizinhos, w, marcado);
		}
		ElementoVarredura = ElementoVarredura->prox;
	}
	pop(); //desemilha
}

void push(int y) 
{ //função push, coloca um elemento na pilha

	STACK *NovoElemento;
	NovoElemento = (struct STACK *)malloc(sizeof(struct STACK));
	NovoElemento->vertice = y;

	if (top == NULL)
	{
		top = NovoElemento;
		top->prox = NULL;
	}
	else
	{
		NovoElemento->prox = top;
		top = NovoElemento;
	}
}

void pop()
{ //função pop, remove um elemento na pilha

	STACK *NovoElemento;
	NovoElemento = (struct STACK *)malloc(sizeof(struct STACK));

	if (top == NULL)
	{
		//top = NovoElemento;
		//top->prox = NULL;
	}
	else
	{
		NovoElemento = top; 
		top = top->prox;
		free(NovoElemento);
	}
}