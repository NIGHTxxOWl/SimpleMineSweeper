//Name: Dylan Yoder
//Date:Aug 31, 2017
//Class:
//Section:
//File: main.cpp
//Description: 

#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

struct Tile
{
    enum Type{
      BOMB,
      NUMBER,
      EMPTY
    }tileType;

    bool isChecked;
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

    Tile** grid;
    int numRows;
    int numCols;
    int numBombs;
};

void printBoard(Board &board);


int main()
{
  srand(12);
  char cont = 'n';
  int rows = 0;
  int cols = 0;
  int bombs = 0;
  do
  {
    cout << "Rows: ";
    cin >> rows;
    cout <<"Columns: ";
    cin >> cols;
    cout << "Bombs: ";
    cin >> bombs;

    Board myBoard(rows, cols, bombs);

    printBoard(myBoard);


    cout << "Continue?(y/n): ";
    cin >> cont;
  }while (cont == 'y');

  return 0;
}


void printBoard(Board &board)
{
  for(int i = board.numRows - 1; i >=0; i--)
  {
    for(int k = 0; k < (board.numCols*2) + 1; k++)
    {
      cout << "-";
    }
    cout << "\n";
    for(int j = 0; j < board.numCols; j++)
    {
      cout << "|";
      if(board.grid[i][j].tileType == Tile::EMPTY)
      {
        cout << " ";
      }
      else if(board.grid[i][j].tileType == Tile::BOMB)
      {
        cout << "#";
      }
    }
    cout << "|";
    cout << "\n";
  }
  for(int k = 0; k < (board.numCols*2) + 1; k++)
  {
    cout << "-";
  }
  cout << "\n";
}
