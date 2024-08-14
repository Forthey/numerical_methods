#include "poly_interpolator.hpp"

int main() {
    std::string funcId, paragraph, postfixId;
    while (true) {
        std::cout << "Input func id and paragraph number: ";
        std::cin >> funcId >> paragraph;
        if (funcId == "0" && paragraph == "0") {
            break;
        }

        postfixId = std::format("_{}_{}",funcId, paragraph);
        std::cout << "Starting for " << postfixId << "..." << std::endl;
        PolyInterpolator polyInterpolator(postfixId);
        std::cout << "Finished for " << postfixId << std::endl;
    }
    return 0;
}