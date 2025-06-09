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

def largest_connected(graph):
    print("saa")
