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
  bool locked;
  int orientation;  // This is a number 0-3, with 0 being the starting orientation
  vector<vector<int>> rotateWeights;  
  bool OutOfBounds(bool checkDown, bool checkLeft, bool checkRight, Grid *grid);
  void Rotate();
  void MoveLoc(int x, int y);
public: //method declarations
  Piece(int block_size, int win_w, int win_h);
  vector<SDL_Rect> Get_Blocks();
  void Move(int x, int y, int r, Grid *grid, SDL_Renderer* rend=NULL);
  bool isLocked();
  int GetWinWidth();
  int GetWinHeight();
  int GetBlockSize();
};
#endif
