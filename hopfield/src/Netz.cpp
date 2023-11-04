#include <iostream>
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

int main() {
    srand(time(NULL));
    system("color f0");

    size_t input_size = 15;
    bool is_auto = true;
    Hopfield hopfield(input_size);
    double* zero = to_bipolar_binary(nums[0], input_size);
    double* _zero = to_bipolar_binary(minnums::nums[0], input_size);

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
    
    hopfield.save(seven);
    std::cout << "Save : ";
    write_array_inline(seven, input_size);
    std::cout << "\nHopfield capacity = " << hopfield.get_capacity() << "; max capacity = " << hopfield.get_max_capasity() << "\n";

    std::cout << "\n\nset:\n";
    write_array_inline(_zero, input_size);
    std::cout << "differences = " << count_differences(zero, _zero, input_size);
    std::cout << "\nWe get:\n";
    write_array_inline(hopfield.predict(_zero, is_auto), input_size);
    std::cout << "\nReal:\n";
    write_array_inline(zero, input_size);

    std::cout << "\n\nset:\n";
    write_array_inline(_five, input_size);
    std::cout << "differences = " << count_differences(five, _five, input_size);
    std::cout << "\nWe get:\n";
    write_array_inline(hopfield.predict(_five, is_auto), input_size);
    std::cout << "\nReal:\n";
    write_array_inline(five, input_size);

    std::cout << "\n\nset:\n";
    write_array_inline(_seven, input_size);
    std::cout << "differences = " << count_differences(seven, _seven, input_size);
    std::cout << "\nWe get:\n";
    write_array_inline(hopfield.predict(_seven, is_auto), input_size);
    std::cout << "\nReal:\n";
    write_array_inline(seven, input_size);

    std::cout << "\n\nset:\n";
    write_array_inline(six, input_size);
    std::cout << "differences = " << count_differences(six, five, input_size);
    std::cout << "\nWe get:\n";
    double* answer = hopfield.predict(six, is_auto);
    write_array_inline(answer, input_size);
    std::cout << "\nReal:\n";
    write_array_inline(five, input_size);

    std::cout << "\n\nset:\n";
    write_array_inline(answer, input_size);
    std::cout << "differences = " << count_differences(answer, five, input_size);
    std::cout << "\nWe get:\n";
    write_array_inline(hopfield.predict(answer), input_size);
    std::cout << "\nReal:\n";
    write_array_inline(five, input_size);

    delete[] seven;
    delete[] _seven;
    delete[] five;
    delete[] _five;
    delete[] zero;
    delete[] _zero;
}
