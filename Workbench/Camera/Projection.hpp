#pragma once

#include "Cache.hpp"
#include <glm/mat4x4.hpp>

namespace Camera
{

class Projection
{

public:

	float fov{ 1.5708f };
	float near_plane{ 1.0f };
	float far_plane{ 100.0f };
	float aspect{ 1.0f };

	void set_aspect (int viewport_width, int viewport_height);

	virtual glm::mat4x4 calc () const;

	virtual ~Projection () = default;

};

class CachedProjection : public Projection, public Cache
{

public:

	void update_cache () override;

};

}
