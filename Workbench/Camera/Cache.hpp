#pragma once

#include <glm/mat4x4.hpp>

namespace Camera
{

class Cache
{

public:

	const glm::mat4x4& get_cache () const;

	const float * get_cache_ptr () const;

	virtual void update_cache () = 0;

	virtual ~Cache () = default;

protected:

	glm::mat4x4 cache;

};

}