#include "Pawn.h"



Pawn::Pawn () : eyeAngle{ 45.0f }
{
}


Pawn::~Pawn ()
{
}

float Pawn::getEyeAngle () const
{
	return eyeAngle;
}
