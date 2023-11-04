#pragma once
#include "DataSets.h"
#include <ctime>

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
        return this->memory_save;
    }
    double get_input_range() {
        return this->memory_range;
    }
    double get_max_capasity() {
        return this->memory_range / (2.0 * std::log(this->memory_range));
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