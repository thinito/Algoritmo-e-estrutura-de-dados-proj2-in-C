#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// Função que cria uma nova lista vazia
Lista* criarLista() {
    Lista *lista =(Lista*) malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função que que coleta os dados de uma pessoa
void lerPessoa(Pessoa *p) {
    getchar();
    printf("Digite o nome: ");
    fgets(p->nome,50,stdin);
    p->nome[strcspn(p->nome, "\n")] = 0;

    printf("Digite a idade: ");
    scanf("%d",&p->idade);

    getchar();
    printf("Digite o endereco: ");
    fgets(p->endereco,100,stdin);
    p->endereco[strcspn(p->endereco, "\n")] = 0;

    printf("Digite o telefone: ");
    fgets(p->telefone,15,stdin);
    p->telefone[strcspn(p->telefone, "\n")] = 0;

}

// Função que insere uma nova pessoa no final da lista
void inserirPessoa(Lista *lista, Pessoa pessoa) {
    No *novoNo = calloc(1,sizeof(No));
    novoNo->pessoa = pessoa;
    novoNo->prox = NULL;
    if (lista->inicio == NULL) {
        lista->inicio = novoNo;
    } else {
        No *aux = lista->inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novoNo;
    }
    lista->tamanho++;
}

// Função que remove uma pessoa da lista
void removerPessoa(Lista *lista, char *nome) {
    No *aux = lista->inicio;
    No *ant = NULL;
    while (aux != NULL) {
        if (strcmp(aux->pessoa.nome, nome) == 0) {
            if (ant == NULL) {
                lista->inicio = aux->prox;
            } else {
                ant->prox = aux->prox;
            }
            free(aux);
            lista->tamanho--;
            return;
        }
        ant = aux;
        aux = aux->prox;
    }
}

// Função que busca uma pessoa na lista por nome
Pessoa* buscarPessoaPorNome(Lista *lista, char *nome) {
    No *aux = lista->inicio;
    while (aux != NULL) {
        if (strcmp(aux->pessoa.nome, nome) == 0) {
            return &(aux->pessoa);
        }
        aux = aux->prox;
    }
    return NULL;
}

// Função que busca uma pessoa na lista por idade
Pessoa* buscarPessoaPorIdade(Lista *lista, int idade) {
    No *aux = lista->inicio;
    while (aux != NULL) {
        if (aux->pessoa.idade == idade) {
            return &(aux->pessoa);
        }
        aux = aux->prox;
    }
    return NULL;
}

// Função que busca uma pessoa na lista por endereço
Pessoa* buscarPessoaPorEndereco(Lista *lista, char *endereco) {
    No *aux = lista->inicio;
    while (aux != NULL) {
        if (strcmp(aux->pessoa.endereco, endereco) == 0) {
            return &(aux->pessoa);
        }
        aux = aux->prox;
    }
    return NULL;
}

Pessoa* buscarPessoaPorTelefone(Lista *lista, char *telefone) {
    No *aux = lista->inicio;
    while (aux != NULL) {
        if (strcmp(aux->pessoa.telefone, telefone) == 0) {
            return &(aux->pessoa);
        }
        aux = aux->prox;
    }
    return NULL;
}

// Função que exibe os dados de uma pessoa
void exibirDadosPessoa(Pessoa *pessoa) {
printf("Nome: %s\n", pessoa->nome);
printf("Idade: %d\n", pessoa->idade);
printf("Endereco: %s\n", pessoa->endereco);
printf("Telefone: %s\n", pessoa->telefone);
printf("--------------------\n");
}

// Função que exibe todos os dados do cadastro
void exibirDadosCadastro(Lista *lista) {
    No *aux = lista->inicio;
    while (aux != NULL) {
        exibirDadosPessoa(&(aux->pessoa));
        aux = aux->prox;
    }
}

// Função que escreve um arquivo binário de listas de Pessoas
void escreverArquivoBinario( Lista *lista) {
    FILE *arquivo;
    No *atual;
    // Abrir o arquivo em modo de escrita
    arquivo = fopen("data_base.txt", "w");
    // Verificar se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", "data_base.txt");
        exit(1);
    }
    // Percorrer a lista e escrever cada elemento no arquivo de texto
    atual = lista->inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%s\n%d\n%s\n%s\n", atual->pessoa.nome, atual->pessoa.idade, atual->pessoa.endereco, atual->pessoa.telefone);
        atual = atual->prox;
    }
    // Fechar o arquivo
    fclose(arquivo);
}

void lerArquivo(Lista *lista) {
    FILE *arquivo;
    char linha[200];
    char *token;
    Pessoa pessoa;

    // abre o arquivo para leitura
    arquivo = fopen("data_base.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    // lê linha por linha do arquivo
    while (fgets(linha, 200, arquivo) != NULL) {
        // separa os campos da linha
         token = strtok(linha, "\n");
        strcpy(pessoa.nome, token);

        fgets(linha, sizeof(linha), arquivo);
        token = strtok(linha, "\n");
        pessoa.idade = atoi(token);

        fgets(linha, sizeof(linha), arquivo);
        token = strtok(linha, "\n");
        strcpy(pessoa.endereco, token);

        fgets(linha, sizeof(linha), arquivo);
        token = strtok(linha, "\n");
        strcpy(pessoa.telefone, token);

        // adiciona a pessoa à lista encadeada
        No *novoNo = (No*) malloc(sizeof(No));
        novoNo->pessoa = pessoa;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        lista->tamanho++;
    }

    fclose(arquivo);
}