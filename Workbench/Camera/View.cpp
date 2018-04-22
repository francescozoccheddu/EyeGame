#include "View.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Camera
{

void View::clamp_rotation_angles ()
{

}

glm::quat View::calc_rotation () const
{
	return glm::quat{ glm::vec3{ look_up, turn, tilt } };
}

glm::mat4x4 View::calc (const glm::vec3 & _forward, const glm::vec3 & _up) const
{
	return glm::lookAt (position, position + _forward, _up);
}

glm::mat4x4 View::calc (const glm::quat& _rot) const
{
	glm::vec3 rot_forward = calc_forward (_rot);
	glm::vec3 rot_up = calc_up (_rot);
	return calc (rot_forward, rot_up);
}

glm::mat4x4 View::calc () const
{
	return calc (calc_rotation ());
}

glm::vec3 View::calc_forward (const glm::quat & _rot) const
{
	return _rot * unr_forward;
}

glm::vec3 View::calc_up (const glm::quat & _rot) const
{
	return _rot * unr_up;
}

glm::vec3 View::calc_right (const glm::quat & _rot) const
{
	return _rot * glm::cross (unr_forward, unr_up);
}

void CachedView::update_cache ()
{
	const glm::quat rotation = calc_rotation ();
	cached_forward = calc_forward (rotation);
	cached_up = calc_up (rotation);
	cache = calc (cached_forward, cached_up);
}

glm::vec3 CachedView::get_cached_forward () const
{
	return cached_forward;
}

glm::vec3 CachedView::get_cached_up () const
{
	return cached_up;
}

glm::vec3 CachedView::get_cached_right () const
{
	return glm::cross (cached_forward, cached_up);
}

void CachedView::move_towards_cached_dirs (const glm::vec3 & _dir)
{
	if (_dir.z != 0.0f)
	{
		position += cached_forward * _dir.z;
	}
	if (_dir.y != 0.0f)
	{
		position += cached_up * _dir.y;
	}
	if (_dir.x != 0.0f)
	{
		position += get_cached_right () * _dir.x;
	}
}

}
