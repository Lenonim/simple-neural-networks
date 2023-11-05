#include <iostream>
#include <fstream>
#include "Neirons.h"

using stdnums::nums;

double* to_bipolar_binary(int arr[], size_t size) {
    double* data = new double[size];
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == 0)
            data[i] = -1;
        else
            data[i] = 1;
    }
    return data;
}

void write_array_inline(double* arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        std::cout << arr[i] << '\t';
    }
}

double* invert_bipolar_binary_sequence(double* seq, size_t size) {
    double* invert_seq = new double[size];
    for (size_t i = 0; i < size; i++) {
        if (seq[i] == -1)
            invert_seq[i] = 1;
        else if (seq[i] == 1)
            invert_seq[i] = -1;
    }
    return invert_seq;
}

size_t bipolar_binary_sequence_to_number(double* seq, size_t size) {
    size_t number = 0;
    for (size_t i = 0, j = size - 1; i < size; i++, j--) {
        if (seq[i] == 1)
            number += pow(2, j);
    }
    return number;
}

double* number_to_bipolar_binary_sequence(size_t number, size_t size) {
    double* bipol_bin_sequence = new double[size];
    for (int i = size - 1; i >= 0; i--) {
        if (number % 2 == 1)
            bipol_bin_sequence[i] = 1;
        else
            bipol_bin_sequence[i] = -1;
        number = number / 2;
    }
    return bipol_bin_sequence;
}

void count_all_hopfiled_enegies(Hopfield& hopfiled) {
    double* temp;
    size_t size = hopfiled.get_input_range();
    std::ofstream dump_file;
    dump_file.open("Energy.csv");
    for (size_t i = 0; i < pow(2, size); i++) {
        temp = number_to_bipolar_binary_sequence(i, size);
        //write_array_inline(temp, size);
        double energy = hopfiled.count_energy(temp);
        //std::cout << "\t energy = " << energy <<"\n";
        dump_file << i << ";" << energy << "\n";
        delete[] temp;
    }
    dump_file.close();
}

size_t count_range(double* fir_arr, double* sec_arr, size_t size) {
    size_t fir_num = bipolar_binary_sequence_to_number(fir_arr, size);
    size_t sec_num = bipolar_binary_sequence_to_number(sec_arr, size);
    return size_t(abs(int(fir_num) - int(sec_num)));
}

int main() {
    srand(time(NULL));
    system("color f0");

    size_t input_size = 15;
    bool is_auto = true;
    Hopfield hopfield(input_size);
    double* zero = to_bipolar_binary(nums[0], input_size);
    double* _zero = to_bipolar_binary(minnums::nums[0], input_size);
    double* invert_zero = invert_bipolar_binary_sequence(zero, input_size);
    double* median = number_to_bipolar_binary_sequence(pow(2, input_size) / 2, input_size);

    double* five = to_bipolar_binary(nums[5], input_size);
    double* _five = to_bipolar_binary(minnums::nums[5], input_size);

    double* seven = to_bipolar_binary(nums[7], input_size);
    double* _seven = to_bipolar_binary(minnums::nums[7], input_size);

    double* six = to_bipolar_binary(nums[6], input_size);

    hopfield.save(zero);
    std::cout << "Save : ";
    write_array_inline(zero, input_size);
    std::cout << "\nHopfield capacity = " << hopfield.get_capacity() << "; max capacity = " << hopfield.get_max_capasity() << "\n";
    
    hopfield.save(five);
    std::cout << "Save : ";
    write_array_inline(five, input_size);
    std::cout << "\nHopfield capacity = " << hopfield.get_capacity() << "; max capacity = " << hopfield.get_max_capasity() << "\n";
    
    //std::cout << "0 = " << bipolar_binary_sequence_to_number(zero, input_size) << "\n";
    //std::cout << "5 = " << bipolar_binary_sequence_to_number(five, input_size) << "\n";

    //hopfield.save(seven);
    //std::cout << "Save : ";
    //write_array_inline(seven, input_size);
    //std::cout << "\nHopfield capacity = " << hopfield.get_capacity() << "; max capacity = " << hopfield.get_max_capasity() << "\n";

    std::cout << "\n\nPut:\n";
    write_array_inline(median, input_size);
    std::cout << "\nWe get:\n";
    write_array_inline(hopfield.predict(median, is_auto), input_size);
    std::cout << "\nReal:\n";
    write_array_inline(median, input_size);

    std::cout << "\n\ndifferences per 5 = " << count_differences(median, five, input_size);
    std::cout << "\nrange per 5 = " << count_range(median, five, input_size);

    std::cout << "\n\ndifferences per 0 = " << count_differences(median, zero, input_size);
    std::cout << "\nrange per 0 = " << count_range(median, zero, input_size);

    //std::cout << "\n\nPut:\n";
    //write_array_inline(_zero, input_size);
    //std::cout << "differences = " << count_differences(zero, _zero, input_size);
    ////std::cout << "range  = " << count_range(zero, _zero, input_size);
    //std::cout << "\nWe get:\n";
    //write_array_inline(hopfield.predict(_zero, is_auto), input_size);
    //std::cout << "\nReal:\n";
    //write_array_inline(zero, input_size);

    //std::cout << "\n\nPut:\n";
    //write_array_inline(invert_zero, input_size);
    //std::cout << "differences = " << count_differences(zero, invert_zero, input_size);
    //std::cout << "\nWe get:\n";
    //write_array_inline(hopfield.predict(invert_zero, is_auto), input_size);
    //std::cout << "\nReal:\n";
    //write_array_inline(zero, input_size);

    //std::cout << "\n\nPut:\n";
    //write_array_inline(_five, input_size);
    //std::cout << "differences = " << count_differences(five, _five, input_size);
    ////std::cout << "range  = " << count_range(five, _five, input_size);
    //std::cout << "\nWe get:\n";
    //write_array_inline(hopfield.predict(_five, is_auto), input_size);
    //std::cout << "\nReal:\n";
    //write_array_inline(five, input_size);

    //std::cout << "\n\nPut:\n";
    //write_array_inline(_seven, input_size);
    ////std::cout << "differences = " << count_differences(seven, _seven, input_size);
    //std::cout << "range  = " << count_range(seven, _seven, input_size);
    //std::cout << "\nWe get:\n";
    //write_array_inline(hopfield.predict(_seven, is_auto), input_size);
    //std::cout << "\nReal:\n";
    //write_array_inline(seven, input_size);

    //std::cout << "\n\nPut:\n";
    //write_array_inline(six, input_size);
    //std::cout << "\nWe get:\n";
    //write_array_inline(hopfield.predict(six, is_auto), input_size);
    //std::cout << "\nReal:\n";
    //write_array_inline(five, input_size);

    delete[] median;
    delete[] invert_zero;
    delete[] seven;
    delete[] _seven;
    delete[] five;
    delete[] _five;
    delete[] zero;
    delete[] _zero;

    //count_all_hopfiled_enegies(hopfield);
    //system("python EnergyVisual.py");
}
