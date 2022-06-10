# Maze_Escape

## Maze Escape is a game that is played by two players-one computer(AI) and another human.

Given a maze from a certain starting point to an end point, there are several blocked paths. The allowed moves are left, right, up or down of the maze from the current position excluding the blocked paths. Each player makes a move that is within the allowed range and leaves the next move to his/its opponent. The player that reaches the end point/ destination is the winner. If at a certain point there is no more valid move, then the game is a draw.
Firstly the user decides the size of the maze based on rows and columns. The default starting point is (0, 1) but the user can change it according to his will. Then a few blocks(about one-third of the total space) are randomly stationed in the maze. The destistination is the bottom last space of the maze. The first move is given to the user and the next move is given to the AI then again
to the user and so on. 
The algorithms used for implementing the AI are Minimax algorithm and Alpha Beta Pruning. The designed AI tries to maximize the chances of winning otherwise turns for a draw in an unfavorable scenario. The game will continue until there is no more valid move, in other words a draw or one player clearly wins the game, namely reaching the destination.
<img width="1395" alt="Step1" src="https://user-images.githubusercontent.com/91896635/172990375-6176bb53-d2ce-47e4-91cc-b07316885068.png">
<img width="1323" alt="Step2" src="https://user-images.githubusercontent.com/91896635/172990383-8c2d0270-e6d8-42a9-87a7-510ddcb61e7b.png">
<img width="1394" alt="Step3" src="https://user-images.githubusercontent.com/91896635/172990388-ae5b4f80-6a24-4fd0-af99-d481b55ddc75.png">
<img width="1341" alt="Step4" src="https://user-images.githubusercontent.com/91896635/172990397-7527d8f4-d0e3-4844-a566-4d35db49207a.png">
<img width="1348" alt="Step5" src="https://user-images.githubusercontent.com/91896635/172990404-e8bf3b94-d9f9-4eae-ade9-01bc891394b1.png">
<img width="1347" alt="Step6" src="https://user-images.githubusercontent.com/91896635/172990418-a4fcdb4f-538f-4be0-8746-c560f452fb8a.png">
