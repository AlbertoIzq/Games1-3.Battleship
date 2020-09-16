#include "UtilsLib.h"
#include "UtilsLib.h"

namespace InputValidation {
    char inputValidatorLetter() {
        bool done{ false };
        char value{};
        do {
            value = inputValidator<char>(1);
            value = tolower(value);
            if (isalpha(value)) {
                done = true;
            }
            if (!done) {
                std::cout << "Incorrect input, please try again: ";
            }
        } while (!done);
        return value;
    }

    std::string inputValidatorPhrase() {
        bool done{ true };
        std::string phrase{ "" };
        do {
            done = true;
            std::getline(cin, phrase);
            for (char& c : phrase) {
                c = tolower(c);
                if (!isalpha(c) && !isspace(c)) {
                    done = false;
                    break;
                }
            }
            if (!done) {
                std::cout << "Incorrect input, please try again: ";
            }
        } while (!done);
        return phrase;
    }
}

namespace Other {
    void clearScreen() {
        std::system("cls");
    }
}