#pragma once
#include <vector>
#include "CircularSectorMesh.hpp"
#include "Pawn.h"

class PawnRenderer
{

public:

	const float eyelashesAngle = 5.0f;

	PawnRenderer ();

	~PawnRenderer ();

	void appendPawns (const std::vector<const Pawn*> pawns);

	void clear ();

	const std::vector<float>& getVertexBuffer () const;

	const std::vector<int>& getIndexBuffer () const;

private:

	std::vector<float> vertexBuffer;
	std::vector<int> indexBuffer;
	const CircularSectorMesh hsphereMesh;

	void appendPawn (const Pawn& pawn, const CircularSectorMesh &mesh);

};

