// see for background
//  https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html
/*
  Author: Matthew Danque
  CS 341: Project 1 9/18
*/
#include "chessboard.h"
#include <iostream>

int main() {
  
  cout << "Chess Time.....\n\n";
  Chessboard chessboard;

  chessboard.place(0, 0, White, Rook);
  chessboard.place(1, 0, White, Knight);
  chessboard.place(2, 0, White, Bishop);
  chessboard.place(3, 0, White, Queen);
  chessboard.place(4, 0, White, King);
  chessboard.place(5, 0, White, Bishop);
  chessboard.place(6, 0, White, Knight);
  chessboard.place(7, 0, White, Rook);
  for (int i = 0; i < 8; i++) {
    chessboard.place(i, 1, White, Pawn);
  }
  chessboard.place(0, 7, Black, Rook);
  chessboard.place(1, 7, Black, Knight);
  chessboard.place(2, 7, Black, Bishop);
  chessboard.place(3, 7, Black, Queen);
  chessboard.place(4, 7, Black, King);
  chessboard.place(5, 7, Black, Bishop);
  chessboard.place(6, 7, Black, Knight);
  chessboard.place(7, 7, Black, Rook);
  for (int i = 0; i < 8; i++) {
    chessboard.place(i, 6, Black, Pawn);
  }
  chessboard.print();
  cout << "\n\n***********Testing get************" << endl;
  Color co;
  Piece p1;
  cout << "Testing get illegal x cood: " << chessboard.get(8, 0, co, p1) << endl;
  cout << "Testing get illegal y cood: " << chessboard.get(0, 8, co, p1) << endl;
  cout << "Testing get occupied square: " << chessboard.get(3, 0, co, p1)
       << endl;
  cout << "Testing get unoccupied square: " << chessboard.get(0, 2, co, p1)
       << endl;
  cout << "\n\n***********Testing place************" << endl;
  Color coPlace = (Color)3;
  Piece piPlace = (Piece)6;
  cout << "Testing place illegal x cood: "
       << chessboard.place(87, 8, coPlace, piPlace) << endl;
  cout << "Testing place illegal y cood: "
       << chessboard.place(0, 8, coPlace, piPlace) << endl;
  cout << "Testing place square occupied: "
       << chessboard.place(0, 0, coPlace, piPlace) << endl;
  cout << "Testing place illegal color: "
       << chessboard.place(0, 2, coPlace, piPlace) << endl;
  coPlace = (Color)0;
  cout << "Testing place illegal piece: "
       << chessboard.place(0, 2, coPlace, piPlace) << endl;
  piPlace = (Piece)3;
  cout << "Testing place everything ok: "
       << chessboard.place(0, 2, coPlace, piPlace) << endl;
  chessboard.print();

  cout << "Special Testing\n";
  
  cout << "\n\n***********Testing move************" << endl;
  cout << "Testing illegal fromX: " << chessboard.move(-1, 0, 2, 2) << endl;
  cout << "Testing illegal fromY: " << chessboard.move(0, -1, 2, 2) << endl;
  cout << "Testing illegal toX: " << chessboard.move(0, 0, -1, 2) << endl;
  cout << "Testing illegal toY: " << chessboard.move(0, 0, 2, -1) << endl;
  cout << "Testing unoccupied starting position: " << chessboard.move(3, 3, 0, 0) << endl;
  cout << "Testing destination and start same color: " << chessboard.move(0, 0, 0, 1) << endl;

  cout << "\n\n***********Testing move(king)************" << endl;
  Chessboard kingBoard;
  kingBoard.place(3, 4, Black, King);
  kingBoard.place(3, 5, White, Pawn);
  kingBoard.place(1, 4, White, Pawn);
  kingBoard.place(6, 4, White, Pawn);
  kingBoard.place(3, 7, White, Pawn);
  kingBoard.place(3, 1, White, Pawn);
  cout << "King Board:\n";
  kingBoard.print();
  cout << "illegal king move right: " << kingBoard.move(3, 4, 1, 4) << endl;
  cout << "illegal king move left: " << kingBoard.move(3, 4, 6, 4) << endl;
  cout << "illegal king move up: " << kingBoard.move(3, 4, 3, 7) << endl;
  cout << "illegal king move down: " << kingBoard.move(3, 4, 3, 1) << endl;
  cout << "illegal king move diagonal: " << kingBoard.move(3, 4, 1, 2) << endl;
  cout << "illegal king move random: " << kingBoard.move(3, 4, 7, 7) << endl;
  cout << "successful king piece take: " << kingBoard.move(3, 4, 3, 5) << endl;
  cout << "successful king move made: " << kingBoard.move(3, 5, 2, 6) << endl;
  cout << "New King Board:\n";
  kingBoard.print();
  
  cout << "\n\n***********Testing move(pawn)************" << endl;
  Chessboard pawnBoard;
  pawnBoard.place(3, 4, Black, Pawn);
  pawnBoard.place(2, 3, White, Pawn);
  pawnBoard.place(3, 5, White, Pawn); 
  
  cout << "Pawn Board:\n";
  pawnBoard.print();
  cout << "illegal pawn move right: " << pawnBoard.move(3, 4, 1, 4) << endl;
  cout << "illegal pawn move left: " << pawnBoard.move(3, 4, 6, 4) << endl;
  cout << "illegal pawn move diagonal: " << pawnBoard.move(3, 4, 2, 4) << endl;
  cout << "illegal black pawn move: " << pawnBoard.move(3, 4, 3, 5) << endl;
  cout << "illegal white pawn move:" << pawnBoard.move(2, 3, 2, 2) << endl;
  cout << "illegal king move random: " << pawnBoard.move(3, 4, 7, 7) << endl;
  cout << "successful pawn piece take: " << pawnBoard.move(3, 4, 2, 3) << endl;
  cout << "successful pawn move: " << pawnBoard.move(2, 3, 2, 2) << endl;
  cout << "New Pawn Board:\n";
  pawnBoard.print();
  
  cout << "\n\n***********Testing move(bishop)************" << endl;
  Chessboard bishopBoard;
  bishopBoard.place(3, 4, Black, Bishop);
  bishopBoard.place(2, 3, White, Pawn);
  bishopBoard.place(4, 5, Black, Pawn); 
  
  cout << "Bishop Board:\n";
  bishopBoard.print();
  cout << "illegal bishop move right: " << bishopBoard.move(3, 4, 1, 4) << endl;
  cout << "illegal bishop move left: " << bishopBoard.move(3, 4, 6, 4) << endl;
  cout << "illegal bishop move up: " << bishopBoard.move(3, 4, 3, 5) << endl;
  cout << "illegal bishop move down:" << bishopBoard.move(3, 4, 3, 3) << endl;
  cout << "illegal bishop move random: " << bishopBoard.move(3, 4, 7, 7) << endl;
  cout << "illegal bishop move blocked by friend: " << bishopBoard.move(3, 4, 6, 7) << endl;
  cout << "successful bishop piece take: " << bishopBoard.move(3, 4, 2, 3) << endl;
  cout << "successful bishop move: " << bishopBoard.move(2, 3, 1, 2) << endl;
  cout << "Bishop Board:\n";
  bishopBoard.print();
  
  cout << "\n\n***********Testing move(knight)************" << endl;
  Chessboard knightBoard;
  knightBoard.place(3, 4, Black, Knight);
  knightBoard.place(2, 6, White, Pawn);
  
  
  cout << "knight Board:\n";
  knightBoard.print();
  cout << "illegal knight move right: " << knightBoard.move(3, 4, 1, 4) << endl;
  cout << "illegal knight move left: " << knightBoard.move(3, 4, 6, 4) << endl;
  cout << "illegal knight move up: " << knightBoard.move(3, 4, 3, 5) << endl;
  cout << "illegal knight move down:" << knightBoard.move(3, 4, 3, 3) << endl;
  cout << "illegal knight move random: " << knightBoard.move(3, 4, 7, 7) << endl;
  cout << "successful knight piece take: " << knightBoard.move(3, 4, 2, 6) << endl;
  cout << "successful knight move: " << knightBoard.move(2, 6, 1, 4) << endl;
  cout << "knight Board:\n";
  knightBoard.print();
  
  cout << "\n\n***********Testing move(rook)************" << endl;
  Chessboard rookBoard;
  rookBoard.place(3, 4, Black, Rook);
  rookBoard.place(1, 4, White, Pawn);
  rookBoard.place(3, 5, White, Pawn);
  
  
  cout << "Rook Board:\n";
  rookBoard.print();
  cout << "illegal Rook move diagonal: " << rookBoard.move(3, 4, 2, 3) << endl;
  cout << "illegal Rook move random: " << rookBoard.move(3, 4, 7, 7) << endl;
  cout << "illegal Rook move blocked by friend: " << rookBoard.move(3, 4, 3, 7) << endl;
  cout << "successful Rook piece take: " << rookBoard.move(3, 4, 1, 4) << endl;
  cout << "successful Rook move: " << rookBoard.move(1, 4, 1, 2) << endl;
  cout << "successful Rook move: " << rookBoard.move(1, 2, 1, 0) << endl;
  cout << "successful Rook move: " << rookBoard.move(1, 0, 1, 7) << endl;
  cout << "Rook Board:\n";
  rookBoard.print();
  
  cout << "\n\n***********Testing move(queen)************" << endl;
  Chessboard queenBoard;
  queenBoard.place(3, 4, Black, Queen);
  queenBoard.place(1, 4, White, Pawn);
  queenBoard.place(3, 5, White, Pawn);
  
  
  cout << "queen Board:\n";
  queenBoard.print();
  cout << "illegal queen move random: " << queenBoard.move(3, 4, 7, 7) << endl;
  cout << "illegal queen move blocked by friend: " << queenBoard.move(3, 4, 3, 7) << endl;
  cout << "successful queen piece take: " << queenBoard.move(3, 4, 1, 4) << endl;
  cout << "successful queen move right: " << queenBoard.move(1, 4, 3, 4) << endl;
  cout << "successful queen move left: " << queenBoard.move(3, 4, 0, 4) << endl;
  cout << "successful queen move diagonal: " << queenBoard.move(0, 4, 1, 5) << endl;
  cout << "successful queen move down: " << queenBoard.move(1, 5, 1, 0) << endl;
  cout << "successful queen move up: " << queenBoard.move(1, 0, 1, 7) << endl;
  cout << "queen Board:\n";
  queenBoard.print();
  
}