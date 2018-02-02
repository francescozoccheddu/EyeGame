#pragma once
#include "../Platform/platform.hpp"


class World
{
public:
	World (Platform::Window *window);
	virtual ~World ();

	void run ();

private:
	Platform::Window *const window;

	void render (float deltaTime, int width, int height, Platform::Input input);

	static void renderFunc (float deltaTime, int width, int height, Platform::Input input, void* userData);
};

