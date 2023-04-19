#pragma once
#include "DataSets.h"
#include <ctime>
#include <xmemory>

class NumsPerceptronPF
{
private:
    int n_sensors = 15;
    int threshold = 9;
    int sum = 0;
    int weights[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int* tema_num;

    void decrease(int num) {
        tema_num = stdnums::nums[num];
        for (int i = 0; i < 15; i++)
            if (tema_num[i] == 1)
                this->weights[i] -= 1;
    }
    void increase(int num) {
        tema_num = stdnums::nums[num];
        for (int i = 0; i < 15; i++)
            if (tema_num[i] == 1)
                this->weights[i] += 1;
    }

public:
    void fit(int tema, int n_lessons = 5000) { // n_lessons - epochs
        srand(time(NULL));
        this->tema_num = stdnums::nums[tema];
        for (int i = 0; i < n_lessons; i++) {
            int rand_index = rand() % 10;

            if (rand_index != tema) {
                if (predict(stdnums::nums[rand_index]))
                    decrease(rand_index);
            }
            else {
                if (!predict(stdnums::nums[rand_index]))
                    increase(rand_index);
            }
        }
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
