using namespace std;

/**
 * Header file for tetris class.
 *
 * @author Max Luo
 * @version Oct 2022
 */

class Tetris {
  public: 
    Tetris();    
    void printBoard();
    void addPts(int);
    void setHud(int, int);
    void setDrop(int, int, int, int);
    void removeDrop();
    void setBoard(int, int, int, int, int);
    void setHudArray(int, int, int, int, int);
    bool collide(int, int, int, int);
    void drop(int, int, int, int);
    int getLevel();
    int getCOL();

  private:
    int ROW = 20;
    int COL = 10;
    int board[20+1][10+2];
    int hud[2][12];
    int score, lines;

    const string RESET = "\033[0;m";
    const string RED = "\033[41m";
    const string GREEN = "\033[42m";
    const string YELLOW = "\033[43m";
    const string BLUE = "\033[44m";
    const string MAGENTA = "\033[45m";
    const string CYAN = "\033[46m";
    const string WHITE = "\033[47m";
    const string REDf = "\033[31m";
    const string GREENf = "\033[32m";
    const string YELLOWf = "\033[33m";
    const string BLUEf = "\033[34m";
    const string MAGENTAf = "\033[35m";
    const string CYANf = "\033[36m";
    const string WHITEf = "\033[37m";
    string color[18] = {RESET, YELLOW, CYAN, GREEN, RED, MAGENTA, WHITE, BLUE, RESET, RESET, RESET, YELLOWf, CYANf, GREENf, REDf, MAGENTAf, WHITEf, BLUEf};

    void clear();
};

