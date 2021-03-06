#include "window.hpp"

#include <glad/glad.h>

#include <iostream>
#include <stdexcept>

const uint64_t BILLION = 1000000000;

Window::Window(const std::string& title) : m_title(title)
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
	m_lastFrameStamp = m_startTime - 1;
	m_avgFpsStart = m_startTime;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// create the window
	m_handle = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			static_cast<int>(m_winSize.x),
			static_cast<int>(m_winSize.y),
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
	if (m_handle == NULL) {
		SDL_Quit();
		throw std::runtime_error("Unable to create window: " + std::string(SDL_GetError()));
	}

	// get window size
	int winWidth, winHeight;
	SDL_GetWindowSize(m_handle, &winWidth, &winHeight);
	m_winSize.x = winWidth;
	m_winSize.y = winHeight;

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

#ifndef NDEBUG
	std::cerr << "Window '" << m_title << "' has been constructed\n";
#endif

}

Window::~Window()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_handle);
	SDL_Quit();
#ifndef NDEBUG
	std::cerr << "Window destroyed: '" << m_title << "'\n";
#endif
}

// private methods

void Window::onResize(Sint32 width, Sint32 height)
{
	// get window size
	m_winSize.x = static_cast<int>(width);
	m_winSize.y = static_cast<int>(height);

	// get framebuffer size
	int fbWidth, fbHeight;
	SDL_GL_GetDrawableSize(m_handle, &fbWidth, &fbHeight);
	m_fbSize.x = static_cast<int>(fbWidth);
	m_fbSize.y = static_cast<int>(fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);

	m_justResized = true;
}

void Window::resetInputDeltas()
{
	m_justResized = false;

	m_keyboard.deltas.fill(ButtonDelta::SAME);
	
	m_mouse.deltas.fill(ButtonDelta::SAME);
	m_mouse.dx = 0;
	m_mouse.dy = 0;
	m_mouse.xscroll = 0.0f;
	m_mouse.yscroll = 0.0f;
}

// TODO event methods (like callbacks)

void Window::onWindowEvent(SDL_WindowEvent &e)
{

	switch (e.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			onResize(e.data1, e.data2);
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
	enum inputs::MouseButton button = inputs::MouseButton::M_INVALID;
	switch (e.button) {
		case SDL_BUTTON_LEFT:
			button = inputs::MouseButton::M_LEFT;
			break;
		case SDL_BUTTON_MIDDLE:
			button = inputs::MouseButton::M_MIDDLE;
			break;
		case SDL_BUTTON_RIGHT:
			button = inputs::MouseButton::M_RIGHT;
			break;
		case SDL_BUTTON_X1:
			button = inputs::MouseButton::M_X1;
			break;
		case SDL_BUTTON_X2:
			button = inputs::MouseButton::M_X2;
			break;
	}

	bool buttonWasDown = m_mouse.buttons[static_cast<int>(button)];
	bool buttonIsDown = (e.state == SDL_PRESSED);
	m_mouse.buttons[static_cast<int>(button)] = buttonIsDown;
	if (buttonIsDown != buttonWasDown) { // (if button was pressed or released)
		// only sets delta if it hasn't already been set this frame (to detect very fast presses)
		if (m_mouse.deltas[static_cast<int>(button)] == ButtonDelta::SAME) {
			m_mouse.deltas[static_cast<int>(button)] = buttonIsDown ? ButtonDelta::PRESSED : ButtonDelta::RELEASED;
		}
	}
}

void Window::onMouseMotionEvent(SDL_MouseMotionEvent &e)
{
	m_mouse.x = e.x;
	m_mouse.y = e.y;
	m_mouse.dx = e.xrel;
	m_mouse.dy = e.yrel;
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

std::string Window::getTitle() const
{
	return m_title;
}

void Window::makeContextCurrent()
{
	if (SDL_GL_MakeCurrent(m_handle, m_glContext) != 0) {
		throw std::runtime_error("Failed to make GL context current");
	}
}

void Window::swapBuffers()
{
#ifndef SDLTEST_NOGFX
	SDL_GL_SwapWindow(m_handle);
#endif
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

bool Window::getVSync() const
{
	return SDL_GL_GetSwapInterval() == 0 ? false : true;
}

glm::ivec2 Window::getViewportSize()
{
	return m_fbSize;
}

void Window::setTitle(std::string title)
{
	SDL_SetWindowTitle(m_handle, title.c_str());
}

bool Window::getWindowResized() const
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

bool Window::hasFocus() const
{
	return m_keyboardFocus;
}

void Window::setCloseFlag()
{
	m_shouldClose = true;
}

bool Window::isRunning() const
{
	return !m_shouldClose;
}

void Window::setFullscreen(bool fullscreen, bool exclusive)
{
	if (SDL_SetWindowFullscreen(m_handle, fullscreen ? (exclusive ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_FULLSCREEN_DESKTOP) : 0) != 0) {
		throw std::runtime_error("Unable to set window to fullscreen/windowed");
	}
	m_fullscreen = fullscreen;
	if (fullscreen) {
		int width, height;
		SDL_GetWindowSize(m_handle, &width, &height);
		onResize(width, height);
	}
}

void Window::toggleFullscreen()
{
	setFullscreen(!m_fullscreen);
}

bool Window::isFullscreen() const
{
	return m_fullscreen;
}

bool Window::setRelativeMouseMode(bool enabled)
{
	m_mouse.captured = enabled;
	int code = SDL_SetRelativeMouseMode(static_cast<SDL_bool>(enabled));
	if (code != 0) {
		throw std::runtime_error("Unable to set relative mouse mode");
	} else {
		return true;
	}
}

bool Window::mouseCaptured()
{
	return m_mouse.captured;
}

// getting input

bool Window::getKey(inputs::Key key) const
{
	return m_keyboard.keys[static_cast<int>(key)];
}

bool Window::getKeyPress(inputs::Key key) const
{
	return m_keyboard.deltas[static_cast<int>(key)] == ButtonDelta::PRESSED;
}

bool Window::getKeyRelease(inputs::Key key) const
{
	return m_keyboard.deltas[static_cast<int>(key)] == ButtonDelta::RELEASED;
}

// TODO mouse input

bool Window::getButton(inputs::MouseButton button) const
{
	return m_mouse.buttons[static_cast<int>(button)];
}

bool Window::getButtonPress(inputs::MouseButton button) const
{
	return m_mouse.deltas[static_cast<int>(button)] == ButtonDelta::PRESSED;
}

bool Window::getButtonRelease(inputs::MouseButton button) const
{
	return m_mouse.deltas[static_cast<int>(button)] == ButtonDelta::RELEASED;
}

int Window::getMouseX() const
{
	return static_cast<int>(m_mouse.x);
}

int Window::getMouseY() const
{
	return static_cast<int>(m_mouse.y);
}

float Window::getMouseNormX() const
{
	return ((float)m_mouse.x * 2.0f / (float)m_winSize.x) - 1.0f;
}

float Window::getMouseNormY() const
{
	return ((float)m_mouse.y * -2.0f / (float)m_winSize.y) + 1.0f;
}

int Window::getMouseDX() const
{
	return static_cast<int>(m_mouse.dx);
}

int Window::getMouseDY() const
{
	return static_cast<int>(m_mouse.dy);
}

float Window::getMouseScrollX() const
{
	return m_mouse.xscroll;
}

float Window::getMouseScrollY() const
{
	return m_mouse.yscroll;
}

// TODO game pad

// get timer value
uint64_t Window::getNanos() const
{
	uint64_t count;

	count = SDL_GetPerformanceCounter();
	if (m_counterFreq == BILLION) {
		return count;
	} else {
		return count * (BILLION / m_counterFreq);
	}
}

uint64_t Window::getLastFrameStamp() const
{
	return m_lastFrameStamp;
}

uint64_t Window::getFrameCount() const
{
	return m_frames;
}

uint64_t Window::getStartTime() const
{
	return m_startTime;
}

float Window::dt() const
{
	return (float)m_lastFrameTime / (float)BILLION;
}

uint64_t Window::getFPS() const
{
	if (m_lastFrameTime == 0) return 0;
	return BILLION / m_lastFrameTime;
}

uint64_t Window::getAvgFPS() const
{
	uint64_t delta_t = getNanos() - m_avgFpsStart;
	if (delta_t == 0) return 0;
	return BILLION * (m_frames - m_avgFpsStartCount) / delta_t;
}

void Window::resetAvgFPS()
{
	m_avgFpsStart = getNanos();
	m_avgFpsStartCount = getFrameCount();
}

bool Window::infoBox(const std::string& title, const std::string& msg)
{
	if (isFullscreen() == false) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), msg.c_str(), m_handle);
		return true;
	} else {
		return false;
	}
}

/* STATIC METHODS */

// Display an error message box
void Window::errorBox(const std::string& message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game Error", message.c_str(), NULL);
}
