import time, os, subprocess, openpyxl
 
book = openpyxl.Workbook()
book.create_sheet("resultados")
resultados_page = book['resultados']
 
progresso = 1
 
tamanho = 100
 
files =["tamanho_100.txt","tamanho_1100.txt","tamanho_2100.txt","tamanho_3100.txt","tamanho_4100.txt","tamanho_5100.txt","tamanho_6100.txt","tamanho_7100.txt","tamanho_8100.txt","tamanho_9100.txt"]
 
 
for arquivo in files:
    print(f"TESTANDO PARA {arquivo}...")
 
    print(str(progresso) + f"/{len(files)}")
    progresso += 1
 
    try:
        start = (time.time() * 1000)
 
        subprocess.call(['/home/otavio/Documents/unifal/aeds3/DataStructures/knapsackMetaheuristics/GRASP',
                        f'./Benchmark{arquivo}'], 
                        stdout=subprocess.DEVNULL,
                        timeout=600) ## timeout é o tempo máximo que o algoritmo pode ficar rodando
 
        end = (time.time() * 1000)
 
        elpsed_time = end - start
 
    except Exception:
         elpsed_time = -1
 
    resultados_page.append([f'{tamanho}',f'{elpsed_time}'])
    tamanho += 100
 
 
    print("========DONE========")
 
book.save("resultados.xlsx")