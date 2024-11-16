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
    cs225::PNG* image = new cs225::PNG(width*10+1, height*10+1);

    // blacken top row excluding start:
    for (int i = 0; i < (width*10+1); i++) {
        if (i < start*10+1 || i >= (start+1) * 10) {
            cs225::HSLAPixel &pix = image->getPixel(i, 0);
            pix.l = 0; // set luminance to 0 (make it black)
        }
    }

    // blacken left col:
    for (int j = 0; j < (height*10+1); j++) {
        cs225::HSLAPixel &pix = image->getPixel(0, j);
        pix.l = 0; // set luminance to 0 (make it black)
    }

    // iterate through maze vector and draw a line if down or right are true;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (maze[j * width + i].right) {
                for (int a = 0; a < 10; a++) {
                    cs225::HSLAPixel &pix = image->getPixel((i + 1) * 10, j * 10 + a);
                    pix.l = 0;
                }
            }

            if (maze[j * width + i].down) {
                //draw vertical wall
                for (int a = 0; a <= 10; a++) {
                    cs225::HSLAPixel &pix = image->getPixel(i * 10 + a, (j + 1) * 10);
                    pix.l = 0;
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
            if (y + 1 >= width) return false;
            return !maze[y*width + x].down;

        case LEFT:
            if (x - 1 < 0) return false;
            return !maze[y*width + (x - 1)].right;

        case UP:
            if (x - 1 < 0) return false;
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
    // std::map <int, int> steps; // map to store steps
    // std::queue<int> q; // queue to store coordinates of nodes visited in the BFS
    // std::vector<bool> visited(height*width, false); // create a vector to store whether or not nodes have been visited
    // std::vector<int> wins;

    // visited[startX] = true;
    // q.push(startX);

    // while (!q.empty()) {
    //     int curr = q.front(); // get current index from top of the queue
    //     q.pop(); // pop it off the queue
        
    //     int x = curr % width;
    //     int y = curr / width;

    //     if (y == height - 1) {
    //         wins.push_back(curr); // if it hits the last row it is a winning path
    //     }

    //     if (canTravel(x, y, RIGHT) && !visited[curr + 1]) {
    //         steps[curr + 1] = curr; // store move
    //         visited[curr + 1] = true;
    //         q.push(curr + 1);
    //     }
    //     if (canTravel(x, y, DOWN) && !visited[curr + width]) {
    //         steps[curr + width] = curr; // store move
    //         visited[curr + width] = true;
    //         q.push(curr + width);
    //     }
    //     if (canTravel(x, y, LEFT) && !visited[curr - 1]) {
    //         steps[curr - 1] = curr; // store move
    //         visited[curr - 1] = true;
    //         q.push(curr - 1);
    //     }
    //     if (canTravel(x, y, UP) && !visited[curr - width]) {
    //         steps[curr - width] = curr; // store move
    //         visited[curr - width] = true;
    //         q.push(curr - width);
    //     }
    // }

    std::vector<Direction> path;
    // int first = 0; // last possible x value the winning path can be at
    // while (wins[first] == wins[first + 1] && first < width) {
    //     first++;
    // }

    // int start = wins[first];
    // while (start != 0) {
    //     int prev = steps[first];

    //     if (start - 1 == prev) 
    //         path.push_back(RIGHT);

    //     else if (start - width == prev) {
    //         path.push_back(DOWN);
    //     }
    //     else if (start + width == prev) {
    //         path.push_back(UP);
    //     }
    //     else if (start + 1 == prev) {
    //         path.push_back(LEFT);
    //     }
    //     start = prev;
    // }
    // std::reverse(path.begin(), path.end());
    return path;
}


cs225::PNG* SquareMaze::drawMazeWithSolution(int start) {
    cs225::PNG* img = new cs225::PNG(width, height);
    return img;
}

