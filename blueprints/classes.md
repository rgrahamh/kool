# Engine Classes
Description and Pseudo-Code to illustrate class relation, distribution of responsibilities, and hierarchy

## class GameEngine
GameEngine would hold a list of all scenes for the game, as well as keep track of the active scene.
GaneEngine is also where the main game loop will exist. 
### void startGame()

### int addScene()

## class Input
Keeps track of the state of input devices such as the keyboard. Input will have at most 1 active instance at any given time which is created by the active instance of the GameEngine class. Input will be responsible for abstracting physical keys being pressed into the actions of a particular player.
Example. InputInstance.p1.getUp() returns whether player 1 is pressing the button that has been defined as their "up" key.

## class Scene

## class View

## class Object

## class Sprite
