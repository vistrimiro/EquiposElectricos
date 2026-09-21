#include "Carga.h"
#include <cmath>
#include <stdlib.h>
#include <corecrt_math_defines.h>

using namespace std;

Carga::Carga(double _PL, double _QL, double _VLn, double _Sbase, double _Vbase) {
	PL = _PL;
	QL = _QL;
	VLn = _VLn;
	Sbase = _Sbase;
	Vbase = _Vbase;
	Ibase = Sbase / (sqrt(3) * Vbase);
	Zbase = pow(Vbase, 2) / Sbase;
	VLnpu = VLn / Vbase;
	SL = std::complex <double> (PL, QL);
	MVASL = abs(SL);
	AngFP = arg(SL); // Angulo en radianes
	AngFPGr = AngFP*180/M_PI; // Angulo en grados
	FP = cos(AngFP);
	if (AngFP < 0) swprintf_s(tipoFP, 10, L"Adelanto");
	if (AngFP > 0) swprintf_s(tipoFP, 10, L"Atraso");
	if (AngFP == 0) swprintf_s(tipoFP, 10, L"Resistivo");
	IL = conj(SL/(sqrt(3)*VLn)); //Corriente nominal forma compleja
	SLpu = SL / Sbase;
	ILpu = IL / Ibase;
	ZL = VLn / (sqrt(3) * IL); //Impedancia equivalente ohm/fase
	ZLpu = ZL / Zbase; //Impedancia equivalente pu
}

double Carga::getPL()
{
	return PL;
}

double Carga::getQL()
{
	return QL;
}

double Carga::getVLn()
{
	return VLn;
}

double Carga::getSbase()
{
	return Sbase;
}

double Carga::getVbase()
{
	return Vbase;
}

double Carga::getIbase()
{
	return Ibase;
}

double Carga::getZbase()
{
	return Zbase;
}

double Carga::getVLnpu()
{
	return VLnpu;
}

complex<double> Carga::getSL()
{
	return SL;
}

double Carga::getMVASL()
{
	return MVASL;
}

double Carga::getAngFP()
{
	return AngFP;
}

double Carga::getAngFPGr()
{
	return AngFPGr;
}

double Carga::getFP()
{
	return FP;
}

const wchar_t* Carga::gettipoFP()
{
	return tipoFP;
}

std::complex<double> Carga::getIL()
{
	return IL;
}

std::complex<double> Carga::getSLpu()
{
	return SLpu;
}

std::complex<double> Carga::getILpu()
{
	return ILpu;
}

std::complex<double> Carga::getZL()
{
	return ZL;
}

std::complex<double> Carga::getZLpu()
{
	return ZLpu;
}
