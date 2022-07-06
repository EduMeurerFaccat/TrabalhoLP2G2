#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "models.h"

int main()
{
    int id;
    do
    {
        ln();
        printf("----MENU----\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Atualizar produto\n");
        printf("4 - Deletar produto\n");
        printf("5 - SAIR\n");
        printf("Digite sua opcao: ");
        fflush(stdin);
        scanf("%d", &id);
        switch (id)
        {
        case 1:
            cadastrarProduto();
            break;
        case 2:
            listarProdutos();
            break;
        case 3:
            atualizarProduto();
            break;
        case 4:
            deletarProduto();
            break;
        default:
        printf("\nOpcao invalida!\n");
        }
    } while (id != 5);

    return 0;
}