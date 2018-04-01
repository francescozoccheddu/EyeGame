#pragma once

class CircularSectorMesh
{
public:
	const int radialSegments;
	const int planarSubdivisions;
	const float sectorAngle;

	CircularSectorMesh (int radialSegments, float sectorAngle);
	CircularSectorMesh (int radialSegments, float sectorAngle, int planarSubdivisions);

	const float * getVertexBuffer () const;

	const int * getIndexBuffer () const;

	int getVertexFloatCount () const;

	int getVertexCount () const;

	size_t getVertexBufferSize () const;

	int getIndexCount () const;

	int getTrianglesCount () const;

	size_t getIndexBufferSize () const;

	int getVertexFloatCount (int radialSegments) const;

	int getVertexCount (int radialSegments) const;

	size_t getVertexBufferSize (int radialSegments) const;

	int getIndexCount (int radialSegments) const;

	int getTrianglesCount (int radialSegments) const;

	size_t getIndexBufferSize (int radialSegments) const;

	virtual ~CircularSectorMesh ();

private:
	float * const vertices;
	int * const indices;

};

