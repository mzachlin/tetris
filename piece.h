#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>          // Graphics libraries
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

using namespace std;

class Grid;

class Piece
{
private: //internal variable declarations
  vector<SDL_Rect> blocks;
  int p_block_size;
  int p_win_h;
  int p_win_w;
  int p_shape;
  bool locked;
  int center_x;
  int center_y;
  bool OutOfBounds(bool checkDown, bool checkLeft, bool checkRight, Grid *grid);
  void Rotate(Grid* grid);
  void MoveLoc(int x, int y);
public: //method declarations
  Piece(int block_size, int win_w, int win_h);
  vector<SDL_Rect> Get_Blocks();
  bool Move(int x, int y, int r, Grid *grid, SDL_Renderer* rend=NULL);
  bool isLocked();
  int GetWinWidth();
  int GetWinHeight();
  int GetBlockSize();
  int GetPShape();
};
#endif
