#pragma once

#include "engine/util/noncopyable.hpp"

#include "engine/window.hpp"

#include "engine/inputs/keyboard.hpp"
#include "engine/inputs/mouse.hpp"

#include <array>
#include <vector>
#include <string>
#include <memory>

namespace engine {

enum class InputDevice : int {
	MOUSE,
	KEYBOARD,
	CONTROLLER,
	SIZE
};

// This class should be used to get platform/input-device independent input
class Input : non_copyable {

private:

	struct ButtonEntry {
		std::string name;
		enum InputDevice device;
		int button; // enumeration of device buttons or axes
	};

	struct AxisEntry {
		std::string name;
		enum InputDevice device;
		int axis;
		bool isButtonAxis;
		int high;
		int low;
	};

	const Window& m_win;

	std::vector<struct ButtonEntry> m_buttonEntries;
	std::vector<struct AxisEntry> m_axisEntries;

	std::array<bool, static_cast<int>(InputDevice::SIZE)> m_enabledDevices;

	// private methods

	float getDeviceAxis(enum InputDevice device, int axis) const;
	bool getDeviceButton(enum InputDevice device, int button) const;
	bool getDeviceButtonDown(enum InputDevice device, int button) const;
	bool getDeviceButtonUp(enum InputDevice device, int button) const;

	float getButtonAxis(enum InputDevice device, int high, int low) const;

	void addInputButton(std::string name, InputDevice device, int button);
	void addInputAxis(std::string name, InputDevice device, int axis);
	void addInputButtonAsAxis(std::string name, InputDevice device, int high, int low);

public:

	// requires a window reference to get input from
	Input(const Window &win);
	~Input();

	// Add a mouse input
	void addInputButton(std::string name, inputs::MouseButton button);
	void addInputAxis(std::string name, inputs::MouseAxis axis);
	void addInputButtonAsAxis(std::string name, inputs::MouseButton high, inputs::MouseButton low);
	// Add a keyboard input
	void addInputButton(std::string name, inputs::Key button);
	void addInputButtonAsAxis(std::string name, inputs::Key high, inputs::Key low);

	void delInputButton(int index);
	void delInputAxis(int index);

	void setDeviceActive(enum InputDevice device, bool active);
	bool getDeviceActive(enum InputDevice device) const;

	float getAxis(std::string axisName) const;
	bool getButton(std::string buttonName) const;
	bool getButtonPress(std::string buttonName) const;
	bool getButtonRelease(std::string buttonName) const;
	
};

}
