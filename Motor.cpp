#include "Motor.h"
#include <cmath>

Motor::Motor(double _MVA, double _Vn, double _Xd, double _Ra) //Constructor 1
{
	MVA = _MVA;
	Vn = _Vn;
	Xd = _Xd;
	Ra = _Ra;
	In = MVA / (sqrt(3) * Vn);
	Zb = pow(Vn, 2) / MVA;
}

void Motor::setBaseNueva(double _MVAN, double _VnN) //Set para base nueva
{
	MVAN = _MVAN;
	VbN = _VnN;
	IbN = MVAN / (sqrt(3) * VbN);
	ZbN = pow(VbN, 2) / MVAN;
	RaN = Ra * (MVAN / MVA) * pow((Vn / VbN), 2);
	XdN = Xd * (MVAN / MVA) * pow((Vn / VbN), 2);
}

double Motor::getMVA() //Geter para MVA
{
	return MVA;
}

double Motor::getVn() //Geter para Vn
{
	return Vn;
}

double Motor::getXd() //Geter para Xd
{
	return Xd;
}

double Motor::getRa() //Geter para Ra
{
	return Ra;
}

double Motor::getIn() //Geter para In
{
	return In;
}

double Motor::getZb() //Geter para Zbase
{
	return Zb;
}

double Motor::getMVAN() //Geter para MVA nuevo
{
	return MVAN;
}

double Motor::getVbN() //Geter para Vbase nuevo
{
	return VbN;
}

double Motor::getXdN() //Geter para Xd nueva
{
	return XdN;
}

double Motor::getRaN() //Geter para Ra nueva
{
	return RaN;
}

double Motor::getIbN() //Geter para Ibase nueva 
{
	return IbN;
}

double Motor::getZbN() //Geter para Zbase nueva
{
	return ZbN;
}
