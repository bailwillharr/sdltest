#include <string>

namespace engine::resource {

class Resource {

public:
	Resource(const std::string& name) {}
	Resource(const Resource&) = delete;
	Resource& operator=(const Resource&) = delete;
	~Resource() = default;

private:


};

}
