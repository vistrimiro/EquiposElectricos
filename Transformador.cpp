#include "Transformador.h"
#include <cmath>

Transformador::Transformador(double _MVA, double _VnA, double _VnB, double _Xt, double _Rt) //Constructor 1
{
	MVA = _MVA;
	VnA = _VnA;
	VnB = _VnB;
	Xt = _Xt;
	Rt = _Rt;
	InA = MVA / (VnA * sqrt(3));
	InB = MVA / (VnB * sqrt(3));
	ZbA = pow(VnA, 2) / MVA;
	ZbB = pow(VnB, 2) / MVA;
	XtA = Xt * ZbA;
	RtA = Rt * ZbA;
	XtB = Xt * ZbB;
	RtB = Rt * ZbB;
}

void Transformador::setBaseNueva(double _MVAN, double _VnAN, double _VnBN)
{
	MVAN = _MVAN;
	VnAN = _VnAN;
	VnBN = _VnBN;
	XtN = Xt * (MVAN / MVA) * pow((VnA / VnAN), 2);
	RtN = Rt * (MVAN / MVA) * pow((VnA / VnAN), 2);
	IbAN = MVAN / (VnAN * sqrt(3));
	IbBN = MVAN / (VnBN * sqrt(3));
	ZbAN = pow(VnAN, 2) / MVAN;
	ZbBN = pow(VnBN, 2) / MVAN;
	XtAN = XtN * ZbAN;
	RtAN = RtN * ZbAN;
	XtBN = XtN * ZbBN;
	RtBN = RtN * ZbBN;
}

double Transformador::getMVA() //Geter para MVA
{
	return MVA;
}

double Transformador::getVnA() //Geter para voltaje de alta
{
	return VnA;
}

double Transformador::getVnB() //Geter para voltaje de baja
{
	return VnB;
}

double Transformador::getXt() //Geter para reactancia del transf en pu
{
	return Xt;
}

double Transformador::getRt() //Geter para resistencia del transf en pu
{
	return Rt;
}

double Transformador::getInA() //Geter para corriente de alta del transformador
{
	return InA;
}

double Transformador::getInB() //Geter para corriente de baja del transformador
{
	return InB;
}

double Transformador::getZbA() //Geter para Impedancia base de alta del transformador
{
	return ZbA;
}

double Transformador::getZbB() //Geter para Impedancia base de baja del transformador
{
	return ZbB;
}

double Transformador::getXtA() //Geter para XtA de alta en ohm del transformador
{
	return XtA;
}

double Transformador::getRtA() //Geter para RtA de alta en ohm del transformador
{
	return RtA;
}

double Transformador::getXtB() //Geter para XtB de baja en ohm del transformador
{
	return XtB;
}

double Transformador::getRtB() //Geter para RtB de baja en ohm del transformador
{
	return RtB;
}

double Transformador::getMVAN() //Geter para MVA nuevo
{
	return MVAN;
}

double Transformador::getVnAN() //Geter para voltaje de alta nuevo
{
	return VnAN;
}

double Transformador::getVnBN() //Geter para voltaje de baja nuevo
{
	return VnBN;
}

double Transformador::getXtN() //Geter para reactancia del transf en pu Nueva
{
	return XtN;
}

double Transformador::getRtN() //Geter para reactancia del transf en pu Nueva
{
	return RtN;
}

double Transformador::getIbAN() //Geter para corriente de alta del transformador Nueva base
{
	return IbAN;
}

double Transformador::getIbBN() //Geter para corriente de baja del transformador Nueva base
{
	return IbBN;
}

double Transformador::getZbAN() //Geter para Impedancia de alta del transformador Nueva base
{
	return ZbAN;
}

double Transformador::getZbBN() //Geter para Impedancia de baja del transformador Nueva base
{
	return ZbBN;
}

double Transformador::getXtAN() //Geter para XtAN de alta en ohm del transformador
{
	return XtAN;
}

double Transformador::getRtAN() //Geter para RtAN de alta en ohm del transformador
{
	return RtAN;
}

double Transformador::getXtBN() //Geter para XtBN de baja en ohm del transformador
{
	return XtBN;
}

double Transformador::getRtBN() //Geter para RtBN de baja en ohm del transformador
{
	return RtBN;
}
