

#ifndef MODELS
#define MODELS

typedef struct
{
    char matricula[10];
    char nome[60];
    float notaFinal;
} Pessoa;

typedef struct
{
    int quantidadeAlunos;
    float mediaTurma;
    char alunoMenorNota[60];
    char alunoMaiorNota[60];
} Estatisticas;

#endif

