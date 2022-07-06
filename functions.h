#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "models.h"

#define caminhoArquivo "produtos.bin"

char tiposProdutos[6][20] = {"", "Mouse e teclados", "Processadores", "HDs e SSDs", "Gabinetes", "Outros"};

#ifndef FUNCTIONS
#define FUNCTIONS

void clear()
{
    system("cls");
}

void ln()
{
    printf("\n");
}

void erroAbrirArquivo()
{
    printf("\nNao e possivel abrir o arquivo!\n");
}

FILE *abrirArquivo(char modo[4])
{
    return fopen(caminhoArquivo, modo);
}

void escreverArquivo(Produto produto)
{
    FILE *file = abrirArquivo("ab+");
    if (file)
    {
        fwrite(&produto, sizeof(Produto), 1, file);
    }
    else
    {
        erroAbrirArquivo();
    }
    fclose(file);
}

void atualizarArquivo(Produto produto)
{
    FILE *file = abrirArquivo("rb+");
    if (file)
    {
        fseek(file, produto.indice * sizeof(Produto), SEEK_SET);
        fwrite(&produto, sizeof(Produto), 1, file);
    }
    else
    {
        erroAbrirArquivo();
    }
    fclose(file);
}

Produto lerArquivo(int opt, int codigo)
{
    int c = 0;
    int achou = 0;
    Produto produto;
    FILE *file = abrirArquivo("rb");
    if (file)
    {
        while (fread(&produto, sizeof(Produto), 1, file))
        {
            if (produto.deleted == 0)
            {
                achou = 1;
            }
            
            if (opt == 1)
            {
                if (produto.deleted == 0)
                {

                    printf("\nCodigo do produto: %d\nNome do produto: %s\nValor unitario: %lf\nQuantidade: %d\nGrupo do produto: %s\n", produto.codigo, produto.nome, produto.valor, produto.quantidade, tiposProdutos[produto.tipo]);
                    printf("===================================");
                }
            }
            else if (opt == 2)
            {

                if (codigo == produto.codigo && produto.deleted == 0)
                {

                    produto.indice = c;
                    fclose(file);
                    return produto;
                    // printf("\nCodigo do produto: %d\nNome do produto: %s\nValor unitario: %f\nQuantidade: %d\nGrupo do produto: %s\n", produto.codigo, produto.nome, produto.valor, produto.quantidade, tiposProdutos[produto.tipo]);
                }
            }
            c++;
        }
        ln();
        if (c > 0 && achou == 0)
        {
            ln();
            printf("Nao ha produtos cadastrados");
            ln();
        }
        ln();
        produto.codigo = 0;
        return produto;
    }
    else
    {
        erroAbrirArquivo();
    }
}

Produto informaProduto(Produto produtoAntigo)
{

    int codigo = 0;

    Produto produto;

    produto.codigo = 0;
    produto.deleted = 0;
    if (produtoAntigo.codigo > 0)
    {
        strcpy(produto.nome, produtoAntigo.nome);
        produto.quantidade = produtoAntigo.quantidade;
        produto.tipo = produtoAntigo.tipo;
        produto.valor = produtoAntigo.valor;
        produto.codigo = produtoAntigo.codigo;
    }

    ln();
    printf("Nome do produto");
    // printf("%d", strcmp(produtoAntigo.nome, ""));
    strcmp(produtoAntigo.nome, "") > 0 ? printf(" (%s):", produtoAntigo.nome) : printf(":");
    fflush(stdin);
    gets(produto.nome);
    do
    {
        ln();
        printf("Valor unitario");
        produtoAntigo.valor > 0.0 ? printf(" (%f):", produtoAntigo.valor) : printf(":");
        fflush(stdin);
        scanf("%lf", &produto.valor);
        if (produto.valor <= 0.0)
        {
            ln();
            printf("Valor invalido");
        }
    } while (produto.valor <= 0.0);
    do
    {
        ln();
        printf("Quantidade do produto");
        produtoAntigo.quantidade > 0 ? printf(" (%d):", produtoAntigo.quantidade) : printf(":");
        fflush(stdin);
        scanf("%d", &produto.quantidade);
        if (produto.quantidade <= 0)
        {
            ln();
            printf("Quantidade invalida");
        }
    } while (produto.quantidade <= 0);
    do
    {
        ln();
        printf("Grupo do produto");
        produtoAntigo.tipo > 0 ? printf(" (%s):", tiposProdutos[produtoAntigo.tipo]) : printf(":");
        ln();
        printf("\t1 - Mouse e teclados");
        ln();
        printf("\t2 - Processadores");
        ln();
        printf("\t3 - HDs e SSDs");
        ln();
        printf("\t4 - Gabinetes");
        ln();
        printf("\t5 - Outros");
        ln();
        fflush(stdin);
        scanf("%d", &produto.tipo);
        switch (produto.tipo)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            break;
        default:
            ln();
            printf("Opcao invalida");
            break;
        }
    } while (produto.tipo > 5 || produto.tipo < 1);

    ln();
    if (produto.codigo == 0)
    {
        printf("Gerando codigo do produto...");
        srand(time(NULL)); // Initialization, should only be called once.
        produto.codigo = (rand() % LIMIT_RAND) + 1;
        ln();
        printf("Codigo: %d", produto.codigo);
    }

    ln();

    return produto;
}

void cadastrarProduto()
{
    clear();
    printf("Cadastro de produto");
    ln();
    ln();
    Produto produto;
    strcpy(produto.nome, "");
    produto.valor = 0.0;
    produto.quantidade = 0;
    produto.tipo = 0;
    produto.codigo = 0;
    produto.deleted = 0;
    escreverArquivo(informaProduto(produto));
}

void listarProdutos()
{
    clear();
    printf("===================================");
    lerArquivo(1, 0);
    printf("===================================");
    ln();
    system("pause");
    clear();
}

void atualizarProduto()
{
    clear();
    int codigo;
    printf("Atualizacao de produtos!");
    ln();
    ln();
    printf("Informe o codigo: ");
    fflush(stdin);
    scanf("%d", &codigo);
    Produto produtoAntigo = lerArquivo(2, codigo);
    if (produtoAntigo.codigo > 0)
    {
        Produto produtoNovo = informaProduto(produtoAntigo);
        produtoNovo.deleted = 0;
        produtoNovo.indice = produtoAntigo.indice;
        atualizarArquivo(produtoNovo);
    }
    else
    {
        ln();
        printf("Codigo nao encontrado!");
        ln();
    }
}

void deletarProduto()
{
    clear();
    printf("Exclusao de produtos!");
    ln();
    ln();
    Produto produto;
    int codigo;
    printf("Informe o codigo: ");
    fflush(stdin);
    scanf("%d", &codigo);
    produto = lerArquivo(2, codigo);
    if (produto.codigo > 0)
    {
        produto.deleted = 1;
        atualizarArquivo(produto);
    }
    else
    {
        ln();
        printf("Codigo nao encontrado!");
        ln();
    }
}

#endif