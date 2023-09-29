#pragma once

//#define BOOL_DATA_FOR_NETWORK
//#define BOOL_NEURO_LOGIC_OPERATORS
//#define INT_DATA_FOR_NETWORK
//#define INT_NEURO_LOGIC_OPERATORS

#define NOT !
#define UP = true
#define DOWN = false

class AbstractLogicPerceptron {
protected:
	float* Weigths;
	float learning_rate;

	bool** temp_train_data;
	bool* temp_etalons;

	bool number_to_bool(int x) {
		if (x == -1)
			return false;
		else if (x == 0)
			return true;
		else
			return bool(x);
	}

	void creat_temp_data(unsigned int size) {
		temp_train_data = new bool* [size];
		temp_etalons = new bool[size];
		for (size_t i = 0; i < size; i++) {
			temp_train_data[i] = new bool[2];
		}
	}

	void delete_temp_data(unsigned int size) {
		for (size_t i = 0; i < size; i++) {
			delete[] temp_train_data[i];
		}
		delete[] temp_train_data;
		delete[] temp_etalons;
	}

	virtual bool predict(bool a, bool b) = 0;
	virtual void train(bool**& train_data, bool*& etalons, unsigned int size) = 0;

public:
	virtual void fit(bool train_data[][2], bool etalons[], unsigned int size) = 0;
	virtual void fit(int train_data[][2], int etalons[], unsigned int size) = 0;
	virtual void fit(bool**& train_data, bool*& etalons, unsigned int size) = 0;
	virtual void fit(int**& train_data, int*& etalons, unsigned int size) = 0;

	bool operator ()(bool a, bool b) {
		return this->predict(a, b);
	}
	int operator ()(int a, int b) {
		if (this->predict(this->number_to_bool(a), this->number_to_bool(b)))
			return 1;
		else
			return -1;
	}

	AbstractLogicPerceptron(float learning_rate = 1) {
		this->Weigths = new float[2]{ 0 };
		this->learning_rate = learning_rate;
	}
	~AbstractLogicPerceptron() {
		if (this->Weigths != nullptr)
			delete[] this->Weigths;
	}
};

class ThresholdLogicPerceptron : public AbstractLogicPerceptron { 
	double threshold = 0;

	void train_weights(bool a, bool b, float delta) {
		this->Weigths[0] = this->Weigths[0] + float(a) * delta * this->learning_rate;
		this->Weigths[1] = this->Weigths[1] + float(b) * delta * this->learning_rate;
		this->threshold = this->threshold - delta * this->learning_rate;
	}

	float count_S(bool a, bool b) {
		return float(a) * this->Weigths[0] + float(b) * this->Weigths[1];
	}

	virtual bool predict(bool a, bool b) override {
		if (this->count_S(a, b) >= threshold)
			return true;
		else
			return false;
	};

	virtual void train(bool**& train_data, bool*& etalons, unsigned int size) override {
		bool error_flag = false;
		do {
			error_flag DOWN;
			for (int i = 0; i < size; i++) {
				bool answer = this->predict(train_data[i][0], train_data[i][1]);
				float delta = float(etalons[i]) - float(answer);
				if (delta != 0) {
					error_flag UP;
					this->train_weights(train_data[i][0], train_data[i][1], delta);
				}
			}
		} while (error_flag);
	}

public:
	virtual void fit(bool train_data[][2], bool etalons[], unsigned int size) override {
		this->creat_temp_data(size);
		for (size_t i = 0; i < size; i++) {
			temp_etalons[i] = etalons[i];
			for (size_t j = 0; j < 2; j++)
				temp_train_data[i][j] = train_data[i][j];
		}

		this->train(temp_train_data, temp_etalons, size);

		this->delete_temp_data(size);
	}
	virtual void fit(int train_data[][2], int etalons[], unsigned int size) override {
		this->creat_temp_data(size);
		for (size_t i = 0; i < size; i++) {
			temp_etalons[i] = number_to_bool(etalons[i]);
			for (size_t j = 0; j < 2; j++)
				temp_train_data[i][j] = number_to_bool(train_data[i][j]);
		}

		this->train(temp_train_data, temp_etalons, size);

		this->delete_temp_data(size);
	}

	virtual void fit(bool**& train_data, bool*& etalons, unsigned int size) {
		this->train(train_data, etalons, size);
	};
	virtual void fit(int**& train_data, int*& etalons, unsigned int size) {
		this->creat_temp_data(size);
		for (size_t i = 0; i < size; i++) {
			temp_etalons[i] = number_to_bool(etalons[i]);
			for (size_t j = 0; j < 2; j++)
				temp_train_data[i][j] = number_to_bool(train_data[i][j]);
		}

		this->train(temp_train_data, temp_etalons, size);

		this->delete_temp_data(size);
	};

	ThresholdLogicPerceptron(float learning_rate = 1) : AbstractLogicPerceptron(learning_rate) {}
	ThresholdLogicPerceptron(bool train_data[][2], bool etalons[], unsigned int size, float learning_rate = 1) : AbstractLogicPerceptron(learning_rate) {
		this->fit(train_data, etalons, size);
	}
	ThresholdLogicPerceptron(int train_data[][2], int etalons[], unsigned int size, float learning_rate = 1) : AbstractLogicPerceptron(learning_rate) {
		this->fit(train_data, etalons, size);
	}
	ThresholdLogicPerceptron(bool**& train_data, bool*& etalons, unsigned int size, float learning_rate = 1) : AbstractLogicPerceptron(learning_rate) {
		this->fit(train_data, etalons, size);
	}
	ThresholdLogicPerceptron(int**& train_data, int*& etalons, unsigned int size, float learning_rate = 1) : AbstractLogicPerceptron(learning_rate) {
		this->fit(train_data, etalons, size);
	}
};

class SignalLogicPerceptron : public AbstractLogicPerceptron {
	float* Biases;

	float first_predict;
	float second_predict;

	void delete_weigths_and_biases() {
		if (this->Weigths != nullptr) {
			delete[] this->Weigths;
			this->Weigths = nullptr;
		}
		if (this->Biases != nullptr) {
			delete[] this->Biases;
			this->Biases = nullptr;
		}
	}

	void create_weigths_and_biases() {
		srand(time(NULL));

		int size_of_weights = 6;
		this->Weigths = new float[size_of_weights];
		for (size_t i = 0; i < size_of_weights; i++) {
			//this->Weigths[i] = float(rand() % 11) / 10;
			this->Weigths[i] = 0.5;
		}

		int size_of_biases = size_of_weights / 2;
		this->Biases = new float[size_of_biases] { 0 };
	}

	void train_weights(bool x, bool y, float de_dpr) {
		float de_dfp = this->Weigths[4] * de_dpr;
		float de_dsp = this->Weigths[5] * de_dpr;

		// ошибка по выходу 
		this->Weigths[4] = this->Weigths[4] - first_predict * de_dpr * this->learning_rate;
		this->Weigths[5] = this->Weigths[5] + second_predict * de_dpr * this->learning_rate;
		this->Biases[2] = this->Biases[2] + de_dpr * this->learning_rate;

		// ошибка по первому нейрону
		this->Weigths[0] = this->Weigths[0] - float(x) * de_dfp * this->learning_rate;
		this->Weigths[1] = this->Weigths[1] - float(y) * de_dfp * this->learning_rate;
		this->Biases[0] = this->Biases[0] + de_dfp * this->learning_rate;

		// ошибка по второму нейрону
		this->Weigths[2] = this->Weigths[2] + float(y) * de_dsp * this->learning_rate;
		this->Weigths[3] = this->Weigths[3] + float(x) * de_dsp * this->learning_rate;
		this->Biases[1] = this->Biases[1] - de_dsp * this->learning_rate;
	}

	float count_S(float a, float b, int i, int j, int k ) {
		return a * Weigths[i] + b * Weigths[j] + Biases[k];
	}

	virtual bool predict(bool a, bool b) override {
		// первый нейрон
		first_predict = count_S((float)a, (float)b, 0, 1, 0);
		// второй нейрон
		second_predict = count_S((float)a, (float)b, 3, 2, 1);
		// выходной нейрон
		float result_predict = count_S(first_predict, second_predict, 4, 5, 2);
		//// выход
		if (result_predict >= 0)
			return true;
		else 
			return false;
	};

	virtual void train(bool**& train_data, bool*& etalons, unsigned int size) override {
		this->delete_weigths_and_biases();
		this->create_weigths_and_biases();

		bool error_flag = false;
		do {
			error_flag DOWN;
			for (int i = 0; i < size; i++) {
				bool answer = this->predict(train_data[i][0], train_data[i][1]);
				float delta = float(etalons[i]) - float(answer);
				if (delta != 0) {
					error_flag UP;
					this->train_weights(train_data[i][0], train_data[i][1], delta);
				}
			}
		} while (error_flag);
	}

public:
	virtual void fit(bool train_data[][2], bool etalons[], unsigned int size) override {
		this->creat_temp_data(size);
		for (size_t i = 0; i < size; i++) {
			temp_etalons[i] = etalons[i];
			for (size_t j = 0; j < 2; j++)
				temp_train_data[i][j] = train_data[i][j];
		}

		this->train(temp_train_data, temp_etalons, size);

		this->delete_temp_data(size);
	}
	virtual void fit(int train_data[][2], int etalons[], unsigned int size) override {
		this->creat_temp_data(size);
		for (size_t i = 0; i < size; i++) {
			temp_etalons[i] = number_to_bool(etalons[i]);
			for (size_t j = 0; j < 2; j++)
				temp_train_data[i][j] = number_to_bool(train_data[i][j]);
		}

		this->train(temp_train_data, temp_etalons, size);

		this->delete_temp_data(size);
	}

	virtual void fit(bool**& train_data, bool*& etalons, unsigned int size) {
		this->train(train_data, etalons, size);
	};
	virtual void fit(int**& train_data, int*& etalons, unsigned int size) {
		this->creat_temp_data(size);
		for (size_t i = 0; i < size; i++) {
			temp_etalons[i] = number_to_bool(etalons[i]);
			for (size_t j = 0; j < 2; j++)
				temp_train_data[i][j] = number_to_bool(train_data[i][j]);
		}

		this->train(temp_train_data, temp_etalons, size);

		this->delete_temp_data(size);
	};

	SignalLogicPerceptron(float learning_rate = 0.1) : AbstractLogicPerceptron(learning_rate) {
		this->delete_weigths_and_biases();
	}
	SignalLogicPerceptron(bool train_data[][2], bool etalons[], unsigned int size, float learning_rate = 0.1) : AbstractLogicPerceptron(learning_rate) {
		this->delete_weigths_and_biases();
		this->fit(train_data, etalons, size);
	}
	SignalLogicPerceptron(int train_data[][2], int etalons[], unsigned int size, float learning_rate = 0.1) : AbstractLogicPerceptron(learning_rate) {
		this->delete_weigths_and_biases();
		this->fit(train_data, etalons, size);
	}
	SignalLogicPerceptron(bool**& train_data, bool*& etalons, unsigned int size, float learning_rate = 0.1) : AbstractLogicPerceptron(learning_rate) {
		this->delete_weigths_and_biases();
		this->fit(train_data, etalons, size);
	}
	SignalLogicPerceptron(int**& train_data, int*& etalons, unsigned int size, float learning_rate = 0.1) : AbstractLogicPerceptron(learning_rate) {
		this->delete_weigths_and_biases();
		this->fit(train_data, etalons, size);
	}
	~SignalLogicPerceptron() {
		this->delete_weigths_and_biases();
	}
};


#ifdef BOOL_DATA_FOR_NETWORK

const int SIZE = 4;
const int SIZE_POINT_PAIR = 2;

bool points_data[SIZE][SIZE_POINT_PAIR] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };

// Threshold (14 функций)
bool NO_etalons[SIZE] = { 0, 0, 0, 0 }; // логическая функция лжи
bool AND_etalons[SIZE] = { 0, 0, 0, 1 }; // логическое и (конъюнкция)
bool NIMP_etalons[SIZE] = { 0, 0, 1, 0 }; // обратная негация 
bool FIRST_etalons[SIZE] = { 0, 0, 1, 1 }; // логическая функция первого аргумента
bool NRIMP_etalons[SIZE] = { 0, 1, 0, 0 }; // обратная негация 
bool SECOND_etalons[SIZE] = { 0, 1, 0, 1 }; // логическая функция второго аргумента
bool OR_etalons[SIZE] = { 0, 1, 1, 1 }; // логическое или (дизъюнкция)
bool PIRS_etalons[SIZE] = { 1, 0, 0, 0 }; // стрелка Пирса
bool NFIRST_etalons[SIZE] = { 1, 1, 0, 0 }; // логическая функция первого аргумента
bool NSECOND_etalons[SIZE] = { 1, 0, 1, 0 }; // логическая функция второго аргумента
bool RIMP_etalons[SIZE] = { 1, 0, 1, 1 }; // обратная импликация
bool IMP_etalons[SIZE] = { 1, 1, 0, 1 }; // импликация
bool SHEFFER_etalons[SIZE] = { 1, 1, 1, 0 }; // стрелка Шеффера
bool YES_etalons[SIZE] = { 1, 1, 1, 1 }; // логическая функция правды

// Signal (2 функции)
bool XOR_etalons[SIZE] = { 0, 1, 1, 0 }; // исключающее или
bool EQ_etalons[SIZE] = { 1, 0, 0, 1 }; // логическая эквиваленция

#ifdef BOOL_NEURO_LOGIC_OPERATORS

static ThresholdLogicPerceptron NO(points_data, NO_etalons, SIZE);
static ThresholdLogicPerceptron AND(points_data, AND_etalons, SIZE);
static ThresholdLogicPerceptron NIMP(points_data, NIMP_etalons, SIZE);
static ThresholdLogicPerceptron FIRST(points_data, FIRST_etalons, SIZE);
static ThresholdLogicPerceptron NRIMP(points_data, NRIMP_etalons, SIZE);
static ThresholdLogicPerceptron SECOND(points_data, SECOND_etalons, SIZE);
static ThresholdLogicPerceptron OR(points_data, OR_etalons, SIZE);
static ThresholdLogicPerceptron PIRS(points_data, PIRS_etalons, SIZE);
static ThresholdLogicPerceptron NFIRST(points_data, NFIRST_etalons, SIZE);
static ThresholdLogicPerceptron NSECOND(points_data, NSECOND_etalons, SIZE);
static ThresholdLogicPerceptron RIMP(points_data, RIMP_etalons, SIZE);
static ThresholdLogicPerceptron IMP(points_data, IMP_etalons, SIZE);
static ThresholdLogicPerceptron SHEFFER(points_data, SHEFFER_etalons, SIZE);
static ThresholdLogicPerceptron YES(points_data, YES_etalons, SIZE);

static SignalLogicPerceptron XOR(points_data, XOR_etalons, SIZE);
static SignalLogicPerceptron EQ(points_data, EQ_etalons, SIZE);

#endif

#endif


#ifdef INT_DATA_FOR_NETWORK

const int SIZE = 4;
const int SIZE_POINT_PAIR = 2;

int points_data[SIZE][SIZE_POINT_PAIR] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

// Threshold (1SIZE функций)
int NO_etalons[SIZE] = { -1, -1, -1, -1 }; // логическая функция лжи
int AND_etalons[SIZE] = { -1, -1, -1, 1 }; // логическое и (конъюнкция)
int NIMP_etalons[SIZE] = { -1, -1, 1, -1 }; // обратная негация 
int FIRST_etalons[SIZE] = { -1, -1, 1, 1 }; // логическая функция первого аргумента
int NRIMP_etalons[SIZE] = { -1, 1, -1, -1 }; // обратная негация 
int SECOND_etalons[SIZE] = { -1, 1, -1, 1 }; // логическая функция второго аргумента
int OR_etalons[SIZE] = { -1, 1, 1, 1 }; // логическое или (дизъюнкция)
int PIRS_etalons[SIZE] = { 1, -1, -1, -1 }; // стрелка Пирса
int NFIRST_etalons[SIZE] = { 1, 1, -1, -1 }; // логическая функция первого аргумента
int NSECOND_etalons[SIZE] = { 1, -1, 1, -1 }; // логическая функция второго аргумента
int RIMP_etalons[SIZE] = { 1, -1, 1, 1 }; // обратная импликация
int IMP_etalons[SIZE] = { 1, 1, -1, 1 }; // импликация
int SHEFFER_etalons[SIZE] = { 1, 1, 1, -1 }; // стрелка Шеффера
int YES_etalons[SIZE] = { 1, 1, 1, 1 }; // логическая функция правды

// Signal (2 функции)
int XOR_etalons[SIZE] = { -1, 1, 1, -1 }; // исключающее или
int EQ_etalons[SIZE] = { 1, -1, -1, 1 }; // логическая эквиваленция

#ifdef INT_NEURO_LOGIC_OPERATORS

static ThresholdLogicPerceptron NO(points_data, NO_etalons, SIZE);
static ThresholdLogicPerceptron AND(points_data, AND_etalons, SIZE);
static ThresholdLogicPerceptron NIMP(points_data, NIMP_etalons, SIZE);
static ThresholdLogicPerceptron FIRST(points_data, FIRST_etalons, SIZE);
static ThresholdLogicPerceptron NRIMP(points_data, NRIMP_etalons, SIZE);
static ThresholdLogicPerceptron SECOND(points_data, SECOND_etalons, SIZE);
static ThresholdLogicPerceptron OR(points_data, OR_etalons, SIZE);
static ThresholdLogicPerceptron PIRS(points_data, PIRS_etalons, SIZE);
static ThresholdLogicPerceptron NFIRST(points_data, NFIRST_etalons, SIZE);
static ThresholdLogicPerceptron NSECOND(points_data, NSECOND_etalons, SIZE);
static ThresholdLogicPerceptron RIMP(points_data, RIMP_etalons, SIZE);
static ThresholdLogicPerceptron IMP(points_data, IMP_etalons, SIZE);
static ThresholdLogicPerceptron SHEFFER(points_data, SHEFFER_etalons, SIZE);
static ThresholdLogicPerceptron YES(points_data, YES_etalons, SIZE);

static SignalLogicPerceptron XOR(points_data, XOR_etalons, SIZE);
static SignalLogicPerceptron EQ(points_data, EQ_etalons, SIZE);

#endif

#endif
