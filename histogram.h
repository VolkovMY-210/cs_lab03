#ifndef histogram_h
#define histogram_h

#include <iostream>
#include <vector>

using namespace std;


void find_minmax(const vector<double> numbers, double& min, double& max);
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke, string fill);
void svg_end();
void show_histogram_svg(const vector<size_t>& bins, const size_t MAX_ASTERISK);


#endif /* histogram_h */
