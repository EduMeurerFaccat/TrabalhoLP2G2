#include <stdio.h>
#include <string.h>
#include "models.h"

#define caminhoArquivo "alunos.bin"

#ifndef FUNCTIONS
#define FUNCTIONS

void erroAbrirArquivo()
{
    printf("\nNao e possivel abrir o arquivo!\n");
}

FILE *abrirArquivo(char caminho[50])
{
    return fopen(caminho, "ab+");
}

void escrever(Pessoa aluno)
{
    FILE *file = abrirArquivo(caminhoArquivo);
    if (file)
    {
        fwrite(&aluno, sizeof(Pessoa), 1, file);
    }
    else
    {
        erroAbrirArquivo();
    }
    fclose(file);
}

void lerArquivo(int opt, char matricula[10])
{
    Pessoa aluno;
    Estatisticas est;
    est.quantidadeAlunos = 0;
    float somaNotas, maiorNota = 0, menorNota = 10;
    FILE *file = abrirArquivo(caminhoArquivo);
    int findCont = 0;
    if (file)
    {
        while (!feof(file))
        {
            if (fread(&aluno, sizeof(Pessoa), 1, file))
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

#endif