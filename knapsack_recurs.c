//Implementação recursiva do problema da mochila
#include <stdio.h>

int max(int a, int b) //o máximo entre dois números
{
    if (a > b) return a;
    else return b;
}

//o valor máximo que cabe numa mochila de capacidade W
int knapsack_rec(int W, int p[], int v[], int n)
{  
    if (n == 0 || W == 0) return 0;

    if (p[n-1] > W) //desconsidere o peso individual que exceda a capacidade
        return knapsack_rec(W, p, v, n-1); 
    
    else
        return max(v[n - 1] + knapsack_rec(W - p[n - 1], p, v, n-1), knapsack_rec(W, p, v, n-1));
/*
Considere:
W = 5;
            0   1    2
valores = [60, 100, 120]
pesos =   [1,    2,   3]

     w  n    
rec (5, 3):
    passa do primeiro if
    passa do segundo if [(p[2] > 5) == 0]
    no else:
        max(v[2] + rec(5 - p[2], 3-1), rec(5, 3-1)), ou seja,
        max(120 + rec(5 - 3, 2), rec(5, 2))
        *no primeiro parâmetro, adiciona-se o item 3; no segundo, continua-se o algoritmo
        *ou seja, o else pergunta qual o máximo valor entre o elemento da rodada e as rodadas que faltam
    
    
    rec(2, 2):
        passa do primeiro if
        passa no segundo if (p[1] > 2 == 0)
        else:
            max(v[1] + rec(2-p[1], 2-1), rec(2, 2-1))
            max(100 + rec(2 - 2, 1)), rec(2,1 ))
            *no primeiro parâmatro, a próxima chamada de rec esgota a capacidade de da mochila, pois teremos w == 0
            *no segundo, veremos se vale a pena continuar adicionando

        rec(2-2, 1) cai no primeiro if (w == 0) e retorna 0
        temos max(100 + 0, rec(2, 1))

            rec(2, 1):
                passa no primeiro if
                passa no segunod [p[0] >= 5 == 0]
                else:
                    max(v[1-1] + rec(2 - p[0], 1-1), rec(2, 0))
                    max(60 + rec(2-1, 0), rec(2, 0))

                    rec(2-1, 0) e rec(2,0) retornam 0.

                    portanto, max(60, 0) == 0
                    portanto, rec(2, 1) == 60
            
        max(100 + 0 , rec(2, 1))  == max(100, 60) == 100
        Ou seja: na possibilidade em que temos um valor 100 e mais 2 de peso restando na mochila, é melhor manter o 100
        
        max(120 + rec(5 - 3, 2), rec(5, 2))  
        max(120 + 100, rec(5, 2))

        rec(5,2):
            vai pro else:
                max(v[2-1] + rec(5 - p[2-1], 2-1), rec(5, 2-1))
                max(100 + rec(5-2, 1), rec(5, 1))
                
                rec(3, 1):
                    else:
                        max(v[0] + rec(3-1, 0), rec(3, 0))
                        vai dar max(60 + 0, 0), que retorna 60
                
                rec(5, 1) retorna 60 (capacidade total e apenas o item 1, que vale 60)
                Assim:
            
                max(100 + 60, 60) == 160
        
        max(220, rec(5, 2)) == max(220, 160) == 220

        220 é a resposta final 
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
    printf("Maior valor possível: %d\n", knapsack_rec(W, pesos, valores, n));
    printf("----------------------------\n");

    return 0;
}