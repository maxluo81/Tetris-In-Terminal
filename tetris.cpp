#include <iostream>
#include <unistd.h> 
#include <cmath>
#include "tetris.hpp"

/**
 * Tetris class to keep track of board information and conditions.
 *
 * @author Max Luo
 * @version Oct 2022
 */

Tetris::Tetris(){
cout << "COL: " << COL << endl;
  for(int r = 0; r < ROW; r++){
    for(int c = 1; c < COL+1; c++){
      board[r][c] = 0;
    }
  }
  for(int c = 0; c < COL+2; c++){
    board[ROW][c] = 8;
  }
  for(int r = 0; r < ROW; r++){
    board[r][0] = 8;
    board[r][COL+1] = 8;
  }
  score = 0;
  lines = 0;
}

void Tetris::printBoard(){
  cout << "\033[F";
  for(int i = 0; i < 99; i++){
    cout << " ";
  }
  for(int i = 0; i < 26; i++){
    cout << "\033[F";
  }
  
  //hud
  cout << RESET << "\033[FHold:       Next:     Score:   Lvl:   Lines: " << endl;
  for(int c = 1; c < 11; c++){
    cout << color[hud[0][c]] << "  ";
  }
  cout << RESET << "  " << score;
  for(int i = 0; i < (8 - (int)(log10(score + 0.9))); i++)
    cout << " ";
  cout << Tetris::getLevel();
  for(int i = 0; i < (6 - (int)(log10(Tetris::getLevel()))); i++)
    cout << " ";
  cout << lines << endl;
  for(int c = 1; c < 11; c++){
    cout << color[hud[1][c]] << "  ";
  }

  //board
  cout << RESET << endl;
  for(int i = 0; i < COL+1; i++)
    cout << "==";  
  cout << endl;
  
  for(int r = 0; r < ROW; r++){
    cout << "|";
    for(int c = 1; c < COL+1; c++){
      if(board[r][c] > 7){
        cout << color[board[r][c]] << "[]" << RESET;
      }
      else{
        cout << color[board[r][c]] << "  ";
      }
      cout << RESET;
    }
    cout << RESET << "|" << endl;
  }
  
  for(int i = 0; i < COL+1; i++)
    cout << "==";
  cout << endl;
}

void Tetris::addPts(int p){
  score += p;
}

void Tetris::setHud(int h, int n){
  if(h == 0 && n == 0){
    for(int r = 0; r < 2; r++){
      for(int c = 0; c < 12; c++){
        hud[r][c] = 0;
      }
    }
  }
  else{
    Tetris::setHudArray(h, 1, 0, 0, h);
    Tetris::setHudArray(n, 7, 0, 0, n);
  }
}

void Tetris::setDrop(int pc, int x, int y, int s){
  int index = 0;
  for(int i = y; i < ROW+1; i++){
    if(Tetris::collide(pc, x, i, s)){
      index = i - 1;
      Tetris::setBoard(pc, x, index, s, (pc + 10));
      break;
    }
  }
}

void Tetris::removeDrop(){
  for(int r = 0; r < ROW; r++){
    for(int c = 1; c < COL+1; c++){
      if(board[r][c] > 7)
        board[r][c] = 0;
    }
  }
}

void Tetris::setBoard(int pc, int x, int y, int s, int p){  
  if(pc == 1){
    board[y][x] = p;
    board[y+1][x] = p;
    board[y][x+1] = p;
    board[y+1][x+1] = p;
  }
  if(pc == 2){
    if(s == 0 || s == 2){
      board[y][x] = p;
      board[y][x+1] = p;
      board[y][x+2] = p;
      board[y][x+3] = p;
    } 
    if(s == 1 || s == 3){
      board[y][x] = p;
      board[y+1][x] = p;
      board[y+2][x] = p;
      board[y+3][x] = p;  
    }
  }
  if(pc == 3){
    if(s == 0 || s == 2){
      board[y][x+1] = p;
      board[y][x+2] = p;
      board[y+1][x] = p;
      board[y+1][x+1] = p; 
    } 
    if(s == 1 || s == 3){
      board[y][x] = p;
      board[y+1][x] = p;
      board[y+1][x+1] = p;
      board[y+2][x+1] = p;  
    }
  }
  if(pc == 4){
    if(s == 0 || s == 2){
      board[y][x] = p;
      board[y][x+1] = p;
      board[y+1][x+1] = p;
      board[y+1][x+2] = p;
    } 
    if(s == 1 || s == 3){
      board[y][x+1] = p;
      board[y+1][x+1] = p;
      board[y+1][x] = p;
      board[y+2][x] = p;
    }
  }
  if(pc == 5){
    if(s == 0){
      board[y][x+1] = p;
      board[y+1][x] = p;
      board[y+1][x+1] = p;
      board[y+1][x+2] = p;
    } 
    if(s == 1){
      board[y][x] = p;
      board[y+1][x] = p;
      board[y+1][x+1] = p;
      board[y+2][x] = p;
    }
    if(s == 2){
      board[y][x] = p;
      board[y][x+1] = p;
      board[y][x+2] = p;
      board[y+1][x+1] = p;  
    }
    if(s == 3){
      board[y][x+1] = p;
      board[y+1][x] = p;
      board[y+1][x+1] = p;
      board[y+2][x+1] = p;
    }
  }
  if(pc == 6){
    if(s == 0){
      board[y][x+2] = p;
      board[y+1][x] = p;
      board[y+1][x+1] = p;
      board[y+1][x+2] = p;
    } 
    if(s == 1){
      board[y][x] = p;
      board[y+1][x] = p;
      board[y+2][x] = p;
      board[y+2][x+1] = p; 
    }
    if(s == 2){
      board[y][x] = p;
      board[y][x+1] = p;
      board[y][x+2] = p;
      board[y+1][x] = p;
    }
    if(s == 3){
      board[y][x] = p;
      board[y][x+1] = p;
      board[y+1][x+1] = p;
      board[y+2][x+1] = p;
    }
  }
  if(pc == 7){
    if(s == 0){
      board[y][x] = p;
      board[y+1][x] = p;
      board[y+1][x+1] = p;
      board[y+1][x+2] = p; 
    } 
    if(s == 1){
      board[y][x] = p;
      board[y][x+1] = p;
      board[y+1][x] = p;
      board[y+2][x] = p;  
    }
    if(s == 2){
      board[y][x] = p;
      board[y][x+1] = p;
      board[y][x+2] = p;
      board[y+1][x+2] = p; 
    }
    if(s == 3){
      board[y][x+1] = p;
      board[y+1][x+1] = p;
      board[y+2][x+1] = p;
      board[y+2][x] = p; 
    }
  }
}

void Tetris::setHudArray(int pc, int x, int y, int s, int p){  
  if(pc == 1){
    hud[y][x] = p;
    hud[y+1][x] = p;
    hud[y][x+1] = p;
    hud[y+1][x+1] = p;
  }
  if(pc == 2){
    if(s == 0 || s == 2){
      hud[y][x] = p;
      hud[y][x+1] = p;
      hud[y][x+2] = p;
      hud[y][x+3] = p;
    } 
    if(s == 1 || s == 3){
      hud[y][x] = p;
      hud[y+1][x] = p;
      hud[y+2][x] = p;
      hud[y+3][x] = p;  
    }
  }
  if(pc == 3){
    if(s == 0 || s == 2){
      hud[y][x+1] = p;
      hud[y][x+2] = p;
      hud[y+1][x] = p;
      hud[y+1][x+1] = p; 
    } 
    if(s == 1 || s == 3){
      hud[y][x] = p;
      hud[y+1][x] = p;
      hud[y+1][x+1] = p;
      hud[y+2][x+1] = p;  
    }
  }
  if(pc == 4){
    if(s == 0 || s == 2){
      hud[y][x] = p;
      hud[y][x+1] = p;
      hud[y+1][x+1] = p;
      hud[y+1][x+2] = p;
    } 
    if(s == 1 || s == 3){
      hud[y][x+1] = p;
      hud[y+1][x+1] = p;
      hud[y+1][x] = p;
      hud[y+2][x] = p;
    }
  }
  if(pc == 5){
    if(s == 0){
      hud[y][x+1] = p;
      hud[y+1][x] = p;
      hud[y+1][x+1] = p;
      hud[y+1][x+2] = p;
    } 
    if(s == 1){
      hud[y][x] = p;
      hud[y+1][x] = p;
      hud[y+1][x+1] = p;
      hud[y+2][x] = p;
    }
    if(s == 2){
      hud[y][x] = p;
      hud[y][x+1] = p;
      hud[y][x+2] = p;
      hud[y+1][x+1] = p;  
    }
    if(s == 3){
      hud[y][x+1] = p;
      hud[y+1][x] = p;
      hud[y+1][x+1] = p;
      hud[y+2][x+1] = p;
    }
  }
  if(pc == 6){
    if(s == 0){
      hud[y][x+2] = p;
      hud[y+1][x] = p;
      hud[y+1][x+1] = p;
      hud[y+1][x+2] = p;
    } 
    if(s == 1){
      hud[y][x] = p;
      hud[y+1][x] = p;
      hud[y+2][x] = p;
      hud[y+2][x+1] = p; 
    }
    if(s == 2){
      hud[y][x] = p;
      hud[y][x+1] = p;
      hud[y][x+2] = p;
      hud[y+1][x] = p;
    }
    if(s == 3){
      hud[y][x] = p;
      hud[y][x+1] = p;
      hud[y+1][x+1] = p;
      hud[y+2][x+1] = p;
    }
  }
  if(pc == 7){
    if(s == 0){
      hud[y][x] = p;
      hud[y+1][x] = p;
      hud[y+1][x+1] = p;
      hud[y+1][x+2] = p; 
    } 
    if(s == 1){
      hud[y][x] = p;
      hud[y][x+1] = p;
      hud[y+1][x] = p;
      hud[y+2][x] = p;  
    }
    if(s == 2){
      hud[y][x] = p;
      hud[y][x+1] = p;
      hud[y][x+2] = p;
      hud[y+1][x+2] = p; 
    }
    if(s == 3){
      hud[y][x+1] = p;
      hud[y+1][x+1] = p;
      hud[y+2][x+1] = p;
      hud[y+2][x] = p; 
    }
  }
}

bool Tetris::collide(int pc, int x, int y, int s){
  if(pc == 1){
    if(board[y][x] != 0 || board[y+1][x] != 0 || 
       board[y][x+1] != 0 || board[y+1][x+1] != 0)
      return true;
  }
  if(pc == 2){
    if(s == 0 || s == 2){
      if(board[y][x] != 0 || board[y][x+1] != 0 ||
         board[y][x+2] != 0 || board[y][x+3] != 0)
        return true;
    } 
    if(s == 1 || s == 3){
      if(board[y][x] != 0 || board[y+1][x] != 0 ||
         board[y+2][x] != 0 || board[y+3][x] != 0)
        return true;
    }
  }
  if(pc == 3){
    if(s == 0 || s == 2){
      if(board[y][x+1] != 0 || board[y][x+2] != 0 ||
         board[y+1][x] != 0 || board[y+1][x+1] != 0)
        return true;
    } 
    if(s == 1 || s == 3){
      if(board[y][x] != 0 || board[y+1][x] != 0 ||
         board[y+1][x+1] != 0 || board[y+2][x+1] != 0)
        return true;
    }
  }
  if(pc == 4){
    if(s == 0 || s == 2){
      if(board[y][x] != 0 || board[y][x+1] != 0 || 
         board[y+1][x+1] != 0||board[y+1][x+2] != 0)
        return true;
    } 
    if(s == 1 || s == 3){
      if(board[y][x+1] != 0 || board[y+1][x+1] != 0 ||
         board[y+1][x] != 0 || board[y+2][x] != 0)
        return true;
    }
  }
  if(pc == 5){
    if(s == 0){
      if(board[y][x+1] != 0 || board[y+1][x] != 0 ||
         board[y+1][x+1] != 0 || board[y+1][x+2] != 0)
        return true;
    } 
    if(s == 1){
      if(board[y][x] != 0 || board[y+1][x] != 0 ||
         board[y+1][x+1] != 0 || board[y+2][x] != 0)
        return true;
    }
    if(s == 2){
      if(board[y][x] != 0 || board[y][x+1] != 0 ||
         board[y][x+2] != 0 || board[y+1][x+1] != 0)
        return true;
    }
    if(s == 3){
      if(board[y][x+1] != 0 || board[y+1][x] != 0 ||
         board[y+1][x+1] != 0 || board[y+2][x+1] != 0)
        return true;
    }
  }
  if(pc == 6){
    if(s == 0){
      if(board[y][x+2] != 0 || board[y+1][x] != 0 || 
         board[y+1][x+1] != 0 || board[y+1][x+2] != 0)
        return true;
    } 
    if(s == 1){
      if(board[y][x] != 0 || board[y+1][x] != 0 ||
         board[y+2][x] != 0 || board[y+2][x+1] != 0)
        return true;
    }
    if(s == 2){
      if(board[y][x] != 0 || board[y][x+1] != 0 ||
         board[y][x+2] != 0 || board[y+1][x] != 0)
        return true;
    }
    if(s == 3){
      if(board[y][x] != 0 || board[y][x+1] != 0 ||
         board[y+1][x+1] != 0 || board[y+2][x+1] != 0)
        return true;
    }
  }
  if(pc == 7){
    if(s == 0){
      if(board[y][x] != 0 || board[y+1][x] != 0 ||
         board[y+1][x+1] != 0 || board[y+1][x+2] != 0)
        return true;
    } 
    if(s == 1){
      if(board[y][x] != 0 || board[y][x+1] != 0 ||
         board[y+1][x] != 0 ||board[y+2][x] != 0)
        return true;
    }
    if(s == 2){
      if(board[y][x] != 0 || board[y][x+1] != 0 ||
         board[y][x+2] != 0 || board[y+1][x+2] != 0)
        return true;
    }
    if(s == 3){
      if(board[y][x+1] != 0 || board[y+1][x+1] != 0 ||
         board[y+2][x+1] != 0 || board[y+2][x] != 0)
        return true;
    }
  }
  return false;
}

void Tetris::drop(int pc, int x, int y, int s){
  int index = 0;
  for(int i = y; i < ROW+1; i++){
    if(Tetris::collide(pc, x, i, s)){
      index = i - 1;
      break;
    }
  }
  Tetris::setBoard(pc, x, index, s, pc);
  Tetris::clear();
}

void Tetris::clear(){
  int clears = 0;
  bool show = false;
  for(int r = ROW-1; r >= 0; r--){
    bool line = true;
    for(int c = 1; c < COL+1; c++){
      if(board[r][c] == 0){
        line = false;
      }
    }
    if(line == true){
      show = true;
      for(int c = 1; c < COL+1; c++){
        board[r][c] = 6;
      }
    }
  }
  if(show){
    Tetris::printBoard();
    sleep(1);
  }  
  
  for(int r = ROW-1; r >= 0; r--){
    bool line = true;
    for(int c = 1; c < COL+1; c++){
      if(board[r][c] == 0){
        line = false;
      }
    }
    if(line){  
      clears++;
      lines++;
      for(int i = r; i > 0; i--){
        for(int c = 1; c < COL+1; c++){
          board[i][c] = board[i-1][c];
        }
      }
      for(int c = 1; c < COL+1; c++){
        board[0][c] = 0;
      }
      r++;
    }
  }
  if(clears == 1)
    score += 40;
  if(clears == 2)
    score += 100;
  if(clears == 3)
    score += 300;
  if(clears == 4)
    score += 1200;
}

int Tetris::getLevel(){
  return (lines / 10) + 1; 
}

int Tetris::getCOL(){
  return COL;
}
