from graph import Graph
from funciones import *
from os import system
from sys import setrecursionlimit
from progress.bar import IncrementalBar

setrecursionlimit(31415296) #es una banda pero como no hay valgrind puedo hacer lo que yo quiera 

page_graph = Graph()
system("clear")
with open('web-Google copy.txt', 'r') as file:#cambiar al archivo original y modificar el largo de la barra
    bar = IncrementalBar("Inicializando Grafo, no desesperes", max=1066587,width=100, suffix='%(percent)d%%')
    for l in file:
        if "# FromNodeId	ToNodeId" in l:
            break
    for l in file:
        if not l:
            break
        edge = tuple(int(v.replace("\n", "").replace("\t", "")) for v in l.split("\t"))
        for v in edge:
            if not page_graph.vertex_exists(v):
                page_graph.add_vertex(str(v))
        bar.next()
    
        page_graph.add_edge(str(edge[0]), str(edge[1]))
    bar.finish()



print(f"Tamaño de la componente conexa más grande:\n{largest_connected(page_graph)}")
print(f"Cantidad de componentes conexas:\n{count_connected_components(page_graph)}")