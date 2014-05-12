

//
// test_frejwork
//

#include <iostream>

static int error_count = 0;

const char* current_test_name = "?";

template <typename T1, typename T2>
void check_equal(T1 const& v1, T2 const& v2, const char* file, int line) {
    if( v1 != v2 ) {
        std::cerr << current_test_name << " (" << file << ":" << line <<  "): ERROR, " << v1 << " != " << v2  << "\n";
        error_count += 1;
    } else {
        std::cerr << current_test_name << " (" << file << ":" << line <<  "): ok, " << v1 << " == " << v2  << "\n";
    } 
}

#define CHECK_EQUAL(a, b) check_equal((a),(b), __FILE__, __LINE__)

void run_test(const char* name, void (*fun)())
{
    current_test_name = name;
    std::cerr << "TEST: " << current_test_name << "\n";
    fun();
}

#define RUN_TEST(name) run_test(#name, &name)

