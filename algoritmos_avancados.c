#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

#define TAMANHO_TABELA 10

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

// Estrutura de um nó da lista ligada
typedef struct Tab {
    Pista pista;               // pista como chave
    char nome[50];             // Armazena o nome
    struct Tab* proximo;       // Ponteiro para o próximo nó
} Tabela;

// A tabela hash é um vetor de ponteiros para Nodo
Tabela* tabela_hash[TAMANHO_TABELA];

int funcaoHash(Pista* pista) {
    int soma = 0;
    for (int i = 0; pista->texto[i] != '\0'; i++) {
        soma += pista->texto[i];
    }
    return soma % TAMANHO_TABELA;
}

void inseriNaHash(Pista* pista, const char* nome) {
    int indice = funcaoHash(pista); // Descobre onde armazenar
    // Cria um nó
    Tabela* novo = (Tabela*)malloc(sizeof(Tabela));
    strcpy(novo->pista.texto, pista->texto);
    strcpy(novo->nome, nome);

    // Insere no início da lista (head)
    novo->proximo = tabela_hash[indice];
    tabela_hash[indice] = novo;
}

Tabela* encontrarSuspeito(Pista* pista) {
        int indice = funcaoHash(pista);
        Tabela* atual = tabela_hash[indice];
    
        while (atual != NULL) {
            if (strcmp(atual->pista.texto, pista->texto) == 0) {
                return atual; // Encontrou
        }
        atual = atual->proximo;
    }

    return NULL; // Não está na lista
}

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void verificarSuspeitoFinal() {
    // --- Contagem de pistas por suspeito ---
    // Estrutura auxiliar local para guardar nome + contagem
    typedef struct {
        char nome[50];
        int contagem;
    } ContaSuspeito;

    ContaSuspeito suspeitos[TAMANHO_TABELA * 5]; // espaço generoso
    int total = 0;

    // Percorre toda a tabela hash
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Tabela* atual = tabela_hash[i];
        while (atual != NULL) {
            // Verifica se o suspeito já está na lista auxiliar
            int encontrado = 0;
            for (int j = 0; j < total; j++) {
                if (strcmp(suspeitos[j].nome, atual->nome) == 0) {
                    suspeitos[j].contagem++;
                    encontrado = 1;
                    break;
                }
            }
            // Se não estava, adiciona
            if (!encontrado) {
                strcpy(suspeitos[total].nome, atual->nome);
                suspeitos[total].contagem = 1;
                total++;
            }
            atual = atual->proximo;
        }
    }

    // --- Exibição dos suspeitos e suas pistas ---
    printf("\n========================================\n");
    printf("   HORA DE RESOLVER O MISTÉRIO!\n");
    printf("========================================\n");
    printf("Lista de Suspeitos:\n\n");

    for (int i = 0; i < total; i++) {
        printf("  [%s]\n", suspeitos[i].nome);
    }

    // --- Determina o culpado real (quem tem 2+ pistas) ---
    char culpadoReal[50] = "";
    int maiorContagem = 0;

    for (int i = 0; i < total; i++) {
        if (suspeitos[i].contagem >= 2 && suspeitos[i].contagem > maiorContagem) {
            maiorContagem = suspeitos[i].contagem;
            strcpy(culpadoReal, suspeitos[i].nome);
        }
    }

    // --- Pede o palpite do jogador ---
    char palpite[50];
    printf("\nQuem você acha que é o culpado? ");
    scanf(" %49[^\n]", palpite);
    limparBufferEntrada();

    // --- Verifica o palpite ---
    printf("\n========================================\n");
    if (strcmp(palpite, culpadoReal) == 0) {
        printf("  PARABÉNS! Você desvendou o caso!\n");
        printf("  %s é mesmo o culpado — flagrado por %d pistas!\n",
               culpadoReal, maiorContagem);
    } else {
        printf("  Errou! %s é inocente nessa história.\n", palpite);
        if (strlen(culpadoReal) > 0) {
            printf("  O verdadeiro culpado era: %s (%d pistas).\n",
                   culpadoReal, maiorContagem);
        } else {
            printf("  Pistas insuficientes para apontar um culpado.\n");
        }
    }
    printf("========================================\n");
}

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

BST* inserirPista(BST* raiz, Pista* pista) {
    if(raiz == NULL) {
        return criarBST(pista); // Se árvore está vazia cria um novo nó
    }

    if(strcmp(pista->texto, raiz->pista.texto) < 0) {
        // insere raiz a esquerda
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    }
    else {
        // insere raiz a direita
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    return raiz;
}

void listarPistas(BST* raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esquerda);
        printf("%s ", raiz->pista.texto);
        printf("(%s); ", encontrarSuspeito(&raiz->pista)->nome);
        listarPistas(raiz->direita);
    }
}

void desmontarBST(BST* raiz) {
    if (raiz == NULL) return;
    desmontarBST(raiz->esquerda);
    desmontarBST(raiz->direita);
    free(raiz);
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
    raiz = inserirPista(raiz, &atual->pista);

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
        printf("    [a] Acusar suspeito");
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
        } else if (opcao == 'a') {
            printf("\n");
            verificarSuspeitoFinal();
            exit(0);
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

    Sala* raiz = NULL;
    BST* bst = NULL;

    Pista pista1;
    Pista pista2;
    Pista pista3;
    Pista pista4;
    strcpy(pista1.texto, "ciclete usado");
    strcpy(pista2.texto, "lenço usado");
    strcpy(pista3.texto, "cartucho de munição");
    strcpy(pista4.texto, "copo de café descartável");

    // inserir comodos e suas pistas
    raiz = conectarSalas(raiz, "Hall de Entrada", &pista1);
    raiz = conectarSalas(raiz, "Sala de Estar", &pista2);
    raiz = conectarSalas(raiz, "Biblioteca", &pista3);
    raiz = conectarSalas(raiz, "Quarto", &pista4);

    inseriNaHash(&pista1, "Bruno");
    inseriNaHash(&pista2, "Bruno");
    inseriNaHash(&pista3, "Ana");
    inseriNaHash(&pista4, "Carlos");

    printf("====================================\n");
    printf("     Detective Quest — Mansão\n");
    printf("====================================\n");
    printf("Explore a mansão!\n");
    printf("Use 'e' (esquerda), 'd' (direita) ou 's' (sair).\n");

    explorarSalas(raiz, bst);

    desmontarCasa(raiz); // libera a memória
    desmontarBST(bst);

    return 0;
}

