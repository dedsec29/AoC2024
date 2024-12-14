import random
from collections import deque
from PIL import Image
import copy

# Directions array (including diagonals)
directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]

# Custom hash function for pairs of uint64_t values
class CustomHash:
    @staticmethod
    def splitmix64(x):
        x += 0x9e3779b97f4a7c15
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb
        return x ^ (x >> 31)

    def __call__(self, x):
        FIXED_RANDOM = random.getrandbits(64)
        return self.splitmix64(x[0] + FIXED_RANDOM) ^ (self.splitmix64(x[1] + FIXED_RANDOM) >> 1)

iterations = 100000
density = []

def read_info(s):
    s = s[2:]  # Removing the first two characters
    arr = list(map(int, s.split(',')))
    return arr[1], arr[0]  # x, y order

def analyse(n, m, robots, it):
    sz = len(robots)
    nodes = set(robots)
    dens = 0

    for robot in robots:
        if robot not in nodes:
            continue

        Q = deque([robot])
        nodes.remove(robot)

        cnt = 0
        while Q:
            x, y = Q.popleft()
            cnt += 1

            for d in directions:
                u, v = d[0] + x, d[1] + y
                if (u, v) in nodes:
                    nodes.remove((u, v))
                    Q.append((u, v))

        dens = max(dens, cnt)

    density.append((dens, it))

def makeImage(n, m, robots, it):
    tileSize = 10
    imagesFolder = "slides"
    grid = [['.' for _ in range(m)] for _ in range(n)]
    for [x, y] in robots:
        grid[x][y] = '#'

    image = Image.new("RGB", (m * tileSize, n * tileSize), "white")
    pixels = image.load()

    color_map = {
        '.': (255, 255, 255),  # White
        '#': (0, 255, 0),      # Green
    }

    for r in range(n):
        for c in range(m):
            color = color_map.get(grid[r][c], (0, 0, 0))  # Default to black for unknown chars
            # Draw a tile of size tile_size x tile_size
            for i in range(tileSize):
                for j in range(tileSize):
                    pixels[c * tileSize + i, r * tileSize + j] = color

    image.save(f"{imagesFolder}/{it}.png")
    image.show()

def advance(a, b, t, m):
    a = (a + m) % m
    b = (b + m) % m
    t = (t + m) % m
    return ((a + (b * t % m)) % m + m) % m

def advance_robots(n, m, robots, velocity, times):
    for i in range(len(robots)):
        robots[i] = (
            advance(robots[i][0], velocity[i][0], times, n),
            advance(robots[i][1], velocity[i][1], times, m)
        )
    makeImage(n, m, robots, times)

def solve():
    m, n = 101, 103
    robots = []
    velocity = []

    with open("input.txt") as file:
        for line in file:
            words = line.split()
            y, x = map(int, words[0].split('=')[1].split(','))
            v, u = map(int, words[1].split('=')[1].split(','))
            robots.append([x, y])
            velocity.append([u, v])

    original = copy.deepcopy(robots)

    for t in range(iterations):
        for i in range(len(robots)):
            robots[i] = (
                advance(robots[i][0], velocity[i][0], 1, n),
                advance(robots[i][1], velocity[i][1], 1, m)
            )
        analyse(n, m, robots, t + 1)

    density.sort(reverse=True, key=lambda x: x[0])

    for k in range(min(iterations, len(density), 10)):
        print(f"This is iteration number {density[k][1]} with density = {density[k][0]}")
        temp_robots = copy.deepcopy(original)
        advance_robots(n, m, temp_robots, velocity, density[k][1])

solve()