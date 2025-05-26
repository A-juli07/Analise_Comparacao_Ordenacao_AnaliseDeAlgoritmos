import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
import numpy as np

# Configurações de estilo melhoradas
sns.set_style("whitegrid")
plt.rcParams['figure.dpi'] = 100
plt.rcParams['savefig.dpi'] = 100
plt.rcParams['font.size'] = 9
plt.rcParams['axes.titlesize'] = 11
plt.rcParams['axes.labelsize'] = 10

def carregar_dados(caminho_arquivo):
    """Carrega e prepara os dados com tratamento de erros"""
    try:
        df = pd.read_csv(caminho_arquivo)
        
        # Verificação das colunas necessárias
        colunas_necessarias = ['algoritmo', 'tipo', 'tamanho', 'comparacoes', 'tempo']
        if not all(col in df.columns for col in colunas_necessarias):
            raise ValueError("Arquivo CSV não contém todas as colunas necessárias")
            
        # Tradução e formatação
        tipo_trad = {'sorted': 'Ordenado', 'random': 'Aleatório', 'reverse': 'Decrescente'}
        df['tipo'] = df['tipo'].map(tipo_trad)
        df['algoritmo'] = df['algoritmo'].str.title() + ' Sort'
        
        # Converter tamanhos para categorias ordenadas
        tamanhos_ordenados = sorted(df['tamanho'].unique())
        df['tamanho_str'] = df['tamanho'].astype(str)
        df['tamanho_cat'] = pd.Categorical(df['tamanho_str'], 
                                         categories=[str(t) for t in tamanhos_ordenados], 
                                         ordered=True)
        
        return df
    
    except Exception as e:
        print(f"Erro ao carregar dados: {str(e)}")
        return None

def plotar_tempo_separado(df, output_dir):
    """Gera gráficos de tempo com valores reais"""
    if df is None:
        return
        
    tipos = df['tipo'].unique()
    
    for tipo in tipos:
        fig, ax = plt.subplots(figsize=(10, 6))  # Tamanho um pouco maior
        
        dados = df[df['tipo'] == tipo]
        
        # Gráfico de linha com valores reais
        sns.lineplot(data=dados, x='tamanho_cat', y='tempo', 
                    hue='algoritmo', style='algoritmo',
                    markers=['o', 's', 'D', '^'],  # Marcadores diferentes para cada algoritmo
                    dashes=False, linewidth=2,
                    markersize=8, errorbar=None, ax=ax)
        
        # Adicionar valores exatos nos pontos
        for algo in dados['algoritmo'].unique():
            subset = dados[dados['algoritmo'] == algo]
            for i, row in subset.iterrows():
                # Formata o tempo de forma inteligente
                tempo_str = f"{row['tempo']:.3f}s" if row['tempo'] >= 0.001 else f"{row['tempo']:.1e}s"
                ax.text(row['tamanho_cat'], row['tempo'] * 1.05, 
                       tempo_str, 
                       ha='center', fontsize=8, color='black')
        
        # Configurações do gráfico
        ax.set_title(f'Tempo de Execução - Entrada {tipo}', pad=15)
        ax.set_xlabel('Tamanho do Vetor')
        ax.set_ylabel('Tempo (segundos)')
        ax.legend(title='Algoritmo', bbox_to_anchor=(1.05, 1), loc='upper left')
        ax.grid(True, linestyle=':', alpha=0.7)
        
        # Ajuste automático dos limites do eixo Y
        y_max = dados['tempo'].max() * 1.2
        ax.set_ylim(0, y_max if y_max > 0 else 1)
        
        # Salvar figura
        nome_arquivo = os.path.join(output_dir, f"tempo_{tipo.lower()}.png")
        plt.savefig(nome_arquivo, bbox_inches='tight', pad_inches=0.5)
        plt.close(fig)
        print(f"Gráfico salvo: {nome_arquivo}")

def plotar_comparacoes_agrupadas(df, output_dir):
    """Gráficos de comparações com valores reais"""
    if df is None:
        return
        
    tipos = df['tipo'].unique()
    
    for tipo in tipos:
        fig, ax = plt.subplots(figsize=(12, 7))  # Tamanho maior para acomodar os valores
        
        dados = df[df['tipo'] == tipo]
        
        # Gráfico de barras com valores reais
        barplot = sns.barplot(data=dados, x='tamanho_cat', y='comparacoes', 
                            hue='algoritmo', palette='muted', ax=ax)
        
        # Adicionar valores nas barras (formatados de forma inteligente)
        for p in barplot.patches:
            if p.get_height() > 0:
                # Formatação condicional para números grandes
                if p.get_height() > 1e6:
                    texto = f"{p.get_height()/1e6:.1f}M"
                elif p.get_height() > 1e3:
                    texto = f"{p.get_height()/1e3:.1f}K"
                else:
                    texto = f"{p.get_height():.0f}"
                
                ax.annotate(texto, 
                           (p.get_x() + p.get_width() / 2., p.get_height()),
                           ha='center', va='center', xytext=(0, 5),
                           textcoords='offset points', fontsize=8)
        
        # Configurações do gráfico
        ax.set_title(f'Comparações Realizadas - Entrada {tipo}', pad=15)
        ax.set_xlabel('Tamanho do Vetor')
        ax.set_ylabel('Número de Comparações')
        ax.legend(title='Algoritmo', bbox_to_anchor=(1.05, 1), loc='upper left')
        ax.grid(True, axis='y', linestyle=':', alpha=0.7)
        
        # Ajuste automático dos limites do eixo Y
        y_max = dados['comparacoes'].max() * 1.1
        ax.set_ylim(0, y_max if y_max > 0 else 1)
        
        # Rotacionar rótulos do eixo X se necessário
        if len(dados['tamanho_cat'].unique()) > 5:
            plt.xticks(rotation=45)
        
        # Salvar figura
        nome_arquivo = os.path.join(output_dir, f"comparacoes_{tipo.lower()}.png")
        plt.savefig(nome_arquivo, bbox_inches='tight', pad_inches=0.5)
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
    
    print("\nIniciando geração de gráficos com valores reais...")
    
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