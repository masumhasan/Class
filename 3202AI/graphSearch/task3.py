# function to perform DFS traversal and detect cycles in a graph
from collections import defaultdict


def dfs_cycle(graph, visited, rec_stack, v):
    # mark current node as visited and add to recursion stack
    visited.add(v)
    rec_stack.add(v)

    # visit all neighbors of current node
    for neighbor in graph[v]:
        # if neighbor is not visited, recurse on it
        if neighbor not in visited:
            if dfs_cycle(graph, visited, rec_stack, neighbor):
                return True
        # if neighbor is in recursion stack, cycle exists
        elif neighbor in rec_stack:
            return True

    # remove current node from recursion stack and return False
    rec_stack.remove(v)
    return False


# main function to read input and call dfs_cycle function


def find_cycle():
    # read input
    n, m = map(int, input().split())
    graph = defaultdict(list)
    for i in range(m):
        u, v = map(int, input().split())
        graph[u].append(v)

    # initialize visited set and recursion stack
    visited = set()
    rec_stack = set()

    # call dfs_cycle on each unvisited node
    for i in range(1, n+1):
        if i not in visited:
            if dfs_cycle(graph, visited, rec_stack, i):
                print("YES")
                return
    # if no cycle found, print "NO"
    print("NO")


# main function
find_cycle()
