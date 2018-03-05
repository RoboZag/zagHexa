#ifndef _TYPES_H_
#define _TYPES_H_

typedef struct bodySpecifications
{
	float Coxa;						// in mm
	float Femur;					// in mm
	float Tibia;					// in mm
	float BodySideLength;
	float BodyCenterOffset1;
	float BodyCenterOffset2;
}bodySpecifications_t;
typedef struct bodyParameters
{
	float IKanglesi[18];
	float Bodyi[18];
	float feetpos[4];
	float angle[3];
	int	  refangle[18];
	int   velocity;
}bodyParameters_t;

#endif