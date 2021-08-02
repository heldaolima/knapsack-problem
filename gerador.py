from random import randint

#gera valores e pesos aleatórios entre a e b 
print("---<Gerador de casos de teste>---")
a = 10
b = 100

n = int(input("Número de casos: "))
     
for i in range(0, n):
    print(f"{randint(a, b)} {randint(a, b)}")
