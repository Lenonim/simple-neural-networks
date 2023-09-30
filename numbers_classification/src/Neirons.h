#pragma once
#include "DataSets.h"
#include <ctime>
#include <thread>

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

