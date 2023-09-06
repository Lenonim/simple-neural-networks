#pragma once

class DeltaPerceptron { // for y = kx + b
private:
	double rate;
	double epochs;

	double Wx; // this is k
	double Wb; // this is b

public:
	void fit(double* x, double* y, size_t size) {
		for (size_t e = 0; e < epochs; e++) {
			double y_answ;
			double y_real;
			double delta;

			for (size_t i = 0; i < size; i++) {
				y_answ = Wx * x[i] + Wb;
				y_real = y[i];
				
				delta = y_real - y_answ;
				
				Wx = delta * x[i] * rate;
				Wb = delta * rate;
			}
		}
	};
	
	double calculate(double x) {
		return Wx * x + Wb;
	};
	double* calculate(double* x, size_t size) {
		double* y;
		this->calculate(x, y, size);
		return y;
	};
	void calculate(double* x, double* y, size_t size) {
		for (size_t i = 0; i < size; i++)
			y[i] = this->calculate(x[i]);
	};

	void show_params() {
		std::cout << "\ny = "<< Wx << " * x + " << Wb << "\n";
	}

	DeltaPerceptron(double epochs, double rate) {
		this->rate = rate;
		this->epochs = epochs;
	}
};
