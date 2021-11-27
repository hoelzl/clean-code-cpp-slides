// ---
// jupyter:
//   jupytext:
//     formats: cpp:percent
//     text_representation:
//       extension: .cpp
//       format_name: percent
//       format_version: '1.3'
//       jupytext_version: 1.13.1
//   kernelspec:
//     display_name: C++17
//     language: C++17
//     name: xcpp17
// ---

// %% [markdown] slideshow={"slide_type": "slide"}
// # Functions

// %% [markdown] slideshow={"slide_type": "subslide"}
// ## The First Rule for Functions
//
// Functions should be small!

// %% [markdown] slideshow={"slide_type": "fragment"}
// Even smaller than that!

// %% [markdown] slideshow={"slide_type": "fragment"}
// **No more than 4 lines**

// %% [markdown] slideshow={"slide_type": "subslide"}
// ## Do One Thing
//
// - Functions should do one thing
// - They should do it well
// - They should do it only

// %% slideshow={"slide_type": "subslide"}
#include <algorithm>
#include <iostream>
#include <vector>

// %%
int compute_result_save_it_and_print_all_results(int a, int b, std::vector<int>& results) {
    auto new_result = a + b; // complex computation...
    results.push_back(new_result);
    std::for_each(cbegin(results), cend(results), [](int r){ std::cout << r << "\n";});
    return new_result;
}

// %% slideshow={"slide_type": "subslide"}
std::vector<int> my_results{};
std::cout << ">>> 1 <<<\n";
compute_result_save_it_and_print_all_results(1, 2, my_results);
std::cout << "\n>>> 2 <<<\n";
compute_result_save_it_and_print_all_results(4, 6, my_results);

// %%
int compute_result(int a, int b) {
    return a + b;
}

// %%
void save_result(int new_result, std::vector<int>& results) {
    results.push_back(new_result);
}

// %%
void print_results(const std::vector<int>& results) {
    std::for_each(cbegin(results), cend(results), [](int r){ std::cout << r << "\n"; });
}

// %%
// Better, but not ideal...
void process_new_sensor_data(int a, int b, std::vector<int>& results) {
    auto new_result = compute_result(a, b);
    save_result(new_result, results);
    print_results(results);
}

// %%
std::vector<int> my_results{};
std::cout << ">>> 1 <<<\n";
process_new_sensor_data(1, 2, my_results);
std::cout << "\n>>> 2 <<<\n";
process_new_sensor_data(4, 6, my_results);

// %% slideshow={"slide_type": "subslide"}
#include <iostream>

class TrafficEstimator {
public:
    void add_data(int vehicles_lane_a, int vehicles_lane_b) {
        auto new_estimate = compute_estimate(vehicles_lane_a, vehicles_lane_b);
        save_estimate(new_estimate);
    }
    
    const std::vector<int>& get_estimates() const { return estimates; }
    
    friend std::ostream& operator<<(std::ostream& os, const TrafficEstimator& estimator) {
        auto& estimates{estimator.get_estimates()};
        std::for_each(cbegin(estimates), cend(estimates), [&os](int r) { os << r << "\n"; });
        return os;
    }
    
private:
    static int compute_estimate(int vehicles_lane_a, int vehicles_lane_b) {
        return vehicles_lane_a + vehicles_lane_b;
    }
    
    void save_estimate(int new_estimate) {
        estimates.push_back(new_estimate);
    }
    
    std::vector<int> estimates{};
};

// %% slideshow={"slide_type": "subslide"}
TrafficEstimator estimator{};
std::cout << ">>> 1 <<<\n";
estimator.add_data(1, 2);
std::cout << estimator << "\n";
std::cout << ">>> 2 <<<\n";
estimator.add_data(4, 6);
std::cout << estimator << "\n";

// %%
