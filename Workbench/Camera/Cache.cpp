#include "Cache.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Camera
{

const glm::mat4x4& Cache::get_cache () const
{
	return cache;
}

const float * Cache::get_cache_ptr () const
{
	return glm::value_ptr(cache);
}

}
