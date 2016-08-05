#include "Manager.h"

//#include <vld.h>

#if EMACS
#pragma comment(lib, "..\\..\\deps\\lib\\x86\\SDL2.lib")
#pragma comment(lib, "..\\..\\deps\\lib\\x86\\SDL2main.lib")
#pragma comment(lib, "..\\..\\deps\\lib\\x86\\SDL2_ttf.lib")
#pragma comment(lib, "..\\..\\deps\\lib\\x86\\SDL2_image.lib")
#pragma comment(lib, "..\\..\\deps\\lib\\x86\\SDL2_mixer.lib")
#pragma comment(lib, "..\\..\\deps\\lib\\x86\\SDL2test.lib")
#else
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2test.lib")
#endif

int main( int argc, char* args[] )
{
    Manager gm;
    gm.Init();
    while ( gm.Update() );
    gm.Close();

    return 0;
}
