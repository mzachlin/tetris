#include "grid.h"
#include <cstdio>
#include <ctime>

using namespace std;

/* Functions */
void drawShape(SDL_Renderer* rend, SDL_Rect rect, int p_shape) {
    // Fill the rectangle with a color
    switch (p_shape) {
      case 0:  // Dark blue right Z
        SDL_SetRenderDrawColor(rend, 3, 90, 252, 170);
        break; 
      case 1:  // Pink left Z
        SDL_SetRenderDrawColor(rend, 234, 3, 252, 170);
        break;
      case 2:  // Red left L
        SDL_SetRenderDrawColor(rend, 163, 13, 6, 170);
        break;
      case 3:  // Green right L
        SDL_SetRenderDrawColor(rend, 6, 163, 11, 170);
        break;
      case 4:  // Purple square
        SDL_SetRenderDrawColor(rend, 166, 3, 252, 170);
        break;
      case 5:  // Golden yellow T
        SDL_SetRenderDrawColor(rend, 252, 181, 3, 170);
        break;
      case 6: // Teal I
        SDL_SetRenderDrawColor(rend, 33, 163, 125, 170);
        break;
    }
    
    SDL_RenderFillRect(rend, &rect);
    // Draw the outline of the rectangle
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawRect(rend, &rect);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
}

void drawPiece(SDL_Renderer* rend, Piece piece) {
  vector<SDL_Rect> blocks = piece.Get_Blocks();
  for (int i = 0; i < 4; i++) {
    drawShape(rend, blocks[i], piece.GetPShape());
  }
}

void drawGrid(SDL_Renderer* rend, Grid g) {
  vector<vector<box>> g_boxes = g.GetGridBlocks();
  for (int i = 0; i < g_boxes.size(); i++) {
    vector<box> row = g_boxes[i];
    for (int k = 0; k < row.size(); k++) {
      SDL_Rect r1 = row[k].rect;
      if (row[k].filled) {
        drawShape(rend, r1, row[k].color);
      }
    }
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
    srand(time(NULL)); //seed random number generator
    Piece piece1(block_size, win_w, win_h);
    drawPiece(rend, piece1);
    SDL_RenderPresent(rend);
    //drawShape(rend, rect);

    // Animation loop
    clock_t start = clock();
    int speed = 30000;
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
                          piece1.Move(0, 0, 1, &grid, rend);
                          break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                          piece1.Move(-1, 0, 0, &grid, rend);
                          break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                          piece1.Move(0, 1, 0, &grid, rend);
                          break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                          piece1.Move(1, 0, 0, &grid, rend);
                          break;
                        default:
                          break;
                    }
            }
        }

        if (piece1.isLocked()) {
          grid.UpdateGrid(piece1);
          piece1 = Piece (block_size, win_w, win_h);
        }

        drawPiece(rend, piece1);
        drawGrid(rend, grid);
        SDL_RenderPresent(rend);
        // Calculate to 60 fps
        SDL_Delay(1000 / 60);    // I'm not sure what the delay is for?
    }

    // Destroy renderer
    SDL_DestroyRenderer(rend);

    // Destroy window
    SDL_DestroyWindow(win);

    return 0;
}
