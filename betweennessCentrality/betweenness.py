import operator
import random
import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import matplotlib.colors as mcolors
from random import randint

import numpy as np


def printGrafo(G: nx.Graph, bc: list) -> None:


    for edge in G.edges:
        i = edge.__getitem__(0)
        j = edge.__getitem__(1)

        print(
            f"Aresta: {str(edge):8}  peso: {str(G[i][j]['weight']):3} Betweenness: ( {str(bc.get(i)):20} , {str(bc.get(j)):20} )")


def adicionarPeso(G: nx.Graph, pesoMinimo: int, pesoMaximo: int) -> nx.Graph:

    for edge in G.edges:
        i = edge.__getitem__(0)
        j = edge.__getitem__(1)
        G[i][j]['weight'] = randint(pesoMinimo, pesoMaximo)
    return G


def mostrarGrafo(G: nx.Graph, bc: list) -> None:

    plt.figure("GrafoAlvo")

    pos = nx.spring_layout(G)
    #pos = nx.nx_agraph.graphviz_layout(G, prog="twopi", args="") para arvore circular
    nx.draw(G, pos, with_labels=True, font_size=8, node_size=200)

    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, font_size=5)

    
    plt.show()

    plt.figure("GrafoBetweenness")

    node_colors = list(bc.values())

    cent = np.fromiter(bc.values(), float)
    sizes = cent / np.max(cent) * 200
    normalize = mcolors.Normalize(vmin=cent.min(), vmax=cent.max())
    colormap = cm.viridis

    scalarmappable = cm.ScalarMappable(norm=normalize, cmap=colormap)
    scalarmappable.set_array(cent)

    plt.colorbar(scalarmappable)

    nx.draw(G, pos, node_color=node_colors, with_labels=False,
            font_color="red", font_size=5, node_size=sizes,
            cmap=colormap)  # Plotando os vértices no grafo

    plt.show()


def main():

    #Descomente o grafo que deseja utilizar e comente os demais
    G = nx.random_regular_graph(3, 74) #Grafo regular grau 3 e 74 vértices
    #G = nx.balanced_tree(3,3)  #Arvore circular (ALTERAR pos em mostrarGrafo() para exibir corretamente)
    #G = nx.erdos_renyi_graph(25,0.3)  #Grafo aleatório de erdos-renyi
    #G = nx.barabasi_albert_graph(40,1, seed=42) #Grafo de Barabasi-Albert
    #G = nx.barbell_graph(50,10) #Grafo de barra


    G = adicionarPeso(G, 1, 20)
   
    bc = nx.betweenness_centrality(G, normalized=True, weight='weight')


    printGrafo(G, bc)

    mostrarGrafo(G, bc)


if __name__ == "__main__":
    main()
