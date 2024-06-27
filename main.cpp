/*4.Вместо количества элементов сделайте подписью столбца процент элементов, попавших в столбец,
 как целое двузначное число с % в конце.*/

#include <iostream>
#include <vector>
#include "histogram.cpp"

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

vector<size_t>
make_histogram(size_t bin_count, const vector<double>& numbers, double number_count) {
    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count);
    
    double bin_size = (max - min) / bin_count;
    
    for (size_t i = 0; i < number_count; i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    
    return bins;
}

void
show_histogram_text(const vector<size_t>& bins, size_t bin_count, size_t number_count) {
    size_t max_count = bins[0];
    
    for (double x: bins){
        if (x > max_count){
            max_count = x;
        }
    }
    
    for (size_t i = 0; i < bin_count; i++) {
        size_t procent = 100 * (static_cast<double>(bins[i]) / number_count);
        size_t height = 0;
        
        if (max_count > MAX_ASTERISK){
            height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
        }
        else {
            height = bins[i];
        }
        
        if (procent < 10) {
            cout << " ";
        }
        
        cout << procent << "%" << "|";
        
        for (size_t j = 0; j < height; j++){
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    
    size_t number_count;
    cerr << "Enter an array size\n";
    cin >> number_count;
    cerr << "Enter numbers of array\n";
    const auto numbers = input_numbers(number_count);
    
    size_t bin_count;
    cerr << "Enter a count of bins\n";
    cin >> bin_count;
    const auto bins = make_histogram(bin_count, numbers, number_count);
    
//    show_histogram_text(bins, bin_count, number_count);
    show_histogram_svg(bins, MAX_ASTERISK);
    
    return 0;
}

