#pragma once
class Motor
{
private:
	double MVA = 100, Vn = 13.8, Ra = 0, Xd = 0.5, In = 1.0, Zb = 10;  //Base original
	double MVAN = 100, VbN = 13.8, RaN = 0, XdN = 0.1, IbN = 2.0, ZbN = 5; //Base nueva
public:
	Motor(double, double, double, double);
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

};
