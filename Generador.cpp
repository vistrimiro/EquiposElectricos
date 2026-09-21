#include "Generador.h"
#include <cmath>
#include <corecrt_math_defines.h>

Generador::Generador() {}

Generador::Generador(double _MVA, double _Vn, double _Xd, double _Ra) //Constructor 1
{
	MVA = _MVA;
	Vn = _Vn;
	Xd = _Xd;
	Ra = _Ra;
	In = MVA / (sqrt(3) * Vn);
	Zb = pow(Vn, 2) / MVA;
}

void Generador::setBaseNueva(double _MVAN, double _VnN) //Set para base nueva
{
	MVAN = _MVAN;
	VbN = _VnN;
	IbN = MVAN / (sqrt(3) * VbN);
	ZbN = pow(VbN, 2) / MVAN;
	RaN = Ra * (MVAN / MVA) * pow((Vn / VbN),2);
	XdN = Xd * (MVAN / MVA) * pow((Vn / VbN), 2);
}

void Generador::DiagVectorialGC(double _P, double _Q, double _V) 
{
	PO = _P/MVAN;
	QO = _Q/MVAN;
	VO = _V;
	VOpu = std::complex<double>(VO / VbN, 0.0);
	SOpu = std::complex <double>(PO, QO);
	IOpu = conj(SOpu / VOpu);
	VRpu = RaN * IOpu;
	Xpu = std::complex<double>(0.0, XdN);
	VXpu = Xpu * IOpu;
	EGpu = VOpu + VRpu + VXpu;

}

double Generador::getMVA() //Geter para MVA
{
	return MVA;
}

double Generador::getVn() //Geter para Vn
{
	return Vn;
}

double Generador::getXd() //Geter para Xd
{
	return Xd;
}

double Generador::getRa() //Geter para Ra
{
	return Ra;
}

double Generador::getIn() //Geter para In
{
	return In;
}

double Generador::getZb() //Geter para Zbase
{
	return Zb;
}

double Generador::getMVAN() //Geter para MVA nuevo
{
	return MVAN;
}

double Generador::getVbN() //Geter para Vbase nuevo
{
	return VbN;
}

double Generador::getXdN() //Geter para Xd nueva
{
	return XdN;
}

double Generador::getRaN() //Geter para Ra nueva
{
	return RaN;
}

double Generador::getIbN() //Geter para Ibase nueva 
{
	return IbN;
}

double Generador::getZbN() //Geter para Zbase nueva
{
	return ZbN;
}

std::complex <double> Generador::getVOpu()
{
	return VOpu;
}

std::complex<double> Generador::getIOpu()
{
	return IOpu;
}

std::complex<double> Generador::getVRpu()
{
	return VRpu;
}
std::complex<double> Generador::getVXpu()
{
	return VXpu;
}
std::complex<double> Generador::getEGpu()
{
	return EGpu;
}
