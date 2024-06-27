#include "histogram.h"

void find_minmax(const vector<double> numbers, double& min, double& max) {
    if (numbers.size() == 0) {
        return;
    }
    
    min = numbers[0];
    max = numbers[0];
    
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
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
show_histogram_svg(const vector<size_t>& bins, const size_t MAX_ASTERISK, double number_count) {
    const auto IMAGE_WIDTH = 850;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    
    size_t max_count = bins[0];
    for (double bin: bins) {
        if (bin > max_count) {
            max_count = bin;
        }
    }

    
    double top = 0;
    for (size_t bin : bins) {
        size_t procent = 100 * (static_cast<double>(bin) / number_count);
        
        string procent_result = to_string(procent) + "%";
        size_t height = 0;
        size_t new_max_count = 0;
        
        if (max_count > MAX_ASTERISK){
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
            new_max_count = MAX_ASTERISK;
        }
        else {
            height = bin;
            new_max_count = max_count;
        }
        
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(height));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        svg_text((new_max_count * BLOCK_WIDTH) + (TEXT_LEFT * 3), top + TEXT_BASELINE, procent_result);
        top += BIN_HEIGHT;
    }
    svg_end();
}
