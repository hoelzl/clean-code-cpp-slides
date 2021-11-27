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

// %% slideshow={"slide_type": "subslide"}
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

// %% slideshow={"slide_type": "subslide"}
// Better, but not ideal. (See later for further refinement.)
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

// %% [markdown]
// ## Workshop
//
// See `ws_040_one_thing_only`, Section "Do one thing only".

// %% [markdown]
// ## Abstraction Levels
//
// Everything the function does in its body should be one (and only one) level of abstraction below the function itself.

// %% [markdown]
// ### "To" Paragraphs: Checking Levels of Abstraction
//
// - To `render_page_with_setups_and_teardowns()`
// - we check to see whether the page is a test page and
// - if so, we include the setups and teardowns.
// - In either case we render the page in HTML.

// %% [markdown]
// ### The Step-Down Rule
//
// - We want code to read like a top-down narrative
// - Every function should be followed by those one level of abstraction below it

// %% slideshow={"slide_type": "subslide"}
class Page{
    void render_page_with_setups_and_teardowns() {
        if (is_test_page()) {
            include_setups_and_teardowns();
        }
        render_page_to_html();
    }

    bool is_test_page() { return false; }
    void include_setups_and_teardowns() {}
    void render_page_to_html() {}
};

// %% [markdown] slideshow={"slide_type": "slide"}
// ## Switches and Abstractions
//
// - `switch`-statements often perform operations on the same level of abstraction
// - often for "subtypes" of the original type
// - "subtypes" are sometimes distinguished by type tags:

// %% slideshow={"slide_type": "subslide"}
enum class EmployeeType {
    commissioned,
    hourly,
    salaried,
}

// %%
struct Money {
    long amount_in_cents{};
    // ...
}

// %%
struct Employee {
    EmployeeType type{};
    // ...
}

// %% slideshow={"slide_type": "subslide"}
Money calculate_commissioned_pay(Employee e) {
    std::cout << "Calculating pay for commissioned employee.";
    return Money{};
}

// %%
Money calculate_hourly_pay(Employee e) {
    std::cout << "Calculating pay for hourly employee.";
    return Money{}; 
}

// %%
Money calculate_salaried_pay(Employee e) {
    std::cout << "Calculating pay for salaried employee.";
    return Money{}; 
}

// %% slideshow={"slide_type": "subslide"}
Money calculate_pay(Employee e) {
    switch (e.type) {
        case EmployeeType::commissioned:
            return calculate_commissioned_pay(e);
        case EmployeeType::hourly:
            return calculate_hourly_pay(e);
        case EmployeeType::salaried:
            return calculate_salaried_pay(e);
    }
}

// %%
Employee an_employee{EmployeeType::commissioned};
calculate_pay(an_employee);

// %%
an_employee = Employee{EmployeeType::hourly};
calculate_pay(an_employee);

// %%
an_employee = Employee{EmployeeType::salaried};
calculate_pay(an_employee);

// %% [markdown] slideshow={"slide_type": "subslide"}
// It is often better to replace this with "real" subtyping and polymorphism:

// %%
struct AbstractEmployee {
    virtual Money calculate_pay() const = 0;
}

// %%
struct CommissionedEmployee : public AbstractEmployee {
    virtual Money calculate_pay() const override {
        std::cout << "Calculating pay for commissioned employee.";
        return Money{};
    }
}

// %%
struct HourlyEmployee : public AbstractEmployee {
    virtual Money calculate_pay() const override {
        std::cout << "Calculating pay for hourly employee.";
        return Money{};
    }
}

// %%
struct SalariedEmployee : public AbstractEmployee {
    virtual Money calculate_pay() const override {
        std::cout << "Calculating pay for salaried employee.";
        return Money{};
    }
}

// %%
#include <memory>
std::unique_ptr<AbstractEmployee> create_employee(EmployeeType type) {
    switch (type) {
        case EmployeeType::commissioned:
            return std::make_unique<CommissionedEmployee>();
        case EmployeeType::hourly:
            return std::make_unique<HourlyEmployee>();
        case EmployeeType::salaried:
            return std::make_unique<SalariedEmployee>();
    }
}

// %%
std::unique_ptr<AbstractEmployee> my_employee{create_employee(EmployeeType::commissioned)};
my_employee->calculate_pay();

// %%
my_employee = create_employee(EmployeeType::hourly);
my_employee->calculate_pay();

// %%
my_employee = create_employee(EmployeeType::salaried);
my_employee->calculate_pay();

// %% [markdown] slideshow={"slide_type": "slide"}
// ## More Rules for Functions
//
// - Use descriptive names
// - Use few (or no) arguments
// - Don't use Boolean arguments
// - Avoid *hidden* side effects

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Hidden Side Effects

// %%
std::unique_ptr<AbstractEmployee> find_employee_by_name(const std::string& name) {
    return create_employee(EmployeeType::salaried);
}

// %%
std::string get_encrypted_phrase(const std::string& phrase) { return phrase; }

// %%
std::string decrypt(const std::string& coded_phrase, const std::string& password) {
    return coded_phrase;
}

// %%
struct Session {
    void initialize() {
        std::cout << ">>> Initializing session <<<\n";
    }
}

// %%
Session session{};

// %% slideshow={"slide_type": "subslide"}
#include <string>
using namespace std::string_literals;

// %% slideshow={"slide_type": "-"}
bool check_password(std::string user_name, std::string password) {
    auto user = find_employee_by_name(user_name);
    if (user) {
        auto phrase = "Hello, world."s;
        auto encrypted_phrase = get_encrypted_phrase(phrase);
        auto decrypted_phrase = decrypt(encrypted_phrase, password);
        if (decrypted_phrase == phrase) {
            session.initialize();
            return true;
        }
    }
    return false;
}

// %%
check_password("Joe", "asdf");

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Avoid Output Arguments

// %%
struct HitResult {
    bool did_collision_occur{false};
    // ...
};

// %%
// Object that can occur in a video game
struct BadActor {
    void check_collision(const BadActor& other_actor, HitResult& hit_result) {
        if (&other_actor != this /* && complex stuff... */) {
            hit_result.did_collision_occur = true;            
        }
    }
};

// %% slideshow={"slide_type": "subslide"}
BadActor a1{};
BadActor a2{};

// %%
HitResult hit_result_1{};
a1.check_collision(a1, hit_result_1);
hit_result_1.did_collision_occur

// %%
HitResult hit_result_2{};
a1.check_collision(a2, hit_result_2);
hit_result_2.did_collision_occur

// %%
// Object that can occur in a video game
struct GoodActor {
    HitResult check_collision(const GoodActor& other_actor) {
        HitResult hit_result{};
        if (&other_actor != this /* && complex stuff... */) {
            hit_result.did_collision_occur = true;            
        }
        return hit_result;
    }
};

// %% slideshow={"slide_type": "subslide"}
GoodActor a3{};
GoodActor a4{};

// %%
HitResult hit_result_3{a3.check_collision(a3)};
hit_result_3.did_collision_occur

// %%
HitResult hit_result_4{a3.check_collision(a4)};
hit_result_4.did_collision_occur

// %% [markdown]
// ### Command-Query Separation

// %%
struct NoCommandQuerySeparation {
    int default_value{-1};
    bool has_default_value() {
        if (default_value >= 0) {
            return true;
        }
        else {
            default_value = 123;
            return false;
        }
    }
}

// %%
NoCommandQuerySeparation no_cqs{};
std::cout << "Has default value? " << no_cqs.has_default_value() << "\n";
std::cout << "Has default value? " << no_cqs.has_default_value() << "\n";

// %% slideshow={"slide_type": "subslide"}
struct CommandQuerySeparation {
    int default_value{-1};

    bool has_default_value() {
        return default_value >= 0;
    }
    
    void set_default_value(int new_value = 123) {
        default_value = new_value;
    }
}

// %%
CommandQuerySeparation cqs{};
std::cout << "Has default value? " << cqs.has_default_value() << "\n";
std::cout << "Has default value? " << cqs.has_default_value() << "\n";
cqs.set_default_value();
std::cout << "Has default value? " << cqs.has_default_value() << "\n";

// %% [markdown]
// ### DRY: Don't Repeat Yourself
//
// - Try to eliminate duplicate code
//     - It bloats the code
//     - It requires multiple modifications for every change
// - But: often duplicated code is interspersed with other code
// - Take into account the scope in which you keep the code DRY!

// %% [markdown] slideshow={"slide_type": "subslide"}
// ## Breaking up Functions into Classes
//
// When refactoring functions it is often useful to create a class that maintains the state that was contained in the original function.

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
