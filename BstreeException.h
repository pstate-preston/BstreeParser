/**
 * The specification for a customized class for reporting
 * exception for a Binary Search Tree class implementation
 * @author Duncan, Preston Gautreaux
 * <pre>
 * File: BstreeException.h
 * Date: 9999-99-99
 * Course: csc 1254 Section 1
 * Instructor: Dr. Duncan
 * NOTE: DO NOT MODIFY THIS FILE
 * </pre>
 */

#include <string>
#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#ifndef BSTREEEXCEPTION_H
#define BSTREEEXCEPTION_H

using namespace std;

/**
 * for report exceptions for the BSTree class
 */
class BstreeException
{
private:
    /**
     * a description of why the exception occurred
     */
    string message;
public:
    /**
     * creates an instance of this class
     * @param msg the reason for the exception
     */
    BstreeException(const string& msg);

    /**
     * Gives the reason for the exception
     * @return the reason for the exception
     */
    string what() const;
};
#endif //BSTREEEXCEPTION_H
