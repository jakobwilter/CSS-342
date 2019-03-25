//
// Created by Jakob Wilter on 12/8/18.
//

#ifndef LONGINT_H
#define LONGINT_H
#include <iostream>
#include "deque.h"

using namespace std;

class LongInt {
    friend istream &operator>>( istream &istream1, LongInt &rhs );
    friend ostream &operator<<( ostream &ostream1, const LongInt &rhs );
public:
    //Constructors
    LongInt( const string string1 );
    LongInt( const LongInt &rhs );
    LongInt( );

    // Destructor
    ~LongInt( );

    // Arithmetic binary operators
    LongInt operator+( const LongInt &rhs ) const;
    LongInt operator-( const LongInt &rhs ) const;

    // assignment operators
    const LongInt &operator=( const LongInt &rhs );

    // Logical binary operators
    bool operator< ( const LongInt & rhs ) const;
    bool operator<=( const LongInt & rhs ) const;
    bool operator> ( const LongInt & rhs ) const;
    bool operator>=( const LongInt & rhs ) const;
    bool operator==( const LongInt & rhs ) const;
    bool operator!=( const LongInt & rhs ) const;

private:
    void init ();
    Deque<char> digits;
    bool negative;
    void convertSign( );
    void remove0s( );
    void addToDequeue(const string string1);
};

#endif