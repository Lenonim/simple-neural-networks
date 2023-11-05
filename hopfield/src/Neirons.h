#pragma once
#include "DataSets.h"
#include <ctime>
#include <vector>
#include <algorithm>

using std::begin;
using std::find;
using std::end;

size_t count_differences(double* fir_arr, double* sec_arr, size_t size) {
    size_t differences = 0;
    for (size_t i = 0; i < size; i++)
        if (fir_arr[i] != sec_arr[i])
            differences++;
    return differences;
}

class Hopfield {
    double memory_range;
    double memory_save;
    double predict_iterator = 0;

    double** W;

    double activate(double x) {
        if (x > 0)
            return 1;
        else if (x < 0)
            return -1;
        else
            return x;
    }

public:
    double count_energy(double* input_data) {
        double enegry = 0;
        for (size_t i = 0; i < this->memory_range; i++)
            for (size_t j = 0; j < this->memory_range; j++)
                enegry += W[i][j] * input_data[i] * input_data[j];
        enegry *= -0.5;
        return enegry;
    }
    double get_capacity() {
        return this->memory_save / this->memory_range;
    }
    double get_input_range() {
        return this->memory_range;
    }
    double get_max_capasity() {
        return this->memory_range / (4.0 * std::log(this->memory_range));
    }

    void save(double* data) {
        double** temp_W = new double* [this->memory_range];
        for (size_t i = 0; i < this->memory_range; i++) 
            temp_W[i] = new double[this->memory_range] {0};

        for (size_t i = 0; i < this->memory_range; i++)
            for (size_t j = 0; j < this->memory_range; j++)
                temp_W[i][j] = data[i] * data[j]; 
        for (size_t i = 0; i < this->memory_range; i++)
            temp_W[i][i] = 0;
   
        for (size_t i = 0; i < this->memory_range; i++)
            for (size_t j = 0; j < this->memory_range; j++)
                W[i][j] += temp_W[i][j] / this->memory_range;

        this->memory_save += 1;

        for (size_t i = 0; i < memory_range; i++)
            delete[] temp_W[i];
        delete[] temp_W;
    }

    double* predict(double* data, bool is_auto = false) {
        double* answer = new double[this->memory_range] {0};
        for (size_t i = 0; i < this->memory_range; i++) {
            for (size_t j = 0; j < this->memory_range; j++) 
                answer[i] += W[i][j] * data[j];
            answer[i] = this->activate(answer[i]);
            if (answer[i] == 0)
                answer[i] = data[i];
        }   

        if (is_auto)
            if (count_differences(data, answer, this->memory_range))
                return this->predict(answer);
            else
                return answer;
        else
            return answer;
    }

    Hopfield(size_t memory_range) {
        this->memory_range = memory_range;
        W = new double* [this->memory_range];
        for (size_t i = 0; i < this->memory_range; i++) 
            W[i] = new double[this->memory_range] {0};
        this->memory_save = 0;
    }
    ~Hopfield() {
        for (size_t i = 0; i < memory_range; i++)
            delete[] W[i];
        delete[] W;
    }
};

class NumsPerceptronPF
{
private:
    int n_sensors = 15;
    int threshold = 0;
    int sum = 0;
    int weights[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int* tema_num;

    void decrease(int num) {
        tema_num = stdnums::nums[num];
        for (int i = 0; i < 15; i++)
            if (tema_num[i] == 1)
                this->weights[i] -= 1;
        threshold += 1;
    }
    void increase(int num) {
        tema_num = stdnums::nums[num];
        for (int i = 0; i < 15; i++)
            if (tema_num[i] == 1)
                this->weights[i] += 1;
    }

public:
    void fit(int tema, int n_lessons = 500, bool whis_random = true) { // n_lessons - epochs
        srand(time(NULL));
        this->tema_num = stdnums::nums[tema];
        for (int i = 0; i < n_lessons; i++) {
            int index;
            if (whis_random)
                index = rand() % 10;
            else
                index = i % 10;

            if (index != tema) {
                if (predict(stdnums::nums[index]))
                    decrease(index);
            }
            else {
                if (!predict(stdnums::nums[index]))
                    increase(index);
            }
        }
    }
    bool is_in(int a) {
        double b = double(a);
        __int16 temp;
        if (b / 10 < 0)
            return this->predict(stdnums::nums[a]);
        else
            while (b > 0) {;
                int fractPart;
                b /= 10;
                double* intPart = new double();
                fractPart = int(10 * modf(b, intPart));
                b = *intPart;
                delete intPart;
                if (this->predict(stdnums::nums[fractPart]))
                    return true;
            }
        return false;
    }
    bool predict(int num[15]) {
        this->sum = 0;
        for (int i = 0; i < 15; i++) {
            this->sum += this->weights[i] * num[i];
        }
        if (this->sum >= this->threshold)
            return true;
        else
            return false;
    }
};

class ClassificationNetwork {
    NumsPerceptronPF* NumsNeurons;
    __int16 digits;

public:
    __int16 predict(int num[15]) {
        for (__int16 i = 0; i < digits; i++) {
            if (NumsNeurons[i].predict(num))
                return i;
        }
        return -1;
    }
    int sequenc_to_int(int Seq[], int size, int nums[][15] = stdnums::nums) {
        int Sum = 0;
        for (int i = 0; i < 4; i++)
            Sum += this->predict(minnums::nums[Seq[i]]) * pow(10, size - 1 - i);
        return Sum;
    }

    ClassificationNetwork() {
        digits = 10;
        NumsNeurons = new NumsPerceptronPF[digits];
        for (__int16 i = 0; i < digits; i++)
            NumsNeurons[i].fit(i, 1000, true);
    }
    ~ClassificationNetwork() {
        delete[] NumsNeurons;
    }
};

