// chessboard.cpp
/*
  Author: Matthew Danque
  CS 341: Project 1 9/18
*/
#include "chessboard.h"

// define containers for color mappings (2 colors) and piece mappings (6 pieces)
enum Color; //Black, White;
enum Piece; //Pawn, Knight, King, Queen, Bishop, Rook;

ChessboardIterator Chessboard::begin() {
  return ChessboardIterator(*this, 0);
}

ChessboardIterator Chessboard::end() {
  return ChessboardIterator(*this, 64);
}

// print the chessboard with white at the bottom (traditional view)
void Chessboard::print() {
  int count = 0;
  for (Square a : *this) {
    Color c;
    Piece p;
    bool occ = false;
    a.get(occ, c, p);
    if (occ == false) {
      cout << " . ";
    } else if (c == White) {
      cout << "w";
    } else if (c == Black) {
      cout << "b";
    }
    
    if (p == Queen) {
      cout << "Q ";
    } else if (p == King) {
      cout << "K ";
    } else if (p == Pawn) {
      cout << "P ";
    } else if (p == Knight) {
      cout << "N ";
    } else if (p == Rook) {
      cout << "R ";
    } else if (p == Bishop) {
      cout << "B ";
    } 
    
    if (count == 7) {
      cout << "\n";
      count = 0;
    } else {
      count++;
    }
  }
}
  
