/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    test.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ZEN_TEST_H
#define ZEN_GUARD_ZEN_TEST_H

#include <zen/equals.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
// #include <zen/foreach.h>
#include <vector>
#include <map>

#define ZEN_TEST_CASE(name) \
struct name \
{ void operator()(zen::test::failure_callback fail) const; }; \
static zen::test::auto_register name ## _register = zen::test::auto_register(#name, name()); \
void name::operator()(zen::test::failure_callback zen_test_fail) const

#define ZEN_DETAIL_TEST_FAIL(message) if (zen_test_fail(message, __FILE__, __LINE__)) return
#define ZEN_DETAIL_TEST_FAIL_EX(message) if (zen_test_fail(message, __FILE__, __LINE__)) throw

#define ZEN_DETAIL_TEST_EXEC(rethrow, ...) \
do \
{ \
    try { __VA_ARGS__; } \
    catch(const std::exception& zen_ex) { ZEN_DETAIL_TEST_FAIL_EX(zen_ex.what()); rethrow } \
    catch(...) { ZEN_DETAIL_TEST_FAIL_EX("An unknown exception has occured"); rethrow } \
} while(0)

#define ZEN_TEST_EXEC(...) ZEN_DETAIL_TEST_EXEC(throw;, __VA_ARGS__)

#define ZEN_TEST_EQUAL(x, ...) \
ZEN_TEST_EXEC(if (!zen::test::equals(x, __VA_ARGS__)) ZEN_DETAIL_TEST_FAIL(std::string(#x) + " != " + #__VA_ARGS__))

#define ZEN_TEST_CHECK(...) if (!(__VA_ARGS__)) ZEN_DETAIL_TEST_FAIL(std::string(#__VA_ARGS__))

namespace zen { namespace test {

typedef boost::function<bool(std::string message, std::string file, long line)> failure_callback;
typedef boost::function<void(failure_callback fail)> test_case;
static std::vector<std::pair<std::string, test_case> > test_cases;

struct auto_register
{
    auto_register(std::string name, test_case tc)
    {
        test_cases.push_back(std::make_pair(name, tc));
    }
};

struct out_failure
{
    typedef bool result_type;
    bool operator()(bool & failed, std::string name, std::string message, std::string file, long line) const
    {
        std::cout << "*****FAILED: " << name << "@" << file << ": " << line << std::endl << message << std::endl;
        failed = true;
        return true;
    }
};

void run()
{
    bool failed = false;
    for(const auto& tc: test_cases)
    {
        // std::cout << "Test " << tc.first << " running..." << std::endl;
        tc.second(boost::bind(out_failure(), boost::ref(failed), tc.first, _1, _2, _3));
    }
    if (!failed) std::cout << "All " << test_cases.size() << " test cases passed." << std::endl;
}

}}

#endif
