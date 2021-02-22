#include "grid.h"

Grid::Grid(int width, int height, int block_size) {
  g_x_num = width/block_size;
  g_y_num = height/block_size;
  g_block_size = block_size;

  //create blank grid
  for (int i = 0; i <= g_y_num; i++) {
    vector<box> row;
    for (int k = 0; k <= g_x_num; k++ ) {
      SDL_Rect r1;
      box one_box = {r1, false};
      row.push_back(one_box);
    }
    grid_blocks.push_back(row);
  }
}

void Grid::UpdateGrid(Piece piece) {
  vector<SDL_Rect> blocks = piece.Get_Blocks();
  for (int i = 0; i < 4; i++) {
    SDL_Rect rect = blocks[i];
    int x = rect.x/piece.GetBlockSize();
    int y = rect.y/piece.GetBlockSize();
    box b = {rect, true};
    if (y >= g_y_num || x >= g_x_num) {
      cout << "wrong! x is " << x << " and y is " << y << endl;
    }
    /*else {
      cout << "rect x is " << rect.x << " and rect y is " << rect.y << endl;
    }*/
    grid_blocks[y][x] = b;
  }
}

vector<vector<box> > Grid::GetGridBlocks() {
  return grid_blocks;
}

bool Grid::isOccupied(int x, int y, int block_size) {
  x = x/block_size;
  y = y/block_size;
  if (x >= g_x_num || y >= g_y_num ) {
    cout << "isOccupied: g_x_num: " << g_x_num << " x: " << x << " g_y_num: " << g_y_num << " y: " << y << endl;
  }
  return grid_blocks[y][x].filled;
}

void Grid::CheckRows() {
  for (auto it = grid_blocks.begin(); it != grid_blocks.end(); ++it){
    bool isFull = true;
    for (int k = 0; k < g_y_num; k++) {
      if (!(*it)[k].filled) {
        isFull = false;
      }
    }
    if (isFull) {
      //copy down all the rows above; decrement their positions
      for (auto kt = grid_blocks.end(); kt != grid_blocks.end(); ++kt) {
        if (kt != grid_blocks.end()) {
          for (int j = 0; j < g_y_num; j++) {
            (*kt)[j] = (*kt)[j+1];
            if ((*kt)[j+1].filled) {
              (*kt)[j].rect.x -= g_block_size;
            }
          }
          //TODO:: blank out top row

        }
      }
    }
  }
}
