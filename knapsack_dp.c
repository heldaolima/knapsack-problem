#include <stdio.h>

int max(int a, int b)
{
    if (a > b) return a;
    else return b;
}

void print_matriz(int W, int n, int k[][W+1])
{
    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < W+1; j++) {printf("%d ", k[i][j]);}
        
        printf("\n");
    }
}

int knapsack_dp(int W, int p[], int v[], int n)
{
    int K[n + 1][W + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (p[i-1] <= w)
                K[i][w] = max(v[i - 1] + K[i - 1][w - p[i - 1]], K[i - 1][w]);
            else
                K[i][w] =  K[i - 1][w];
        }
    }
    print_matriz(W, n, K);
    return K[n][W];

    
/*
    W = 5;
            0   1    2
valores = [60, 100, 120]
pesos =   [1,    2,   3]

matriz[n+1]x[W+1]: 0 1 2 3 4 5
                 0  _ _ _ _ _ _
                 1  _ _ _ _ _ _
                 2  _ _ _ _ _ _
                 3  _ _ _ _ _ _
                 
m[x][y]
Eixo X -> quantos itens são analisados no momento, para serem inseridos
Eixo Y -> unidades de peso da mochila utilizados no momento

O algoritmo preenche a tabela
Deste modo, a resolução do problema se encontra, nesse caso, em m[3][5], que é onde todos os produtos foram inseridos e todo o peso foi ocupado

for (i): considera todos os itens
    i = 0: 
    for (w): considera as unidades de peso
        
        i = 0, w = 0
        if (i == 0|| w == 0) -> K[0][0] = 0
            Na quantidade 0, unidade de peso 0, eu consigo armazenar 0 produtos
        
        i= 0, w = 1
        if (i == 0|| w == 0) -> K[0][1] = 0
            Considerando 1 unidade de peso, mas 0 produto, a quantidade segue 0
        
        i = 0, w = 2 -> K[0][2] = 0
            Ou seja, se eu não considerar item nenhum, o resultado é sempre 0
    
    Matriz quando i == 0
    
    0 0 0 0 0 0
    _ _ _ _ _ _
    _ _ _ _ _ _
    _ _ _ _ _ _

    i = 1, w = 0 -> K[1][0] = 0
    Inserir 1 item na mochila, porém sem unidades de peso disponíveis

    i = 1, w = 1
    else if (p[i-1] <= w) 1 <= 1 -> true, então:
        k[1][1] = max(v[1-1] + K[1-1][1-p[1-1]], k[1-1][1])
                  max(v[0] + k[0][0], k[0][1])
                  max(60 + 0, 0) -> 60
        k[1][1] = 60

        1 unidade de peso e 1 item, que tem peso 1, é o próprio item, cujo peso é 60
    
    i = 1, w = 2
    (p[0] <= 2)? (1 <= 2) -> true
    k[1][2] = max(v[0] + k[0][2-p[0]], k[0][2])
              max(60 + 0, 0) -> 60 
    k[1][2] = 60
    1 item, que pesa 1, e duas unidades de peso
    
    max significa -> o item mais o seu anterior ou nenhum
    para i == 1, o item anterior é sempre 0; portanto, será sempre o valor do item 0.
    matriz até aqui (mais a consideração de w = 0 em todo i): 

    0 0 0 0 0 0
    0 60 60 60 60 60
    0 _ _ _ _ _
    0 _ _ _ _ _

    i = 2, w = 1
    (p[1] <= 1)? (2 <= 1)? -> false
    else:
        k[2][1] = k[1][1]
        dois itens com a capacidade 1 é a mesma coisa de 1 item e 1 capacidade
        k[1][1] == 60
    O mesmo será válido para 3 itens (que são ainda mais que 2). Portanto, teremos a tabela: 
    
    0 0 0 0 0 0
    0 60 60 60 60 60
    0 60 _ _ _ _
    0 60 _ _ _ _
    
    i = 2, w = 2
    (p[1] <= 2)? (2 <= 2) -> true
    
    k[2][2] = max(v[1] + k[1][2 - p[1]], k[1][2])
              max(100 + k[1][2 - 2], k[1][2])
              max(100 + k[1][0], 60)
              max(100 + 0, 60) -> 100

    i = 2, w = 3
    (p[1] <= 3)? -> true
    k[2][3] = max(100 + k[1][3-2], k[1][3])
              max(100 + 60, 60) -> 160
    se para a capacidade 3 eu consigo 160, para capacidades maiores também. Então a tabela é:
    
    0 0 0 0 0 0
    0 60 60 60 60 60
    0 60 100 160 160 160
    0 60 _ _ _ _

    i = 3, w = 2
    (p[2] <= 2) (3 <= 2) -> false
    else:
        k[3][2] = k[2][2] = 100
        O item não cabe numa mochila de capacidade 2. Então, uso o maior que eu consegui para capacidades 2, no caso 100
    
    i = 3, w = 3
    k[3][3] = max(v[2] + k[2][3-3], k[2][3])
              max(120 + 0, 160) -> 160
              
              Inserir o terceiro item, de peso 3, ou os dois primeiros, cuja soma é 3? Segunda opção, que tem valor maior
    k[3][3] = 160

    i = 3, w = 4
    k[2][4] = max(120 + k[2][4-3], k[2][4])
              max(120 + 60, 160) -> 180
    k[2][4] = 180

    final:
    i = 3, w = 5
    k[2][5] = max(120 + k[2][5-3], k[2][5])
              max(120 + 100, 160) -> 220
    k[2][5] = 220 == resposta final

    0 0 0 0 0 0
    0 60 60 60 60 60
    0 60 100 160 160 160
    0 60 100 160 180 220
*/

}

int main()
{
    printf("---<Knapsack Problem>---\n");
    
    int n;
    printf("\nNúmero de itens: ");
    scanf("%d", &n);

    int valores[n], pesos[n], W;

    for (int i = 0; i < n; i++)
    {
        printf("\nValor do item [%d]: ", i);
        scanf("%d", &valores[i]);
        printf("Peso do item [%d]: ", i);
        scanf("%d", &pesos[i]);
    }

    printf("\nCapacidade da mochila: ");
    scanf("%d", &W);

    printf("----------------------------\n");
    printf("Maior valor possível: %d\n", knapsack_dp(W, pesos, valores, n));
    printf("----------------------------\n");

    return 0;
}
