#pragma once

class non_copyable {

protected:
	non_copyable() = default;
	~non_copyable() = default;

	non_copyable(const non_copyable &) = delete;
	non_copyable& operator=(const non_copyable&) = delete;

};
