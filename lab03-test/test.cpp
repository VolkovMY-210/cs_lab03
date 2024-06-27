#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void
test_three_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-3, -5, -1}, min, max);
    assert(min == -5);
    assert(max == -1);
}

void
test_all_equal() {
    double min = 0;
    double max = 0;
    find_minmax({3, 3, 3}, min, max);
    assert(min == 3);
    assert(max == 3);
}

void
test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

int main() {
    test_positive();
    test_three_negative();
    test_all_equal();
    test_empty();
}
