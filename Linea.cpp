#include "Linea.h"
#include <cmath>

Linea::Linea(double _MVAb, double _Vb, double _XL, double _RL)
{
	MVAb = _MVAb;
	Vb = _Vb;
	RL = _RL;
	XL = _XL;
	Zb = pow(Vb, 2) / MVAb;
	Ib = MVAb / (sqrt(3) * Vb);
	Xpu = XL / Zb;
	Rpu = RL / Zb;
	ZL = std::complex <double>(RL, XL);
	ZLpu = ZL/Zb;
}

double Linea::getRL()
{
	return RL;
}

double Linea::getXL()
{
	return XL;
}

double Linea::getMVAb()
{
	return MVAb;
}

double Linea::getVb()
{
	return Vb;
}

double Linea::getZb()
{
	return Zb;
}

double Linea::getIb()
{
	return Ib;
}

double Linea::getXpu()
{
	return Xpu;
}

double Linea::getRpu()
{
	return Rpu;
}

std::complex<double> Linea::getZL()
{
	return ZL;
}

std::complex<double> Linea::getZLpu()
{
	return ZLpu;
}