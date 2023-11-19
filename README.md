# miniRT
42 School - Level04

A simple ray tracer using the miniLibX

Check out [this guide](https://harm-smits.github.io/42docs/libs/minilibx) for everything about the miniLibX including the setup.

## Usage

`make` compiles the program.

As an argument it takes an rt file (only with .rt extension)
```
$ ./miniRT <file.rt>
```

The file format follows certain rules:
+ Each type of element can be separated by one or more line break(s).
+ Each type of information from an element can be separated by one or more space(s).
+ Each type of element can be set in any order in the file.
+ Elements which are defined by a capital letter can only be declared once in the scene.

#### Elements

##### Ambient lightning

Key | Value
--- | ---
Identifier | A
Ambient lighting ratio | In range [0.0,1.0]
R,G,B colors | In range [0-255]

##### Camera

Key | Value
--- | ---
Identifier | C
x,y,z coordinates | In range [-inf,+inf]
3d normalized orientation vector | In range [-1,1] for each x,y,z axis
FOV (Horizontal field of view) in degrees | In range [0,180]

##### Light

Key | Value
--- | ---
Identifier | L
x,y,z coordinates | In range [-inf,+inf]
Light brightness ratio | In range [0.0,1.0]

##### Sphere

Key | Value
--- | ---
Identifier | sp
x,y,z coordinates of the sphere center | In range [-inf,+inf]
Sphere diameter | In range [-inf,+inf]
R,G,B colors | In range [0-255]

##### Plane

Key | Value
--- | ---
Identifier | pl
x,y,z coordinates of a point in the plane | In range [-inf,+inf]
3d normalized normal vector | In range [-1,1] for each x,y,z axis
R,G,B colors | In range [0-255]

##### Cylinder

Key | Value
--- | ---
Identifier | cy
x,y,z coordinates of the center of the cylinder | In range [-inf,+inf]
3d normalized vector of axis of cylinder | In range [-1,1] for each x,y,z axis
Cylinder diameter | In range [-inf,+inf]
Cylinder height | In range [-inf,+inf]
R,G,B colors | In range [0,255]

E.g.:
```
A                             0.1  0,50,255
C 50,0,10    -1,0,0                           100
L 0,0,30                      1

cy -20,0,15   0,1,0  5    20       50,50,200
sp -20,20,15         10            100,0,70
pl -40,0,0    1,0,0                100,200,0
```

