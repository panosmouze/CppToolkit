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
 * @file CtFileSink.cpp
 * @brief 
 * @date 09-03-2024
 * 
 */

#include "io/sinks/CtFileSink.hpp"

#include "exceptions/CtFileExceptions.hpp"

#include <memory>

CtFileSink::CtFileSink(const std::string& p_fileName, WriteMode p_mode) {
    CtBlock::setInVectorTypes({CtBlockDataType::CtRawData});
    switch (p_mode) {
        case WriteMode::Append:
            m_file.open(p_fileName, std::ios::out | std::ios::app);
            break;
            default:
        case WriteMode::Truncate:
            m_file.open(p_fileName, std::ios::out | std::ios::trunc);
            break;
    }
    if (!m_file.is_open()) {
        throw CtFileWriteError("File cannot open.");
    }
}

CtFileSink::~CtFileSink() {
    stopSink();
    if (m_file.is_open()) {
        m_file.close();
    }
}

void CtFileSink::setDelimiter(const char* p_delim, CtUInt8 p_delim_size) {
    if (p_delim_size > 0 && p_delim != nullptr) {
        m_delim_size = p_delim_size;
        m_delim.reset();
        m_delim = std::make_unique<char[]>(m_delim_size);
        memcpy(m_delim.get(), p_delim, m_delim_size);
    }
}

CtUInt32 CtFileSink::write(CtBlockDataPtr& p_data) {
    CtUInt32 eventCode = CTEVENT_DATA_WRITE_FAIL;
    if (m_file.is_open()) {
        CtRawData* s_data = (CtRawData*) p_data.get();
        m_file.write((char*)s_data->get(), s_data->size());
        m_file.write(m_delim.get(), m_delim_size);
        eventCode = CTEVENT_DATA_WRITE;
    }

    return eventCode;
}
