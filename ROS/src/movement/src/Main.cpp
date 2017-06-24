#include <BodyIK.h>

BodyIk Hexa;

void main()
{
	Hexa.Coxa = 12;
	Hexa.Femur = 35;
	Hexa.Tibia = 72;
	Hexa.BodySideLength = 80;
	Hexa.calibration();
	Hexa.clacHexaBodyIK(5, 5, 5,5,5,5);

	/*
	for (int j = 0; j < 6; j++)
	{
	for (vec_float::iterator i = Hexa.IKangles[j].begin(); i != Hexa.IKangles[j].end(); i++)
	{
	std::cout << *(i) << "\n";
	}

	}



	int x;
	std::cin >> x;*/

}