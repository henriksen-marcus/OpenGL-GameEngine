Exam 2023 Candidate 1202

The green sphere is the trophy/pickup. It will increase the score which gets printed to the Qt console and the standard console.
The red tetrahedron is the enemy, hit it and it will restart the game.
The pink cube is the light switch which will toggle the light on collision.

I am using smooth phong shading, fragment version.
The monkey in the scene is loaded from an obj created in blender.

CODE GUIDE:
The code starts in renderwindow.cpp. I initialize the world from the Init function. The Tick function runs the game.
I have created my own hieracrhy inspired by unreal engine's structure which runs the entire game from the line 
WorldManager::GetInstance().GetWorld()->Tick(deltaTime); From there you can see where all the code comes from.
All the specific code for the scene lies in Source/Game/Scenes/Eksamen2023Scene.h (and .cpp).

Keybinds:
Switch camera - Left shift
glPolygonMode - TAB
glCullFace - Left alt
Move - WASD
Turn - Q/E

Project is made in visual studio using Qt VS Tools plugin. Have verified that it works in standard Qt Creator using MingGW compiler as well. 
Qt Creator version 10.0.1.