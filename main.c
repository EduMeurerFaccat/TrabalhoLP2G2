#include <stdio.h>
#include <string.h>

typedef struct
{
    char matricula[10];
    char nome[60];
    float notaFinal;
} Aluno;

typedef struct
{
    int quantidadeAlunos;
    float mediaTurma;
    char alunoMenorNota[60];
    char alunoMaiorNota[60];
} Estatisticas;

char caminhoArquivo[50] = "alunos.bin";

void erroAbrirArquivo()
{
    printf("\nNao e possivel abrir o arquivo!\n");
}

FILE *abrirArquivo(char caminho[50])
{
    return fopen(caminho, "ab+");
}

void escrever(Aluno aluno)
{
    FILE *file = abrirArquivo(caminhoArquivo);
    if (file)
    {
        fwrite(&aluno, sizeof(Aluno), 1, file);
    }
    else
    {
        erroAbrirArquivo();
    }
    fclose(file);
}

void lerArquivo(int opt, char matricula[10])
{
    Aluno aluno;
    Estatisticas est;
    est.quantidadeAlunos = 0;
    float somaNotas, maiorNota = 0, menorNota = 10;
    FILE *file = abrirArquivo(caminhoArquivo);
    int findCont = 0;
    if (file)
    {
        while (!feof(file))
        {
            if (fread(&aluno, sizeof(Aluno), 1, file))
            {
                if (opt == 1)
                {
                    printf("\nMatricula: %s\nNome: %s\nNota final: %f\n\n", aluno.matricula, aluno.nome, aluno.notaFinal);
                }
                else if (opt == 2)
                {
                    if (!strcmp(aluno.matricula, matricula))
                    {
                        findCont = 1;
                        printf("\nMatricula: %s\nNome: %s\nNota final: %f\n\n", aluno.matricula, aluno.nome, aluno.notaFinal);
                    }
                }
                else if (opt == 3)
                {
                    est.quantidadeAlunos++;
                    somaNotas += aluno.notaFinal;
                    if (aluno.notaFinal > maiorNota)
                    {
                        maiorNota = aluno.notaFinal;
                        strcpy(est.alunoMaiorNota, aluno.nome);
                    }

                    if (aluno.notaFinal < menorNota)
                    {
                        menorNota = aluno.notaFinal;
                        strcpy(est.alunoMenorNota, aluno.nome);
                    }
                }
            }
        }
        if (findCont == 0 && opt == 2)
        {
            printf("\nNao ha registro com a matricula %s", matricula);
        }
        if (opt == 3)
        {
            est.mediaTurma = somaNotas / est.quantidadeAlunos;
            printf("\nQuantidade de alunos existentes no arquivo: %d", est.quantidadeAlunos);
            printf("\nMedia da turma: %f", est.mediaTurma);
            printf("\nNome do aluno com a menor nota: %s", est.alunoMenorNota);
            printf("\nNome do aluno com a maior nota: %s", est.alunoMaiorNota);
            printf("\n");
        }
    }
    else
    {
        erroAbrirArquivo();
    }
}

int main()
{
    int opt, repetir = 1;
    Aluno aluno;
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