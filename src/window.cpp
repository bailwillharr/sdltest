#include "window.hpp"

#include <glad/glad.h>

#include <SDL2/SDL.h>

#include <iostream>
#include <stdexcept>

namespace window {

Window::Window(std::string title) : m_title(title)
{

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		const std::string errMsg("Unable to initialise SDL: " + std::string(SDL_GetError()));
		if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL error", errMsg.c_str(), NULL) != 0) {
			std::cerr << errMsg << "\nAre you in a graphical environment?\n";
		}
		throw std::runtime_error(errMsg);
	}

	m_counterFreq = SDL_GetPerformanceFrequency();
	m_startTime = getNanos();
	m_lastFrameTime = m_startTime;

	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) != 0) {

	}
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) != 0) {

	}
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0) {

	}

	// create the window
	m_handle = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			m_winSize.x,
			m_winSize.y,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
	if (m_handle == NULL) {
		SDL_Quit();
		throw std::runtime_error("Unable to create window: " + std::string(SDL_GetError()));
	}

	// get window size
	int winWidth, winHeight;
	SDL_GetWindowSize(m_handle, &winWidth, &winHeight);
	m_winSize.x = static_cast<float>(winWidth);
	m_winSize.y = static_cast<float>(winHeight);

	const int WINDOWED_MIN_WIDTH = 640;
	const int WINDOWED_MIN_HEIGHT = 480;
	SDL_SetWindowMinimumSize(m_handle, WINDOWED_MIN_WIDTH, WINDOWED_MIN_HEIGHT);

	m_glContext = SDL_GL_CreateContext(m_handle);
	if (m_glContext == NULL) {
		SDL_DestroyWindow(m_handle);
		SDL_Quit();
		throw std::runtime_error("Unable to create OpenGL context: " + std::string(SDL_GetError()));
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_DestroyWindow(m_handle);
		SDL_Quit();
		throw std::runtime_error("Unable to initialise GLAD");
	}

	onResize(m_winSize.x, m_winSize.y);

}

Window::~Window()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_handle);
	SDL_Quit();
}

// private methods

void Window::onResize(Sint32 width, Sint32 height)
{
	std::cout << "RESIZED\n";
	// get window size
	m_winSize.x = static_cast<GLsizei>(width);
	m_winSize.y = static_cast<GLsizei>(height);

	// get framebuffer size
	int fbWidth, fbHeight;
	SDL_GL_GetDrawableSize(m_handle, &fbWidth, &fbHeight);
	m_fbSize.x = static_cast<float>(fbWidth);
	m_fbSize.y = static_cast<float>(fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);
}

void Window::resetInputDeltas()
{
	m_justResized = false;

	m_keyboard.deltas.fill(ButtonDelta::SAME);
	
	m_mouse.deltas.fill(ButtonDelta::SAME);
	m_mouse.xrel = 0;
	m_mouse.yrel = 0;
	m_mouse.xscroll = 0.0f;
	m_mouse.yscroll = 0.0f;
}

// TODO event methods (like callbacks)

void Window::onWindowEvent(SDL_WindowEvent &e)
{
	switch (e.event) {
		case SDL_WINDOWEVENT_RESIZED:
			onResize(e.data1, e.data2);
			m_justResized = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			m_keyboardFocus = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			m_keyboardFocus = false;
			break;
	}
}

void Window::onKeyEvent(SDL_KeyboardEvent &e)
{
	bool keyWasDown = m_keyboard.keys[e.keysym.scancode];
	bool keyIsDown = (e.state == SDL_PRESSED);
	m_keyboard.keys[e.keysym.scancode] = keyIsDown;
	if (keyIsDown != keyWasDown) { // (if key was pressed or released)
		m_keyboard.deltas[e.keysym.scancode] = keyIsDown ? ButtonDelta::PRESSED : ButtonDelta::RELEASED;
	}
}

void Window::onMouseButtonEvent(SDL_MouseButtonEvent &e)
{
	enum MouseButton button = MouseButton::M_INVALID;
	switch (e.button) {
		case SDL_BUTTON_LEFT:
			button = MouseButton::M_LEFT;
			break;
		case SDL_BUTTON_MIDDLE:
			button = MouseButton::M_MIDDLE;
			break;
		case SDL_BUTTON_RIGHT:
			button = MouseButton::M_RIGHT;
			break;
		case SDL_BUTTON_X1:
			button = MouseButton::M_X1;
			break;
		case SDL_BUTTON_X2:
			button = MouseButton::M_X2;
			break;
	}

	bool buttonWasDown = m_mouse.buttons[button];
	bool buttonIsDown = (e.state == SDL_PRESSED);
	m_mouse.buttons[button] = buttonIsDown;
	if (buttonIsDown != buttonWasDown) { // (if button was pressed or released)
		// only sets delta if it hasn't already been set this frame (to detect very fast presses)
		if (m_mouse.deltas[button] == ButtonDelta::SAME) {
			m_mouse.deltas[button] = buttonIsDown ? ButtonDelta::PRESSED : ButtonDelta::RELEASED;
		}
	}
}

void Window::onMouseMotionEvent(SDL_MouseMotionEvent &e)
{
	m_mouse.x = e.x;
	m_mouse.y = e.y;
	m_mouse.xrel = e.xrel;
	m_mouse.yrel = e.yrel;
}

void Window::onMouseWheelEvent(SDL_MouseWheelEvent &e)
{
	if (e.direction == SDL_MOUSEWHEEL_NORMAL) {
		m_mouse.xscroll = e.preciseX;
		m_mouse.yscroll = e.preciseY;
	} else { // flipped
		m_mouse.xscroll = -e.preciseX;
		m_mouse.yscroll = -e.preciseY;
	}
}

// public methods

void Window::makeContextCurrent() { if (SDL_GL_MakeCurrent(m_handle, m_glContext) != 0) {
		throw std::runtime_error("Failed to make GL context current");
	}
}

void Window::swapBuffers()
{
	SDL_GL_SwapWindow(m_handle);
	m_frames++;
	uint64_t currentFrameStamp = getNanos();
	m_lastFrameTime = currentFrameStamp - m_lastFrameStamp;
	m_lastFrameStamp = currentFrameStamp;
}

void Window::getInputAndEvents()
{

	resetInputDeltas();

	// loop through all available events
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {

			case SDL_QUIT:
				setCloseFlag();
				break;

			case SDL_WINDOWEVENT:
				onWindowEvent(e.window);
				break;

			case SDL_KEYDOWN: // FALL THROUGH
			case SDL_KEYUP:
				onKeyEvent(e.key);
				break;

			case SDL_MOUSEBUTTONDOWN: // FALL THROUGH
			case SDL_MOUSEBUTTONUP:
				onMouseButtonEvent(e.button);
				break;

			case SDL_MOUSEMOTION:
				onMouseMotionEvent(e.motion);
				break;

			case SDL_MOUSEWHEEL:
				onMouseWheelEvent(e.wheel);
				break;

		}
	}

}

void Window::setVSync(bool enable)
{
	if (SDL_GL_SetSwapInterval(enable ? 1 : 0) != 0) {
		throw std::runtime_error("Failed to set swap interval");
	}
}

bool Window::getVSync()
{
	return SDL_GL_GetSwapInterval() == 0 ? false : true;
}

bool Window::getWindowResized()
{
	return m_justResized;
}

void Window::show()
{
	SDL_ShowWindow(m_handle);
}

void Window::hide()
{
	SDL_HideWindow(m_handle);
}

void Window::focus()
{
	SDL_RaiseWindow(m_handle);
	m_keyboardFocus = true;
}

bool Window::hasFocus()
{
	return m_keyboardFocus;
}

void Window::setCloseFlag()
{
	m_shouldClose = true;
}

bool Window::shouldClose()
{
	return m_shouldClose;
}

void Window::setFullscreen(bool fullscreen)
{
	if (SDL_SetWindowFullscreen(m_handle, fullscreen ? SDL_WINDOW_FULLSCREEN : 0) != 0) {
		throw std::runtime_error("Unable to set window to fullscreen/windowed");
	}
	m_fullscreen = fullscreen;
}

void Window::toggleFullscreen()
{
	setFullscreen(!m_fullscreen);
}

bool Window::isFullscreen()
{
	return m_fullscreen;
}

bool Window::setRelativeMouseMode(bool enabled)
{
	int code = SDL_SetRelativeMouseMode(static_cast<SDL_bool>(enabled));
	if (code != 0) {
		if (code == -1) {
			return false;
		} else {
			throw std::runtime_error("Unable to set relative mouse mode: ");
		}
	} else {
		return true;
	}
}

// getting input

bool Window::getKey(int key)
{
	return m_keyboard.keys[key];
}

bool Window::getKeyPress(int key)
{
	return m_keyboard.deltas[key] == ButtonDelta::PRESSED;
}

bool Window::getKeyRelease(int key)
{
	return m_keyboard.deltas[key] == ButtonDelta::RELEASED;
}

// TODO mouse input

bool Window::getButton(enum MouseButton button)
{
	return m_mouse.buttons[button];
}

bool Window::getButtonPress(enum MouseButton button)
{
	return m_mouse.deltas[button] == ButtonDelta::PRESSED;
}

bool Window::getButtonRelease(enum MouseButton button)
{
	return m_mouse.deltas[button] == ButtonDelta::RELEASED;
}

int Window::getMouseX()
{
	return static_cast<int>(m_mouse.x);
}

int Window::getMouseY()
{
	return static_cast<int>(m_mouse.y);
}

int Window::getMouseXRel()
{
	return static_cast<int>(m_mouse.xrel);
}

int Window::getMouseYRel()
{
	return static_cast<int>(m_mouse.yrel);
}

float Window::getMouseScrollX()
{
	return m_mouse.xscroll;
}

float Window::getMouseScrollY()
{
	return m_mouse.yscroll;
}

// TODO game pad

// get timer value
uint64_t Window::getNanos()
{
	uint64_t count;

	count = SDL_GetPerformanceCounter();
	if (m_counterFreq == BILLION) {
		return count;
	} else {
		return count * (BILLION / m_counterFreq);
	}
}

uint64_t Window::getFrameCount()
{
	return m_frames;
}

uint64_t Window::getStartTime()
{
	return m_startTime;
}

uint64_t Window::getLastFrameTime()
{
	return m_lastFrameTime;
}

uint64_t Window::getFPS()
{
	return BILLION / m_lastFrameTime;
}

}