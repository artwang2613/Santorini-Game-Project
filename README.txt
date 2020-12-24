	My submission houses the gameboard on an multidimentional int array.
The player is marked as the num 15 on the board and the AI as 16, since the 
tile val can't go above 4 this is a easy way to tell things apart. The player
and AI are represented as int arrays containing current row and column coordinates
as well as thre value of the square they are currently sitting on. That way when 
they jump, the board can replace the 15 or 16 with the past value. The AI isn't 
particularly smart but it is probably equivalent to a young child. It's goal is to 
choose a legal move that allows it to be the closest to the player's position.
In some cases this works kinda well, but in others it fails miserably, allowing the
player to win in just a couple turns. The most important functions are playerMove
(prompting player action), aiMove (chooses shortest path to player), build (both 
increments or decrements building level depending on whether the AI or the player
is using it) and getLegalMoves (gets the moves that the AI/player can take w/o 
violating game rules).

URL:https://youtu.be/srOCzhBIbtg