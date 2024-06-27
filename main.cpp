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
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox= '0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "yellow") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

void
svg_end() {
    cout << "</svg>\n";
}

void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 850;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    
    size_t max_count = bins[0];
    for (double bin: bins){
        if (bin > max_count){
            max_count = bin;
        }
    }
    
    double top = 0;
    for (size_t bin : bins) {
        size_t height = 0;
        if (max_count > MAX_ASTERISK){
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
        }
        else {
            height = bin;
        }
        
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();
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
    show_histogram_svg(bins);
    
    return 0;
}

