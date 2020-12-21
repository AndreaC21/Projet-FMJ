# THE 3D SCENE VIEWER

## HOW TO COMPILE ##

J'utilise le makefile fourni avec ce dossier ( qui le second que vous nous avez donnée )
La dernière fois, il y a certainement eu des erreurs car je n'avais pas deg_to_quat, operator*(Quaternion,Vector)
Normalement cela devrait compilé( c'est bien le cas chez moi )

Je ne passe pas test_quaternion_n car il doit y avoir un soucis avec mon operateur*(Quaternion,Vector)

J'ai vérifié les resulats de plusieurs des fonctions avec ces sites :
* https://www.andre-gaschler.com/rotationconverter/
* https://www.vcalc.com/wiki/vCalc/Quaternion+Inverse

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

 
