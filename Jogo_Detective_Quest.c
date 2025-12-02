#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

/*
===========================================================
    ESTRUTURAS DE DADOS
===========================================================
*/

// Nó da árvore binária da mansão
typedef struct sala {
    char nome[50];
    char pista[100];  // pista associada ao cômodo
    struct sala *esq;
    struct sala *dir;
} Sala;

// Nó da árvore BST de pistas
typedef struct pistaNode {
    char pista[100];
    struct pistaNode *esq;
    struct pistaNode *dir;
} PistaNode;

// Entrada da tabela hash: pista → suspeito
typedef struct hashNode {
    char pista[100];
    char suspeito[50];
    struct hashNode *prox;
} HashNode;


/*
===========================================================
    FUNÇÃO criarSala()
-----------------------------------------------------------
Cria dinamicamente uma sala da mansão com nome e pista.
===========================================================
*/
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esq = nova->dir = NULL;
    return nova;
}


/*
===========================================================
    FUNÇÕES DA BST DE PISTAS
===========================================================
*/

// Inserção na BST
PistaNode* inserirPista(PistaNode *raiz, const char *p) {
    if (p[0] == '\0') return raiz; // pista vazia → ignora

    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(novo->pista, p);
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (strcmp(p, raiz->pista) < 0)
        raiz->esq = inserirPista(raiz->esq, p);
    else
        raiz->dir = inserirPista(raiz->dir, p);

    return raiz;
}

// Exibir pistas em ordem alfabética
void exibirPistas(PistaNode *raiz) {
    if (raiz == NULL) return;
    exibirPistas(raiz->esq);
    printf(" - %s\n", raiz->pista);
    exibirPistas(raiz->dir);
}


/*
===========================================================
    FUNÇÕES DA TABELA HASH
===========================================================
*/

// Hash simples: primeira letra da pista
int hashFunction(const char *p) {
    return (p[0] % TAM_HASH);
}

/*
-----------------------------------------------------------
    inserirNaHash()
Associa uma pista a um suspeito na tabela hash.
-----------------------------------------------------------
*/
void inserirNaHash(HashNode *tabela[], const char *pista, const char *suspeito) {
    int pos = hashFunction(pista);

    HashNode *novo = (HashNode*) malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabela[pos];
    tabela[pos] = novo;
}

/*
-----------------------------------------------------------
    encontrarSuspeito()
Retorna o nome do suspeito vinculado à pista.
-----------------------------------------------------------
*/
char* encontrarSuspeito(HashNode *tabela[], const char *pista) {
    int pos = hashFunction(pista);
    HashNode *aux = tabela[pos];

    while (aux != NULL) {
        if (strcmp(aux->pista, pista) == 0)
            return aux->suspeito;
        aux = aux->prox;
    }
    return NULL; // não encontrado
}


/*
===========================================================
    FASE DE JULGAMENTO FINAL
===========================================================
*/

/*
-----------------------------------------------------------
    contarPistasDoSuspeito()
Conta quantas pistas da BST pertencem ao acusado.
-----------------------------------------------------------
*/
int contarPistasDoSuspeito(PistaNode *raiz, HashNode *tabela[], const char *suspeito) {
    if (raiz == NULL) return 0;

    int total = 0;

    char *achei = encontrarSuspeito(tabela, raiz->pista);
    if (achei != NULL && strcmp(achei, suspeito) == 0)
        total++;

    total += contarPistasDoSuspeito(raiz->esq, tabela, suspeito);
    total += contarPistasDoSuspeito(raiz->dir, tabela, suspeito);

    return total;
}

/*
-----------------------------------------------------------
    verificarSuspeitoFinal()
Realiza a acusação final e verifica se é sustentada.
-----------------------------------------------------------
*/
void verificarSuspeitoFinal(PistaNode *raiz, HashNode *tabela[]) {
    char suspeito[50];

    printf("\n===== FASE FINAL: ACUSAÇÃO =====\n");
    printf("Digite o nome do suspeito a acusar:\n-> ");
    scanf(" %[^\n]", suspeito);

    int qtd = contarPistasDoSuspeito(raiz, tabela, suspeito);

    printf("\nRESULTADO DA ANÁLISE:\n");

    if (qtd >= 2) {
        printf("Acusação válida! %s possui %d evidências contra si.\n", suspeito, qtd);
        printf("Você solucionou o caso!\n");
    } else {
        printf("Acusação insuficiente. Apenas %d pista(s) apontam para %s.\n", qtd, suspeito);
        printf("Caso não resolvido.\n");
    }
}


/*
===========================================================
    FUNÇÃO explorarSalas()
-----------------------------------------------------------
Controla a navegação da mansão, coleta pistas,
insere na BST e relaciona na hash.
===========================================================
*/
void explorarSalas(Sala *inicio, PistaNode **arvorePistas, HashNode *tabela[]) {
    Sala *atual = inicio;
    char opcao;

    printf("\n===== INÍCIO DA EXPLORAÇÃO =====\n");

    while (1) {
        printf("\nVocê está em: **%s**\n", atual->nome);

        // Coleta automática
        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: \"%s\"\n", atual->pista);

            // insere pista na BST
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);

            // associa pista ao suspeito correspondente
            char *sus = encontrarSuspeito(tabela, atual->pista);
            if (sus != NULL)
                printf("Esta pista aponta para: %s\n", sus);
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }

        // Opções de navegação
        printf("\nEscolha seu caminho:\n");
        if (atual->esq) printf(" (e) Ir para esquerda → %s\n", atual->esq->nome);
        if (atual->dir) printf(" (d) Ir para direita → %s\n", atual->dir->nome);
        printf(" (s) Sair da exploração\n-> ");
        scanf(" %c", &opcao);

        if (opcao == 'e' && atual->esq)
            atual = atual->esq;
        else if (opcao == 'd' && atual->dir)
            atual = atual->dir;
        else if (opcao == 's') {
            printf("\nEncerrando exploração...\n");
            return;
        }
        else
            printf("Opção inválida!\n");
    }
}


/*
===========================================================
    FUNÇÃO PRINCIPAL
===========================================================
*/
int main() {
    // ---------------------------
    // Montagem da mansão (árvore)
    // ---------------------------

    Sala *hall        = criarSala("Hall de Entrada",      "Pegada de sapato");
    Sala *salaEstar   = criarSala("Sala de Estar",        "Copo quebrado");
    Sala *cozinha     = criarSala("Cozinha",              "Faca afiada");
    Sala *biblioteca  = criarSala("Biblioteca",           "Página arrancada");
    Sala *jardim      = criarSala("Jardim",               "");
    Sala *porao       = criarSala("Porão",                "Luvas sujas");
    Sala *quarto      = criarSala("Quarto de Hóspedes",   "Foto rasgada");

    hall->esq = salaEstar;
    hall->dir = cozinha;

    salaEstar->esq = biblioteca;
    salaEstar->dir = jardim;

    cozinha->esq = porao;
    cozinha->dir = quarto;

    // ---------------------------
    // TABELA HASH (pista → suspeito)
    // ---------------------------
    HashNode *tabela[TAM_HASH] = { NULL };

    // Mapeamento fixo das pistas
    inserirNaHash(tabela, "Pegada de sapato", "Sr. Ricardo");
    inserirNaHash(tabela, "Copo quebrado", "Sra. Helena");
    inserirNaHash(tabela, "Faca afiada", "Sra. Helena");
    inserirNaHash(tabela, "Página arrancada", "Sr. Ricardo");
    inserirNaHash(tabela, "Luvas sujas", "Jardineiro");
    inserirNaHash(tabela, "Foto rasgada", "Sra. Helena");

    // ---------------------------
    // Árvore de pistas coletadas
    // ---------------------------
    PistaNode *pistas = NULL;

    // ---------------------------
    // Exploração interativa
    // ---------------------------
    explorarSalas(hall, &pistas, tabela);

    // ---------------------------
    // Relatório de pistas
    // ---------------------------
    printf("\n===== PISTAS COLETADAS =====\n");
    if (pistas == NULL)
        printf("Nenhuma pista coletada.\n");
    else
        exibirPistas(pistas);

    // ---------------------------
    // Fase final: acusação
    // ---------------------------
    verificarSuspeitoFinal(pistas, tabela);

    printf("\n===== FIM DA INVESTIGAÇÃO =====\n");
    return 0;
}