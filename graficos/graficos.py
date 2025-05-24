import pandas as pd
import matplotlib.pyplot as plt
import os

# Carregar dados
df = pd.read_csv("resultados/resultados.csv")

# Garantir que a pasta graficos/ existe
os.makedirs("graficos", exist_ok=True)

# Gráficos por tipo de entrada
tipos = ['random', 'sorted', 'reverse']
metricas = ['tempo', 'comparacoes']

for tipo in tipos:
    df_tipo = df[df['tipo'] == tipo]

    # 1. Tempo × Tamanho
    plt.figure(figsize=(8, 5))
    for alg in df_tipo['algoritmo'].unique():
        sub = df_tipo[df_tipo['algoritmo'] == alg]
        plt.plot(sub['tamanho'], sub['tempo'], label=alg, marker='o')
    plt.title(f'Tempo de Execução - Entrada {tipo}')
    plt.xlabel('Tamanho da Entrada')
    plt.ylabel('Tempo (s)')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f'graficos/tempo_{tipo}.png')

    # 2. Comparações × Tamanho
    plt.figure(figsize=(8, 5))
    for alg in df_tipo['algoritmo'].unique():
        sub = df_tipo[df_tipo['algoritmo'] == alg]
        plt.plot(sub['tamanho'], sub['comparacoes'], label=alg, marker='o')
    plt.title(f'Número de Comparações - Entrada {tipo}')
    plt.xlabel('Tamanho da Entrada')
    plt.ylabel('Comparações')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f'graficos/comparacoes_{tipo}.png')

print("✅ Gráficos salvos na pasta 'graficos/'")
