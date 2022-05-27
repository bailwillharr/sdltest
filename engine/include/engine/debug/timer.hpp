#pragma once

#include <chrono>
#include <iostream>
#include <string>

struct Timer {

	std::string m_name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

	Timer(const std::string& name) : m_name(name)
	{
		m_start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - m_start;
		std::cerr << "Duration for " << m_name << ": " << duration.count() * 1000.0f << " ms\n";
	}
};
