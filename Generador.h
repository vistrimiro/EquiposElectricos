#pragma once
#include <complex>
#include <string>

class Generador
{
private:
	double MVA = 100, Vn = 13.8, Ra = 0, Xd = 0.5, In = 1.0, Zb = 10;  //Base original
	double MVAN = 100, VbN = 13.8, RaN = 0, XdN=0.1, IbN=2.0, ZbN = 5; //Base nueva
	double PO = 0.8 * MVA, QO = 0.6 * MVA, VO = Vn;// Condiciones de operacion
	std::complex<double> SOpu, IOpu, VRpu, Xpu, VXpu, EGpu, VOpu; // Variables de operacion en pu
public:
	Generador();
	Generador(double, double, double, double);
	void setBaseNueva(double, double);
	double getMVA();
	double getVn();
	double getXd();
	double getRa();
	double getIn();
	double getZb();
	double getMVAN();
	double getVbN();
	double getXdN();
	double getRaN();
	double getIbN();
	double getZbN();
	void DiagVectorialGC(double, double, double);
	std::complex<double> getVOpu();
	std::complex<double> getIOpu();
	std::complex<double> getVRpu();
	std::complex<double> getVXpu();
	std::complex<double> getEGpu();
};


