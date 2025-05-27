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
A FAZER

## Saída

Arquivo CSV com resultados: resultados/resultados.csv

Gráficos gerados na pasta graficos/:

- tempo_random.png, comparacoes_random.png
- tempo_sorted.png, comparacoes_sorted.png
- tempo_reverse.png, comparacoes_reverse.png

## Autores

Ana Julia Vieira P.A. Costa
Gabriel Menezes
