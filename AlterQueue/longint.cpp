//
// Created by Jakob Wilter on 12/8/18.
//
// longint.cpp
// Functions implement ascii table char conversions.
//

#include "longint.h"
#include "cmath"

//----------------------------------------------- Constructors ---------------------------------------------------------

LongInt::LongInt(const string string1) {
    negative = 0;
    addToDequeue(string1); // string parameter added to deque.
}

LongInt::LongInt(const LongInt &rhs) {
    negative = rhs.negative;
    digits.clear();
    // LongInt parameter added to new deque initialized and assigned.
    Deque<char> deque(rhs.digits);
    while (!deque.isEmpty()) {
        digits.addBack(deque.removeFront());
    }
}

LongInt::LongInt() {
    negative = 0;
}

LongInt::~LongInt() {
    // clears digits stored in this deque
    digits.clear();
}

//------------------------------------------ Arithmetic Binary Operators -----------------------------------------------

/**
 * Function overrides operator + and passes in a single LongInt parameter. The LongInt passed through is tested for
 * to see if signs need to be adjusted or converted. Then the parameter is added to *this in which the function returns
 * the sum or result of the equation x + y.
 * @param &rhs, holds the value being passed through the function for if statement logic.
 * @return result, (lhs + rhs) or x + y
 */
LongInt LongInt::operator+(const LongInt &rhs) const {
    LongInt result;
    if (negative == rhs.negative) {
        if (negative) {
            LongInt x(*this);
            LongInt y(rhs);
            // convert from the int value to char so we can store result in the deque.
            x.convertSign();
            y.convertSign();

            result = x + y;
            result.convertSign();

            return result;
        }

        Deque<char> leftSide(digits);
        Deque<char> rightSide(rhs.digits);
        int i = 0;
        // carry will bring the first int of a two digits sum to the next int that is iterated to.
        int carry = 0;

        // while the iterator is still less than the size of the largest deque comparing left and right deques.
        while (i < max(rightSide.size(), leftSide.size())) {
            int value;
            int x;
            int y;

            if (!leftSide.isEmpty()) {
                x = (int) leftSide.removeBack() - '0';
            } else {
                x = 0;
            }

            if (!rightSide.isEmpty()) {
                y = (int) rightSide.removeBack() - '0';
            } else {
                y = 0;
            }

            value = x + y + carry; // carry will only affect equation if prevous value was larger than 10.
            carry = value / 10; // extracts the first digit of the sum.
            result.digits.addFront((char) (value % 10 + '0'));
        }
        if (carry) // if larger than 0, will add 1 to the front of the deque.
            result.digits.addFront('1');

    } else {
        // if lhs + -rhs then lhs - rhs
        if (rhs.negative) {
            LongInt temp(rhs);
            temp.convertSign();
            result = operator-(temp);
        } else {
            LongInt temp((*this));
            temp.convertSign();
            result = rhs.operator-(temp);
        }
    }
    return result;
}

/**
 * Function overrides operator - and passes in a single LongInt parameter. The LongInt passed through is tested for
 * to see if signs need to be adjusted or converted. Then the parameter is added to *this in which the function returns
 * the difference or result of the equation x - y.
 * @param &rhs, holds the value being passed through the function for if statement logic.
 * @return result, (lhs - rhs) or x - y
 */
LongInt LongInt::operator-(const LongInt &rhs) const {
    LongInt result;

    // exception cases which will handle unusual or unexpected sign logic.
    // This includes x - -y, x + -y, -x - y, -x + -y, etc.
    if (negative == rhs.negative) {
        if ((*this) <= rhs && !negative) { // if -x - -y then x + y
            // subtract is assigned the *this deque.
            LongInt subtract(rhs);
            subtract.convertSign();
            subtract.negative = 0;

            result = (*this) + subtract;
            result.negative = 1;
        } else if ((*this) > rhs && !negative) {
            // subtract is assigned the *this deque.
            LongInt subtract((*this));
            subtract.convertSign();
            subtract.negative = 0;

            result = subtract + rhs;
            result.negative = 1; // results negative assigned to 1
            result.convertSign();
        } else if ((*this) <= rhs && negative) {
            // subtract is assigned the *this deque.
            LongInt subtract((*this));
            subtract.negative = 0;
            LongInt subtractEnd(rhs);
            subtractEnd.convertSign();

            result = subtract + subtractEnd;
            result.negative = 1;
        } else {
            // subtract is assigned the *this deque.
            LongInt subtract((*this));
            subtract.convertSign();
            LongInt subtractEnd(rhs);
            subtractEnd.negative = 0;

            result = subtract + subtractEnd;
            result.negative = 1; // results negative assigned to 1
            result.convertSign();
        }
        result.remove0s();
    } else {
        if (negative && !rhs.negative) {
            LongInt right(rhs);
            right.convertSign();

            result = (*this) + (right);
        }
        if (!negative && rhs.negative) {
            LongInt right(rhs);
            right.convertSign();

            result = (*this) + (right);
        }
    }
    return result;
}

//---------------------------------------------- Assignment Operators --------------------------------------------------

/**
 * Function overrides operator = and passes in a single LongInt parameter. The LongInt passed through is tested to see
 * if it is already equivalent to *this. If not, each digit in this is assigned to its respective digit in the rhs
 * LongInt. In this case, *this = rhs or x = y.
 * @param &rhs, holds the value being passed through the function to be assigned to *this.
 * @return *this
 */
const LongInt &LongInt::operator=(const LongInt &rhs) {
    if (this != &rhs) {
        digits.clear(); // digits are cleared from the deque.
        // *this digits are each assigned to their respective digits in rhs.
        (*this).digits = rhs.digits;
        negative = rhs.negative;
    }
    return *this;
}

//-------------------------------------------- Logical Binary Operators ------------------------------------------------

/**
 * Function overrides operator < and passes in a single LongInt parameter. The LongInt passed through is tested against
 * *this.
 * @param &rhs, holds the value being passed through the function to be tested against *this.
 * @return boolean
 */
bool LongInt::operator<(const LongInt &rhs) const {
    if (operator==(rhs))
        return false;
    else {
        if (negative != rhs.negative)
            return negative;
        if (digits.size() != rhs.digits.size())
            return digits.size() > rhs.digits.size() == negative;
        else { // left compare right has failed if statements, function must iterate through each side and test values.
            Deque<char> leftSide(digits);
            Deque<char> rightSide(rhs.digits);

            int i = 0;
            while (i < max(rightSide.size(), leftSide.size())) {
                int left;
                int right;

                if (!leftSide.isEmpty()) { // while left side is not empty remove front
                    left = (int) leftSide.removeFront();
                } else {
                    left = -1;
                }

                if (!rightSide.isEmpty()) { // while right side is not empty remove front
                    right = (int) rightSide.removeFront();
                } else {
                    right = -1;
                }

                if (negative && left != right)
                    return left < right; // return boolean
                if (!negative && left != right)
                    return left < right; // return boolean

            }
        }
    }
    return false;
}

/**
 * Function overrides operator == and passes in a single LongInt parameter. The LongInt passed through is tested to see
 * if it is already equivalent to *this. If not, each digit in this is assigned to its respective digit in the rhs
 * LongInt. In this case, *this == rhs or x == y.
 * @param &rhs, holds the value being passed through to test if it is equivalent to *this.
 * @return boolean
 */
bool LongInt::operator==(const LongInt &rhs) const { // operator to test equivalence of *this and value passed through.
    if (negative == rhs.negative) { // checks whether value and rhs are equivalent when negative.
        // new deques are created to store digits of this and rhs, respectively.
        Deque<char> *rightValue = new Deque<char>(rhs.digits);
        Deque<char> *leftValue = new Deque<char>(digits);
        int i = 0;

        while (i < max(rightValue->size(), leftValue->size())) {
            // left and right will store the integer value from values after the front is removed.
            int left;
            int right;

            // when left value is not empty remove the front.
            if (!leftValue->isEmpty()) {
                left = (int) leftValue->removeFront();
            } else {
                left = -1;
            }

            // when right value is not empty remove the front.
            if (!rightValue->isEmpty()) {
                right = (int) rightValue->removeFront();
            } else {
                right = -1;
            }

            if (left == -1 || right == -1 || !(left == right)) // left and right value cannot equal -1.
                return false;
        }
        return true;
    }
    // negative is not equivalent to the negative of rhs
    else {
        return false;
    }
}

// <= operator
bool LongInt::operator<=(const LongInt &rhs) const {
    return (operator==(rhs) || operator<(rhs));
}

// > operator
bool LongInt::operator>(const LongInt &rhs) const {
    return !(operator<=(rhs));
}

// >= operator
bool LongInt::operator>=(const LongInt &rhs) const {
    return !(operator<(rhs));
}

// != operator
bool LongInt::operator!=(const LongInt &rhs) const {
    return !operator==(rhs);
}

//------------------------------------------ convertSign Function -----------------------------------------------

/**
 * Void function which converts sign that is acting on right and left values, respectively.
 * char will be added the the back of the deque. Iterator will allow while loop to
 * convert each value from int to character.
 */
void LongInt::convertSign() {
    int i = 0;
    while (i < digits.size()) {
        char conversion = (char) (9 - ((int) digits.removeFront() - '0') + '0');
        digits.addBack(conversion);
        i++;
    }
    negative = !negative;
}

//---------------------------------------------- remove0s Function -----------------------------------------------------
// Function removes any 0s at the front of a value to simplify input.
// i.e., 0000001 == 1
void LongInt::remove0s() {
    while (!digits.isEmpty() && negative && digits.getFront() == '9')
        digits.removeFront();
    while (!digits.isEmpty() && !negative && digits.getFront() == '0')
        digits.removeFront();
}

//---------------------------------------------- addtoDequeue Function -------------------------------------------------
// Function continues to add to the deque using the string that is passed through the function.
void LongInt::addToDequeue(const string string1) {
    int i;
    while (i < string1.length() && (string1[i] <= '0' || string1[i] > '9')) { // if string[i] is less than or equal to 0
        if (string1[i] == '-')
            negative = 1;
        i++;
    }
    while (i < string1.length()) {
        // checks whether string1[i] is a decimal digit character
        if (isdigit(string1[i])) {
            if (negative)
                digits.addBack((char) (105 - (int) string1[i]));
            else
                digits.addBack(string1[i]);
        }
        i++;
    }
}

//-------------------------------------------- Input / Output Operators ------------------------------------------------

/**
 * Function overrides ostream operator >> and passes in two parameters, an istream and a LongInt.
 * Instantiates a string to store the user input allowing function to add the inputted converted string
 * to the rhs dequeue.
 * @param &istream1, given the user input istream1 will store value allowing program to store and make
 * modifications to input.
 * @param &rhs, holds the LongInt value being passed through the function
 */
istream &operator>>(istream &istream1, LongInt &rhs) {
    string string1;
    istream1 >> string1;

    // adds the string into the deque of rhs.
    rhs.addToDequeue(string1);

    return istream1;
}

/**
 * Function overrides ostream operator << and passes in two parameters, an ostream and a LongInt. If the
 * LongInt passed through is empty, return 0. If the LongInt passed through is negative, return negative value.
 * Otherwise, return the ostream without modification.
 * @param &ostream1 prepares output value based on actions made within the function to return.
 * @param &rhs, holds the value being passed through the function for if statement logic.
 */
ostream &operator<<(ostream &ostream1, const LongInt &rhs) {
    if (rhs.digits.isEmpty()) {
        ostream1 << 48; // ascii decimal value 48 is char '0'
        return ostream1;
    }
    if (rhs.negative)
        ostream1 << '-';
    Deque<char> deque(rhs.digits);
    while (!deque.isEmpty()) {
        if (rhs.negative) {
            ostream1 << (char) (105 - deque.removeFront());
        } else {
            ostream1 << deque.removeFront();
        }
    }
    return ostream1;
}