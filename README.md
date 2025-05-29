# Análise e Comparação de Algoritmos de Ordenação em C

## Objetivo
Implementar e comparar diferentes algoritmos de ordenação em C, avaliando-os com base em:
- Tempo de execução
- Número de comparações realizadas

## Algoritmos Implementados
- Bubble Sort
- Insertion Sort
- Merge Sort
- Quick Sort

## Tipos de entrada geradas

- Ordenado crescente (`sorted`)
- Ordenado decrescente (`reverse`)
- Aleatório (`random`)

## Estrutura de Diretórios

- Algoritmos :
     - bubble_sort.c
     - insertion_sort.c
     - merge_sort.c
     - quick_sort.c
- Entradas : Entradas geradas como sorted, random e reverse entre 1000, 10000, 100000, 500000, 1000000;
- Graficos :
     - graficos.py : Codigo para criação dos graficos.
     - resultados_graficos : Primeiro arquivo de teste
     - resultados_graficos_5rep : Primeiro arquivo de resultados com 5rep
- Resultados:
     - resultados.csv : Rewsultados com 1rep
     - resultados_3rep.csv : Resultados com 5rep
- Utils:
     - gerar_entradas.c : Gerador de entradas
     - medir_performance.c : Medir a Performance

## Como Executar

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/A-juli07/Analise_Comparacao_Ordenacao_AnaliseDeAlgoritmos.git

2. **Gerar arquivos de entrada**
   ```bash
   gcc utils/gerar_entradas.c -o gerar_entradas
   ./gerar_entradas

3. **Executar os algoritmos e salvar os dados**
   ```bash
   gcc utils/medir_performance.c algoritmos/*.c -o medir
   ./medir

4. **Gerar os gráficos (requer Python)**
   ```bash
   pip install pandas matplotlib
   python graficos/graficos.py

## Ambiente de Execução
Os testes foram executados em um ambiente contendo Sistema Operacional
Windows 11 Home 64 bits. Nossa plataforma de testes foi um computador com processador Processador AMD Ryzen 5 5600, 3.5GHz (4.4GHz Turbo), 6-Cores 12-Threads,
Memória DDR4, 16GB, 3733Mhz, SSD 500GB Leitura 4800MBs e Gravação 2700MBs e Placa de Vídeo MSI NVIDIA GeForce RTX 3060 VENTUS 2X OC, LHR, 12GB GDDR6, DLSS, Ray Tracing.

## Saída

Arquivo CSV com resultados: resultados/resultados.csv

Gráficos gerados na pasta graficos/:

- tempo_random.png, comparacoes_random.png
- tempo_sorted.png, comparacoes_sorted.png
- tempo_reverse.png, comparacoes_reverse.png

## Insights dos Resultados

- Comparações Ordenadas
- ![comparações ordenadas](graficos/resultados_graficos_5rep/comparacoes_ordenado.png)
  
**Insertion Sort** destaca-se: faz apenas ~𝑛–1 comparações (linear), ficando absurdamente abaixo de todos os demais no eixo log.

**Bubble Sort** continua O(𝑛²) mesmo em vetor já ordenado (pois a implementação não interrompe cedo), explodindo no número de comparações conforme 𝑛 cresce.

**Merge Sort e Quick Sort** apresentam comportamento típico O(𝑛 log 𝑛), quase sobrepostos no gráfico, com Quick Sort ligeiramente acima de Merge (devido às pequenas variações no particionamento), mas ambos muito mais eficientes que Bubble/Insertion para grandes 𝑛.

## Autores

Ana Julia Vieira P.A. Costa e
Gabriel Menezes
