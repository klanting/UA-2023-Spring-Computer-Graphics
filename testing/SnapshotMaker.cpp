
#include <cstdlib>

int main(){


    system("cd ../ini-tests; ./../cmake-build-debug/engine");
    system("cd ../ini-tests; find . -iregex \".*bmp\" -exec cp {} ./../ini-snapshots/ \\;");
}