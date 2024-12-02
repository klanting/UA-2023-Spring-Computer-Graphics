
#include <cstdlib>
int main(){
    system("> ../ini-tests/filelist \\;");
    system("cd ../ini-1; find . -iregex \".*ini*\" -exec sh -c 'echo \"${1}\" | cut -c3-' _ {} >> ./../ini-tests/filelist \\;");
    system("cd ../ini-1; find . -iregex \".*L2D*\" -exec cp {} ./../ini-tests/ \\;");


    system("cd ../ini-tests; ./../cmake-build-debug/engine");
    system("cd ../ini-tests; find . -iregex \".*bmp\" -exec mv {} ./../ini-snapshots/ \\;");
}