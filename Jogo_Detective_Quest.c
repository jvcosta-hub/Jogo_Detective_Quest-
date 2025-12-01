#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
-----------------------------------------------------------
    Estrutura da Sala (nó da árvore binária)
-----------------------------------------------------------
Cada sala possui:
 - nome: string com o nome do cômodo
 - esq: ponteiro para sala à esquerda
 - dir: ponteiro para sala à direita
*/
typedef struct sala {
    char nome[50];
    struct sala *esq;
    struct sala *dir;
} Sala;

/*
-----------------------------------------------------------
    Função criarSala()
-----------------------------------------------------------
Cria dinamicamente uma nova sala com o nome fornecido.
Retorno: ponteiro para a sala criada.
*/
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (!nova) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

/*
-----------------------------------------------------------
    Função explorarSalas()
-----------------------------------------------------------
Navega interativamente pela árvore binária a partir da sala
informada pelo parâmetro. O jogador escolhe:
 - 'e' → ir para a esquerda
 - 'd' → ir para a direita
 - 's' → sair da exploração

A navegação termina quando o jogador decide sair ou
quando chega a um nó-folha (sem caminhos).
*/
void explorarSalas(Sala *atual) {
    char opcao;

    printf("\n===== INÍCIO DA EXPLORAÇÃO =====\n");

    while (atual != NULL) {
        printf("\nVocê está em: **%s**\n", atual->nome);

        // Nó-folha: não há caminhos para seguir
        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Esta sala não possui caminhos. Fim da exploração!\n");
            return;
        }

        printf("Escolha seu caminho:\n");
        if (atual->esq != NULL) printf(" (e) Ir para a esquerda (%s)\n", atual->esq->nome);
        if (atual->dir != NULL) printf(" (d) Ir para a direita (%s)\n", atual->dir->nome);
        printf(" (s) Sair da exploração\n");
        printf("-> ");
        scanf(" %c", &opcao);

        if (opcao == 'e' && atual->esq != NULL) {
            atual = atual->esq;
        } else if (opcao == 'd' && atual->dir != NULL) {
            atual = atual->dir;
        } else if (opcao == 's') {
            printf("Exploração encerrada pelo jogador.\n");
            return;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

/*
-----------------------------------------------------------
    Função main()
-----------------------------------------------------------
Monta automaticamente um mapa da mansão usando uma árvore
binária fixa. Depois inicia a exploração a partir do Hall
de Entrada.
*/
int main() {
    // Criação do mapa da mansão (árvore binária fixa)
    Sala *hall        = criarSala("Hall de Entrada");
    Sala *salaEstar   = criarSala("Sala de Estar");
    Sala *cozinha     = criarSala("Cozinha");
    Sala *biblioteca  = criarSala("Biblioteca");
    Sala *jardim      = criarSala("Jardim");
    Sala *porao       = criarSala("Porão");
    Sala *quarto      = criarSala("Quarto de Hóspedes");

    // Montagem da árvore
    hall->esq = salaEstar;
    hall->dir = cozinha;

    salaEstar->esq = biblioteca;
    salaEstar->dir = jardim;

    cozinha->esq = porao;
    cozinha->dir = quarto;

    // Inicia exploração a partir do Hall
    explorarSalas(hall);

    return 0;
}
