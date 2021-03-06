#pragma once

#include "inputs/mouse.hpp"
#include "inputs/keyboard.hpp"

#include <vector>
#include <array>
#include <string>

class Window;

enum class InputDevice : int {
	MOUSE,
	KEYBOARD,
	CONTROLLER,
	SIZE
};

// This class should be used to get platform/input-device independent input
class Input {

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

	void addInputButton(const std::string& name, InputDevice device, int button);
	void addInputAxis(const std::string& name, InputDevice device, int axis);
	void addInputButtonAsAxis(const std::string& name, InputDevice device, int high, int low);

public:

	// requires a window reference to get input from
	Input(const Window &win);
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	~Input();

	// Add a mouse input
	void addInputButton(const std::string& name, inputs::MouseButton button);
	void addInputAxis(const std::string& name, inputs::MouseAxis axis);
	void addInputButtonAsAxis(const std::string& name, inputs::MouseButton high, inputs::MouseButton low);
	// Add a keyboard input
	void addInputButton(const std::string& name, inputs::Key button);
	void addInputButtonAsAxis(const std::string& name, inputs::Key high, inputs::Key low);

	void delInputButton(int index);
	void delInputAxis(int index);

	void setDeviceActive(enum InputDevice device, bool active);
	bool getDeviceActive(enum InputDevice device) const;

	float getAxis(const std::string& axisName) const;
	bool getButton(const std::string& buttonName) const;
	bool getButtonPress(const std::string& buttonName) const;
	bool getButtonRelease(const std::string& buttonName) const;
	
};
