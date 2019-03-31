# Engine Classes
Description and Pseudo-Code to illustrate class relation, distribution of responsibilities, and hierarchy

## class GameEngine
GameEngine would hold a list of all scenes for the game, as well as keep track of the active scene.
GameEngine is also where the main game loop will exist. 
### void startGame()
A function that is called to initialize all required data structures and start the game

### int addScene()
Adds a scene to the GameEngine

## class Input
Keeps track of the state of input devices such as the keyboard. Input will have at most 1 active instance at any given time which is created by the active instance of the GameEngine class. Input will be responsible for abstracting physical keys being pressed into the actions of a particular player.
Example. InputInstance.p1.getUp() returns whether player 1 is pressing the button that has been defined as their "up" key.

## class Scene
One "level" of a game; contains sprites and objects, as well as a View object that controls how objects in the scene are drawn to the screen

## class View
Controls drawing everything to the screen

## class Object
An interactable object; stores the size and position of the object, as well as a sprite for the object.

## class Sprite
Has offset position (offset of the origin if used independantly, offset of the object if linked to an image), Sprite dimentions, an array of images (probably some sort of SFML asset?), and animation frames

## Talk about separating Sprite into an Animation class and a Sprite class (so that we could hold an array of Sprites in an image)?
