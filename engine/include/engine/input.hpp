#pragma once

#include "engine/window.hpp"

#include "engine/util/noncopyable.hpp"

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

enum class MouseAxis : int {
	X,
	Y,
	X_SCR,
	Y_SCR
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

	float getDeviceAxis(enum InputDevice device, int axis);
	bool getDeviceButton(enum InputDevice device, int button);
	bool getDeviceButtonDown(enum InputDevice device, int button);
	bool getDeviceButtonUp(enum InputDevice device, int button);

	float getButtonAxis(enum InputDevice device, int high, int low);

public:

	// requires a window reference to get input from
	Input(const Window &win);
	~Input();

	void addInputButton(std::string name, enum InputDevice device, int button);
	void delInputButton(int index);

	void addInputAxis(std::string name, enum InputDevice device, int axis);
	void addInputButtonAsAxis(std::string name, enum InputDevice device, int high, int low);
	void delInputAxis(int index);

	void setDeviceActive(enum InputDevice device, bool active);
	bool getDeviceActive(enum InputDevice device);

	float getAxis(std::string axisName);
	bool getButton(std::string buttonName);
	bool getButtonPress(std::string buttonName);
	bool getButtonRelease(std::string buttonName);
	
};

}
