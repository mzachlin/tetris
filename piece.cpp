#include "piece.h"
#include "grid.h"

// Piece constructer
Piece::Piece(int block_size, int win_w, int win_h) {
  p_block_size = block_size;
  p_win_w = win_w;
  p_win_h = win_h;
  locked = false;
  //create shape with blocks
  for (int i = 0; i < 4; i++) {
    // Create rectangle
    SDL_Rect rect;
    rect.w = p_block_size;
    rect.h = p_block_size;
    // Set initial x and y position
    rect.x = p_win_w/2-p_block_size;
    rect.y = p_block_size*i;
    blocks.push_back(rect);
  }

}

int Piece::GetWinWidth() {
  return p_win_w;
}

int Piece::GetWinHeight() {
  return p_win_h;
}

int Piece::GetBlockSize() {
  return p_block_size;
}

//member functions
vector<SDL_Rect> Piece::Get_Blocks() {
  return blocks;
}

bool Piece::isLocked() {
  return locked;
}

bool Piece::OutOfBounds(bool checkDown, bool checkLeft, bool checkRight, Grid *grid) {
  for (int i = 0; i < 4; i++) {
    if (checkDown && (blocks[i].y + blocks[i].h > p_win_h || grid->isOccupied(blocks[i].x, blocks[i].y, blocks[i].h))) {
      cout << "occupied; x is " << blocks[i].x << " y is " << blocks[i].y << endl;
      return true;
    }
    if (checkLeft && (blocks[i].x < 0 || grid->isOccupied(blocks[i].x, blocks[i].y, blocks[i].h))) {
      return true;
    }
    if (checkRight && (blocks[i].x + blocks[i].w > p_win_w || grid->isOccupied(blocks[i].x, blocks[i].y, blocks[i].h))) {
      return true;
    }
  }
  return false;
}

void Piece::MoveLoc(int x, int y) {
  //move down, left, right

  for (int i = 3; i >= 0; i--) {
    blocks[i].x += p_block_size*x;
    blocks[i].y += p_block_size*y;
  }


}


void Piece::Move(int x, int y, int r, Grid *grid, SDL_Renderer* rend) {

  MoveLoc(x, y);

  if (r) {
    Rotate();
    drawPiece(rend, *this);
  }

  //left boundary check
  while (OutOfBounds(false, true, false, grid) && x<0) {
    MoveLoc(1, 0);
  }

  //right boundary check
  while (OutOfBounds(false, false, true, grid) && x >0) {
    MoveLoc(-1, 0);
  }

  //lower boundary check
  while (OutOfBounds(true, false, false, grid) && y) {
    MoveLoc(0, -1);
    locked = true;
  }
  grid->CheckRows();
  /*for (int i = 0; i < 4; i++) {
    cout << "Move: location is (x: " << blocks[i].x << ", y: " << blocks[i].y << ")" << endl;
  }*/

}


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

void Piece::drawPiece(SDL_Renderer* rend, Piece piece) {
  vector<SDL_Rect> blocks = piece.Get_Blocks();
  for (int i = 0; i < 4; i++) {
    drawShape(rend, blocks[i]);
  }
}


