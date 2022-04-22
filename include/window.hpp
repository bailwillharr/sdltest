#pragma once

#include "util/noncopyable.hpp"

#include <SDL2/SDL.h>

#include <glm/vec2.hpp>

#include <array>
#include <string>

namespace window {

const uint64_t BILLION = 1000000000;

enum MouseButton {
	M_LEFT,
	M_MIDDLE,
	M_RIGHT,
	M_X1,
	M_X2,
	M_INVALID=7,
	M_SIZE=7
};

class Window : non_copyable {

private:
	SDL_Window *m_handle;
	SDL_GLContext m_glContext;

	bool m_shouldClose = false;

	std::string m_title;

	bool m_fullscreen = false;
	bool m_justResized = false;
	bool m_keyboardFocus = true;

	// size in screen coordinates
	glm::vec2 m_winSize = glm::vec2(640, 480);
	// actual framebuffer size
	glm::vec2 m_fbSize;

	// performance counter frequency
	uint64_t m_counterFreq;

	// number of frames swapped
	uint64_t m_frames = 0;
	// in nanoseconds
	uint64_t m_startTime;
	// in nanoseconds
	uint64_t m_lastFrameStamp;
	// in nanoseconds; elapsed time between frames
	uint64_t m_lastFrameTime;

	// input stuff

	enum class ButtonDelta {
		SAME,
		PRESSED,
		RELEASED
	};

	struct {
		std::array<bool, SDL_NUM_SCANCODES> keys;
		std::array<enum ButtonDelta, SDL_NUM_SCANCODES> deltas;
	} m_keyboard;

	struct {
		std::array<bool, static_cast<int>(MouseButton::M_SIZE)> buttons;
		std::array<enum ButtonDelta, 8> deltas;
		Sint32 x;
		Sint32 y;
		Sint32 xrel;
		Sint32 yrel;
		float xscroll;
		float yscroll;
	} m_mouse;

	// private methods

	void onResize(Sint32 width, Sint32 height);
	void resetInputDeltas();

	// event methods (like callbacks)

	void onWindowEvent(SDL_WindowEvent &e);
	void onKeyEvent(SDL_KeyboardEvent &e);
	void onMouseButtonEvent(SDL_MouseButtonEvent &e);
	void onMouseMotionEvent(SDL_MouseMotionEvent &e);
	void onMouseWheelEvent(SDL_MouseWheelEvent &e);

public:
	Window(std::string title);
	~Window();

	void makeContextCurrent();
	void swapBuffers();
	void getInputAndEvents();

	void setVSync(bool enable);
	bool getVSync();

	bool getWindowResized();

	void show();
	void hide();
	void focus();
	bool hasFocus();

	void setCloseFlag();
	bool shouldClose();

	void setFullscreen(bool fullscreen);
	void toggleFullscreen();

	bool isFullscreen();

	// Relative mouse mode captures the cursor for FPS style use. Returns false if unsupported.
	bool setRelativeMouseMode(bool enabled);

	// getting input

	// returns true if key is down
	bool getKey(int key);
	// returns true if key was just pressed
	bool getKeyPress(int key);
	// returns true if key was just released
	bool getKeyRelease(int key);

	// mouse events,

	// returns true if button is down
	bool getButton(enum MouseButton button);
	// returns true if button was just pressed
	bool getButtonPress(enum MouseButton button);
	// returns true if button was just released
	bool getButtonRelease(enum MouseButton button);

	// retrieve x coordinate of the mouse
	int getMouseX();
	// retrieve y coordinate of the mouse
	int getMouseY();
	// retrieve dx of the mouse since the last frame
	int getMouseXRel();
	// retrieve dy of the mouse since the last frame
	int getMouseYRel();
	// retrieve amount scrolled vertically
	float getMouseScrollX();
	// retrieve amount scrolled horizontally
	float getMouseScrollY();

	// joystick/gamepad events (maybe), other misc events

	// return the performance counter value in nanoseconds;
	uint64_t getNanos();

	uint64_t getFrameCount();
	uint64_t getStartTime();
	uint64_t getLastFrameTime();
	uint64_t getFPS();

};

}
