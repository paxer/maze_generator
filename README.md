# Maze Generator

Developed with Unreal Engine 4.25 and C++

The project allows to generate a maze in the editor with a differnt sizes and then save it as a separate Blueprint in order to use it as a single prefab which GameMode can load on the fly.

The generated maze contains PlayerStart and Portal blueprints, once the player (FPS Controller) reached the Portal - the next level will be loaded. This game logic is implemented for the TestLoadLevels map.

MazeGenerator map should be used only to generate different mazes in the UE Editor: Select BP_MazeGenerator in the WorldOutliner, change Maze Properties, then open Maze folder in WorldOutliner -> Select Immediate Children and then in Blueprint Menu -> Convert selection to a blueprint class which should be then saved to the Levels folder.

GameMode has an array of blueprint levels which will be loaded when playing on TestLoadLevels map.

The Maze Generation algorithm based on slightly modified version of https://forums.unrealengine.com/community/community-content-tools-and-tutorials/105-saxonrahs-tutorial-thread-random-maze-generation-solving  and https://github.com/robertsmieja/UE4-Maze

![GitHub Logo](https://github.com/paxer/maze/blob/master/maz_generator.png)
