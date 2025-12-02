#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define TAM_STR_NOME 30
#define TAM_STR_TIPO 20
#define MAX_ITENS 10

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[TAM_STR_NOME];
    char tipo[TAM_STR_TIPO];
    int quantidade;
} Item;

void exibirMenu(int numItens);
void inserirItem(Item mochila[], int *numItems);
void removerItem(Item mochila[], int *numItens);
void listarItens(Item mochila[], int numItens);
void buscarItem(Item mochila);
void limparBufferEntrada();

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // Vetor mochila:
    // Armazena até 10 itens coletados.
    Item mochila[MAX_ITENS];

    // Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
    int numItens = 0;
    int opcao;

    do {
        char nome[TAM_STR_NOME];
        exibirMenu(numItens);
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        // A estrutura switch trata cada opção chamando a função correspondente.
        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 0:
                printf("Saindo...");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}


// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).


// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
void exibirMenu(int numItens) {
    // Apresenta o menu principal ao jogador, com destaque para status da ordenação.
    printf("\n======================================================");
    printf("\n      MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA");
    printf("\n======================================================");
    printf("\nItens na Mochila: %d/%d", numItens, MAX_ITENS);
    printf("\n");
    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("0. Sair\n");
}

// inserirItem():
void inserirItem(Item mochila[], int *numItens) {
    // Adiciona um novo componente à mochila se houver espaço.
    if (*numItens >= MAX_ITENS) {
        printf("Erro: mochila cheia!\n");
        return;
    }

    // Solicita nome, tipo, quantidade e prioridade.
    printf("\n");
    printf("--- Adicionar Novo Item ---\n");

    printf("Nome do Item:\n");
    fgets(mochila[*numItens].nome, TAM_STR_NOME, stdin);
    
    printf("Tipo do Item (arma, municao, cura, etc.):\n");
    fgets(mochila[*numItens].tipo, TAM_STR_TIPO, stdin);
    
    mochila[*numItens].nome[strcspn(mochila[*numItens].nome, "\n")] = '\0';
    mochila[*numItens].tipo[strcspn(mochila[*numItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*numItens].quantidade);
    limparBufferEntrada();

    printf("\n");
    printf("Item '%s' adicionado com sucesso!\n", mochila[*numItens].nome);
    
    (*numItens)++;
    listarItens(mochila, *numItens);
    // Após inserir, marca a mochila como "não ordenada por nome".
}

// removerItem():
void removerItem(Item mochila[], int* numItens) {
    // Verifica se a mochila está vazia
    if (*numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    // Permite remover um componente da mochila pelo nome.
    char nome[TAM_STR_NOME];
    printf("--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nome, TAM_STR_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Erro: Item '%s' nao encontrado na mochila.\n", nome);
        return;
    }

    // Se encontrado, reorganiza o vetor para preencher a lacuna.
    for (int i = pos; i < *numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*numItens)--;
    printf("\n");
    printf("Item '%s' removido com sucesso!\n", nome);
    listarItens(mochila, *numItens);
}

// listarItens():
void listarItens(Item mochila[], int numItens) {
    // Exibe uma tabela formatada com todos os componentes presentes na mochila.
    printf("\n");
    printf("--- ITENS NA MOCHILA (%d/%d) ---\n", numItens, MAX_ITENS);
    printf("------------------------------------------------------\n");
    printf("NOME                 | TIPO               | QUANTIDADE\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("%-20s | %-18s | %d\n",
            mochila[i].nome,
            mochila[i].tipo,
            mochila[i].quantidade
        );
    }
    printf("------------------------------------------------------\n");
    printf("\n");
    printf("Pressione Enter para continuar...\n");
    getchar();
}

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
