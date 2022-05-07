#include "engine/input.hpp"

#include "engine/window.hpp"

#include <string>
#include <stdexcept>
#include <iostream>

namespace engine {

Input::Input(const Window &win) : m_win(win)
{
	std::cout << "Input handler for '" << m_win.getTitle() << "' has been constructed\n";

	m_enabledDevices.fill(true);
}

Input::~Input() { std::cout << "Input handler destroyed\n"; }

// private methods

float Input::getDeviceAxis(enum InputDevice device, int axis)
{
	switch (device) {
		case MOUSE:
			switch (axis) {
				case MOUSE_AXIS_X:
					return m_win.getMouseXRel();
				case MOUSE_AXIS_Y:
					return m_win.getMouseYRel();
				case MOUSE_AXIS_X_SCR:
					return m_win.getMouseScrollX();
				case MOUSE_AXIS_Y_SCR:
					return m_win.getMouseScrollY();
				default: break;
			}
			break;
		case KEYBOARD:
			break;
		case CONTROLLER: // fall-through (as of right now)
			break;
		default: break;
	}
	throw std::runtime_error("Error getting device axis");
}

bool Input::getDeviceButton(enum InputDevice device, int button)
{
	switch (device) {
		case MOUSE:
			return m_win.getButton(static_cast<enum MouseButton>(button));
		case KEYBOARD:
			return m_win.getKey(button);
		case CONTROLLER:
			break;
		default: break;
	}
	throw std::runtime_error("Error getting device button");
}

bool Input::getDeviceButtonDown(enum InputDevice device, int button)
{
	switch (device) {
		case MOUSE:
			return m_win.getButtonPress(static_cast<enum MouseButton>(button));
		case KEYBOARD:
			return m_win.getKeyPress(button);
		case CONTROLLER:
			break;
		default: break;
	}
	throw std::runtime_error("Error getting device button");
}

bool Input::getDeviceButtonUp(enum InputDevice device, int button)
{
	switch (device) {
		case MOUSE:
			return m_win.getButtonRelease(static_cast<enum MouseButton>(button));
		case KEYBOARD:
			return m_win.getKeyRelease(button);
		case CONTROLLER:
			break;
		default: break;
	}
	throw std::runtime_error("Error getting device button");
}

float Input::getButtonAxis(enum InputDevice device, int high, int low)
{
	float value = 0.0f;
	if (getDeviceButton(device, high)) value += 10.0f;
	if (low != 0) {
		if (getDeviceButton(device, low)) value += -10.0f;
	}
	return value;
}

// public methods

void Input::addInputButton(std::string name, enum InputDevice device, int button)
{
	m_buttonEntries.push_back( { name, device, button } );
}

void Input::addInputAxis(std::string name, enum InputDevice device, int axis)
{
	m_axisEntries.push_back( { name, device, axis, false, 0, 0 } );
}

void Input::addInputButtonAsAxis(std::string name, enum InputDevice device, int high, int low)
{
	m_axisEntries.push_back( { name, device, 0, true, high, low } );
}

void Input::delInputButton(int index)
{
	std::vector<struct ButtonEntry>::iterator it = m_buttonEntries.begin();
	std::advance(it, index);
	m_buttonEntries.erase(it);
}

void Input::delInputAxis(int index)
{
	std::vector<struct AxisEntry>::iterator it = m_axisEntries.begin();
	std::advance(it, index);
	m_axisEntries.erase(it);
}

void Input::setDeviceActive(enum InputDevice device, bool active)
{
	m_enabledDevices[device] = active;
}

bool Input::getDeviceActive(enum InputDevice device)
{
	return m_enabledDevices[device];
}

float Input::getAxis(std::string axisName)
{
	for (struct AxisEntry e : m_axisEntries) {
		if (e.name == axisName) {
			if (m_enabledDevices[e.device]) {
				if (e.isButtonAxis) {
					return getButtonAxis(e.device, e.high, e.low);
				} else {
					return getDeviceAxis(e.device, e.axis);
				}
			}
		}
	}
	return 0.0f; // instead of throwing an exception, just return nothing
//	throw std::runtime_error("Unable to find mapping in input table");
}

bool Input::getButton(std::string buttonName)
{
	bool isDown = false;

	for (struct ButtonEntry e : m_buttonEntries) {
		if (e.name == buttonName) {
			if (m_enabledDevices[e.device]) {
				if (getDeviceButton(e.device, e.button) == true) {
					isDown = true;
					break;
				}
			}
		}
	}
	return isDown;
}

bool Input::getButtonPress(std::string buttonName)
{
	bool isPressed = false;

	for (struct ButtonEntry e : m_buttonEntries) {
		if (e.name == buttonName) {
			if (m_enabledDevices[e.device]) {
				if (getDeviceButtonDown(e.device, e.button) == true) {
					isPressed = true;
					break;
				}
			}
		}
	}
	return isPressed;
}

bool Input::getButtonRelease(std::string buttonName)
{
	bool isReleased = false;

	for (struct ButtonEntry e : m_buttonEntries) {
		if (e.name == buttonName) {
			if (m_enabledDevices[e.device]) {
				if (getDeviceButtonUp(e.device, e.button) == true) {
					isReleased = true;
					break;
				}
			}
		}
	}
	return isReleased;
}

}
