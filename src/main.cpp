#include <SDL2/SDL.h>

#include <iostream>
#include <memory>

class Window {
private:
	SDL_Window *m_handle;
public:
	Window(int width, int height);
	~Window();
};

Window::Window(int width, int height)
{
	m_handle = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
}

Window::~Window()
{
	SDL_DestroyWindow(m_handle);
}

int main()
{

	std::unique_ptr<Window> win(new Window(640, 480));

	for (;;);

	return 0;

}
