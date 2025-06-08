from graph import *
from graph_exercises_solved import *

def testWithoutCycleTrivial():
    print("=== Corriendo test sin ciclos sin aristas ===")
    g = Graph()
    for v in ['A', 'B', 'C', 'D', 'E']:
        g.add_vertex(v)

    print("Tiene ciclo:", has_cycle(g))

    assert has_cycle(g) == False
    
    print("¡Test pasado satifactoriamente!\n")

def testWithoutCycle():
    print("=== Corriendo test sin ciclos sin aristas ===")
    g = Graph()
    for v in ['A', 'B', 'C', 'D', 'E']:
        g.add_vertex(v)

    g.add_edge('A', 'B')
    g.add_edge('A', 'E')
    g.add_edge('B', 'C')
    g.add_edge('B', 'D')
    

    print("Tiene ciclo:", has_cycle(g))

    assert has_cycle(g) == False
    
    print("¡Test pasado satifactoriamente!\n")


def testWithCycleAndOneConnectedComponent():
    print("=== Corriendo test grafo con ciclo y una sola componente conexa ===")
    g = Graph()
    for v in ['A', 'B', 'C', 'D', 'E']:
        g.add_vertex(v)

    g.add_edge('A', 'B')
    g.add_edge('A', 'E')
    g.add_edge('B', 'C')
    g.add_edge('B', 'D')
    g.add_edge('C', 'D')
    g.add_edge('D', 'E')

    print("Tiene ciclo:", has_cycle(g))

    assert has_cycle(g) == True
    
    print("¡Test pasado satifactoriamente!\n")

def testWithCycleWithMultipleConnectedComponents():
    print("=== Corriendo test grafo con ciclo y varias componentes conexa ===")
    g = Graph()
    for v in ['A', 'B', 'C', 'D', 'E', 'G', 'H', 'J']:
        g.add_vertex(v)

    g.add_edge('A', 'B')
    g.add_edge('A', 'E')
    g.add_edge('B', 'C')
    g.add_edge('G', 'H')
    g.add_edge('H', 'J')
    g.add_edge('J', 'G')


    print("Tiene ciclo:", has_cycle(g))
    
    assert has_cycle(g) == True

    print("¡Test pasado satifactoriamente!\n")

def testConnectedComponents():
    print("=== Corriendo tests componentes conexas ===")
    # Caso 1: Grafo completamente conectado
    g1 = Graph()
    for v in ['A', 'B', 'C']:
        g1.add_vertex(v)
    g1.add_edge('A', 'B'); g1.add_edge('B', 'A')
    g1.add_edge('B', 'C'); g1.add_edge('C', 'B')
    assert count_connected_components(g1) == 1

    # Caso 2: 2 componentes separados
    g2 = Graph()
    for v in ['A', 'B', 'C', 'D']:
        g2.add_vertex(v)
    g2.add_edge('A', 'B'); g2.add_edge('B', 'A')
    g2.add_edge('C', 'D'); g2.add_edge('D', 'C')
    assert count_connected_components(g2) == 2

    # Caso 3: 3 nodos aislados
    g3 = Graph()
    for v in ['X', 'Y', 'Z']:
        g3.add_vertex(v)
    assert count_connected_components(g3) == 3

    # Caso 4: Componente grande y un nodo aislado
    g4 = Graph()
    for v in ['A', 'B', 'C', 'D']:
        g4.add_vertex(v)
    g4.add_edge('A', 'B'); g4.add_edge('B', 'A')
    g4.add_edge('B', 'C'); g4.add_edge('C', 'B')
    # 'D' está aislado
    assert count_connected_components(g4) == 2

    # Caso 5: Grafo vacío
    g5 = Graph()
    assert count_connected_components(g5) == 0

    print("¡Tests pasados satifactoriamente!")

def testTwoColores():
    
    print("=== Corriendo tests bicoloreo ===")

    # Caso 1: Grafo bipartito
    g1 = Graph()
    for v in ['A', 'B', 'C', 'D', 'E', 'G', 'H', 'J']:
        g1.add_vertex(v)

    g1.add_edge('A', 'B')
    g1.add_edge('A', 'E')
    g1.add_edge('B', 'C')
    g1.add_edge('G', 'H')
    g1.add_edge('H', 'J')
    g1.add_edge('J', 'G')  # Crea un ciclo impar (G-H-J-G)

    assert is_two_colored(g1) == False

    # Caso 2: Grafo bipartito simple
    g2 = Graph()
    for v in ['A', 'B', 'C', 'D']:
        g2.add_vertex(v)

    g2.add_edge('A', 'B')
    g2.add_edge('B', 'C')
    g2.add_edge('C', 'D')

    assert is_two_colored(g2) == True

    # Caso 3: Grafo vacío
    g3 = Graph()
    assert is_two_colored(g3) == True

    # Caso 4: Grafo con ciclo impar (no bipartito)
    g4 = Graph()
    for v in ['A', 'B', 'C']:
        g4.add_vertex(v)

    g4.add_edge('A', 'B')
    g4.add_edge('B', 'C')
    g4.add_edge('C', 'A')  # Ciclo impar

    assert is_two_colored(g4) == False

    print("¡Tests pasados satifactoriamente!\n")


if __name__ == "__main__":
    testWithoutCycle()
    testWithoutCycleTrivial()
    testWithCycleAndOneConnectedComponent()
    testWithCycleWithMultipleConnectedComponents()
    testConnectedComponents()
    testTwoColores()