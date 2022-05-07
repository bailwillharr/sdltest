#pragma once

#include "engine/util/noncopyable.hpp"

#include <SDL2/SDL.h>

#include <glm/vec2.hpp>

#include <array>
#include <string>

namespace engine {

extern const uint64_t BILLION;

enum class MouseButton : int {
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

	// Return the title name
	std::string getTitle() const;

	// Make this window the current OpenGL context.
	// This is already done in window initialisation.
	void makeContextCurrent();

	// Tell the GPU to render the back buffer to the screen.
	// Run this on every frame.
	void swapBuffers();
	// Update the window state to capture any events that have occurred.
	// Run this on every frame.
	void getInputAndEvents();

	// if 'true', swapBuffers() will wait in order to synchronise with the
	// monitor's refresh rate.
	void setVSync(bool enable);
	// Returns true if VSync is enabled.
	bool getVSync() const;

	// Hides the window (it will appear closed to the user).
	void hide();
	// Shows the window again.
	void show();
	// Raises the window above other windows and sets the input focus
	void focus();
	// Returns true if the window has focus
	bool hasFocus() const;

	// Sets the close flag, check this with shouldClose()
	void setCloseFlag();
	// Returns true if the window should remain open
	bool isRunning() const;

	void setFullscreen(bool fullscreen);
	void toggleFullscreen();

	bool isFullscreen() const;

	// Relative mouse mode captures the cursor for FPS style use. Returns false if unsupported.
	bool setRelativeMouseMode(bool enabled);

	// window events

	// Returns true if the window was just resized during the previous frame
	bool getWindowResized() const;

	// keyboard events

	// returns true if key is down
	bool getKey(int key) const;
	// returns true if key was just pressed
	bool getKeyPress(int key) const;
	// returns true if key was just released
	bool getKeyRelease(int key) const;

	// mouse events

	// returns true if button is down
	bool getButton(MouseButton button) const;
	// returns true if button was just pressed
	bool getButtonPress(MouseButton button) const;
	// returns true if button was just released
	bool getButtonRelease(MouseButton button) const;

	// retrieves x coordinate of the mouse
	int getMouseX() const;
	// retrieves y coordinate of the mouse
	int getMouseY() const;
	// retrieves dx of the mouse since the last frame
	int getMouseXRel() const;
	// retrieves dy of the mouse since the last frame
	int getMouseYRel() const;
	// retrieves amount scrolled vertically
	float getMouseScrollX() const;
	// retrieves amount scrolled horizontally
	float getMouseScrollY() const;

	// joystick/gamepad events (maybe), other misc events



	// returns the performance counter value in nanoseconds;
	uint64_t getNanos() const;

	// returns the number of frames elapsed since window creation
	uint64_t getFrameCount() const;
	uint64_t getStartTime() const;
	uint64_t getLastFrameTime() const;
	uint64_t getFPS() const;

};

}
