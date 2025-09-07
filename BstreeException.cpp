/**
 * implementation for a customized class for reporting
 * exception for a Binary Search Tree class implementation
 * @author Duncan, Preston Gautreaux
 * <pre>
 * File: BstreeExcepion.cpp
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

#include "BstreeException.h"

using namespace std;

BstreeException::BstreeException(const string& msg)
{
	message = msg;
}

string BstreeException::what() const
{
	return message;
}
