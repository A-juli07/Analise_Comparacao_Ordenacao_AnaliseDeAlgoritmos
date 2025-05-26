import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
import numpy as np

# Configurações otimizadas
sns.set_style("whitegrid")
plt.rcParams['figure.dpi'] = 72  # Reduzido para evitar erros de tamanho
plt.rcParams['savefig.dpi'] = 72
plt.rcParams['font.size'] = 9
plt.rcParams['axes.titlesize'] = 11
plt.rcParams['axes.labelsize'] = 10

def carregar_dados(caminho_arquivo):
    """Carrega e prepara os dados de forma segura"""
    try:
        df = pd.read_csv(caminho_arquivo)
        
        # Verifica colunas essenciais
        colunas_necessarias = ['algoritmo', 'tipo', 'tamanho', 'comparacoes', 'tempo']
        if not all(col in df.columns for col in colunas_necessarias):
            raise ValueError("Arquivo CSV não contém todas as colunas necessárias")
            
        # Tradução e formatação
        tipo_trad = {'sorted': 'Ordenado', 'random': 'Aleatório', 'reverse': 'Decrescente'}
        df['tipo'] = df['tipo'].map(tipo_trad)
        df['algoritmo'] = df['algoritmo'].str.title() + ' Sort'
        
        # Converter tamanhos para strings e categorias ordenadas
        df['tamanho_str'] = df['tamanho'].astype(str)
        df['tamanho_cat'] = pd.Categorical(df['tamanho_str'], categories=sorted(df['tamanho_str'].unique()), ordered=True)
        
        return df
    
    except Exception as e:
        print(f"Erro ao carregar dados: {str(e)}")
        return None

def plotar_tempo_separado(df, output_dir):
    """Gera gráficos de tempo otimizados"""
    if df is None:
        return
        
    tipos = df['tipo'].unique()
    
    for tipo in tipos:
        fig, ax = plt.subplots(figsize=(8, 5))  # Tamanho reduzido
        
        dados = df[df['tipo'] == tipo]
        
        # Gráfico de linha otimizado
        sns.lineplot(data=dados, x='tamanho_cat', y='tempo', 
                    hue='algoritmo', style='algoritmo',
                    markers=['o', 's', 'D', '^'],  # Marcadores diferentes
                    dashes=False, linewidth=1.5,
                    markersize=6, errorbar=None, ax=ax)
        
        # Ajustes de escala
        max_tempo = dados['tempo'].max()
        if max_tempo > 1:
            ax.set_yscale('log')
            ax.set_ylabel('Tempo (s) - Escala Log')
        else:
            ax.set_ylabel('Tempo (s)')
        
        # Configurações do gráfico
        ax.set_title(f'Tempo de Execução - Entrada {tipo}', pad=15)
        ax.set_xlabel('Tamanho do Vetor')
        ax.legend(title='Algoritmo', bbox_to_anchor=(1.05, 1), loc='upper left')
        ax.grid(True, linestyle=':', alpha=0.7)
        
        # Salvar figura
        nome_arquivo = os.path.join(output_dir, f"tempo_{tipo.lower()}.png")
        plt.savefig(nome_arquivo, bbox_inches='tight', pad_inches=0.3)
        plt.close(fig)
        print(f"Gráfico salvo: {nome_arquivo}")

def plotar_comparacoes_agrupadas(df, output_dir):
    """Gráficos de comparações otimizados"""
    if df is None:
        return
        
    tipos = df['tipo'].unique()
    
    for tipo in tipos:
        fig, ax = plt.subplots(figsize=(8, 5))  # Tamanho reduzido
        
        dados = df[df['tipo'] == tipo]
        
        # Gráfico de barras otimizado
        sns.barplot(data=dados, x='tamanho_cat', y='comparacoes', 
                   hue='algoritmo', palette='muted', ax=ax)
        
        # Escala logarítmica obrigatória para comparações
        ax.set_yscale('log')
        ax.set_ylabel('Número de Comparações (log)')
        
        # Configurações do gráfico
        ax.set_title(f'Comparações Realizadas - Entrada {tipo}', pad=15)
        ax.set_xlabel('Tamanho do Vetor')
        ax.legend(title='Algoritmo', bbox_to_anchor=(1.05, 1), loc='upper left')
        ax.grid(True, axis='y', linestyle=':', alpha=0.7)
        
        # Salvar figura
        nome_arquivo = os.path.join(output_dir, f"comparacoes_{tipo.lower()}.png")
        plt.savefig(nome_arquivo, bbox_inches='tight', pad_inches=0.3)
        plt.close(fig)
        print(f"Gráfico salvo: {nome_arquivo}")

def main():
    # Configuração de diretórios
    script_dir = os.path.dirname(os.path.abspath(__file__))
    output_dir = os.path.join(script_dir, 'resultados_graficos')
    
    # Criar diretório de saída se não existir
    os.makedirs(output_dir, exist_ok=True)
    
    # Caminho do arquivo de dados
    arquivo_resultados = os.path.join(script_dir, '../resultados/resultados.csv')
    
    if not os.path.exists(arquivo_resultados):
        print(f"Erro: Arquivo não encontrado - {arquivo_resultados}")
        return
    
    print("\nIniciando geração de gráficos...")
    
    # Carregar dados
    df = carregar_dados(arquivo_resultados)
    
    if df is not None:
        # Gerar gráficos
        print("\nGerando gráficos de tempo de execução...")
        plotar_tempo_separado(df, output_dir)
        
        print("\nGerando gráficos de comparações...")
        plotar_comparacoes_agrupadas(df, output_dir)
        
        print(f"\nProcesso concluído! Gráficos salvos em: {output_dir}")
    else:
        print("\nFalha ao gerar gráficos devido a erros nos dados.")

if __name__ == "__main__":
    main()