import heapq


class Puzzle:
    def __init__(self, state, parent=None, move=None):
        self.state = state
        self.parent = parent
        self.move = move
        self.g = 0
        self.h = self.manhattan_distance()

    def manhattan_distance(self):
        h = 0
        for i in range(3):
            for j in range(3):
                if self.state[i][j] != 0:
                    row, col = divmod(self.state[i][j]-1, 3)
                    h += abs(i-row) + abs(j-col)
        return h

    def __lt__(self, other):
        return self.g + self.h < other.g + other.h


def solve_puzzle(start_state):
    frontier = []
    explored = set()
    start_node = Puzzle(start_state)
    heapq.heappush(frontier, start_node)
    while frontier:
        node = heapq.heappop(frontier)
        if node.state == goal_state:
            path = []
            while node.parent:
                path.append(node.move)
                node = node.parent
            return path[::-1]
        explored.add(tuple(map(tuple, node.state)))
        for move, next_state in generate_moves(node.state):
            if tuple(map(tuple, next_state)) not in explored:
                child_node = Puzzle(next_state, node, move)
                child_node.g = node.g + 1
                heapq.heappush(frontier, child_node)


def generate_moves(state):
    i, j = next((i, j) for i in range(3) for j in range(3) if state[i][j] == 0)
    for di, dj in ((-1, 0), (1, 0), (0, -1), (0, 1)):
        if 0 <= i+di < 3 and 0 <= j+dj < 3:
            next_state = [row[:] for row in state]
            next_state[i][j], next_state[i+di][j +
                                               dj] = next_state[i+di][j+dj], next_state[i][j]
            yield (next_state[i+di][j+dj], next_state)


def read_puzzle_from_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
        puzzle = []
        for line in lines:
            row = [int(x) for x in line.split()]
            puzzle.append(row)
    return puzzle


def print_puzzle(puzzle):
    for row in puzzle:
        print(" ".join(str(x) for x in row))


def main():
    start_state = read_puzzle_from_file('input.txt')
    print("Initial puzzle:")
    print_puzzle(start_state)
    path = solve_puzzle(start_state)
    print("Solved puzzle:")
    print_puzzle(goal_state)
    print("Moves needed to solve the puzzle:")
    print(path)


goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
main()
