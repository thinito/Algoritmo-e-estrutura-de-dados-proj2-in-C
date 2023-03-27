#ifndef data
#define data

typedef struct {
    char nome[50];
    int idade;
    char endereco[100];
    char telefone[15];
} Pessoa;

typedef struct no {
    Pessoa pessoa;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    int tamanho;
} Lista;

typedef struct {
    Lista *listas;
    int tamanho;
} ListaDeListas;

ListaDeListas* lerArquivoBinario();
void escreverArquivoBinario(Lista *lista);
void lerPessoa(Pessoa *p);
Lista* criarLista();
void inserirPessoa(Lista *lista, Pessoa pessoa);
void removerPessoa(Lista *lista, char *nome);
Pessoa* buscarPessoaPorNome(Lista *lista, char *nome);
Pessoa* buscarPessoaPorIdade(Lista *lista, int idade);
Pessoa* buscarPessoaPorEndereco(Lista *lista, char *endereco);
Pessoa* buscarPessoaPorTelefone(Lista *lista, char *telefone);
void exibirDadosPessoa(Pessoa *pessoa);
void exibirDadosCadastro(Lista *lista);
void apagar_lista(Lista *lista);
void lerArquivo(Lista *lista);

#endif