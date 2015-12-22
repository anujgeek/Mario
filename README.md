# Game: Mario
Final project for CpSc6160 Data-driven 2D Game Development
Created using C++ and SDL

Created by: Anuj Agrawal (Clemson Email Address: anuja@clemson.edu)
Class website: http://people.cs.clemson.edu/~malloy/courses/416-2015/

Project description:

Its a Mario game. The player class (Mario) is derived from TwoWayMultiSprite.
Mario is always jumping. Mario can either stand still in x-direction (key s)
or move continuously in either directions (keys a or d).

AI- Enemies always follow Mario.
Enemies explode when they come in contact with Mario.

Birds (ducks) are also implemented as TwoWayMultiSprite. Bigger birds are in front
of the clouds while the smaller one are behind the clouds and travel with smaller velocity.
Tracker now only tracks Mario and only in X direction.
HUD can be toggled using F1 key.
Restart - F2. I just respotion Mario and set its XVelocity to 0;
GodMode can be toggled using F1 key. (I disable the collision detection with enemies)

Game Objective:
Mario wins after colliding with the tropy at the end of the game.


Resources:
Mario sprite from: http://www.spriters-resource.com/
Duck sprite from: http://all-free-download.com
All others are built from scratch using photoshop.
Sounds from:
http://themushroomkingdom.net/media/smb/wav
