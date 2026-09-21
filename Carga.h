#pragma once
#include <complex>
#include <string>

class Carga
{
private:
	double PL = 8.0, QL = 6.0, VLn = 120, Sbase = 100, Vbase = 120, Ibase = 10, Zbase = 20;
	double FP = 0.5, AngFP = 0.5, AngFPGr = 30, MVASL = 10, VLnpu = 1.0;
	wchar_t tipoFP[10] = L"ade";
	std::complex<double> SL, IL, SLpu, ILpu, ZL, ZLpu;
	
public:
	Carga(double _PL, double _QL, double _VLn, double _Sbase, double _Vbase);
	double getPL();
	double getQL();
	double getVLn();
	double getSbase();
	double getVbase();
	double getIbase();
	double getZbase();
	double getVLnpu();
	std::complex<double> getSL();
	double getMVASL();
	double getAngFP();
	double getAngFPGr();
	double getFP();
	const wchar_t* gettipoFP();
	std::complex<double> getIL();
	std::complex<double> getSLpu();
	std::complex<double> getILpu();
	std::complex<double> getZL();
	std::complex<double> getZLpu();
};

