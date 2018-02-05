#include "EyeMesh.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

CircularSectorMesh::CircularSectorMesh (int radialSubdivisions) : radialSubdivisions{ radialSubdivisions }, vertices{ new float[getFloatCount()] }
{
	int vi = 0;
	const int sc = getPlanarSubdivisions();
	for (int a = 0; a < radialSubdivisions; a++)
	{
		double angle = a * M_PI * 2.0 / radialSubdivisions;
		for (int s = 0; s < sc; s++)
		{
			double sx = ((s * 2) - (sc - 1)) / static_cast<double>(sc);
			double sr = sqrt (1.0 - sx * sx);
			vertices[vi++] = static_cast<float>(sx);
			vertices[vi++] = static_cast<float>(sin (angle) * sr);
			vertices[vi++] = static_cast<float>(cos (angle) * sr);
		}
	}
	vertices[vi++] = -1.0f;
	vertices[vi++] = 0.0f;
	vertices[vi++] = 0.0f;
	vertices[vi++] = 1.0f;
	vertices[vi++] = 0.0f;
	vertices[vi++] = 0.0f;
}

void CircularSectorMesh::update (float angle)
{

}

const float * CircularSectorMesh::get () const
{
	return vertices;
}

int CircularSectorMesh::getFloatCount () const
{
	return 3 * getVertexCount();
}

int CircularSectorMesh::getVertexCount () const
{
	return (radialSubdivisions + 1) * getPlanarSubdivisions() + 2;
}

size_t CircularSectorMesh::getBufferSize () const
{
	return sizeof (float) * getFloatCount ();
}


CircularSectorMesh::~CircularSectorMesh ()
{
	delete[] vertices;
}

int CircularSectorMesh::getPlanarSubdivisions () const
{
	return (radialSubdivisions - 1) / 2;
}
