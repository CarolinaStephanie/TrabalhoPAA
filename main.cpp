#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#define vertice int
#define MAXTAM 1000
#define INFINITY 999999

typedef struct TipoFila
{
    int Item[MAXTAM];
    int Tamanho;
    int Frente, Tras;
};

typedef struct
{
    vertice v, w;
    int c;
} edge;

struct graph
{
    int V;
    int A;
    int **adj;
};

static edge EDGE(vertice v, vertice w, int c)
{
    edge e;
    e.v = v, e.w = w;
    e.c = c;
    return e;
}

typedef struct graph *Graph;

int **alocarMatriz(int r, int c, int val)
{
    int **m = (int **)malloc(r * sizeof(int *));
    for (vertice i = 0; i < r; ++i)
        m[i] = (int *)malloc(c * sizeof(int));
    for (vertice i = 0; i < r; ++i)
        for (vertice j = 0; j < c; ++j)
            m[i][j] = val;
    return m;
}

void **LiberarMatriz(int r, float **m)
{

    for (int i = 0; i < r; i++)
        free(m[i]);
    free(m);
}

Graph iniciarGrafo(int V)
{
    Graph G = (graph *)malloc(sizeof(graph));
    G->V = V;
    G->A = 0;
    G->adj = alocarMatriz(V, V, 0);
    return G;
}

void inserirAresta(Graph G, vertice v, vertice w)
{
    if (G->adj[v][w] == 0)
    {
        G->adj[v][w] = 1;
        G->A++;
    }
}

void inserirArestaVal(Graph G, vertice v, vertice w, int val)
{
    if (G->adj[v][w] == 0)
    {
        G->adj[v][w] = val;
        G->A++;
    }
}

void removerAresta(Graph G, vertice v, vertice w)
{
    if (G->adj[v][w] >= 1)
    {
        G->adj[v][w] = 0;
        G->A--;
    }
}

void imprimirGrafo(Graph G)
{
    for (vertice v = 0; v < G->V; ++v)
    {
        printf("%2d ->", v);
        for (vertice w = 0; w < G->V; ++w)
            if (G->adj[v][w] >= 1)
                printf(" %2d(%d)", w, G->adj[v][w]);
        printf("\n");
    }
}

vertice verticeAleatorio(Graph G)
{
    double r;
    r = rand() / (RAND_MAX + 1.0);
    return r * G->V;
}

// Constroi um grafo aleatorio de 0 a V-1 vertices e com A arestas.
Graph gerarGrafoAleatorio(int V, int A)
{
    Graph G = iniciarGrafo(V);
    while (G->A < A)
    {
        vertice v = verticeAleatorio(G);
        vertice w = verticeAleatorio(G);
        if (v != w)
            inserirAresta(G, v, w);
    }
    return G;
}

// Procedimento que inicializa a fila
void FFVazia(TipoFila &Fila)
{
    Fila.Frente = 1;
    Fila.Tras = Fila.Frente;
    Fila.Tamanho = 0;
}

// Procedimento que verifica se a fila está vazia
bool Vazia(TipoFila Fila)
{
    return (Fila.Frente == Fila.Tras);
}

// Procedimento que insere um novo elemento no topo da fila
void Enfileira(TipoFila &Fila, int item)
{
    if ((Fila.Tras % MAXTAM) + 1 == Fila.Frente)
    {
        printf("Erro: Fila Cheia!\n");
    }
    else
    {
        Fila.Item[Fila.Tras - 1] = item;
        Fila.Tras = Fila.Tras % MAXTAM + 1;
        Fila.Tamanho++;
    }
}

// Procedimento que remove um elemento do topo da fila
int Desenfileira(TipoFila &Fila)
{
    if (Vazia(Fila))
    {
        printf("Erro: Fila Vazia!\n");
        return -1;
    }
    else
    {
        int item = Fila.Item[Fila.Frente - 1];
        Fila.Frente = Fila.Frente % MAXTAM + 1;
        Fila.Tamanho--;
        return item;
    }
}

// Procedimento que retorna o tamanho da fila
int Tamanho(TipoFila Fila)
{
    return Fila.Tamanho;
}

// Procedimento que imprimi os dados da fila
void Imprimi(TipoFila Fila)
{

    printf("Tamanho da Fila: %d\n", Tamanho(Fila));

    for (int i = Fila.Frente - 1; i != Fila.Tras - 1; i = i % MAXTAM + 1)
        printf("%d\n", Fila.Item[i]);
}

// Imprime se o grafo é completo ou não
void grafoCompleto(Graph G)
{
    bool resultado = true;
    for (vertice v = 0; v < G->V; ++v)
    {
        for (vertice w = 0; w < G->V; ++w)
            if (G->adj[v][w] == 0 && v != w)
                resultado = false;
    }
    if (resultado)
    {
        printf(" \n\n O grafo é completo!! \n\n ");
    }
    else
    {
        printf(" \n\n O grafo não é completo!! \n\n ");
    }
}

// Retorna o Grafo completo
Graph completarGrafo(Graph G)
{
    for (vertice v = 0; v < G->V; ++v)
    {
        for (vertice w = 0; w < G->V; ++w)
            if (G->adj[v][w] == 0 && v != w)
                inserirAresta(G, v, w);
    }
    return G;
}

// Imprime o caminhamento em largura a partir de s
void buscaEmLargura(Graph G, vertice s)
{
    int cnt = 0;
    int num[G->V];
    TipoFila fila;
    for (vertice v = 0; v < G->V; ++v)
        num[v] = -1;
    FFVazia(fila);
    num[s] = 1;
    Enfileira(fila, s);
    printf("\n\n Caminho em Largura: %d", s);
    while (Tamanho(fila) > 0)
    {
        vertice v = Desenfileira(fila);
        for (vertice a = 0; a < G->V; ++a)
        {
            if (G->adj[v][a] >= 1 && num[a] == -1)
            {
                printf(" ->  %d", a);
                num[a] = 1;
                Enfileira(fila, a);
            }
        }
    }
    printf("\n\n");
}

// Imprime o caminhamento em profundidade a partir de s
void buscaEmProfundidade(Graph G, vertice s, int *visitado)
{
    printf("-> %d ", s);
    visitado[s] = 1;
    for (vertice a = 0; a < G->V; ++a)
    {
        if (G->adj[s][a] >= 1 && visitado[a] == -1)
        {
            buscaEmProfundidade(G, a, visitado);
        }
    }
}

void dfsRconComps(Graph G, vertice v, int id, int *visitados)
{
    visitados[v] = id;

    for (vertice a = 0; a < G->V; ++a)
    {
        if (G->adj[v][a] >= 1 && visitados[a] == -1)
        {
            dfsRconComps(G, a, id, visitados);
        }
    }
}

// Imprime o numero de componentes em um grafo
void numeroComponentes(Graph G)
{
    int count = 0;
    int visitados[G->V];
    for (vertice v = 0; v < G->V; ++v)
        visitados[v] = -1;

    for (vertice v = 0; v < G->V; ++v)
    {
        if (visitados[v] == -1)
        {
            dfsRconComps(G, v, count++, visitados);
        }
    }
    printf("\n\n A quantidade de componentes no grafo é %d!\n\n", count);
}

Graph gerarGrafoCompleto(int qtdVertices)
{
    int qtdAresta = ((qtdVertices * (qtdVertices - 1)) / 2) * 2; // vezes dois pq é direcionado
    return gerarGrafoAleatorio(qtdVertices, qtdAresta);
}

Graph gerarGrafoParaComponentes()
{
    Graph G = iniciarGrafo(4);
    inserirAresta(G, 0, 1);
    inserirAresta(G, 1, 0);
    inserirAresta(G, 2, 3);
    inserirAresta(G, 3, 2);
    return G;
}

bool isSafe(int v, Graph graph, int path[], int pos)
{
    if (graph->adj[path[pos - 1]][v] == 0)
        return false;
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool hamCycleUtil(Graph graph, int path[], int pos)
{
    if (pos == graph->V)
    {
        if (graph->adj[path[pos - 1]][path[0]] >= 1)
            return true;
        else
            return false;
    }
    for (int v = 1; v < graph->V; v++)
    {
        if (isSafe(v, graph, path, pos))
        {
            path[pos] = v;
            if (hamCycleUtil(graph, path, pos + 1) == true)
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

// Imprime se é ou não grafo hamiltoniano e se sim, exibe o caminho hamiltoniano
void grafoHamiltoniano(Graph G)
{
    int path[G->V];
    for (int i = 0; i < G->V; i++)
        path[i] = -1;
    path[0] = 0;
    if (hamCycleUtil(G, path, 1) == false)
    {
        printf("\n\nNão existe um caminho hamiltoniano\n\n");
    }
    else
    {
        printf("\n\nExiste um caminho hamiltoniano:\n\n");
        for (int i = 0; i < G->V; i++)
            printf(" -> %d ", path[i]);

        printf(" -> %d \n", path[0]);
    }
}

Graph gerarGrafoHamilton()
{
    Graph G = iniciarGrafo(5);
    inserirAresta(G, 0, 1);
    inserirAresta(G, 0, 3);
    inserirAresta(G, 1, 0);
    inserirAresta(G, 1, 2);
    inserirAresta(G, 1, 3);
    inserirAresta(G, 1, 4);
    inserirAresta(G, 2, 1);
    inserirAresta(G, 2, 4);
    inserirAresta(G, 3, 1);
    inserirAresta(G, 3, 4);
    inserirAresta(G, 4, 1);
    inserirAresta(G, 4, 2);
    inserirAresta(G, 4, 3);
    return G;
}

int findStartVert(Graph tempGraph)
{
    for (int i = 0; i < tempGraph->V; i++)
    {
        int deg = 0;
        for (int j = 0; j < tempGraph->V; j++)
        {
            if (tempGraph->adj[i][j] >= 1)
                deg++;
        }
        if (deg % 2 != 0)
            return i;
    }
    return 0;
}

bool isBridge(Graph tempGraph, int v)
{
    int deg = 0;
    for (int i = 0; i < tempGraph->V; i++)
        if (tempGraph->adj[v][i] >= 1)
            deg++;
    if (deg > 1)
    {
        return false;
    }
    return true;
}
int edgeCount(Graph tempGraph)
{
    int count = 0;
    for (int i = 0; i < tempGraph->V; i++)
        for (int j = i; j < tempGraph->V; j++)
            if (tempGraph->adj[i][j] >= 1)
                count++;
    return count;
}

// Imprime as arestas do cliclo de euler
void grafoEuleriano(Graph G, Graph tempGraph, int start)
{
    int edge = edgeCount(tempGraph);
    for (int v = 0; v < G->V; v++)
    {
        if (G->adj[start][v] >= 1)
        {
            if (edge <= 1 || !isBridge(tempGraph, v))
            {
                printf("  %d  --  %d  ", start, v);
                removerAresta(G, start, v);
                removerAresta(tempGraph, start, v);
                edge--;
                grafoEuleriano(G, tempGraph, v);
            }
        }
    }
}

Graph gerarGrafoEuleriano()
{
    Graph G = iniciarGrafo(5);
    inserirAresta(G, 0, 1);
    inserirAresta(G, 0, 2);
    inserirAresta(G, 0, 3);
    inserirAresta(G, 0, 4);
    inserirAresta(G, 1, 0);
    inserirAresta(G, 1, 2);
    inserirAresta(G, 1, 3);
    inserirAresta(G, 1, 4);
    inserirAresta(G, 2, 0);
    inserirAresta(G, 2, 1);
    inserirAresta(G, 2, 3);
    inserirAresta(G, 2, 4);
    inserirAresta(G, 3, 0);
    inserirAresta(G, 3, 1);
    inserirAresta(G, 3, 2);
    inserirAresta(G, 3, 4);
    inserirAresta(G, 4, 0);
    inserirAresta(G, 4, 1);
    inserirAresta(G, 4, 2);
    inserirAresta(G, 4, 3);
    return G;
}

bool checarSeEEuleriano(Graph G)
{
    int result = true;
    for (int i = 0; i < G->V; i++)
    {
        int deg = 0;
        for (int j = 0; j < G->V; j++)
        {
            if (G->adj[i][j] >= 1)
                deg++;
        }
        if (deg % 2 != 0)
            result = false;
    }
    return result;
}

void imprimirArvore(edge mst[], int tam)
{
    printf("\n\n");
    edge point;
    for (int i = 0; i < tam; i++)
    {
        point = mst[i];
        printf("%d-%d ", point.c, point.v);
    }
    printf("\n");
    for (int i = 0; i < tam; i++)
    {
        point = mst[i];
        printf("%3d", point.w);
    }
    printf("\n\n");
}
// kruskal
void gerarArvoreGeradora(Graph G, edge mst[], int &k)
{
    vertice chefe[G->V];
    for (vertice v = 0; v < G->V; ++v)
        chefe[v] = v;
    while (true)
    {
        // a floresta tem arestas mst[0..k-1]
        int min = INFINITY;
        vertice x, y;
        for (vertice v = 0; v < G->V; ++v)
        {
            for (vertice a = 0; a < G->V; ++a)
            {

                vertice w = a;
                int c = G->adj[v][a];
                if (v < w && chefe[v] != chefe[w] && c < min)
                {
                    min = c;
                    x = v, y = w;
                }
            }
        }
        if (min == INFINITY)
            return;
        mst[k++] = EDGE(x, y, min);
        vertice v0 = chefe[x], w0 = chefe[y];
        for (vertice v = 0; v < G->V; ++v)
        {
            if (chefe[v] == w0)
                chefe[v] = v0;
        }
    }
}

int main()
{
    // Exemplos de grafos completos
    // Graph G = gerarGrafoAleatorio(2, 2);
    // Graph G = gerarGrafoAleatorio(1, 0);
    //Graph G = gerarGrafoAleatorio(4, 3);
    // Graph G = gerarGrafoCompleto(4);
    //Graph G = gerarGrafoAleatorio(5, 4); // Constroi um grafo aleatorio de 5 vertices e com 4 arestas.
    Graph G = gerarGrafoParaComponentes();
    //Graph G = gerarGrafoHamilton();
    //  Graph G = gerarGrafoEuleriano();

    imprimirGrafo(G);
    //grafoCompleto(G);

    // // Se o grafo não for completo, ele irá completar
    //G = completarGrafo(G);
    //grafoCompleto(G);
    // printf("\n\nGrafo completo: \n\n");
    //  imprimirGrafo(G);

    // Busca em largura a partir do vertice 3
    // buscaEmLargura(G, 0);

    // int visitado[G->V];
    // for (vertice v = 0; v < G->V; ++v)
    //     visitado[v] = -1;
    // printf("\n\n Caminho em profundidade: ");
    // //Busca em profundidade a partir do vertice 3
    // buscaEmProfundidade(G, 0, visitado);

    numeroComponentes(G);
    //grafoHamiltoniano(G);
    // Um grafo G é dito unicursal se ele possuir um percurso aberto de Euler
    // if (checarSeEEuleriano(G))
    // {
    //     Graph tempGraph = gerarGrafoEuleriano();
    //     printf("\nO grafo é unicursal com o ciclo de Euler: ");
    //     grafoEuleriano(G, tempGraph, findStartVert(tempGraph));
    //     free(tempGraph);
    // }
    // else
    // {
    //     printf("\nO grafo não é euleriano, portanto não é unicursal\n");
    // }
    // edge mst[10000];
    // int tam = 0;
    // gerarArvoreGeradora(G, mst, tam);
    // imprimirArvore(mst, tam);

    free(G);

    return 0;
}
