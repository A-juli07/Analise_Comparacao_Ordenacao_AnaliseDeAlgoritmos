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

ordenacao/
├── algoritmos/              # Algoritmos de ordenacao em C
│   ├── bubble_sort.c
│   ├── insertion_sort.c
│   ├── merge_sort.c
│   └── quick_sort.c
│
├── entradas/                # Arquivos de entrada gerados (sorted, random, reverse)
│   ├── entrada_1000_sorted.txt
│   ├── entrada_1000_random.txt
│   ├── entrada_1000_reverse.txt
│   └── ... (ate 1.000.000)
│
├── resultados/              # Resultados dos testes em formato CSV
│   └── resultados_3rep.csv
│
├── graficos/                # Graficos gerados e script Python
│   ├── graficos.py
│   ├── tempo_random.png
│   ├── comparacoes_sorted.png
│   └── ...
│
├── utils/                   # Utilitarios em C
│   ├── gerar_entradas.c
│   └── medir_performance.c
│
├── rodar_tudo.sh            # Script opcional para rodar tudo com um comando
├── .gitignore               # Ignora arquivos temporarios/executaveis
└── README.md 

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

## Autores

Ana Julia Vieira P.A. Costa
Gabriel Menezes
