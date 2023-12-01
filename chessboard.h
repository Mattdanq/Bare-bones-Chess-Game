// see for background
//  https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html
/*
  Author: Matthew Danque
  CS 341: Project 1 9/18
*/
#include <iostream>
#include <iterator>
using namespace std;

// define separate containers for Color, Piece (enums recommended)
enum Color { Black, White, NONE };
enum Piece { Pawn, Knight, King, Queen, Bishop, Rook, EMPTY };

// a chessboard contains squares
class Square {
private:
  Color color;
  Piece piece;
  bool occupied;

public:
  Square() { // default, square unoccupied
    // fill out
    color = NONE;
    piece = EMPTY;
    occupied = false;
  }

  Square(Color c, Piece p) { // an occupied square
    // fill out
    color = c;
    piece = p;
    occupied = true;
  }

  void get(bool &o, Color &c, Piece &p) {
    o = occupied;
    c = color;
    p = piece;
  }

  void print();
};

class ChessboardIterator;

class Chessboard {
  // make the container iterator friendly
  typedef ChessboardIterator iterator;

private:
  Square chessboard[8][8];

public:
  friend class ChessboardIterator;

  Chessboard() {} // Square does all the initialization

  // return an x,y square from chessboard
  Square square(int x, int y) { return chessboard[x][y]; }

  ChessboardIterator begin();
  ChessboardIterator end();

  bool colorIllegal(Color c) {
    switch (c) {
    case (Black):
      return true;
    case (White):
      return true;
    default:
      return false;
    }
  }

  bool pieceIllegal(Piece p) {
    switch (p) {
    case (Pawn):
      return true;
    case (Knight):
      return true;
    case (King):
      return true;
    case (Queen):
      return true;
    case (Bishop):
      return true;
    case (Rook):
      return true;
    default:
      return false;
    }
  }

  // removes piece from board
  void takePiece(int fromX, int fromY, int toX, int toY, Piece p, Color c) {
    Square empty;
    Square taker(c, p);
    chessboard[fromX][fromY] = empty;
    chessboard[toX][toY] = taker;
  }

  // true if the piece is blocked, false otherwise
  bool pieceBlocked(Piece piece, int fromX, int fromY, int toX, int toY) {
    if (piece == Bishop) {

      int xIter, yIter;

      if ((toX - fromX) > 0) {
        xIter = 1;
      } else {
        xIter = -1;
      }

      if ((toY - fromY) > 0) {
        yIter = 1;
      } else {
        yIter = -1;
      }

      for (int i = 1; i < abs(fromX - toX); i++) {
        Color c;
        Piece p;
        bool occ;
        chessboard[fromX + xIter][fromY + yIter].get(occ, c, p);
        xIter += xIter;
        yIter += yIter;
        if (occ == true) {
          return true;
        }
      }

    } else if (piece == Rook) {
      if (fromX == toX) {
        // cout << "";
        int iter = 0;
        if (fromY < toY) {
          iter = 1;
        } else {
          iter = -1;
        }

        for (int i = 1; i < abs(fromY - toY); i++) {
          Color c;
          Piece p;
          bool occ = false;
          chessboard[fromX][fromY + iter].get(occ, c, p);
          iter += iter;
          if (occ == true) {
            return true;
          }
        }
      } else if (fromY == toY) {
        int iter = 0;
        if (fromX < toX) {
          iter = 1;
        } else {
          iter = -1;
        }
        for (int i = 1; i < abs(fromX - toX); i++) {
          Color c;
          Piece p;
          bool occ = false;
          chessboard[fromX + iter][fromY].get(occ, c, p);
          iter += iter;
          if (occ == true) {
            return true;
          }
        }
      }
    }
    return false;
  }

  // place a piece on a x,y square in the chessboard
  int place(int x, int y, Color c, Piece p) {
    Color colorCheck;
    Piece pieceCheck;
    bool placeCheck;

    if (x > 7 || x < 0) {
      return -1;
    } else if (y > 7 || y < 0) {
      return -2;
    }
    chessboard[x][y].get(placeCheck, colorCheck, pieceCheck);
    if (placeCheck == true) {
      return -3;
    } else if (colorIllegal(c) == false) {
      return -4;
    } else if (pieceIllegal(p) == false) {
      return -5;
    }

    Square newPiece(c, p);
    chessboard[x][y] = newPiece;

    return 1;
  }

  int get(int x, int y, Color &c, Piece &p) {
    // fill out
    Color colorHold;
    Piece pieceHold;
    bool placeCheck;

    if (x > 7 || x < 0) {
      return -1;
    } else if (y > 7 || y < 0) {
      return -2;
    }
    chessboard[x][y].get(placeCheck, colorHold, pieceHold);
    if (placeCheck == false) {
      return -3;
    }

    c = colorHold;
    p = pieceHold;
    return 1;
  }

  int move(int fromX, int fromY, int toX, int toY) {
    // fill out
    Color color, color2;
    Piece piece, piece2;
    bool place, place2;

    if (fromX > 7 || fromX < 0) {
      return -1;
    } else if (fromY > 7 || fromY < 0) {
      return -2;
    } else if (toX > 7 || toX < 0) {
      return -3;
    } else if (toY > 7 || toY < 0) {
      return -4;
    }
    chessboard[fromX][fromY].get(place, color, piece);
    chessboard[toX][toY].get(place2, color2, piece2);
    if (place == false) {
      return -5;
    } else if (color == color2) {
      return -6;
    }

    // tests to see if piece(queen) can be categorized as something else for
    // fastness sake
    // piece2 becomes the original piece if this is the case.
    if (piece == Queen) {
      if ((fromX == toX && abs(fromY - toY) >= 1) ||
          (fromY == toY && abs(fromX - toX) >= 1)) {
        if (pieceBlocked(Rook, fromX, fromY, toX, toY) == true) {
          return -7;
        } else {
          takePiece(fromX, fromY, toX, toY, piece, color);
        }
      } else if (abs(toX - fromX) == abs(toY - fromY)) {
        if (pieceBlocked(Bishop, fromX, fromY, toX, toY) == true) {
          return -7;
        } else {
          takePiece(fromX, fromY, toX, toY, piece, color);
        }
      } else {
        return -7;
      }
    }

    if (piece == Pawn) { // pawn

      if (color == White && (fromY - toY) >= 1) {
        return -7;
      } else if (color == Black && (fromY - toY) <= -1) {
        return -7;
      } else if (place2 == true && abs(fromY - toY) == 1 &&
                 abs(fromX - toX) == 0) {
        return -7;
      } else if (abs(fromY - toY) == 1 && abs(fromX - toX) <= 1) {
        takePiece(fromX, fromY, toX, toY, piece, color);
      } else {
        return -7;
      }

    } else if (piece == King) { // king

      if (abs(fromY - toY) <= 1 && abs(fromX - toX) <= 1) {
        takePiece(fromX, fromY, toX, toY, piece, color);
      } else {
        return -7;
      }

    } else if (piece == Knight) { // knight

      if (abs(fromY - toY) == 1 && abs(fromX - toX) == 2) {
        takePiece(fromX, fromY, toX, toY, piece, color);
      } else if (abs(fromY - toY) == 2 && abs(fromX - toX) == 1) {
        takePiece(fromX, fromY, toX, toY, piece, color);
      } else {
        return -7;
      }

    } else if (piece == Bishop) { // Bishop -> increasing by 1x1 square basis

      if (abs(toX - fromX) == abs(toY - fromY)) {
        if (pieceBlocked(piece, fromX, fromY, toX, toY) == true) {
          return -7;
        } else {
          takePiece(fromX, fromY, toX, toY, piece, color);
        }
      } else {
        return -7;
      }

    } else if (piece == Rook) { // Rook

      if ((fromX == toX && abs(fromY - toY) >= 1) ||
          (fromY == toY && abs(fromX - toX) >= 1)) {
        if (pieceBlocked(piece, fromX, fromY, toX, toY) == true) {
          return -7;
        } else {
          takePiece(fromX, fromY, toX, toY, piece, color);
        }
      } else {
        return -7;
      }
    }

    return 1;
  }

  void print();
};

class ChessboardIterator {
private:
  int position; // a number in [0..64]
  Chessboard chessboard;

public:
  ChessboardIterator(Chessboard &board, int pos) {
    chessboard = board;
    position = pos;
  }

  void xy(int &x, int &y) { // break position down into x and y
    y = position / 8;
    x = position % 8;
  }

  // return the square
  Square operator*() {
    // fill out
    int x = 0, y = 0;
    xy(x, y);
    return chessboard.chessboard[x][7 - y];
  }

  // pre-increment
  ChessboardIterator &operator++() {
    // fill out
    position++;
    return *this;
  }

  // needed to support foreach
  int operator!=(ChessboardIterator &a) {
    // fill out
    return position != a.position;
  }
};
