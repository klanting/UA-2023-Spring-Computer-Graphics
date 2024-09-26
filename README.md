# Computer Graphics

[![CodeFactor](https://www.codefactor.io/repository/github/klanting/ua-2023-spring-computer-graphics/badge)](https://www.codefactor.io/repository/github/klanting/ua-2023-spring-computer-graphics)

## Supporting Features


|   | Functionality            |
|---|--------------------------|
| 1 | 2D L-systems             |
|   | With brackets            |
|   | Stochastic               |
| 2 | Transformations          |
|   | Eye-point                |
|   | Projection               |
| 3 | Platonic Bodies          |
|   | Cone and cylinder        |
|   | Sphere                   |
|   | Torus                    |
|   | 3D L-systems             |
| 4 | Z-buffering (lines)      |
| 5 | Triangulation            |
|   | Z-buffering (triangles)  |
| 6 | 3D fractals              |
|   | BuckyBall                |
|   | Mengersponge             |
|   | View Frustum             |
| 7 | Ambient light            |
|   | Diffuus light (infinity) |
|   | Diffuus light (point)    |
|   | Speculair light          |
| 8 | Schadow                  |
|   | Texture mapping          |
| 9 | spheres and cylinders    |
|   | UV-coordinates           |
|   | Cube mapping             |

Geïmplementeerde vorm van texture mapping: Willkeurig oppervlak

## Gekende problemen
## Niet-gequoteerde functionaliteit
...

## Extra functionaliteit, niet in de opgaves beschreven
Ook de platonische lichamen Mobius en Umbilic Torus (navelvormige Torus)
worden ondersteunt (zie own_mobius.ini en own_torus_umb.ini)
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
\
## Extra uitleg normaal_vectoren
texture_coord002.ini houdt geen rekening met normaal_vectoren,
de overeenkomstige file die dat wel doet is texture_coord003.ini
analoog voor cube_mapping005.ini -> cube_mapping006.ini





