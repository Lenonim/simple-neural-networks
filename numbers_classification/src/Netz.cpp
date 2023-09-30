#include <iostream>
#include "Neirons.h"

int main() {
    srand(time(NULL));

    // простое распознавание ( да или нет ) на поданное число
    std::cout << "fit on 5 and check on standart data\n";
    NumsPerceptronPF pf;
    pf.fit(5);
    for (int i = 0; i < 10; i++) {
        std::cout << i << " answer of network = " << pf.predict(stdnums::nums[i]) << "\n";
    }
    std::cout << "\nrefit on 8 and check on other data\n";
    pf.fit(8, 2000);
    for (int i = 0; i < 10; i++) {
        std::cout << i << " answer of network = " << pf.predict(minnums::nums[i]) << "\n";
    }

    std::cout << "\ncheck numbers on tema number\n";
    std::cout << "Is in 546 fit number? answer = " << pf.is_in(546) << '\n';
    std::cout << "Is in 873 fit number? answer = " << pf.is_in(873) << '\n';

    // комплексное распознование ( это есть ____ цифра) на поданное число
    std::cout << "\ncheck answers of classification network\n";
    ClassificationNetwork classnet;
    for (int i = 0; i < 10; i++) {
        std::cout << "put " << i << " number to network; answer of network: is it " << classnet.predict(minnums::nums[i]) << "\n";
    }

    // создадим последовательность из массивов
    const int SeqSize = 4;
    int SeqNums[SeqSize] = { 1, 4, 9, 0 };
    std::cout << "\nnumber sequens (1490) to int; answer = " << classnet.sequenc_to_int(SeqNums, SeqSize);
}
