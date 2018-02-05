#pragma once

class CircularSectorMesh
{
public:
	const int radialSubdivisions;

	CircularSectorMesh (int radialSubdivisions);

	void update (float angle);

	const float * get () const;

	int getFloatCount () const;

	int getVertexCount () const;

	size_t getBufferSize () const;

	virtual ~CircularSectorMesh ();

private:
	float * const vertices;

	int getPlanarSubdivisions () const;

};

