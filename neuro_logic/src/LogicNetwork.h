#pragma once

#define DATA_FOR_NETWORK
#define NEURO_LOGIC_OPERATORS
#define NOT !
#define UP = true
#define DOWN = false

#include "dataset.h"

class AbstractLogicPerceptron {
protected:
	float* Weigths = nullptr;

	float count_S(bool a, bool b) {
		return float(a) * this->Weigths[0] + float(b) * this->Weigths[1];
	}
	virtual bool predict(bool a, bool b) = 0;

public:
	virtual void fit(const bool train_data[][2], const bool etalons[]) = 0;

	bool operator ()(bool a, bool b) {
		return this->predict(a, b);
	}

	AbstractLogicPerceptron() {
		this->Weigths = new float[2]{ 0 };
	}
	~AbstractLogicPerceptron() {
		if (this->Weigths != nullptr)
			delete[] this->Weigths;
	}
};

class ThresholdLogicPerceptron : public AbstractLogicPerceptron { 
	double threshold = 0;

	virtual bool predict(bool a, bool b) override {
		if (this->count_S(a, b) >= threshold)
			return true;
		else
			return false;
	};

public:
	virtual void fit(const bool train_data[][2], const bool etalons[]) override {
		bool error_flag = false;
		bool answer;
		float delta;
		float temp_multer;
		do {
			error_flag DOWN;
			for (int i = 0; i < 4; i++) {
				answer = this->predict(train_data[i][0], train_data[i][1]);
				delta = float(etalons[i]) - float(answer);
				if (delta != 0) {
					error_flag UP;

					this->Weigths[0] = this->Weigths[0] + (float)train_data[i][0] * delta;
					this->Weigths[1] = this->Weigths[1] + (float)train_data[i][1] * delta;

					this->threshold = this->threshold - delta;
				}
			}
		} while (error_flag);
	}

	ThresholdLogicPerceptron() : AbstractLogicPerceptron() {}
	ThresholdLogicPerceptron(const bool train_data[][2], const bool etalons[]) {
		this->fit(train_data, etalons);
	}
};

class SignalLogicPerceptron : public AbstractLogicPerceptron {
	double bottom_threshold = 0.5;
	double top_threshold = this->bottom_threshold + 0.5;
	
	bool is_backward_activation;

	bool forward_activate_functin(bool a, bool b) {
		if (this->count_S(a, b) >= bottom_threshold && this->count_S(a, b) <= top_threshold)
			return true;
		else
			return false;
	}

	bool backward_activate_functin(bool a, bool b) {
		if (this->count_S(a, b) < bottom_threshold || this->count_S(a, b) > top_threshold)
			return true;
		else
			return false;
	}

	virtual bool predict(bool a, bool b) override {
		if (this->is_backward_activation)
			return backward_activate_functin(a, b);
		else
			return forward_activate_functin(a, b);
	};

public:
	virtual void fit(const bool train_data[][2], const bool etalons[]) override {
		bool error_flag = false;
		bool answer;
		float delta;
		do {
			error_flag DOWN;
			for (int i = 0; i < 4; i++) {
				answer = this->predict(train_data[i][0], train_data[i][1]);

				delta = float(etalons[i]) - float(answer);
				
				if (delta != 0) {
					error_flag UP;

					this->Weigths[0] = this->Weigths[0] + (float)train_data[i][0] * delta;
					this->Weigths[1] = this->Weigths[1] + (float)train_data[i][1] * delta;
					this->bottom_threshold = this->bottom_threshold - delta;
					this->top_threshold = this->top_threshold - delta;
				}
			}
		} while (error_flag);
	}

	SignalLogicPerceptron(bool backward_activation = false) : AbstractLogicPerceptron() {
		is_backward_activation = backward_activation;
	}
	SignalLogicPerceptron(const bool train_data[][2], const bool etalons[], bool backward_activation = false) {
		is_backward_activation = backward_activation;
		this->fit(train_data, etalons);
	}
};

#ifdef NEURO_LOGIC_OPERATORS

static ThresholdLogicPerceptron NO(points_data, NO_etalons);
static ThresholdLogicPerceptron AND(points_data, AND_etalons);
static ThresholdLogicPerceptron NIMP(points_data, NIMP_etalons);
static ThresholdLogicPerceptron FIRST(points_data, FIRST_etalons);
static ThresholdLogicPerceptron NRIMP(points_data, NRIMP_etalons);
static ThresholdLogicPerceptron SECOND(points_data, SECOND_etalons);
static ThresholdLogicPerceptron OR(points_data, OR_etalons);
static ThresholdLogicPerceptron PIRS(points_data, PIRS_etalons);
static ThresholdLogicPerceptron NFIRST(points_data, NFIRST_etalons);
static ThresholdLogicPerceptron NSECOND(points_data, NSECOND_etalons);
static ThresholdLogicPerceptron RIMP(points_data, RIMP_etalons);
static ThresholdLogicPerceptron IMP(points_data, IMP_etalons);
static ThresholdLogicPerceptron SHEFFER(points_data, SHEFFER_etalons);
static ThresholdLogicPerceptron YES(points_data, YES_etalons);

static SignalLogicPerceptron XOR(points_data, XOR_etalons, false);
static SignalLogicPerceptron EQ(points_data, EQ_etalons, true);

#endif
