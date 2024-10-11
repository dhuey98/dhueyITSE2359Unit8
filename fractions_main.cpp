#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// Manually implement GCD function
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

class Fraction {
private:
    int numerator;
    int denominator;

    // Helper function to reduce the fraction by its greatest common divisor (GCD)
    void reduce() {
        int gcdValue = gcd(numerator, denominator);
        numerator /= gcdValue;
        denominator /= gcdValue;
    }

public:
    // Constructors
    Fraction(int n = 0, int d = 1) : numerator(n), denominator(d) {
        if (d == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        reduce();
    }

    // Getters for numerator and denominator
    int getNumerator() const {
        return numerator;
    }

    int getDenominator() const {
        return denominator;
    }

    // Overload + operator for Fraction addition
    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + denominator * other.numerator;
        int den = denominator * other.denominator;
        return Fraction(num, den); // Return the reduced fraction
    }

    // Overload == operator for Fraction equality check
    bool operator==(const Fraction& other) const {
        return (numerator == other.numerator) && (denominator == other.denominator);
    }

    // Overload << operator for output stream (stream insertion)
    friend ostream& operator<<(ostream& os, const Fraction& f) {
        os << f.numerator << "/" << f.denominator;
        return os;
    }

    // Overload >> operator for input stream (stream extraction)
    friend istream& operator>>(istream& is, Fraction& f) {
        char slash;  // To capture the '/' character in the fraction
        is >> f.numerator >> slash >> f.denominator;
        f.reduce(); // Reduce after input
        return is;
    }
};

// Template function to find the maximum of two values of any type
template <typename T>
T findMax(const T& a, const T& b) {
    return (a > b) ? a : b;
}

// Specialized template function to find the maximum of two Fraction objects
template <>
Fraction findMax(const Fraction& a, const Fraction& b) {
    if ((a.getNumerator() * b.getDenominator()) > (b.getNumerator() * a.getDenominator())) {
        return a;
    } else {
        return b;
    }
}

// Function to process fractions from input file and write results to the output file
void processFractions(const std::string& inputFile, const std::string& outputFile) {
    ifstream infile(inputFile);
    ofstream outfile(outputFile);

    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Fraction f1, f2;
    while (infile >> f1 >> f2) {
        // Addition
        Fraction sum = f1 + f2;
        outfile << f1 << " + " << f2 << " = " << sum << endl;

        // Equality check
        if (f1 == f2) {
            outfile << f1 << " is equal to " << f2 << endl;
        } else {
            outfile << f1 << " is not equal to " << f2 << endl;
        }
    }

    infile.close();
    outfile.close();
}

int main() {
    // Process fractions from input file and write results to output file
    processFractions("fractions.txt", "results.txt");

    // Test the findMax function with fractions
    Fraction f1(3, 4), f2(2, 3);
    Fraction maxFraction = findMax(f1, f2);
    cout << "The maximum fraction between " << f1 << " and " << f2 << " is " << maxFraction << endl;

    return 0;
}