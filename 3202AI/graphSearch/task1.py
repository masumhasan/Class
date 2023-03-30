from collections import defaultdict, deque

# Define the BFS function that takes a graph and a starting vertex as input


def bfs(graph, start):
    # Initialize a set to keep track of visited vertices, a deque to hold the vertices to be visited, and add the starting vertex to both sets
    visited = set()
    queue = deque([start])
    visited.add(start)

    # Start a loop that continues until the queue is empty
    while queue:
        # Dequeue a vertex from the queue
        curr = queue.popleft()
        # Print the dequeued vertex
        print(curr, end=" ")
        # Iterate over the neighbors of the dequeued vertex
        for neighbor in graph[curr]:
            # If a neighbor has not been visited yet, mark it as visited, enqueue it to the queue, and continue the loop
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)


# Read the input values for the number of cities and roads
n, m = map(int, input().split())
# Create a defaultdict of lists to represent the graph
graph = defaultdict(list)
# Read the input values for the bidirectional roads and add them to the graph
for _ in range(m):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

# Call the BFS function with the graph and starting vertex 1
bfs(graph, 1)
