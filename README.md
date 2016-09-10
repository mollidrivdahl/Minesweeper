# Minesweeper
This repository contains the code for my own version of Minesweeper. It was created as an assignment for my Data Structures course at Oregon Tech (Winter 2016 - Sophomore Year). NOTE: This is a console app so it is played through the command line. There is no GUI associated with this game.

<b>Game Description:</b><br />
The purpose of the game is to simulate the classic Minesweeper game. There are three levels: Beginner, Intermediate, and Expert. A board is populated with a certain number of mines over a certain number of cells based on the level. The rest of the cells are populated with numbers representing how many mines are adjacent to a particular cell. All cells start covered, and the user can either uncover a cell, flag a cell to mark as a potential mine, or remove a flag. If the user uncovers a cell with a mine, the user loses. If the user uncovers all cells that are not mines, the user wins. If the user has every mine flagged, and no other cells are flagged, the user wins.<br />

<b>Technologies:</b><br />
This program was written in C++ using Microsoft Visual Studio 2015.<br />

<b>Execution Instructions:</b><br />
To run this program, one must open this project in Visual Studio and "Start Without Debugging."<br />

<b>Screenshots:</b><br />

<img src= "/img/welcomeScreen.PNG" width="600" height="200">
<br />
Welcome screen

<img src= "/img/menuMidGame.PNG" width="600" height="200">
<br />
Main menu during gameplay and intermediate level board

<img src= "/img/chooseRowColumn.PNG" width="600" height="200">
<br />
Prompts when choosing to uncover a cell

<img src= "/img/gameOver.PNG" width="600" height="200">
<br />
Game over screen when bomb is uncovered
