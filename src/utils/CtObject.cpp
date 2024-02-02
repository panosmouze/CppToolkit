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
 * @file CtObject.cpp
 * @brief 
 * @date 02-02-2024
 * 
 */

#include "utils/CtObject.hpp"

#include "exceptions/CtEventExceptions.hpp"

CtObject::CtObject() : m_pool(1) {

}

CtObject::~CtObject() {
    m_pool.join();
}

void CtObject::connectEvent(CtObject* p_obj, uint8_t p_eventCode, CtTask& p_task) {
    p_obj->connectEvent(p_eventCode, p_task);
}

void CtObject::connectEvent(uint8_t p_eventCode, CtTask& p_task) {
    std::scoped_lock lock(m_mtx_control);
    if (!hasEvent(p_eventCode)) {
        throw CtEventNotExistsError("Event is not registed.");
    }
    m_triggers.insert({p_eventCode, p_task});
}

void CtObject::triggerEvent(uint8_t p_eventCode) {
    std::scoped_lock lock(m_mtx_control);
    if (!hasEvent(p_eventCode)) {
        throw CtEventNotExistsError("Event is not registed.");
    }
    std::pair<std::multimap<uint8_t, CtTask>::iterator, std::multimap<uint8_t, CtTask>::iterator> s_iterRange;
    s_iterRange = m_triggers.equal_range(p_eventCode);

    std::multimap<uint8_t, CtTask>::iterator s_iter;
    for (s_iter = s_iterRange.first; s_iter != s_iterRange.second; s_iter++) {
        m_pool.addTask(s_iter->second);
    }
}

void CtObject::registerEvent(uint8_t p_eventCode) {
    std::scoped_lock lock(m_mtx_control);
    if (hasEvent(p_eventCode)) {
        throw CtEventAlreadyExistsError("Event is already registed.");
    }
    m_events.push_back(p_eventCode);
}

bool CtObject::hasEvent(uint8_t p_eventCode) {
    for (uint8_t s_event: m_events) {
        if (s_event == p_eventCode) {
            return true;
        }
    }
    return false;
}
