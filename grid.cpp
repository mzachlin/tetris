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
  g_num_lines_cleared = 0;
  g_level = 0;
  g_score = 0;
}
int Grid::getLevel() {
  return g_level;
}

int Grid::getScore() {
  return g_score;
}

void Grid::UpdateGrid(Piece piece) {
  vector<SDL_Rect> blocks = piece.Get_Blocks();
  for (int i = 0; i < 4; i++) {
    SDL_Rect rect = blocks[i];
    int x = rect.x/piece.GetBlockSize();
    int y = rect.y/piece.GetBlockSize();
    box b = {rect, true, piece.GetPShape()};
    if (y >= g_y_num || x >= g_x_num) {
      cout << "wrong! x is " << x << " and y is " << y << endl;
    }

    grid_blocks[y][x] = b;
  }
}

vector<vector<box> > Grid::GetGridBlocks() {
  return grid_blocks;
}

bool Grid::isOccupied(int x, int y, int block_size) {
  x = x/block_size;
  y = y/block_size;
  return grid_blocks[y][x].filled;
}

void Grid::CheckRows() {
  int curr_lines_cleared = 0;
  for (int i = 0; i <= g_y_num; i++){
    bool isFull = true;
    for (int k = 0; k < g_x_num; k++) {
        if (!grid_blocks[i][k].filled) {
          isFull = false;
          break;
        }

    }
    if (isFull) {
      //copy down all the rows above; decrement their positions
      for (int k = i; k > 0; k--) {
          for (int j = 0; j < g_x_num; j++) {
            grid_blocks[k][j] = grid_blocks[k-1][j];
            if (grid_blocks[k-1][j].filled) {
              grid_blocks[k][j].rect.y += g_block_size;
            }
          }
      }
      //blank out top row
      for (int j = 0; j < g_x_num; j++) {
        grid_blocks[0][j].filled = false;
      }
      curr_lines_cleared++;

    }
  }

  //update level and score
  vector<double> multipliers = {1, 2.5, 7.5, 30};
  if (curr_lines_cleared) {
    g_score += 40*(g_level+1)*multipliers[curr_lines_cleared - 1];
    cout << "score: " << g_score << " level: " << g_level << endl;
  }
  g_num_lines_cleared+=curr_lines_cleared;
  g_level = g_num_lines_cleared/10;

}
