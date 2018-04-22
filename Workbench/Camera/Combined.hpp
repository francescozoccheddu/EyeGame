#pragma once

#include "Projection.hpp"
#include "View.hpp"
#include "Cache.hpp"
#include <glm/mat4x4.hpp>

namespace Camera
{

class Combined
{

public:

	Projection projection;
	View view;

	glm::mat4x4 calc ();

	virtual ~Combined () = default;

};

class CachedCombined : public Cache
{
	
public:

	CachedProjection projection;
	CachedView view;

	void update_cache () override;

};

}