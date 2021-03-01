# BlackJack

Console-based card game that is run in terminal, coded in C++ and using the ranges v3 library.

How to play

When prompted by the game, the user is able to issue commands by typing into the console. Valid commands are:
 - add [playername] : Adds a player to the game (the game can have a maximum of 7 players)
 - remove [playername]: Removes a player from the game
 - play : Starts a round of blackjack 
 - end: Exit out of the program

When a round of blackjack is in progress, players will be prompted for input. Valid commands are:
- hit : Receive another card from the dealer
- hold: Keep your current hand and end your turn.
- split: Split your hand into two hands to play separately (only valid if you have two cards of similar value in your hand)

