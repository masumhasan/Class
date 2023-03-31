from collections import defaultdict

# define a recursive function to perform DFS


def dfs(node, graph, visited, dfs_path):
    visited[node] = True  # mark the current node as visited
    dfs_path.append(node)  # add the current node to the DFS path

    # visit all neighbours of the current node
    for neighbour in graph[node]:
        if not visited[neighbour]:  # if neighbour is not visited
            # recursively call DFS on neighbour
            dfs(neighbour, graph, visited, dfs_path)


# read input
n, m = map(int, input().split())
graph = defaultdict(list)  # initialize an empty adjacency list
for i in range(m):
    u, v = map(int, input().split())
    graph[u].append(v)  # add edge from u to v
    graph[v].append(u)  # add edge from v to u

visited = [False] * (n+1)  # initialize visited list for all nodes
dfs_path = []  # initialize DFS path as an empty list

# perform DFS starting from node 1
dfs(1, graph, visited, dfs_path)

# print the DFS path
print(*dfs_path)
