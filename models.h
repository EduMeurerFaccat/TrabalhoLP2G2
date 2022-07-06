

#ifndef MODELS
#define MODELS


#define LIMIT_RAND 100
typedef struct
{
    int indice;
    int codigo;
    char nome[100];
    int tipo;
    int quantidade;
    double valor;
    int deleted;
    
} Produto;

typedef struct
{
    int quantidadeAlunos;
    float mediaTurma;
    char alunoMenorNota[60];
    char alunoMaiorNota[60];
} Estatisticas;

#endif

