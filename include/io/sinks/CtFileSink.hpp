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
 * @file CtFileSink.hpp
 * @brief 
 * @date 09-03-2024
 * 
 */

#ifndef INCLUDE_CTFILESINK_HPP_
#define INCLUDE_CTFILESINK_HPP_

#include "io/CtSink.hpp"

#include <fstream>
#include <sstream>
#include <cstring>

class CtFileSink : public CtSink {
public:
    /**
     * @brief Enum representing write mode.
     */
    enum class WriteMode { Append, Truncate };

    /**
     * @brief Constructs the CtFileSink object.
     * 
     * @param p_fileName Filename.
     */
    EXPORTED_API CtFileSink(const std::string& p_fileName, WriteMode p_mode = WriteMode::Append);

    /**
     * @brief Destructor for CtFileSink.
     *
     * Performs any necessary cleanup.
     */
    EXPORTED_API ~CtFileSink();

    /**
     * @brief Set the the delimiter of write() method.
     * 
     * @param p_delim The delimiter.
     * @param p_delim_size The delimiter size.
     */
    EXPORTED_API void setDelimiter(const char* p_delim, CtUInt8 p_delim_size);

protected:
    EXPORTED_API virtual CtUInt32 write(CtBlockDataPtr& p_data) override;

private:
    std::ofstream m_file; ///< File stream.
    std::unique_ptr<char[]> m_delim; ///< Batch write delimiter.
    CtUInt8 m_delim_size; ///< Delimeter size.
};


#endif //INCLUDE_CTFILESINK_HPP_