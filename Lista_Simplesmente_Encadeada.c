#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct no {
    int valor;
    struct no *prox;
};

typedef struct no Lista;

Lista* criarLista() {
    return NULL;
}

int listaVazia(Lista *lista) {
    if (lista == NULL)
        return 1;

    return 0;
}

void exibirLista(Lista *lista) {

    if (listaVazia(lista))
        printf("\nLista vazia");
    else {
        Lista *pont;
        for (pont = lista; pont != NULL; pont = pont->prox)
            printf("%d -> ", pont->valor);
    }

    printf("\n");
}

Lista* inserirNoInicioLista(Lista *lista, int valor) {
    //reserva mem�ria para o novo n�
    Lista* novoNo = (Lista*) malloc(sizeof(Lista));
    novoNo->valor = valor;
    novoNo->prox = lista;

    return novoNo;
}

Lista* inserirNoFinalLista (Lista* lista, int valor) {

    Lista* novoNo = (Lista*)malloc(sizeof(Lista));
    novoNo->prox = NULL;
    novoNo->valor = valor;

    if (listaVazia(lista))
        lista = novoNo;
    else {
        Lista *pont;
        for (pont = lista; pont != NULL; pont = pont->prox) {
            if (pont->prox == NULL) { //encontrou o �ltimo
                pont->prox = novoNo;
                break;
            }
        }
    }

    return lista;
}

Lista* inserirNoOrdenado (Lista *lista, int valor) {
    if (lista == NULL) {
       lista = inserirNoInicioLista(lista, valor);
       return lista;
    }
    else if (lista->prox == NULL) { //s� tem um n�
        if (lista->valor < valor)
            lista = inserirNoFinalLista(lista, valor);
        else
            lista = inserirNoInicioLista(lista, valor);

        return lista;
    }
    else {
        Lista *no_atual, *no_anterior;
        for (no_atual = lista; no_atual != NULL; no_atual = no_atual->prox) {

            if (no_atual->valor > valor) {
                if (no_atual == lista) //n� entra na frente
                    lista = inserirNoInicioLista(lista, valor);
                else {
                    // n� entra no meio na ordem certa
                    Lista *novo_no = (Lista*)malloc(sizeof(Lista));
                    novo_no->valor = valor;
                    novo_no->prox  = no_atual;
                    no_anterior->prox = novo_no;
                }
                return lista;
            }
            no_anterior = no_atual;
        }
        //o n�mero � maior que todos valores dos n�s existentes
        inserirNoFinalLista(lista, valor);
    }
    return lista;
}

int alterarElemento(Lista *lista, int valor) {
int var, novovalor;
    if (listaVazia(lista))
        return 0;
    else {

        Lista* pont;
        for (pont = lista; pont != NULL; pont = pont->prox) {
            if (pont->valor == valor){
            		printf("Digite o novo valor: ");
            		scanf("%d", &novovalor);
            		pont->valor = novovalor;;
            		return 1;
				}           
        }

        return 0; //se n�o achar
    }

}

int pesquisarElemento(Lista *lista, int valor) {

    if (listaVazia(lista))
        return 0;
    else {

        Lista* pont;
        for (pont = lista; pont != NULL; pont = pont->prox) {
            if (pont->valor == valor)
                return 1;
        }

        return 0; //se n�o achar
    }

}

int totalElementosLista(Lista *lista) {
    if (listaVazia(lista))
        return 0;
    else {

        Lista *pont;
        int totalElementos = 0;
        for (pont = lista; pont != NULL; pont = pont->prox)
            totalElementos++;

        return totalElementos;
    }
}

Lista* removerInicioLista(Lista *lista) {

    if (listaVazia(lista))
        return NULL;
    else {
        Lista *removerNo = lista;

        if (lista->prox != NULL) //tem pelo menos 2 n�s
            lista = lista->prox;
        else  //tem apenas um n�s
            lista = NULL;

        free(removerNo);

        return lista;
    }
}

Lista* removerFinalLista(Lista *lista) {
	Lista *no;
	
    if (!listaVazia(lista)) {
        if (lista->prox == NULL) { //verifica se existe s� 1 n� {
            free(lista);
            lista = NULL;
        }
        else {
           for (no = lista; no != NULL; no = no->prox) {
               if (no->prox->prox == NULL) { //identifica pen�lt. n�
                    Lista *removeNo = no->prox;
                    no->prox = NULL;
                    free(removeNo);
                    break;
                }
            }
        }
    }
    return lista;
}

Lista* removerQualquerNo (Lista *lista, int valor) {
    Lista *no_atual, *no_anterior;
    for (no_atual=lista; no_atual != NULL; no_atual=no_atual->prox) {
        if (no_atual->valor == valor) {
            if (no_atual == lista) {
                //n� encontrado est� no in�cio da lista
                lista = removerInicioLista(lista);
                break;
            }
                if (no_atual->prox == NULL) {
                //n� encontrado est� no fim da lista
                removerFinalLista(lista);
                break;
            }
            //n� encontrado est� no meio da lista
            no_anterior ->prox = no_atual->prox;
            free(no_atual);
            break;
        }
        else
            no_anterior = no_atual;
    }
    return lista;
}

void menu() {
	int resposta, num;
    Lista *lista1 = criarLista();

    do {
        printf("\n0 - Sair do programa\n");
        printf("1 - Inserir elemento de forma ordenada\n");
        printf("2 - Alterar Elemento\n");
        printf("3 - Excluir Elemento\n");
        printf("4 - Localizar Elemento\n");
        printf("5 - Exibir Todos Elementos\n");
        printf("6 - Exibir quantidade de elementos da lista\n");
        printf("Informe uma op��o: ");
        scanf("%d", &resposta);

        switch (resposta) {
            case 0:
                printf("\nFim do Programa\n");
                break;
            case 1:
                printf("Digite o n�mero:\n");
                scanf("%d", &num);
                lista1 = inserirNoOrdenado(lista1, num);
                printf("\n");
                exibirLista(lista1);
                system("pause");
                break;
            case 2:
                printf("Digite o n� que deseja alterar: \n");
                scanf("%d", &num);
                if (alterarElemento(lista1, num))
                    printf("\nElemento encontrado e alterado\n");
                else
                    printf("\nElemento n�o encontrado\n");
                    system("pause");
                break;
            case 3:
                printf("Digite o valor do n� para remo��o: \n");
                scanf("%d", &num);
                printf("\n");
                lista1 = removerQualquerNo(lista1, num);
                exibirLista(lista1);
                system("pause");
                break;
            case 4:
                printf("Digite o n� para busca: \n");
                scanf("%d", &num);
                if (pesquisarElemento(lista1, num))
                    printf("\nEncontrado\n");
                else
                    printf("\nN�o encontrado\n");
                    system("pause");
                break;
            case 5:
                exibirLista(lista1);
                system("pause");
                break;
            case 6:
                printf("\nTotal de elementos: %d\n", totalElementosLista(lista1));
                system("pause");
                break;
            default:
                printf("\nOp��o inv�lida, por favor selecione outra\n");
                system("pause");
                break;
        }
        
        system("cls");

    } while (resposta != 0);
}

int main() {
            
    setlocale(LC_ALL, "portuguese");
    menu();
}
