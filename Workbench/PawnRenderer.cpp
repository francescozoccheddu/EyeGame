#include "PawnRenderer.h"
#include <vector>
#include <algorithm>
#include "CircularSectorMesh.hpp"
#include "Pawn.h"


PawnRenderer::PawnRenderer () : hsphereMesh (24, 180.0f)
{

}


PawnRenderer::~PawnRenderer ()
{
}

void PawnRenderer::appendPawns (const std::vector<const Pawn*> pawns)
{
	for (const Pawn *pawn : pawns)
	{
		appendPawn (*pawn, hsphereMesh);
	}
}

void PawnRenderer::appendPawn (const Pawn & pawn, const CircularSectorMesh &mesh)
{
	float sectorAngle = 180.0f - pawn.getEyeAngle () / 2.0f;
	int meshSegments = static_cast<int>(sectorAngle / (180.0f / mesh.radialSegments));
	std::copy (mesh.getVertexBuffer (), mesh.getVertexBuffer () + mesh.getVertexFloatCount (meshSegments), std::back_inserter (vertexBuffer));
	std::copy (mesh.getIndexBuffer (), mesh.getIndexBuffer () + mesh.getIndexCount (meshSegments), std::back_inserter (indexBuffer));
}

void PawnRenderer::clear ()
{
	vertexBuffer.clear ();
	indexBuffer.clear ();
}

const std::vector<float>& PawnRenderer::getVertexBuffer () const
{
	return vertexBuffer;
}

const std::vector<int>& PawnRenderer::getIndexBuffer () const
{
	return indexBuffer;
}
