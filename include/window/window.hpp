#pragma once

#include "util/noncopyable.hpp"

#include <SDL2/SDL.h>

#include <glm/vec2.hpp>

#include <array>
#include <string>

namespace window {

enum MouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	X1,
	X2,
	INVALID=7,
	SIZE=7
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
		std::array<bool, static_cast<int>(MouseButton::SIZE)> buttons;
		std::array<enum ButtonDelta, 8> deltas;
	} m_mouse;

	// private methods

	void onResize(Sint32 width, Sint32 height);
	void resetInputDeltas();

public:
	Window(std::string title);
	~Window();

	// class cannot be copied
	Window(const Window &) = delete;
	void operator=(const Window &) = delete;

	void makeContextCurrent();
	void swapBuffers();
	void getInputAndEvents();

	void setVSync(bool enable);
	bool getVSync();

	bool getWindowResized();

	void show();
	void hide();
	void focus();

	void setCloseFlag();
	bool shouldClose();

	void setFullscreen(bool fullscreen);
	void toggleFullscreen();

	bool isFullscreen();

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

	// joystick/gamepad events (maybe), other misc events

	// get timer value
	// TODO

};

}
