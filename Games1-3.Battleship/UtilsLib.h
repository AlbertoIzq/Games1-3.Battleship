#pragma once

#include <vector>
#include <string>
#include <cctype> // Used in inputValidatorPhrase
#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;

namespace InputValidation {

    template <typename T> // Validates input from the user
    inline T inputValidator() {
        T value{};
        std::string user_entry;
        bool done{ false };
        do {
            std::cin >> user_entry;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards the input buffer
            std::istringstream iss{ user_entry };
            if (iss >> value) {
                done = true;
            }
            else {
                std::cout << "Incorrect input, please try again: ";
            }
        } while (!done);
        return value;
    }

    template <typename T> // Input must have a specific length
    inline T inputValidator(const unsigned& len) {
        T value{};
        std::string user_entry;
        bool done{ false };
        do {
            std::cin >> user_entry;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards the input buffer
            std::istringstream iss{ user_entry };
            if (iss >> value && user_entry.size() == len) {
                done = true;
            }
            else {
                std::cout << "Incorrect input, please try again: ";
            }
        } while (!done);
        return value;
    }

    template <typename T> // Input must be within a list of allowed values
    inline T inputValidatorSpecific(const std::vector<T>& v) {
        bool done{ false };
        T value{};
        do {
            value = inputValidator<T>();
            for (T element : v) {
                if (value == element) {
                    done = true;
                    break;
                }
            }
            if (!done) {
                std::cout << "Incorrect input, please try again: ";
            }
        } while (!done);
        return value;
    }

    template <typename T> // Input must be within a range of values, [minVal maxVal]
    inline T inputValidatorSpecific(const T& minVal, const T& maxVal) {
        bool done{ false };
        T value{};
        do {
            value = inputValidator<T>();
            if (value >= minVal && value <= maxVal) {
                done = true;
                break;
            }
            if (!done) {
                std::cout << "Incorrect input, please try again: ";
            }
        } while (!done);
        return value;
    }

    template <typename T> //Input must be within a list of allowed values and have a specific length
    inline T inputValidatorSpecificValueAndLength(const std::vector<T>& v, const unsigned& len) {
        bool done{ false };
        T value{};
        do {
            value = inputValidator<T>(len);
            for (T element : v) {
                if (value == element) {
                    done = true;
                    break;
                }
            }
            if (!done) {
                std::cout << "Incorrect input, please try again: ";
            }
        } while (!done);
        return value;
    }

    char inputValidatorLetter(); // Input must be a letter

    std::string inputValidatorPhrase(); // Read a sentence from user (only letters and white spaces). Returns lower case sentence
}

namespace Other {
    void clearScreen();
}