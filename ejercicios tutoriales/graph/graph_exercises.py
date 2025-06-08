from collections import deque
from graph import *


def bfs(graph: Graph, start: str) -> None:
    visitados = set()
    queue = deque()
    queue.append(start)
    visitados.add(start)
    while queue:
        now=queue.popleft()
        if graph.get_neighbors(now) not in visitados:
            queue.append(graph.get_neighbors(now))
        if now not in visitados: visitados.add(now)

    return visitados

def dfs(graph: Graph, vertex: str, visited: set) -> None:
    visited.add(vertex)
    for neighbor in graph.get_neighbors(vertex):
        if neighbor not in visited:
            dfs(graph, neighbor, visited)

def has_cycle(graph: Graph) -> bool:
    return False


def count_connected_components(graph: Graph) -> int:
    count=0
    visited=set()
    for node in graph:
        if node not in visited:
            count+=1
            dfs(graph,node,visited)

'''
En una ciudad ficticia representada como un grafo no dirigido, los nodos representan
ubicaciones y las aristas representan caminos directos entre ellas. Todas las aristas tienen
un costo de 1 unidad de tiempo para cruzarlas. Hay dos personas, Alice y Bob, ubicadas
inicialmente en dos nodos distintos del grafo, startA y startB.

1. Diseña un algoritmo eficiente para determinar si Alice y Bob pueden encontrarse en
algún nodo del grafo, minimizando el tiempo total que ambos necesitan recorrer.

2. Si es posible que se encuentren, indica en qué nodo sería el encuentro y cuánto
tiempo tomaría en total considerando que parten al mismo tiempo.

'''

def bidirectional_bfs(graph: Graph, startA: str, startB: str):
    return None, None

def is_two_colored(graph: Graph) -> bool:
    return False