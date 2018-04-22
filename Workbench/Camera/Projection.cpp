#include "Projection.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Camera
{

void Projection::set_aspect (int _w, int _h)
{
	aspect = _w / static_cast<float>(_h);
}

glm::mat4x4 Projection::calc () const
{
	return glm::perspective (fov, aspect, near_plane, far_plane);
}

void CachedProjection::update_cache ()
{
	cache = calc ();
}

}
