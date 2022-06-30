#include <stdio.h>
#include <string.h>
#include "functions.h"

int main()
{
    int opt, repetir = 1;
    Pessoa aluno;
    char matricula[10];
    do
    {
        do
        {
            printf("\nDigite a opcao desejada:\n1 - Apresentar todo conteudo do arquivo\n2 - Apresentar conteudo de um registro\n3 - Cadastrar um registro\n4 - Estatisticas\n5 - Fechar o programa\n");
            scanf("%d", &opt);

            if (opt < 1 || opt > 5)
            {
                printf("\nOpcao invalida\n");
            }
            system("cls");
        } while (opt < 1 || opt > 5);
        
        switch (opt)
        {
            case 1:
                lerArquivo(1, "");
                break;
            case 2:

                printf("\nInforme a matricula: ");
                scanf("%s", aluno.matricula);
                lerArquivo(2, aluno.matricula);
                break;
            case 3:
                printf("\nNome: ");
                scanf("%s", aluno.nome);
                printf("\nMatricula: ");
                scanf("%s", aluno.matricula);
                printf("\nNota Final: ");
                scanf("%f", &aluno.notaFinal);

                escrever(aluno);

                break;
            case 4:
                lerArquivo(3, "");
                break;
            case 5:
                repetir = 0;
                break;
        }
        printf("\n");
        if(repetir > 0)
            system("pause");
        system("cls");
    } while (repetir > 0);

    return 0;
}