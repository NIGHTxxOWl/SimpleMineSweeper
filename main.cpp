//Name: Dylan Yoder
//Date:Aug 31, 2017
//Class:
//Section:
//File: main.cpp
//Description: 

#include<iostream>
#include<cstdlib>
#include<time.h>
#include <string>
using namespace std;

struct Tile
{
    enum Type{
      BOMB,
      EMPTY
    }tileType;

    bool isChecked;
    int bombsNear;
};

class Board
{
  public:
    Board():grid(NULL), numRows(0), numCols(0), numBombs(0){}

    Board(int rows, int cols, int bombs)
    {
      numRows = rows;
      numCols = cols;
      numBombs = bombs;
      grid = new Tile*[numRows];

      for(int i = 0; i < numRows; i++)
      {
        grid[i] = new Tile[numCols];
        for(int j = 0; j < numCols; j++)
        {
          grid[i][j].tileType = Tile::EMPTY;
          grid[i][j].isChecked = false;
          grid[i][j].bombsNear = -1;
        }
      }

      for(int bombsPlaced = 0; bombsPlaced < numBombs;)
      {
        int xcoord = rand()%numRows;
        int ycoord = rand()%numCols;

        if(grid[xcoord][ycoord].tileType == Tile::EMPTY)
        {
          grid[xcoord][ycoord].tileType = Tile::BOMB;
          bombsPlaced++;
        }
      }
    }

    ~Board(){
      if(grid != NULL)
      {
        for(int i = 0; i < numRows; i++)
        {
            delete[] grid[i];
        }
        delete[] grid;

      }
    }

    bool CheckForBomb(int x, int y)
    {
      bool isBomb = false;
      if(withinGrid(x, y))
      {
        if(grid[x][y].isChecked)
        {
          cout << "You already checked that space!" << endl;
          isBomb = grid[x][y].tileType == Tile::BOMB;
        }
        else
        {
          if(grid[x][y].tileType == Tile::EMPTY)
          {
            grid[x][y].bombsNear = GetTileValue(x, y);
            cout << grid[x][y].bombsNear << endl;
            isBomb = false;
          }
          else
          {
            isBomb = true;
          }
          grid[x][y].isChecked = true;
        }
      }
      else
      {
        cout <<"Coord is out of bounds" << endl;
      }

      return isBomb;
    }

    int GetTileValue(int x, int y)
    {
      int value = 0;

      for(int newX = x - 1; newX <= x + 1; newX++)
      {
        for (int newY = y + 1; newY >= y - 1; newY--)
        {
          if(!(newX == x && newY == y) && withinGrid(newX, newY))
          {
            if(grid[newX][newY].tileType == Tile::BOMB)
            {
              value++;
              cout << "Bombs Near: " << value << endl;
            }
          }
        }
      }


      return value;
    }

    bool withinGrid(int x, int y)
    {
      return (x >= 0 && x < numCols && y >= 0 && y < numRows);
    }

    Tile** grid;
    int numRows;
    int numCols;
    int numBombs;
};

void printBoard(Board &board);


int main()
{
  srand(time(NULL));
  bool cont = false;
  int rows = 0;
  int cols = 0;
  int bombs = 0;

  int colGuess = 0;
  int rowGuess = 0;
  cout << "Rows: ";
  cin >> rows;
  cout <<"Columns: ";
  cin >> cols;
  cout << "Bombs: ";
  cin >> bombs;
  Board myBoard(rows, cols, bombs);
  do
  {
    printBoard(myBoard);

    cout << "Guess: (col row): ";
    cin >> colGuess;
    cin >> rowGuess;

    cont = !myBoard.CheckForBomb(colGuess, rowGuess);
  }while (cont);
  cout << endl;
  printBoard(myBoard);

  return 0;
}


void printBoard(Board &board)
{
  int colIndex = 0;
  int rowIndex = board.numRows - 1;
  for(int i = board.numRows - 1; i >=0; i--)
  {
    cout << " ";
    for(int k = 0; k < (board.numCols*2) + 1; k++)
    {
      cout << "-";
    }
    cout << "\n";
    for(int j = 0; j < board.numCols; j++)
    {
      if(j == 0)
      {
        cout << rowIndex--;
      }
      cout << "|";
      if(!board.grid[i][j].isChecked)
      {
        cout << "?";
      }
      else if(board.grid[i][j].tileType == Tile::EMPTY)
      {
        if(board.grid[i][j].bombsNear <= 0)
        {
          cout << " ";
        }
        else
        {
          cout << board.grid[i][j].bombsNear;
        }
      }
      else if(board.grid[i][j].tileType == Tile::BOMB)
      {
        cout << "#";
      }
    }
    cout << "|";
    cout << "\n";
  }
  cout << " ";
  for(int k = 0; k < (board.numCols*2) + 1; k++)
  {
    cout << "-";
  }
  cout << "\n ";
  for(int k = 0; k < (board.numCols*2) + 1; k++)
  {
    if(k%2 == 0)
    {
      cout << " ";

    }
    else
    {
      cout << colIndex++;
    }
  }
  cout << "\n";
}
