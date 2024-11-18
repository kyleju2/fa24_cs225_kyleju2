#include "maze.h"
#include <algorithm>
#include <queue>
#include <map>


SquareMaze::SquareMaze() {
    this->width = 0;
    this->height = 0;
    connections = new DisjointSets();
}


SquareMaze::SquareMaze(int width, int height) {
    this->width = width;
    this->height = height;
    connections = new DisjointSets();
    connections->addelements(width*height);
}


SquareMaze::~SquareMaze() {
    delete connections;
    connections = NULL;
}


void SquareMaze::makeMaze(int width, int height) {
    // clear existing
    this->width = width;
    this->height = height;
    maze.clear();
    delete connections;
    //

    // create new
    connections = new DisjointSets();
    connections->addelements(width * height);

    for (int i = 0; i < (width*height); i++) {
        maze.emplace_back(MazeNode(true, true)); // default condition (full grid)
    }

    std::vector<std::pair<int, Direction>> walls; // list of removable walls (not perimeter walls)
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i < width - 1)
                walls.push_back({j*width + i, RIGHT});
            
            if (j < height - 1) {
                walls.push_back({j*width + i, DOWN});
            }
        }
    }

    // shuffle walls vector
    std::random_shuffle(walls.begin(), walls.end());

    // iterate through walls vector
    for (const auto &wall: walls) {
        int cell = wall.first;
        Direction dir = wall.second;

        int neighbor;
        if (dir == RIGHT)
            neighbor = cell + 1; // right neighbor (x + 1)
        else
            neighbor = cell + width; // (y + 1) go a row down

        if (connections->find(cell) != connections->find(neighbor)) {
            connections->setunion(cell, neighbor);

            if (dir == RIGHT) {
                maze[cell].right = false;
            }
            else if (dir == DOWN) 
                maze[cell].down = false;
        }
    }
}


cs225::PNG* SquareMaze::drawMaze(int start) const {
    cs225::PNG* image = new cs225::PNG(width * 10 + 1, height * 10 + 1);

    // Blacken top row excluding the entrance
    for (int i = 0; i < (width * 10 + 1); i++) {
        if (i < start * 10 + 1 || i >= (start + 1) * 10) {
            cs225::HSLAPixel &pix = image->getPixel(i, 0);
            pix.l = 0; // Set luminance to 0 (make it black)
        }
    }

    // Blacken left column (full height)
    for (int j = 0; j < (height * 10 + 1); j++) {
        cs225::HSLAPixel &pix = image->getPixel(0, j);
        pix.l = 0; // Set luminance to 0 (make it black)
    }

    // Iterate through each cell in the maze and draw walls
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int cellIndex = j * width + i;

            // Draw right wall if present
            if (maze[cellIndex].right) {
                for (int k = 0; k <= 10; k++) { // Ensure full wall coverage
                    if (static_cast<unsigned int>((i + 1) * 10) < image->width()) { // Bounds check
                        cs225::HSLAPixel &pix = image->getPixel((i + 1) * 10, j * 10 + k);
                        pix.l = 0; // Set luminance to 0 (make it black)
                    }
                }
            }

            // Draw bottom wall if present
            if (maze[cellIndex].down) {
                for (int k = 0; k <= 10; k++) { // Ensure full wall coverage
                    if (static_cast<unsigned int>((j + 1) * 10) < image->height()) { // Bounds check
                        cs225::HSLAPixel &pix = image->getPixel(i * 10 + k, (j + 1) * 10);
                        pix.l = 0; // Set luminance to 0 (make it black)
                    }
                }
            }
        }
    }

    return image;
}


bool SquareMaze::canTravel(int x, int y, Direction dir) const {
    switch (dir) {
        case RIGHT:
            if (x + 1 >= width) return false;
            return !maze[y*width + x].right;

        case DOWN:
            if (y + 1 >= height) return false;
            return !maze[y*width + x].down;

        case LEFT:
            if (x - 1 < 0) return false;
            return !maze[y*width + (x - 1)].right;

        case UP:
            if (y - 1 < 0) return false;
            return !maze[(y - 1) * width + x].down;

        default:
            return false;
    };
}


void SquareMaze::setWall(int x, int y, Direction dir, bool exists) {
    if (dir == RIGHT) {
        maze[y*width + x].right = exists;
    }
    else if (dir == DOWN) {
        maze[y*width + x].down = exists;
    }
}


std::vector<Direction> SquareMaze::solveMaze(int startX) {
    // BFS setup
    std::queue<std::pair<int, int>> q; // Queue for BFS (x, y)
    std::vector<int> distance(width * height, -1); // Distance from start
    std::vector<int> parent(width * height, -1); // Parent tracking for path reconstruction
    std::vector<Direction> directionFromParent(width * height); // Direction taken to reach each cell
    std::vector<bool> visited(width * height, false); // Visited cells

    // Directions: RIGHT, DOWN, LEFT, UP
    std::vector<Direction> directions = {RIGHT, DOWN, LEFT, UP};
    std::vector<int> dx = {1, 0, -1, 0};
    std::vector<int> dy = {0, 1, 0, -1};

    // Start BFS from the first cell (startX, 0)
    q.push({startX, 0});
    visited[startX] = true;
    distance[startX] = 0;

    int destX = -1, destY = -1, maxDistance = -1;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        int currentIdx = y * width + x;

        // Check if we're on the last row
        if (y == height - 1) {
            if (distance[currentIdx] > maxDistance || 
                (distance[currentIdx] == maxDistance && x < destX)) {
                maxDistance = distance[currentIdx];
                destX = x;
                destY = y;
            }
        }

        // Explore all four directions
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Validate move
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && canTravel(x, y, directions[i])) {
                int neighborIdx = ny * width + nx;
                if (!visited[neighborIdx]) {
                    visited[neighborIdx] = true;
                    distance[neighborIdx] = distance[currentIdx] + 1;
                    parent[neighborIdx] = currentIdx;
                    directionFromParent[neighborIdx] = directions[i];
                    q.push({nx, ny});
                }
            }
        }
    }

    // Path reconstruction from destination to start
    std::vector<Direction> path;
    if (destX != -1 && destY != -1) {
        int currentIdx = destY * width + destX;
        while (currentIdx != startX) {
            path.push_back(directionFromParent[currentIdx]);
            currentIdx = parent[currentIdx];
        }
        std::reverse(path.begin(), path.end());
    }

    return path;
}


cs225::PNG* SquareMaze::drawMazeWithSolution(int start) {
    // Generate the maze image using drawMaze()
    cs225::PNG* image = drawMaze(start);

    // Get the solution path using solveMaze()
    std::vector<Direction> solution = solveMaze(start);

    // Start coordinates at the middle of the square (start, 0)
    int x = start * 10 + 5;
    int y = 5;

    // Color the solution path in red
    for (Direction dir : solution) {
        // Determine direction deltas
        int dx = 0, dy = 0;
        if (dir == RIGHT) dx = 1;
        else if (dir == DOWN) dy = 1;
        else if (dir == LEFT) dx = -1;
        else if (dir == UP) dy = -1;

        // Draw 11 pixels in the direction
        for (int i = 0; i <= 10; i++) { // 0 to 10 inclusive, 11 pixels
            int currX = x + dx * i;
            int currY = y + dy * i;

            // Color the current pixel red (HSLA: 0,1,0.5,1)
            cs225::HSLAPixel &pixel = image->getPixel(currX, currY);
            pixel.h = 0;
            pixel.s = 1;
            pixel.l = 0.5;
            pixel.a = 1;
        }

        // Update x and y for the next segment
        x += dx * 10;
        y += dy * 10;
    }

    // Calculate the final destination maze coordinates
    int destX = (x - 5) / 10;
    int destY = (y - 5) / 10;

    // Undo the bottom wall of the destination square
    for (int k = 1; k <= 9; k++) { // k from 1 to 9 inclusive
        cs225::HSLAPixel &pixel = image->getPixel(destX * 10 + k, (destY + 1) * 10);
        pixel.l = 1; // Set luminance to 1 (make it white)
    }

    return image;
}
