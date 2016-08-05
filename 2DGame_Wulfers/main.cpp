#include "Manager.h"

//#include <vld.h>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2test.lib")

int main( int argc, char* args[] )
{
	Manager gm;
	gm.Init();
	while ( gm.Update() );
	gm.Close();

	return 0;
}