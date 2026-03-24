#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

typedef struct {
    char texto[50];
} Pista;

typedef struct Sala {
    char nome[50];
    Pista pista;
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct BST {
    Pista pista;
    struct BST* esquerda;
    struct BST* direita;
} BST;

// --- Criação
Sala* criarSala(char* nome, Pista* pista) {
    Sala* novo = (Sala*) malloc(sizeof(Sala));
    strcpy(novo->nome, nome);
    strcpy(novo->pista.texto, pista->texto);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

Sala* conectarSalas(Sala* sala, char* nome, Pista* pista) {
    if(sala == NULL) {
        return criarSala(nome, pista); // Se árvore está vazia cria um novo nó
    }

    if(strcmp(nome, sala->nome) < 0) {
        // insere sala a esquerda
        sala->esquerda = conectarSalas(sala->esquerda, nome, pista);
    }
    else {
        // insere sala a direita
        sala->direita = conectarSalas(sala->direita, nome, pista);
    }
    return sala;
}

void desmontarCasa(Sala* sala) {
    if (sala == NULL) return;
    desmontarCasa(sala->esquerda);
    desmontarCasa(sala->direita);
    free(sala);
}

// Fução que insere pista na BST
BST* criarBST(Pista* pista) {
    BST* novo = (BST*) malloc(sizeof(BST));
    strcpy(novo->pista.texto, pista->texto);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

BST* inserirBST(BST* raiz, Pista* pista) {
    if(raiz == NULL) {
        return criarBST(pista); // Se árvore está vazia cria um novo nó
    }

    if(strcmp(pista->texto, raiz->pista.texto) < 0) {
        // insere raiz a esquerda
        raiz->esquerda = inserirBST(raiz->esquerda, pista);
    }
    else {
        // insere raiz a direita
        raiz->direita = inserirBST(raiz->direita, pista);
    }
    return raiz;
}

void listarPistas(BST* raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esquerda);
        printf("%s; ", raiz->pista.texto);
        listarPistas(raiz->direita);
    }
}

void desmontarBST(BST* raiz) {
    if (raiz == NULL) return;
    desmontarBST(raiz->esquerda);
    desmontarBST(raiz->direita);
    free(raiz);
}

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// --- Exploração
// Retorna 1 se o jogador se moveu, 0 se o caminho estava bloqueado
int explorarSalas(Sala* atual, BST* raiz) {
    if (atual == NULL) {
        printf(">>> Caminho bloqueado! Não há sala nessa direção.\n");
        printf("    (Pressione qualquer tecla para voltar...)\n");
        getchar();
        return 0;  // sinaliza: não houve movimento
    }

    char opcao;

    printf("\n  Pista coletada: %s\n", atual->pista.texto);
    raiz = inserirBST(raiz, &atual->pista);

    while (1) {
        printf("\n========================================\n");
        printf("  Você está em: %s\n", atual->nome);
        printf("  Saídas disponíveis:\n");
        printf("    [e] Ir para a esquerda");
        if (atual->esquerda)
            printf("  - %s", atual->esquerda->nome);
        else
            printf("  (sem saída)");
        printf("\n");
        printf("    [d] Ir para a direita");
        if (atual->direita)
            printf("  - %s", atual->direita->nome);
        else
            printf("  (sem saída)");
        printf("\n");
        printf("    [l] Listar pistas coletadas");
        printf("\n");
        printf("    [s] Sair\n");
        printf("========================================\n");
        printf("Sua escolha: ");

        scanf(" %c", &opcao);
        limparBufferEntrada();

        if (opcao == 'e') {
            if (explorarSalas(atual->esquerda, raiz))  // só sai do loop se houve movimento
                break;
        } else if (opcao == 'd') {
            if (explorarSalas(atual->direita, raiz))  // só sai do loop se houve movimento
                break;
        } else if (opcao == 'l') {
            printf("\n Lista das pistas coletadas: ");
            listarPistas(raiz);
            printf("\n");
        } else if (opcao == 's') {
            printf("\nVocê saiu da mansão. Até a próxima!\n");
            exit(0);
        } else {
            printf("Opção inválida. Use 'e', 'd' ou 's'.\n");
        }
    }

    return 1;  // houve movimento
}

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.
    
    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    Sala* raiz = NULL;
    BST* bst = NULL;

    Pista pista1;
    Pista pista2;
    Pista pista3;
    Pista pista4;

    // inserir comodos e suas pistas
    strcpy(pista1.texto, "ciclete usado");
    raiz = conectarSalas(raiz, "Hall de Entrada", &pista1);
    strcpy(pista2.texto, "lenço usado");
    raiz = conectarSalas(raiz, "Sala de Estar", &pista2);
    strcpy(pista3.texto, "cartucho de munição");
    raiz = conectarSalas(raiz, "Biblioteca", &pista3);
    strcpy(pista4.texto, "copo de café descartável");
    raiz = conectarSalas(raiz, "Quarto", &pista4);

    printf("====================================\n");
    printf("     Detective Quest — Mansão\n");
    printf("====================================\n");
    printf("Explore a mansão!\n");
    printf("Use 'e' (esquerda), 'd' (direita) ou 's' (sair).\n");

    explorarSalas(raiz, bst);

    desmontarCasa(raiz); // libera a memória
    desmontarBST(bst);

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    return 0;
}

