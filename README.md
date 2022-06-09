# Maze_Escape

## Maze Escape is a game that is played by two players-one computer(AI) and another human.

Given a maze from a certain starting point to an end point, there are several blocked paths. The allowed moves are left, right, up or down of the maze from the current position excluding the blocked paths. Each player makes a move that is within the allowed range and leaves the next move to his/its opponent. The player that reaches the end point/ destination is the winner. If at a certain point there is no more valid move, then the game is a draw.
Firstly the user decides the size of the maze based on rows and columns. The default starting point is (0, 1) but the user can change it according to his will. Then a few blocks(about one-third of the total space) are randomly stationed in the maze. The destistination is the bottom last space of the maze. The first move is given to the user and the next move is given to the AI then again
to the user and so on. 
The algorithms used for implementing the AI are Minimax algorithm and Alpha Beta Pruning. The designed AI tries to maximize the chances of winning otherwise turns for a draw in an unfavorable scenario. The game will continue until there is no more valid move, in other words a draw or one player clearly wins the game, namely reaching the destination.
