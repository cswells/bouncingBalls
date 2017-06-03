# bouncingBalls
C++ program with a 3d room and rudimentry physics

## Introduction
This program using an object oriented approach to program a simple room with balls that both have to follow physics engines rules. This program was designed so that you can replace any part of it with your own engine, ball, room code and it should still work. I played with a couple of physics engines myself but chose this one for my project. This was a School project I have not had time to update and fix bugs.
##Known Orginal Bugs
There is a commented peice of code in the run loop that should not have been present, but present in the ball creation method. when this command is uncommmented, it will randomly choose preset colors for the balls and change this for every frame, not the desired effect. (Working on a fix when I have time to clean up my code.)
There is a bug where the glossy light effects are still present and change the rooms default light color evertime a ball is spawned. Not sure what is causing it but will try to fix soon.
There is a bug where Ball become trapped in the walls... this is my fault I used a quick trick to fix a bug and created that one. This is also the same reason the ball get stuck when they spawn in to fast. My bad will fix soon.
## Controls
to move around the room use the "WASD" where W and A moves the camera forward and backward, A and D make the camrea rotate left and right respectively. Q and Z rotate the camera up and down. R spawn a Ball into the room. For every press of R a ball is spawned. There is no cap on Balls.
W - Move Camera forward on the Z axis
S - Move the Camera Backwards on the Z axis
A - Rotate the camera to the Left on the Y axis
D - Roate the Camera to the right on the Y axis
Q - Roate the Camera down on the X axis (the effect of pushing the camera down)
Z - Rotate the Camera up on the X axis (the effect of pulling the camera up)
R - Spawns a Ball in the room.
