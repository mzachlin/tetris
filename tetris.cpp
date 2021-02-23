#include "grid.h"
#include <cstdio>
#include <ctime>

using namespace std;

/* Functions */
void drawShape(SDL_Renderer* rend, SDL_Rect rect) {
    // Fill the rectangle with a color 
    // FIXME: Make color a variable that can be passed in depending on shape?
    // Maybe make this a function of shape
    SDL_SetRenderDrawColor(rend, 33, 163, 125, 170);
    SDL_RenderFillRect(rend, &rect);
    // Draw the outline of the rectangle
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawRect(rend, &rect);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
}

void drawGrid(SDL_Renderer* rend, Grid g) {
  vector<vector<box>> g_boxes = g.GetGridBlocks();
  for (int i = 0; i < g_boxes.size(); i++) {
    vector<box> row = g_boxes[i];
    for (int k = 0; k < row.size(); k++) {
      SDL_Rect r1 = row[k].rect;
      drawShape(rend, r1);
    }
  }
}

void drawPiece(SDL_Renderer* rend, Piece piece) {
  vector<SDL_Rect> blocks = piece.Get_Blocks();
  for (int i = 0; i < 4; i++) {
    drawShape(rend, blocks[i]);
  }
}

/* Main Execution */
int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    // Create game window
    int win_w = 500;  
    int win_h = 700;  

    int block_size = 25;

    SDL_Window* win = SDL_CreateWindow("TETRIS",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       win_w, win_h, 0);
    // Error check the window appearing
    if (!win) {
        std::cout << "Failed to create window.\n";
        return -1;
    }

    // Trigger the program that controls graphics hardware and set flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // Create a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    // Create grid
    Grid grid(win_w, win_h, block_size);

    int close = 0;    // Controls animation loop

    // Draw initial shape

    Piece piece1(block_size, win_w, win_h);
    drawPiece(rend, piece1);
    SDL_RenderPresent(rend);
    //drawShape(rend, rect);

    // Animation loop
    clock_t start = clock();
    int speed = 100000; //25000;
    while (!close) {
        SDL_RenderClear(rend);
        SDL_Event event;

        if (clock() - start >= speed) {
          piece1.Move(0, 1, 0, &grid);
          start = clock();
        }
        // Events mangement
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // Handling of close button
                    close = 1;
                    break;

                case SDL_KEYDOWN:
                    // Keyboard API for key pressed
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                          piece1.Move(0, 0, 1, &grid);
                          break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                          piece1.Move(-1, 0, 0, &grid);
                          break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                          piece1.Move(0, 1, 0, &grid);
                          break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                          piece1.Move(1, 0, 0, &grid);
                          break;
                        default:
                          break;
                    }
            }
        }


        drawPiece(rend, piece1);
        drawGrid(rend, grid);
        SDL_RenderPresent(rend);
        // Calculate to 60 fps
        SDL_Delay(1000 / 60);    // I'm not sure what the delay is for?

        if (piece1.isLocked()) {
          grid.UpdateGrid(piece1);
          piece1 = Piece (block_size, win_w, win_h);
        }
    }

    // Destroy renderer
    SDL_DestroyRenderer(rend);

    // Destroy window
    SDL_DestroyWindow(win);

    return 0;
}
