# Computer Graphics

[![CodeFactor](https://www.codefactor.io/repository/github/klanting/ua-2023-spring-computer-graphics/badge)](https://www.codefactor.io/repository/github/klanting/ua-2023-spring-computer-graphics)[![Codacy Badge](https://app.codacy.com/project/badge/Grade/8b06cd245c4d47e0940dd264d78df07b)](https://app.codacy.com/gh/klanting/UA-2023-Spring-Computer-Graphics/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

## Supported Functionality

<details>
<summary>L-systems</summary>

### 2D L-systems

- Generation of 2D L-systems can be done based on L-system rules
- the use of brackets is possible
- stochastic randomization can be applied

### 3D L-systems

- Generation of 3D L-systems can be done based on L-system rules
- the use of brackets is possible

</details>

<details>
<summary>Rendering</summary>

3D objects can be rendered to a 2D image/surface.

### Projection

3D objects can be projected to a 2D surface as an image.

### Triangulation

Able to convert a Face having n (>2) amount of points into multiple triangle faces.

### Z-buffering (lines)

When using objects, only consisting of wireframes, this engine will provide Z-buffering support for these lines.

### Z-buffering (triangles)

Support of Z-buffering of triangles.

</details>

<details>
<summary>Platonic Bodies</summary>

### Platonic Bodies

The engine has a build in tool to create some basic 3D shapes:

- Cube
- Icosahedron
- Octahedron
- Dodecahedron
- Cone
- Cylinder
- Sphere
- Torus
- Tetrahedron
- MobiusStrip
- Umbilical
- BuckyBall
- MengerSponge

### 3D fractals
Able to create Fractals given a platonic shape.

</details>

<details>
<summary>View Frustum</summary>

### View Frustum

When the camera is not able to cover the entire shape, it will cut of some parts, this cutting of is referred to as 
View Frustum.

</details>

<details>
<summary>Lighting</summary>

### Ambient light

The general color the object has when not applying external light.

### Diffuse light (infinity)

Light provided from an object infinity far away, like sunlight.

### Diffuse light (point)

Light coming from a lamp.

### Specular light

Light that comes from the reflection on an object

</details>

<details>
<summary>Shadows</summary>

### Shadows

be able to show shadows on places of the object where light is absent

</details>

<details>
<summary>Textures</summary>

### Texture mapping

Map texture on the object using the random surface approach

### UV-coordinates

Make Spheres more realistic when light is present

### Cube mapping

Perform cube mapping

### spheres and cylinders

Make a wireframe of an object, but as wires and corners have very thick cylinders and spheres

</details>

## Extra uitleg 2D L-systemen Stochastisch
Voor subonderdeel Stochastisch (2D L-systemen) zijn en 2 .ini en .L2D
files (own_1.ini, own_1.L2D) en (own_2.ini, own_2.L2D)
Voor het gebruik van Stochastisch waardes zijn hier enkele veranderingen
de .ini bevat een line: stochastic = true (indien niet aanwezig default = false)
Dit geeft weer dat het een L-systeem is met Stochastisch kans, in de overeenkomstige L-systemen is er ook een wijziging bij de replacement rules:
Een character kan meerdere replacement rules hebben, na het character wordt het gevolgd door een double die weergeeft hoeveel de kans is value tussen 0 en 1
De som van alle dubbels van 1 character moet gelijk zijn aan 1
example:
F 0.5 -> "-F+F-F-FFFF",
F 0.3 -> "--FFF-F",
F 0.2 -> "+FFF++F"
Om dit te kunnen doen zijn er wijzigingen aan de gegeven l_parser gebeurd.

## Extra uitleg texture mapping
Indien u de waardes aanpast van de texture map moet u met het volgende rekening houden:
De hele figuur moet binnen de texture map liggen, cde vectoren P, A, B zijn in het gewone coordinaat systeem

## Extra uitleg normaal_vectoren
texture_coord002.ini houdt geen rekening met normaal_vectoren,
de overeenkomstige file die dat wel doet is texture_coord003.ini
analoog voor cube_mapping005.ini -> cube_mapping006.ini





