#include <iostream>
#include <random>
#include <termios.h>
#include "tetris.hpp"
#define key 1
using namespace std;

/**
 * Tetris in Terminal
 *
 * A very bare bones and industry nonstandard tetris game that I made my senior year of high school.
 * Read README.md for controls
 * Have fun!
 *
 * @author Max Luo
 * @version Oct 2022
 */

int main() {
    // better RNG
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 7);

    // arrow key input
    struct termios term;
    tcgetattr(key, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(key, TCSANOW, &term);
    char k, e, input;

    int piece, y, pos, spin; // all you need 
    bool canHold;
    Tetris *tet = new Tetris(); //ONE OBJECT
    int next, moves, hold = 0, defaultPos = tet->getCOL() / 2 - 1;

    next = distr(gen);  
    while(true){
        piece = next;
        next = distr(gen);
        
        y = 0;
        pos = defaultPos;
        spin = 0; 
        canHold = true;
        moves = 1;
        
        if(tet->collide(piece, pos, y, spin)){
          tet->setBoard(piece, pos, y, spin, piece);
          tet->printBoard();
          cout << "GAME OVER" << endl;
          break;
        }
        
        bool movePiece = true;
        while(movePiece){
            tet->setHud(0, 0);
            tet->setHud(hold, next);
    
            tet->setDrop(piece, pos, y, spin);
            tet->setBoard(piece, pos, y, spin, piece);
            tet->printBoard();
            tet->removeDrop();
            tet->setBoard(piece, pos, y, spin, 0);
    
            bool inputLoop = true;
            while(inputLoop){
                while (true){
                    cin >> k;
                    if(k == 'd' || k == 'c'){
                        e = '~';
                        input = '~';
                        break;
                    }
                    cin >> e;
                    cin >> input;
                    if(e == '[')
                        break;
                } //input loop
                
                if(input == 'D' && !tet->collide(piece, (pos-1), y, spin)){
                    pos--;
                    inputLoop = false;
                } //left
                if(input == 'C' && !tet->collide(piece, (pos+1), y, spin)){
                    pos++;
                    inputLoop = false;
                } //right
                if(input == 'B' && !tet->collide(piece, pos, (y), spin)){
                    y++;
                    tet->addPts(1);
                    inputLoop = false;
                } //down
                if(input == 'A'){          
                    int ns = spin + 1;
                    if(ns == 4)
                    ns = 0;
        
                    if(piece != 2 && !tet->collide(piece, pos, y, ns)){
                        spin++;
                    }
                    else if(pos == (tet->getCOL()-1) && !tet->collide(piece, (pos-1), y, ns)){
                        pos--;
                        spin++;
                    }
                    else if(piece == 2 && (spin == 0 || spin == 2)){
                        if(!tet->collide(piece, (pos+1), y, 1)){
                            pos++;
                            spin++;
                        }
                        else if(!tet->collide(piece, (pos+2), y, 1)){
                            pos += 2;
                            spin++;
                        }     
                    } 
                    else if(piece == 2 && (spin == 1 || spin == 3)){
                        if(!tet->collide(piece, (pos-1), y, next)){
                            pos--;
                            spin++;
                        }
                        else if(!tet->collide(piece, (pos-2), y, next)){
                            pos -= 2;
                            spin++;
                        }
                        else if(!tet->collide(piece, (pos-3), y, next)){
                            pos -= 3;
                            spin++;
                        }     
                    } 
                  
                    if(spin == 4)
                        spin = 0;
        
                    inputLoop = false;
                } //spin
                if(k == 'd' && canHold){
                  canHold = false;
                  int temp = piece;          
                  if(hold != 0)
                    piece = hold;
                  else
                    piece = next;
                  
                  hold = temp;
                  spin = 0;
                  y = 0;
                  pos = defaultPos;
                  break;
                } //hold
                if(k == 'c'){
                  tet->addPts(30);
                  tet->drop(piece, pos, y, spin);
                  movePiece = false;
                  break;
                } //drop
        
                int s = (11 - tet->getLevel());
                if(s < 1)
                  s = 1;
                if(moves % s == 0){
                  y++;
                }
                if(tet->collide(piece, pos, (y), spin)){
                  tet->drop(piece, pos, (y-1), spin);
                  movePiece = false;
                  break;
                }
        
          } //while key 
          moves++;
          
        } //while movepiece
  } //game loop
} //main
