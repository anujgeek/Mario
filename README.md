# Game: Mario
Created by: Anuj Agrawal (Email: anuja@clemson.edu)
<br>
Class website: http://people.cs.clemson.edu/~malloy/courses/416-2015/index.html

Final project for:
<br>
Clemson University - CpSc 6160 - Data-driven 2D Game Development
<br>
Created using C++ and SDL

## Demo:

<a href="http://www.youtube.com/watch?feature=player_embedded&v=lzHiHssj1jk" target="_blank"><img src="http://img.youtube.com/vi/lzHiHssj1jk/0.jpg" alt="MARIO" border="10"/></a>

## Project description:

Its a Mario game. The player class (Mario) is derived from TwoWayMultiSprite.
Mario is always jumping. Mario can either stand still in x-direction (key s)
or move continuously in either directions (keys a or d).

AI - Enemies always follow Mario.
Enemies explode when they come in contact with Mario.

Birds (ducks) are also implemented as TwoWayMultiSprite. Bigger birds are in front
of the clouds while the smaller one are behind the clouds and travel with smaller velocity.
Tracker now only tracks Mario and only in X direction.
HUD can be toggled using F1 key.
Restart - F2. I just respotion Mario and set its XVelocity to 0;
GodMode can be toggled using F1 key. (I disable the collision detection with enemies)

Game Objective:
Mario wins after colliding with the tropy at the end of the game.


## Resources:

Sprites:

Mario sprite from: http://www.spriters-resource.com/
<br>
Duck sprite from: http://all-free-download.com
<br>
All others are built from scratch using photoshop.


Sounds:
<br>
http://themushroomkingdom.net/media/smb/wav
