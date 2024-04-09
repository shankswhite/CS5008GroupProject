# CS5008GroupProject
A game about path-finding algorithms

Downloads:

[![Download Mac](https://img.shields.io/badge/Download-Mac-brightgreen?logo=github)](https://drive.google.com/file/d/1CAgzVN_g604vQ3UzxbGj8jsxvvyH5_gH/view?usp=sharing)
[![Download Win](https://img.shields.io/badge/Download-Win-brightgreen?logo=github)](https://drive.google.com/drive/folders/1D8zUZ1wIoVny_iM_nRBHavIzM3Y9s48j?usp=sharing)

Download FAQ: the first time you run it on mac, you need to right-click on the file and select open to open it. Or you can compile it yourself by "make" in ./Codes


Developers:
Junhui Su, Xiaofeng Zhao, Zhechao Jin


Keywords: 
OpenGL, Path-finding Algorithms.


Description:
The core of the game is to explore the performance of path finding algorithms (such as depth-first search DFS, breadth-first search BFS, Greedy, A*, etc.) in environments with obstacles through a 20x20 two-dimensional array grid map. The interactivity of the game is mainly reflected in the fact that players can place obstacles to affect the path selection of the algorithm agent (controlled by the computer), thereby testing the efficiency and strategies of different path finding algorithms in solving practical problems.

Gameplay overview:
  * Game startup: Display a 20x20 grid map with a computer-controlled agent on the map, moving from a starting point.
  * Agent Selection: Players can select different agents by clicking a button, each using a different path-finding algorithm.
  * Game Controls: Players have several clickable buttons to control the flow of the game, including "Select Agent," "Next Round," and "Restart."
  * Obstacle Placement: Players can place up to 10 obstacles on the grid to block the agent's path.
  * Scoring mechanism: Each grid the agent passes increases the player's score.
  * Game Process: When the player presses the [Next Round] button, the agent will move to the next grid according to its algorithm. After each round, players can continue to place obstacles to affect the agent's movement.
  * Game Over: When the agent reaches the end point, the game ends, the score is displayed, and the option to start over is given.


Technical implementation ideas:
  * C language and OpenGL: Use C language combined with the OpenGL library to implement the game's graphical interface. OpenGL can be used to draw the game's 2D grid map, as well as graphical representations of agents and obstacles.
  * Agent algorithm implementation: Implement different path finding algorithms, such as DFS, BFS, etc., for players to choose from. The agent for each algorithm needs to be able to decide the next optimal move based on the current state of the map, including the location of obstacles.
  * Game logic: Develop the core logic of the game, including the movement mechanism of the agent, placement of obstacles, calculation of scores and game rounds, etc.
  * User Interface: Design and implement the user interface, including displaying grid maps, scores, available control buttons, etc.
  * Overall, the game design challenge was to effectively integrate the concepts of path-finding algorithms into gameplay and demonstrate how these algorithms perform in real-world applications through player-agent interaction. At the same time, using C language and OpenGL to implement such a game can not only exercise programming skills, but also provide an in-depth understanding of computer graphics and algorithm knowledge.

Environment installation instruction:
GLUT for UI: brew install freeglut
OpenGL for graph: build-in on mac
Compiler: Xcode: xcode-select --install


Goal:
We use this project to horn our programming skills for game development. It is very challenging for us. We just wanna complete this, which is already too much.



