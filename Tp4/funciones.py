from collections import deque
from graph import *
from random import randint, choice
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
    visited = set()
    max_size = 0

    for vertex in graph._graph:
        if vertex not in visited:
            
            queue = deque([vertex])
            component_size = 0
            visited.add(vertex)

            while queue:
                current = queue.popleft()
                component_size += 1
                for neighbor in graph.get_neighbors(current):
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)

            if component_size > max_size:
                max_size = component_size



    
    return max_size

def triangles(graph: Graph):
    triangulos = 0
    seen = set()
    for v in graph._graph:
        for u in graph.get_neighbors(v):
            if u <= v:
                continue 
            for w in graph.get_neighbors(u):
                if w <= u or w == v:
                    continue
                if v in graph.get_neighbors(w):

                    triangle = tuple(sorted([v, u, w]))
                    if triangle not in seen:
                        seen.add(triangle)
                        triangulos += 1
    return triangulos


def bfs_max_distance(graph, start):
    visited = set()
    distance = {start: 0}
    queue = deque([start])
    visited.add(start)

    max_dist = 0
    farthest_node = start

    while queue:
        current = queue.popleft()

        for neighbor in graph.get_neighbors(current):
            if neighbor not in visited:
                visited.add(neighbor)
                distance[neighbor] = distance[current] + 1
                if distance[neighbor] > max_dist:
                    max_dist = distance[neighbor]
                    farthest_node = neighbor
                queue.append(neighbor)

    return farthest_node, max_dist

def graph_diameter(graph):
    if not graph._graph:
        return 0

    start_node = next(iter(graph._graph))
    farthest_node, _ = bfs_max_distance(graph, start_node)

    _, diameter = bfs_max_distance(graph, farthest_node)

    return diameter

def pagerank(graph:Graph):
    vertices=list(graph._graph)
    #vertices=list(vertices.keys())
    
    dic_final={}
    randomwalks=10000
    for walk in range(randomwalks):
        vtx=randint(0,len(vertices))

        for paso in range(1000):
            if paso==0:
                encontrados= graph.get_neighbors(str(vertices[vtx]))
            else: encontrados= graph.get_neighbors(vtx)
            if not encontrados:
                continue
            vtx=choice(encontrados)
            for vecino in encontrados:
                if vecino in dic_final:
                    dic_final[vecino]+=1
                else: dic_final[vecino]=1
                
    1

    # Ordenar dic_final por valor descendente
    sorted_dic = sorted(dic_final.items(), key=lambda x: x[1], reverse=True)
    return sorted_dic


        