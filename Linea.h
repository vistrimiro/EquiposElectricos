#pragma once
#include <complex>

class Linea
{
private:
	double RL = 1, XL = 1; // en ohm
	double Rpu = 0.1, Xpu = 0.1; // en pu  (se calculan en el constructor)
	double MVAb = 10, Vb = 10, Zb = 10, Ib = 10; // Base ( se calcula Zb en el constructor)
	std::complex <double> ZL, ZLpu;
public:
	Linea(double, double, double, double);
	//void setBase(double, double); //Se asigna la base, se calcula Zb, Rpu y Xpu
	double getRL();
	double getXL();
	double getRpu();
	double getXpu();
	double getMVAb();
	double getVb();
	double getZb();
	double getIb();
	std::complex<double> getZL();
	std::complex<double> getZLpu();
};

