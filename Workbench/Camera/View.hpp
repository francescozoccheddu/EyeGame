#pragma once

#include "Cache.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Camera
{

class View
{

public:

	glm::vec3 position{ 0.0f,0.0f,0.0f };

	float turn{ 0.0f };
	float look_up{ 0.0f };
	float tilt{ 0.0f };

	glm::vec3 unr_forward{ 0.0f,0.0f,1.0f };
	glm::vec3 unr_up{ 0.0f,1.0f,0.0f };

	virtual void clamp_rotation_angles ();

	glm::quat calc_rotation () const;

	virtual glm::mat4x4 calc (const glm::vec3& forward, const glm::vec3& up) const;

	glm::mat4x4 calc (const glm::quat& rotation) const;

	glm::mat4x4 calc () const;
	
	glm::vec3 calc_forward (const glm::quat& rotation) const;
	
	glm::vec3 calc_up (const glm::quat& rotation) const;

	glm::vec3 calc_right (const glm::quat& rotation) const;

	virtual ~View () = default;

};

class CachedView : public View, public Cache
{

public:

	void update_cache () override;

	glm::vec3 get_cached_forward () const;

	glm::vec3 get_cached_up () const;

	glm::vec3 get_cached_right () const;

	void move_towards_cached_dirs (const glm::vec3& direction);

protected:

	glm::vec3 cached_forward;
	glm::vec3 cached_up;

};

}
