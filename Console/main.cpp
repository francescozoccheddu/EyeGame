#include "../Platform/platform.hpp"
#include "../Gameplay/world.h"
#include <iostream>


int main ()
{
	Platform::Window window;
	World world (&window);
	window.create ();
	world.run ();
	return 0;
}