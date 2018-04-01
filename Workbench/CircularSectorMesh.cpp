#include "CircularSectorMesh.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <stdexcept>

CircularSectorMesh::CircularSectorMesh (int radialSegments, float sectorAngle)
	: CircularSectorMesh (radialSegments, sectorAngle, radialSegments) {}

CircularSectorMesh::CircularSectorMesh (int radialSegments, float sectorAngle, int planarSubdivisions)
	: radialSegments{ radialSegments }, planarSubdivisions{ planarSubdivisions }, sectorAngle{ sectorAngle},
	vertices{ new float[getVertexFloatCount ()] }, indices{ new int[getIndexCount ()] }
{
	if (radialSegments <= 0)
	{
		throw std::runtime_error ("Radial segment number must be > 0");
	}

	int vi = 0;
	vertices[vi++] = -1.0f;
	vertices[vi++] = 0.0f;
	vertices[vi++] = 0.0f;
	vertices[vi++] = 1.0f;
	vertices[vi++] = 0.0f;
	vertices[vi++] = 0.0f;

	const double angleFactor = (sectorAngle * M_PI / 180.0) / radialSegments;
	for (int a = 0; a <= radialSegments; a++)
	{
		double angle = a * angleFactor;
		for (int s = 0; s < planarSubdivisions; s++)
		{
			double sx = ((s * 2) - (planarSubdivisions - 1)) / static_cast<double>(planarSubdivisions);
			double sr = sqrt (1.0 - sx * sx);
			vertices[vi++] = static_cast<float>(sx);
			vertices[vi++] = static_cast<float>(sin (angle) * sr);
			vertices[vi++] = static_cast<float>(cos (angle) * sr);
		}
	}

	int ii = 0;
	for (int a = 1; a <= radialSegments; a++)
	{
		indices[ii++] = 0;
		indices[ii++] = a * planarSubdivisions + 2;
		indices[ii++] = (a-1) * planarSubdivisions + 2;
		for (int s = 1; s < planarSubdivisions; s++)
		{
			indices[ii++] = a * planarSubdivisions + s + 1;
			indices[ii++] = a * planarSubdivisions + s + 2;
			indices[ii++] = (a - 1) * planarSubdivisions + s + 1;
			indices[ii++] = a * planarSubdivisions + s + 2;
			indices[ii++] = (a - 1) * planarSubdivisions + s + 2;
			indices[ii++] = (a - 1) * planarSubdivisions + s + 1;
		}
		indices[ii++] = (a + 1) * planarSubdivisions + 1;
		indices[ii++] = 1;
		indices[ii++] = a * planarSubdivisions + 1;
	}
}

const float * CircularSectorMesh::getVertexBuffer () const
{
	return vertices;
}

const int * CircularSectorMesh::getIndexBuffer () const
{
	return indices;
}

int CircularSectorMesh::getVertexFloatCount () const
{
	return getVertexFloatCount (radialSegments);
}

int CircularSectorMesh::getVertexCount () const
{
	return getVertexCount (radialSegments);
}

size_t CircularSectorMesh::getVertexBufferSize () const
{
	return getVertexBufferSize (radialSegments);
}

int CircularSectorMesh::getIndexCount () const
{
	return getIndexCount (radialSegments);
}

int CircularSectorMesh::getTrianglesCount () const
{
	return getTrianglesCount (radialSegments);
}

size_t CircularSectorMesh::getIndexBufferSize () const
{
	return getIndexBufferSize (radialSegments);
}

int CircularSectorMesh::getVertexFloatCount (int radialSegments) const
{
	return 3 * getVertexCount(radialSegments);
}

int CircularSectorMesh::getVertexCount (int radialSegments) const
{
	return (radialSegments + 1) * planarSubdivisions + 2;
}

size_t CircularSectorMesh::getVertexBufferSize (int radialSegments) const
{
	return sizeof (float) * getVertexFloatCount (radialSegments);
}

int CircularSectorMesh::getIndexCount (int radialSegments) const
{
	return 3 * getTrianglesCount (radialSegments);
}

int CircularSectorMesh::getTrianglesCount (int radialSegments) const
{
	return radialSegments * (planarSubdivisions - 1) * 2 + 2 * radialSegments;
}

size_t CircularSectorMesh::getIndexBufferSize (int radialSegments) const
{
	return sizeof (int) * getIndexCount (radialSegments);
}


CircularSectorMesh::~CircularSectorMesh ()
{
	delete[] vertices;
	delete[] indices;
}
