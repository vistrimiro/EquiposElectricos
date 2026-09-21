#pragma once
class Transformador
{
private:
	double MVA = 10, VnA = 120, VnB = 2.4, Xt = 0.5, Rt = 0.05, InA = 1.0, InB = 10, ZbA = 10, ZbB = 5; //Bases originales
	double XtA = 1, RtA = 1, XtB = 1, RtB = 1;
	double MVAN = 20, VnAN = 100, VnBN = 2.0, XtN = 0.1, RtN = 0.01, IbAN = 0.8, IbBN = 8, ZbAN = 8, ZbBN = 4; //Bases nuevas
	double XtAN = 1, RtAN = 1, XtBN = 1, RtBN = 1;
public:
	Transformador(double, double, double, double, double); //Constructor 1
	double getMVA();
	double getVnA();
	double getVnB();
	double getXt();
	double getRt();
	double getInA();
	double getInB();
	double getZbA();
	double getZbB();
	double getXtA(), getRtA(), getXtB(), getRtB();
	void setBaseNueva(double, double, double);
	double getMVAN();
	double getVnAN();
	double getVnBN();
	double getXtN();
	double getRtN();
	double getIbAN();
	double getIbBN();
	double getZbAN();
	double getZbBN();
	double getXtAN(), getRtAN(), getXtBN(), getRtBN();
};

