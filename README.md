# tictactoe
made by Lily Lee, 2017

This is a simple command-line C++ application that plays Tic Tac Toe.

Features:
* You can play against the AI! (however, the AI algorithm is extremely naive, and needs improvement.)
* You can choose to play as either X or O (where X always goes first)
* Command-line level display of the tic-tac-toe board every time it is your turn as the player

How to play:
First choose one of X (1) or O (2) when prompted. When it is your turn, type the coordinate (starting at index 0) as if you
are referencing an element in a matrix (for example, the input 1 0 is the 2nd row, 1st column, and the input '0 2' is the
1st row, 3rd column).
The rule of the game itself is pretty obvious: complete a line, vertically, horizontally, or diagonally.

Improvements:
* Error checking when user inputs data (for example, the coordinate of the next marker)
* Better AI algorithm (should be fairly simple to implement, because there is a very finite way of playing. For example, 
the number of "unique first moves" is actually only 3, not 9: the middle, the edge, or the corner.)
