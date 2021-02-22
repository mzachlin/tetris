#ifndef GRID_H
#define GRID_H

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>          // Graphics libraries
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "box.h"
#include "piece.h"

using namespace std;


class Grid
{

private: //internal variable declarations
  int g_x_num;
  int g_y_num;
  int g_block_size;
  vector<vector<box> > grid_blocks;

public: //method declarations
  Grid(int width, int height, int block_size);
  void UpdateGrid(Piece piece);
  vector<vector<box> > GetGridBlocks();
  bool isOccupied(int x, int y, int block_size);
  void CheckRows();
};
#endif
