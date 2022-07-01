#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ACONSELHO SEMPRE ESCOLHER A OPÇÃO 1 AO ABRIR O PROGRAMA POIS O MESMO PRECISA PARA CARREGAR OS REGISTROS DO ARQUIVO.
FILE *ponteiroParaArquivo;
int cont = 0;
struct produtosRegistro
{
    int codigoProduto;
    char nomeProduto[100];
    int tipoProduto;
    int quantProduto;
    float valorProduto;
};
struct produtosRegistro produto[100];

void verificar()
{
    char textoLido[180];
    char codigoP[50];
    char nome[100];
    char tipoProd[4];
    char quantP[4];
    char valorP[4];
    int x, w;
    int contL;
    ponteiroParaArquivo = fopen("binario.txt", "rb");
    if (ponteiroParaArquivo == NULL)
    {
        printf("Nao foi possivel abrir arquivo.");
    }
    else
    {
        while (fgets(textoLido, 180, ponteiroParaArquivo) != NULL)
        {
            contL = 0;
            // PEGA O NOME
            for (x = 0, w = 0; x < strlen(textoLido); x++)
            {
                if (textoLido[x] != ';')
                {
                    nome[w] = textoLido[x];
                    produto[cont].nomeProduto[w] = textoLido[x];
                    w = w + 1;
                    contL = contL + 1;
                }
                else
                {
                    contL = contL + 1;
                    break;
                }
            }
            printf("Nome do Produto:%s\n", nome);

            // PEGA O TIPO DO PRODUTO
            for (x = contL, w = 0; x < strlen(textoLido); x++)
            {
                if (textoLido[x] != ';')
                {
                    tipoProd[w] = textoLido[x];
                    w = w + 1;
                    contL = contL + 1;
                }
                else
                {
                    contL = contL + 1;
                    break;
                }
            }
            printf("Tipo do Produto:%s\n", tipoProd);

            // PEGA A QUANTIDADE DO PRODUTO
            for (x = contL, w = 0; x < strlen(textoLido); x++)
            {
                if (textoLido[x] != ';')
                {
                    quantP[w] = textoLido[x];
                    w = w + 1;
                    contL = contL + 1;
                }
                else
                {
                    contL = contL + 1;
                    break;
                }
            }
            printf("Quantidade do Produto:%s\n", quantP);

            // PEGA O VALOR DO PRODUTO
            for (x = contL, w = 0; x < strlen(textoLido); x++)
            {
                if (textoLido[x] != ';')
                {
                    valorP[w] = textoLido[x];
                    w = w + 1;
                    contL = contL + 1;
                }
                else
                {
                    contL = contL + 1;
                    break;
                }
            }
            printf("Valor do Produto:R$%s\n", valorP);
            printf("\n");

            // PEGA O CODIGO DO PRODUTO
            for (x = contL, w = 0; x < strlen(textoLido); x++)
            {
                if (textoLido[x] != ';')
                {
                    codigoP[w] = textoLido[x];
                    w = w + 1;
                    contL = contL + 1;
                }
                else
                {
                    contL = contL + 1;
                    break;
                }
            }
            printf("Codigo do Produto:%s\n", codigoP);
            printf("\n");

            int codigo = atoi(codigoP);
            int tipo = atoi(tipoProd[0]);
            int quant = atoi(quantP);
            float valor = atof(valorP);

            produto[cont].codigoProduto = codigo;
            produto[cont].tipoProduto = tipo;
            produto[cont].quantProduto = quant;
            produto[cont].valorProduto = valor;
            cont = cont + 1;
        }
        fclose(ponteiroParaArquivo);
    }
}
void verificarRegistro()
{
    int n_codigo;
    printf("Qual codigo devo buscar?");
    scanf("%d", &n_codigo);

    int x;

    for (x = 0; x <= cont; x++)
    {
        if (produto[x].codigoProduto == n_codigo)
        {
            printf("Matricula:%d\n", produto[x].codigoProduto);
            printf("Nome:%s\n", produto[x].nomeProduto);
            if (produto[cont].tipoProduto == 1)
            {
                printf("%d - Mouse e teclados;\n", produto[cont].tipoProduto);
            }
            else if (produto[cont].tipoProduto == 2)
            {
                printf("%d - Processadores;\n", produto[cont].tipoProduto);
            }
            else if (produto[cont].tipoProduto == 3)
            {
                printf("%d - HD e SSD;\n", produto[cont].tipoProduto);
            }
            else if (produto[cont].tipoProduto == 4)
            {
                printf("%d - Gabinetes;\n", produto[cont].tipoProduto);
            };
            printf("Quantidade em estoque:%d\n", produto[cont].quantProduto);
            printf("Valor do Produto: R$%.2f\n", produto[cont].valorProduto);
            printf(" \n");
        }
        else
        {
            if (x == cont - 1 && produto[x].codigoProduto != n_codigo)
            {
                printf("Não encontramos esse produto!");
            }
        }
    }
}

void escreverRegistro()
{
    printf("1- Mouse e teclados \n");
    printf("2- Processadores \n");
    printf("3- HD e SSD\n");
    printf("4- Gabinetes\n");
    printf("Digita o codigo que corresponde ao grupo do produto: ");
    scanf("%d", &produto[cont].tipoProduto);

    printf("Digite o nome do produto: ");
    setbuf(stdin, 0);
    fgets(produto[cont].nomeProduto, 100, stdin);
    produto[cont].nomeProduto[strlen(produto[cont].nomeProduto) - 1] = '\0';

    printf("Digite a quantidade desse Produto no estoque: ");
    scanf("%d", &produto[cont].quantProduto);

    printf("Digite o valor do produto: ");
    scanf("%d", &produto[cont].valorProduto);

    printf("Digite o codigo desse Produto: ");
    scanf("%d", &produto[cont].codigoProduto);

    ponteiroParaArquivo = fopen("binario.txt", "ab+");
    fprintf(ponteiroParaArquivo, "%s;", produto[cont].nomeProduto);

    if (produto[cont].tipoProduto == 1)
    {
        fprintf(ponteiroParaArquivo, "%d - Mouse e teclados;", produto[cont].tipoProduto);
    }
    else if (produto[cont].tipoProduto == 2)
    {
        fprintf(ponteiroParaArquivo, "%d - Processadores;", produto[cont].tipoProduto);
    }
    else if (produto[cont].tipoProduto == 3)
    {
        fprintf(ponteiroParaArquivo, "%d - HD e SSD;", produto[cont].tipoProduto);
    }
    else if (produto[cont].tipoProduto == 4)
    {
        fprintf(ponteiroParaArquivo, "%d - Gabinetes;", produto[cont].tipoProduto);
    };

    fprintf(ponteiroParaArquivo, "%s;", produto[cont].quantProduto);

    fprintf(ponteiroParaArquivo, "%.2f;", produto[cont].valorProduto);

    fprintf(ponteiroParaArquivo, "%d\n;", produto[cont].codigoProduto);

    printf("Cadastrado! \n");
    printf(" \n");
    fclose(ponteiroParaArquivo);
    cont = cont + 1;
}

void main()
{
    int id;
    do
    {
        printf("----MENU----\n");
        printf("1 - Apresentar todo conteúdo do arquivo\n");
        printf("2 - Apresentar conteúdo de um registro\n");
        printf("3 - Cadastrar um registro\n");
        printf("4 - Estatisticas do registro\n");
        printf("5 - SAIR\n");
        printf("Digite sua opção: ");
        scanf("%d", &id);
        switch (id)
        {
        case 1:
            verificar();
            break;
        case 2:
            verificarRegistro();
            break;
        case 3:
            escreverRegistro();
            break;
        case 4:
            estatisticasRegistro();
            break;
        }
    } while (id != 5);
}