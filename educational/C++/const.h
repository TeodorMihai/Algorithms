class Complex {
private:
	double im;
	double re;
public:
	Complex(double, double);
	double getRe() const;
	double getIm() const;
	void setRe(double);
	void setIm(double);
};
