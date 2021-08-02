//Implementação recursiva do problema da mochila
#include <stdio.h>
#include <time.h>

int max(int a, int b) //o máximo entre dois números
{
    if (a > b) return a;
    else return b;
}

//o valor máximo que cabe numa mochila de capacidade W
int knapsack_rec(int W, int p[], int v[], int n) //complexidade O(2^n)
{  
    if (n == 0 || W == 0) return 0;

    if (p[n - 1] > W) //desconsidere o peso individual que exceda a capacidade
        return knapsack_rec(W, p, v, n-1); 
    
    else
        return max(v[n - 1] + knapsack_rec(W - p[n - 1], p, v, n-1), knapsack_rec(W, p, v, n-1));

/*
    pesos[] = {1, 1, 1}, W = 2, valores[] = {10, 20, 30}
    n = 3, W = 2
    
   K(W, n)
   K(2, 3):
        max(v[2] + K(2 - p[2], 3-1), K(2, 2))
        max(30 + K(1, 2), K(2, 2))

            30 + K(1, 2)
                    K(1, 2) : max(v[1] + K(1 - 1, 1), K(1, 1))
        
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

    clock_t start = clock();
    int r = knapsack_rec(W, pesos, valores, n);
    clock_t end = clock(); 

    double time_taken = (double)(end - start)/CLOCKS_PER_SEC; //o tempo que levou para a execução de knapsack_rec
    
    printf("----------------------------\n");
    printf("Maior valor possível: %d\n", r);
    printf("----------------------------\n");

    printf("Tempo de execução: %lf\n", time_taken);
    return 0;
}