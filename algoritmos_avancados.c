#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

typedef struct No {
    char nome[50];
    struct No* esquerda;
    struct No* direita;
} Sala;

// --- Criação
Sala* criarSala(char* nome) {
    Sala* novo = (Sala*) malloc(sizeof(Sala));
    strcpy(novo->nome, nome);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

Sala* conectarSalas(Sala* sala, const char* nome) {
    if(sala == NULL) {
        return criarSala(nome); // Se árvore está vazia cria um novo nó
    }

    if(strcmp(nome, sala->nome) < 0) {
        // insere sala a esquerda
        sala->esquerda = conectarSalas(sala->esquerda, nome);
    }
    else {
        // insere sala a direita
        sala->direita = conectarSalas(sala->direita, nome);
    }
    return sala;
}

// --- Exploração
// Retorna 1 se o jogador se moveu, 0 se o caminho estava bloqueado
int explorarSalas(Sala* atual) {
    if (atual == NULL) {
        printf(">>> Caminho bloqueado! Não há sala nessa direção.\n");
        printf("    (Pressione qualquer tecla para voltar...)\n");
        getchar();
        return 0;  // sinaliza: não houve movimento
    }

    char opcao;

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
        printf("    [s] Sair\n");
        printf("========================================\n");
        printf("Sua escolha: ");

        scanf(" %c", &opcao);
        limparBufferEntrada();

        if (opcao == 'e') {
            if (explorarSalas(atual->esquerda))  // só sai do loop se houve movimento
                break;
        } else if (opcao == 'd') {
            if (explorarSalas(atual->direita))   // só sai do loop se houve movimento
                break;
        } else if (opcao == 's') {
            printf("\nVocê saiu da mansão. Até a próxima!\n");
            exit(0);
        } else {
            printf("Opção inválida. Use 'e', 'd' ou 's'.\n");
        }
    }

    return 1;  // houve movimento
}

void desmontarCasa(Sala* sala) {
    if (sala == NULL) return;
    desmontarCasa(sala->esquerda);
    desmontarCasa(sala->direita);
    free(sala);
}

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
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
    
    Sala* raiz = NULL;

    raiz = conectarSalas(raiz, "Hall de Entrada");
    raiz = conectarSalas(raiz, "Sala de Estar");
    raiz = conectarSalas(raiz, "Biblioteca");
    raiz = conectarSalas(raiz, "Quarto");

    printf("====================================\n");
    printf("     Detective Quest — Mansão\n");
    printf("====================================\n");
    printf("Explore a mansão!\n");
    printf("Use 'e' (esquerda), 'd' (direita) ou 's' (sair).\n");

    explorarSalas(raiz);

    desmontarCasa(raiz); // libera a memória

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

    return 0;
}

