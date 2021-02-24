#include "piece.h"
#include "grid.h"

// Piece constructor

Piece::Piece(int block_size, int win_w, int win_h) {
  p_block_size = block_size;
  p_win_w = win_w;
  p_win_h = win_h;
  locked = false;
  SDL_Rect rect;
  rect.w = p_block_size;
  rect.h = p_block_size;
  p_shape = rand()%7;
  switch(p_shape) {
    case 0: // right z
      // Top right
      rect.x = p_win_w/2-p_block_size;
      rect.y = p_block_size;
      blocks.push_back(rect);
      // Top left
      rect.x = p_win_w/2-2*p_block_size;
      rect.y = p_block_size;
      blocks.push_back(rect);
      // Bottom right
      rect.x = p_win_w/2-2*p_block_size;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      // Bottom left
      rect.x = p_win_w/2-3*p_block_size;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      center_x = blocks[2].x + p_block_size/2;
      center_y = blocks[2].y + p_block_size/2;
      break;
    case 1: //left z
      // Bottom right
      rect.x = p_win_w/2-p_block_size;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      // Bottom left
      rect.x = p_win_w/2-2*p_block_size;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      // Top right
      rect.x = p_win_w/2-2*p_block_size;
      rect.y = p_block_size;
      blocks.push_back(rect);
      // Top left
      rect.x = p_win_w/2-3*p_block_size;
      rect.y = p_block_size;
      blocks.push_back(rect);
      center_x = blocks[1].x + p_block_size/2;
      center_y = blocks[1].y + p_block_size/2;
      break;
    case 2: //left l
      // Top left
      rect.x = p_win_w/2-p_block_size;
      rect.y = p_block_size;
      blocks.push_back(rect);
      // Left
      rect.x = p_win_w/2-p_block_size;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      // Middle
      rect.x = p_win_w/2;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      // Right
      rect.x = p_win_w/2+p_block_size;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      center_x = blocks[1].x + p_block_size*1.5;
      center_y = blocks[1].y + p_block_size/2;
      break;
    case 3: //right l
      // Top right
      rect.x = p_win_w/2+p_block_size;
      rect.y = p_block_size;
      blocks.push_back(rect);
      // Left
      rect.x = p_win_w/2-p_block_size;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      // Middle
      rect.x = p_win_w/2;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      // Right
      rect.x = p_win_w/2+p_block_size;
      rect.y = 2*p_block_size;
      blocks.push_back(rect);
      center_x = blocks[1].x + p_block_size*1.5;
      center_y = blocks[1].y + p_block_size/2;
      break;
    case 4: // square
      // Top left
      rect.x = p_win_w/2-p_block_size;
      rect.y = p_block_size;
      blocks.push_back(rect);
      // Top right
      rect.x = p_win_w/2;
      rect.y = p_block_size;
      blocks.push_back(rect);
      // Bottom left
      rect.x = p_win_w/2-p_block_size;
      rect.y = p_block_size*2;
      blocks.push_back(rect);
      // Bottom right
      rect.x = p_win_w/2;
      rect.y = p_block_size*2;
      blocks.push_back(rect);
      center_x = blocks[0].x + p_block_size;
      center_y = blocks[0].y + p_block_size;
      break;
    case 5: // t
      // Stem
      rect.x = p_win_w/2-p_block_size;
      rect.y = p_block_size;
      blocks.push_back(rect);
      // Middle
      rect.x = p_win_w/2-p_block_size;
      rect.y = p_block_size*2;
      blocks.push_back(rect);
      // Left
      rect.x = p_win_w/2-2*p_block_size;
      rect.y = p_block_size*2;
      blocks.push_back(rect);
      rect.x = p_win_w/2;
      rect.y = p_block_size*2;
      // Right
      blocks.push_back(rect);
      center_x = blocks[1].x + p_block_size/2;
      center_y = blocks[1].y + p_block_size/2;
      break;
    case 6: // line
      for (int i = 0; i < 4; i++) {
        rect.x = p_win_w/2-p_block_size;
        rect.y = p_block_size*i;
        blocks.push_back(rect);
      }
      center_x = blocks[0].x + p_block_size;
      center_y = blocks[1].y + p_block_size;
      break;
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
      cout << "occupied| oob; x is " << blocks[i].x << " y is " << blocks[i].y << endl;
      return true;
    }
    if (checkLeft && (blocks[i].x < 0 || grid->isOccupied(blocks[i].x, blocks[i].y, blocks[i].h))) {
      cout << "occupied| oob; x is " << blocks[i].x << " y is " << blocks[i].y << endl;
      return true;
    }
    if (checkRight && (blocks[i].x + blocks[i].w > p_win_w || grid->isOccupied(blocks[i].x, blocks[i].y, blocks[i].h))) {
      cout << "occupied| oob; x is " << blocks[i].x << " y is " << blocks[i].y << endl;
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
  center_x += p_block_size*x;   // Move center
  center_y += p_block_size*y;

}

void Piece::Rotate(Grid *grid) {
  vector<SDL_Rect> oldBlocks = blocks;
  for (int i = 0; i < 4; i++) {
    int oldX = blocks[i].x;
    blocks[i].x = blocks[i].y + center_x - center_y;
    blocks[i].y = center_x + center_y - oldX - p_block_size;
    if (blocks[i].x%5) {
      blocks[i].x++;
    }
    if (blocks[i].y%5) {
      blocks[i].y++;
    }
  }
  if (OutOfBounds(true, true, true, grid)) {
    cout << "dude is out of bounds" << endl;
    blocks = oldBlocks;
  }
}

void Piece::Move(int x, int y, int r, Grid *grid, SDL_Renderer* rend) {

  MoveLoc(x, y);

  if (r) {
    Rotate(grid);
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
