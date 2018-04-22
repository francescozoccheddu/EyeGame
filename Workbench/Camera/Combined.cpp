#include "Combined.hpp"

#include <glm/mat4x4.hpp>

namespace Camera
{

glm::mat4x4 Camera::Combined::calc ()
{
	return projection.calc () * view.calc ();
}

void CachedCombined::update_cache ()
{
	cache = projection.get_cache () * view.get_cache ();
}

}
