#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void Menu_principal(int a){
    printf("=====  MENU DE LISTAS  =====\n");
    printf("=====  Listas disponiveis: %d  =====\n",a);
    printf("Selecione uma opção:\n");
    printf("1 - Criar uma lista\n");
    printf("2 - Acessar uma lista\n");
    printf("3 - Juntar todas as listas\n");
    printf("0 - Sair\n");
}

void Menu_cad(int c,Lista *lista){
    int op,idade;
    char string[100];
    do{
        printf("=====  MENU DE CADASTRO DA LISTA %d =====\n",c);
        printf("Selecione uma opção:\n");
	    printf("1 - Inserir o cadastro de uma pessoa na lista criada\n");
    	printf("2 - Remover o cadastro de uma pessoa na lista criada\n");
	    printf("3 - Buscar o cadastro de uma pessoa na lista criada pelo nome\n");
	    printf("4 - Buscar o cadastro de uma pessoa na lista criada pela idade\n");
	    printf("5 - Buscar o cadastro de uma pessoa na lista criada pelo endereço\n");
	    printf("6 - Buscar o cadastro de uma pessoa na lista criada pelo telefone\n");
	    printf("7 - Mostrar dados de todas as pessoas cadastradas na lista\n");
	    printf("8 - Voltar ao menu principal\n\n");
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            Pessoa p;
            lerPessoa(&p);
            inserirPessoa(lista, p);
            printf("== CADASTRO REALIZADO COM SUCESSO ==\n\n");
            break;

        case 2:
            printf("Digite o nome da pessoa a ser removida: ");
            scanf("%49s",string);
            if(buscarPessoaPorNome(lista, string) == NULL){
                printf("== PESSOA NÃO ENCONTRADA NESTA LISTA ==\n\n");
            }
            else{
                removerPessoa(lista, string);
                printf("== CADASTRO REMOVIDO COM SUCESSO ==\n\n");
            }
            break;
        
        case 3:
            printf("Digite o nome da pessoa a ser buscada\n");
            scanf("%49s", string);
            Pessoa *res = buscarPessoaPorNome(lista,string);
            if (res == NULL){
                printf("== PESSOA NÃO ENCONTRADA NESTA LISTA ==\n\n");
            }
            else{
                exibirDadosPessoa(res);
            }
            break;
        
        case 4:
            printf("Digite a idade da pessoa a ser buscada\n");
            scanf("%d", &idade);
            Pessoa *result = buscarPessoaPorIdade(lista,idade);
            if (result == NULL){
                printf("== PESSOA NÃO ENCONTRADA NESTA LISTA ==\n\n");
                }
            else{
                exibirDadosPessoa(result);
            }
            break;

        case 5:
            printf("Digite o endereço da pessoa a ser buscada\n");
            scanf("%99s", string);
            Pessoa *total = buscarPessoaPorEndereco(lista,string);
            if (total == NULL){
                printf("== PESSOA NÃO ENCONTRADA NESTA LISTA ==\n");
            }
            else{
                exibirDadosPessoa(total);
            }
            break;
        
        case 6:
            printf("Digite o telefone da pessoa a ser buscada\n");
            scanf("%15s", string);
            Pessoa *val = buscarPessoaPorTelefone(lista,string);
            if (val == NULL){
                printf("== PESSOA NÃO ENCONTRADA NESTA LISTA ==\n\n");
            }
            else{
                exibirDadosPessoa(val);
            }
            break;
        
        case 7:
            printf("==CADASTROS DA LISTA %d==\n",c);
    		exibirDadosCadastro(lista);
            if (lista->inicio == NULL)
            {
                printf("Não há cadastros nesta lista\n\n");
            }
            
            break;
        case 8 :
            return;
        default : printf("==Entre com a opcao correta de 1 a 8==\n\n");
			break;
        }
    } while (op!=8);
    
}
// Função principal que testa o cadastro
int main() { 
    int op, Nlista,idade;
    int total_list =0;
    Lista *cadastro =(Lista*) malloc(100*sizeof(Lista));
    lerArquivo(&cadastro[0]);
    if(cadastro[0].inicio!=NULL){
        total_list++;
    }
    do{ 
        Menu_principal(total_list);
		scanf("%d",&op);
        switch (op)
        {
        case 1:
        	cadastro[total_list].inicio = NULL;
            cadastro[total_list].tamanho = 0;
        	printf("== LISTA %d CRIADA ==\n\n", total_list+1);
        	total_list++;
		    break;

        case 2:
            printf("== Qual lista deseja acessar?\n");
            scanf("%d",&Nlista);
            if(Nlista<=0 || Nlista >total_list){
                printf("Essa lista não existe,por favor tente novamente.\n");
            } else{
                Menu_cad(Nlista,&cadastro[Nlista-1]);
            }
            break;

        case 3:
            Lista *novaLista = criarLista();
            int i=0;
            while (i<total_list) {
                No *aux = cadastro[i].inicio;
                for (int c = 0;c<cadastro[i].tamanho;c++){
                    inserirPessoa(novaLista,aux->pessoa);
                    aux = aux->prox;
                }
                i++;
            }
            free(cadastro);
            Lista *cadastro =(Lista*) malloc(100*sizeof(Lista));
            cadastro[0].inicio = novaLista->inicio;
            cadastro[0].tamanho = novaLista ->tamanho;
            total_list = 1;
            free(novaLista);
            break;            
        }
	}while(op!=0);
    escreverArquivoBinario(&cadastro[0]);

return 0;
}
