# RC Submarine

## Overview

### Context

This is for me a personal project, that started from a crazy idea of creating a submarine 100% by myself. As a experimented software developer, i want to diversify my knowledge to other disciplines.
In this case, i can improve my electronics ability, and also general engineering : two domains where I did not have any basis to start this project.

### Conception phase

I first started to document myself about submarines main challenges.
They are :
- Waterproofness, handling pressure
- Ability to change electronically volume/mass ratio to dive/float
- Miniaturization, efficiently using available space.

So i started unrealistic drawings (see first-drawing.jpg in the repo) trying to solve theses issues.
At the time i started the project, chatGPT rised from nowhere, so i used it a lot to discuss about it and fill my absolute ignorance about electronics.
I created lot of 3D pieces with Fusion360.

### POC & Testing

As my electronics skills were void, i started learning Arduino.
I ordered chineese Elegoo Mega card, and some sensors, controllers, motors, lights on Aliexpress.

I played around with theses components to lear using my advanced C++ skills to control electronics.

After coding a lot, i got all the main parts (engine, ballast, lights, camera) working (spearately, one at once) controllable from my computer.

### Assembling 

IN PROGRESS


## Technical details

### Waterproof case

A submarine needs a strong waterproof case. I made the choice to target 10m of depth.
The case needs to be openable easily to charge the battery, and do some maintenance operations.

For this use, i took a 125mm wide PVC tube. The PVC tube is intended to hold 16 bar of pressure, but this pressure is supposed to come from the inside of the tube, and not from the outside as it will be in the sea. At 10m, the water pressure will be 1 bar, so I suppose the PVC will hold it.

The tube is closed by two standard PVC screwed tip :
- I've cut a hole in one of the tips to fit a plexiglass dome (glued with PVC glue) in order to let the camera see. In this way, the dome is easily removable, and the camera & battery compartiment accesible.
- The rear tip is drilled with holes to let the cables and the water intake pass. All is waterproofed using epoxy resin sealing.

### Energy management

### Communication with surface

### Engine

### Ballast

### Camera

### Lightning


## Software

### Diver

### Controller