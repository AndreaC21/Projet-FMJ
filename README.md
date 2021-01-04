# THE 3D SCENE VIEWER

## HOW TO COMPILE ##

J'ai utilisé VSCode et pour compiler, j'utilise le makefile fourni avec ce dossier ( qui le second que vous nous avez donnée ).
Je compile avec make et j'execute avec bin/./tdsv  data/tetrahedron1.obj
J'ai normalement implementé toutes les fonctions demandé ( certaine retournent directement 0 ou true )
Mon projet n'est pas complet, j'ai mis une image du résulat que j'obtient pour l'instant dans le dossier images.

## INCLUDE 

J'ai dans la plupart des fichiers, des include de ce type : 
* #include "../include/libmatrix.hpp" 
* #include "../include/libgeometry.hpp"
## Directory tree explained

bin/
: Executable files, both for the application, tests and spikes.

build/
: Object files (removed with make clean).

data/
: Data files (contain the objects to be shown in the scene).

doc/
: Documentation files.

fonts/
: Font files.

include/
: All necessary header files that do not exist on the system path.

lib/
: Libraries needed in development (we do not need in this project).

spikes/
: Smaller classes or files to test technologies or ideas. They can be keept around for future reference.

src/
: Application source files.

test/
: Test code files.

images/
: Current result.

 
