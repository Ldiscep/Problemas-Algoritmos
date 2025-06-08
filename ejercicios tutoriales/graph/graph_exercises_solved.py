from collections import deque
from graph import *

def bfs(graph: Graph, start: str) -> None:
    visited = set()
    queue = deque()

    visited.add(start)
    queue.append(start)

    while queue:
        current = queue.popleft()
        print(f"Visited {current}")

        for neighbor in graph.get_neighbors(current):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

def dfs(graph: Graph, vertex: str, visited: set) -> None:
        visited.add(vertex)
        for neighbor in graph.get_neighbors(vertex):
            if neighbor not in visited:
                dfs(graph, neighbor, visited)

def dfsCycle(graph: Graph, vertex: str, visited: set, parent: Optional[str]) -> bool:
    visited.add(vertex)
    for neighbor in graph.get_neighbors(vertex):
        if neighbor not in visited:
            if dfsCycle(graph, neighbor, visited, vertex):
                return True
        elif neighbor != parent:
            return True
    return False

def has_cycle(graph: Graph) -> bool:
    visited = set()

    for vertex in graph._graph:
        if vertex not in visited:
            if dfsCycle(graph, vertex, visited, None):
                return True
    return False


def count_connected_components(graph: Graph) -> int:
    visited = set()
    count = 0

    for vertex in graph._graph:
        if vertex not in visited:
            dfs(graph, vertex, visited)
            count += 1

    return count



def bidirectional_bfs(graph: Graph, startA: str, startB: str) -> tuple[str, int]:
    queueA = new_queue()
    queueB = new_queue()
    queueA.add(startA)
    queueB.add(startB)
    #Visitados desde ambos. Usamos diccionario de la forma clave (nodo) : valor
    #(tiempo que tardo en llegar hasta ahi desde el start)
    visitedA = {startA: 0}
    visitedB = {startB: 0}
    while queueA and queueB:
    #Expandir desde el lado de A
        if queueA:
            currentA = queueA.pop()
            for neighbor in graph.get_neighbors(currentA):
                if neighbor not in visitedA:
                    visitedA[neighbor] = visitedA[currentA] + 1
                    queueA.append(neighbor)
        #Si el nodo está en el otro conjunto de visitados, hay intersección
                if neighbor in visitedB:
                    total_distance = max(visitedA[neighbor], visitedB[neighbor])
                    return neighbor, total_distance
    # Expandir desde el lado de B
        if queueB:
            currentB = queueB.pop()
            for neighbor in graph.get_neighbors(currentB):
                if neighbor not in visitedB:
                    visitedB[neighbor] = visitedB[currentB] + 1
                    queueB.append(neighbor)
    # Si el nodo está en el otro conjunto de visitados, hay intersección
                if neighbor in visitedA:
                    total_distance = max(visitedB[neighbor], visitedA[neighbor])
                    return neighbor, total_distance
    # Si no se encuentra intersección
    return None, -1


def is_two_colored(graph: Graph) -> bool:
    color: Dict[str, int] = {}

    for node in graph._graph:
        if node not in color:
            queue = deque([node])
            color[node] = 0  # Asignamos color 0 al primer nodo

            while queue:
                current = queue.popleft()
                for neighbor in graph.get_neighbors(current):
                    if neighbor not in color:
                        color[neighbor] = 1 - color[current]  # Alternamos color
                        queue.append(neighbor)
                    elif color[neighbor] == color[current]:
                        return False  # Dos vecinos con el mismo color => no bipartito
    return True
