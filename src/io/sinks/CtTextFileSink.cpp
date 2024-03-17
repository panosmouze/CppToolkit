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
 * @file CtTextFileSink.cpp
 * @brief 
 * @date 10-03-2024
 * 
 */

#include "io/sinks/CtTextFileSink.hpp"

CtTextFileSink::CtTextFileSink(const std::string& p_fileName, WriteMode p_mode) : CtFileSink(p_fileName, p_mode) {
    CtBlock::setInVectorTypes({CtBlockDataType::CtTextData});
    CtFileSink::setDelimiter("\n", 1);
}

CtTextFileSink::~CtTextFileSink() {

}

CtUInt32 CtTextFileSink::write(CtBlockDataPtr& p_data) {
    CtString s_text = ((CtTextData*)p_data.get())->get();
    CtRawData* s_rawData = new CtRawData(s_text.size());
    s_rawData->clone((CtUInt8*)s_text.c_str(), s_text.size());
    CtBlockDataPtr s_data(s_rawData);
    return CtFileSink::write(s_data);
}
