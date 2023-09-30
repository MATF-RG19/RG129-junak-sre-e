# Junak srece (Bold and brash)

# Controls: 
Player can move using AWDS, and for shooting K.

Shortcuts:    
n/N - skips intro scene(beginning animation)   
p/P - skips first region    
o/O - starts ending animation   

# Gameplay:         
Intro animation: witch stealing the painting from the museum, running away through portal on wall followed by secret security guard.  
First level: goal is to destroy all cubes which will cause border to disappear and second level will start.  
Second level: goal is to collect key that will unlock second border and to get out of maze.      
Ending animation(end of game): game ends when player crosses place where second border was. That will start ending animation where witch is throwing painting "Junak srece"("Bold and brash") in the trash. 

# Functionality:    
Health of player is represented as three hearts in upper right corner. 
Actions that cause loosing one health: collision of player and enemy cubes, collision of player and shooting of any enemy, collision of player and spikes. 
When loosing health player gets spawned on starting place of first or second level. If player losses last helth point then game gets restarted.

Cube enemy changes collor from green to red to signal to player it is about to shoot. 

In second level one key opens the border and that is the only key needed to proceede to the end of game. Other key is a trap and it activates spikes. 
# Starting of game:    
Linux - gcc Main.c -lGL -lGLU -lglut -lm    
Windows - Open JunakSrece.vcxproj in VisualStudio and start it from there.

