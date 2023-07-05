from random import randint
tamanho_inicial = 100
salto = 1000
quantidade = 10

print("[", end="")

for i in range(0, quantidade):

    f = open(f"./Benchmark/tamanho_{tamanho_inicial}.txt", 'x')
    f.write(f"{tamanho_inicial} {tamanho_inicial*5}\n")

    print(f'"tamanho_{tamanho_inicial}.txt"', end="")
    if not (i + 1 == quantidade):
        print(",", end="")

    for x in range(0, tamanho_inicial):
        f.write(f"{randint(0, 999)} {randint(0, 999)}\n")

    tamanho_inicial += salto

print("]")