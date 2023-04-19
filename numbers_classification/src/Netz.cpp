#include <iostream>
#include "Neirons.h"

int main() {
    srand(time(NULL));
    NumsPerceptronPF pf;
    pf.fit(5);
    for (int i = 0; i < 10; i++) {
        std::cout << i << " answer of network = " << pf.predict(stdnums::nums[i]) << "\n";
    }
    std::cout << "\n";
    pf.fit(9, 10000);
    for (int i = 0; i < 10; i++) {
        std::cout << i << " answer of network = " << pf.predict(minnums::nums[i]) << "\n";
    }
}
