/*
MIT License

Copyright (c) 2024 Mouzenidis Panagiotis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file CtFileExceptions.hpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTFILEEXCEPTIONS_HPP_
#define INCLUDE_CTFILEEXCEPTIONS_HPP_

#include "exceptions/CtException.hpp"

class CtFileError : public CtException {
public:
    explicit CtFileError(const std::string& msg): CtException(msg) {};
};

class CtFileWriteError : public CtException {
public:
    explicit CtFileWriteError(const std::string& msg): CtException(msg) {};
};

class CtFileReadError : public CtException {
public:
    explicit CtFileReadError(const std::string& msg): CtException(msg) {};
};

class CtFileParseError : public CtException {
public:
    explicit CtFileParseError(const std::string& msg): CtException(msg) {};
};

#endif //INCLUDE_CTFILEEXCEPTIONS_HPP_