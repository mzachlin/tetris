#include "grid.h"
#include <cstdio>
#include <ctime>

using namespace std;

/* Functions */
void drawShape(SDL_Renderer* rend, SDL_Rect rect, int p_shape) {
    int is_bg = 0;
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
      case 7: // background
        SDL_SetRenderDrawColor(rend, 40, 40, 40, 170);
        is_bg = 1;
        break;
    }

    SDL_RenderFillRect(rend, &rect);
    // Draw the outline of the rectangle
    if (is_bg) {
      SDL_SetRenderDrawColor(rend, 25, 25, 25, 25);
    }
    else {
      SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    }
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
      else {
        r1.w = 25;
        r1.h = 25;
        r1.x = k*25;
        r1.y = i*25;
        if (k != 500/25) {
          drawShape(rend, r1, 7);
        }
      }
    }
  }
}

/* Main Execution */
int main() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      printf("error initializing SDL: %s\n", SDL_GetError());
  }
  TTF_Init();

  // Create game window
  int win_w = 500;
  int win_h = 700;
  int win_w_buffer = 200;

  int block_size = 25;

  SDL_Window* win = SDL_CreateWindow("TETRIS",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      win_w + win_w_buffer, win_h, 0);

  // Error check the window appearing
  if (!win) {
      std::cout << "Failed to create window.\n";
      return -1;
  }

  // Trigger the program that controls graphics hardware and set flags
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;

  // Create a renderer to render our images
  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);


  // Prepare game over messages
  TTF_Font* font = TTF_OpenFont("Arial Unicode.ttf", 22);
  SDL_Color white = {255, 255, 255};
  SDL_Color red = {163, 13, 6};
  SDL_Surface* surf = TTF_RenderText_Solid(font, "GAME OVER.", red);
  SDL_Texture* message = SDL_CreateTextureFromSurface(rend, surf);

  SDL_Surface* sassSurf0 = TTF_RenderText_Solid(font, "Better luck next time, comrade.", white);
  SDL_Texture* sass0 = SDL_CreateTextureFromSurface(rend, sassSurf0);
  SDL_Surface* sassSurf1 = TTF_RenderText_Solid(font, "Off to the gulag with you!", white);
  SDL_Texture* sass1 = SDL_CreateTextureFromSurface(rend, sassSurf1);
  SDL_Surface* sassSurf2 = TTF_RenderText_Solid(font, "You played worse than a capitalist!", white);
  SDL_Texture* sass2 = SDL_CreateTextureFromSurface(rend, sassSurf2);
  SDL_Surface* sassSurf3 = TTF_RenderText_Solid(font, "You will get better, Marx my words.", white);
  SDL_Texture* sass3 = SDL_CreateTextureFromSurface(rend, sassSurf3);

  SDL_Surface* smSurf = TTF_RenderText_Solid(font, "Play again?  [Y] or [N]", white);
  SDL_Texture* smMessage = SDL_CreateTextureFromSurface(rend, smSurf);

  int sassNum = -1; // Controls which message is displayed

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
  int base_speed = 50000;
  int speed = base_speed;
  bool gameOver = false;

  bool reset = false;

  while (!close) {
    SDL_RenderClear(rend);
    SDL_Event event;

    speed = base_speed/pow(1.2, grid.getLevel());

    if (clock() - start >= speed) {
      gameOver = piece1.Move(0, 1, 0, &grid);
      start = clock();
    }

    // Events mangement
    while (SDL_PollEvent(&event) && !gameOver) {
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
              gameOver = piece1.Move(0, 0, 1, &grid, rend);  
              break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
              gameOver = piece1.Move(-1, 0, 0, &grid, rend);
              break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
              gameOver = piece1.Move(0, 1, 0, &grid, rend);
              break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
              gameOver = piece1.Move(1, 0, 0, &grid, rend);
              break;
            case SDL_SCANCODE_SPACE:
                while (!piece1.isLocked()) {
                  gameOver = piece1.Move(0, 1, 0, &grid, rend);
                }
                break;
            default:
              break;
          }
      }
    }

    if (!gameOver && piece1.isLocked()) {
      grid.UpdateGrid(piece1);
      piece1 = Piece (block_size, win_w, win_h);
    }

    if (gameOver) {
      sassNum += 1;
      if (sassNum > 3) {
        sassNum = 0;
      }
    }

    while (gameOver) {
      SDL_RenderClear(rend);
        
      // Boundaries of message
      SDL_Rect messageRect;
      messageRect.x = 165;
      messageRect.y = 100;
      messageRect.w = 400;
      messageRect.h = 200;
      SDL_Rect sassRect;
      sassRect.x = 160;
      sassRect.y = 300;
      sassRect.w = 400;
      sassRect.h = 60;
      SDL_Rect smRect;
      smRect.x = 200;
      smRect.y = 475;
      smRect.w = 300;
      smRect.h = 65;
      
      SDL_RenderCopy(rend, message, NULL, &messageRect);
    
      switch (sassNum) {
        case 0:
          SDL_RenderCopy(rend, sass0, NULL, &sassRect);
          break;
        case 1:
          SDL_RenderCopy(rend, sass1, NULL, &sassRect);
          break;
        case 2:
          SDL_RenderCopy(rend, sass2, NULL, &sassRect);
          break;
        case 3:
          SDL_RenderCopy(rend, sass3, NULL, &sassRect);
          break;
        default:
          break;
      }
      
      SDL_RenderCopy(rend, smMessage, NULL, &smRect);
      SDL_RenderPresent(rend);
      
      while (SDL_PollEvent(&event) && gameOver) {
        switch(event.key.keysym.scancode) {
          case SDL_SCANCODE_Y:
            gameOver = false;
            grid = Grid(win_w, win_h, block_size);
            piece1 = Piece (block_size, win_w, win_h);
            cout << "Y pressed!" << endl;
            reset = true;
            break;
          case SDL_SCANCODE_N:
            close = 1;
            gameOver = false;
            break;
          default:
            break;
        }
      }
      SDL_Delay(1000 / 60);  
    }
    if (reset || close) {
      reset = false;
      continue;
    }

    // display score
    int score = grid.getScore();
    char str[256];
    sprintf(str, "Score: %d", score);
    SDL_Surface* s1 = TTF_RenderText_Solid(font, str, white);
    SDL_Texture* m = SDL_CreateTextureFromSurface(rend, s1);
    SDL_Rect mr;
    mr.x = 525;
    mr.y = 100;
    mr.w = 100;
    mr.h = 75;
    SDL_RenderCopy(rend, m, NULL, &mr);

    // display level
    int lvl = grid.getLevel();
    sprintf(str, "Level: %d", lvl);
    s1 = TTF_RenderText_Solid(font, str, white);
    m = SDL_CreateTextureFromSurface(rend, s1);
    mr.x = 525;
    mr.y = 170;
    mr.w = 100;
    mr.h = 75;
    SDL_RenderCopy(rend, m, NULL, &mr);
    
    drawGrid(rend, grid);
    drawPiece(rend, piece1);
    SDL_RenderPresent(rend);
    // Calculate to 60 fps
    SDL_Delay(1000 / 60);   
  }
 
  // // free surface and texture later?

  // Clean up font stuff
  SDL_DestroyTexture(message);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);
  TTF_Quit();

  // Destroy renderer
  SDL_DestroyRenderer(rend);

  // Destroy window
  SDL_DestroyWindow(win);

  return 0;
}
