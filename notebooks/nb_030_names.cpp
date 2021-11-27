// ---
// jupyter:
//   jupytext:
//     formats: ipynb,cpp:percent
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
// # Names
//
// Never underestimate the power of names!

// %% [markdown]
// ## What is a good name?
//
// A good name:
// - Answers these questions:
//   - Why does this exist?
//   - What does it do?
//   - How is it used?
// - Communicates
// - Is generally not easy to find

// %% [markdown]
// ## Ottinger's Rule: Use Self-Explanitory Names

// %%
// BAD:

// Elapsed time in days
int d;

// %%
// GOOD:
int elapsed_time_in_days{0};

// %% [markdown]
// ## Why are good names important?

// %% slideshow={"slide_type": "subslide"}
#include <iostream>
#include <stdexcept>

// %%
double foo(double a, double b)
{
    if (b > 40.0) {
        throw std::logic_error("Not allowed!");
    }
    return a * 40.0 + b * 60.0;
}

// %% slideshow={"slide_type": "-"}
foo(160.0, 20.0)

// %%
try {
    foo(160.0, 60.0);
}
catch(std::logic_error err) {
    std::cout << "Caught logic error!\n";
}

// %% slideshow={"slide_type": "subslide"}
constexpr double regular_pay_per_hour{40.0};
constexpr double overtime_pay_per_hour{60.0};
constexpr double max_allowed_overtime{40.0};

#ifndef TOO_MUCH_OVERTIME
#define TOO_MUCH_OVERTIME
class too_much_overtime : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};
#endif

// %%
too_much_overtime{"Too much overtime!"}

// %% slideshow={"slide_type": "-"}
double compute_total_salary(double regular_hours_worked, double overtime_hours_worked)
{
    if (overtime_hours_worked > max_allowed_overtime) {
        throw too_much_overtime("Too much overtime!");
    }
    double regular_pay{regular_hours_worked * regular_pay_per_hour};
    double overtime_pay{overtime_hours_worked * overtime_pay_per_hour};
    return regular_pay + overtime_pay;
}

// %% slideshow={"slide_type": "subslide"}
compute_total_salary(160.0, 20.0)

// %%
try {
    compute_total_salary(160.0, 60.0);
}
catch (too_much_overtime) {
    std::cout << "Caught too much overtime!\n";
}

// %% [markdown] slideshow={"slide_type": "subslide"}
// ## Why are good names important?
//
// - Names are a powerful tool for communication
// - They are everywhere in the program
// - They tie code to domain concepts

// %% [markdown] slideshow={"slide_type": "subslide"}
//
// ## How to choose a good name?
//
// - Select for expressivity, not convenience
// - Use names that say what they mean and mean what they say
// 	- Otherwise maintenance becomes much harder...
// 	- ... and most of the costs of software come from maintenance.

// %% [markdown] slideshow={"slide_type": "subslide"}
// ## What is a bad name?
//
// - Needs a comment
// - Can only be understood by looking at the code
// - Provides disinformation
// - Does not conform to naming rules

// %% [markdown] slideshow={"slide_type": "slide"}
// ## Naming rules according to Uncle Bob
//
// - Intention-revealing names
// - Pronounceable and searchable names
// - Describe problem, not implementation
// - Avoid disinformation and make meaningful distinctions
// - Avoid encodings (Hungarian notation)
// - Choose parts of speech well
// - Use scope-length rules

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Intention revealing names
//
// Reflect intention, behavior, reason for existence.

// %%
#include <array>

std::array<int, 12> array{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
std::array<int, 12> dpm_arr{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
std::array<int, 12> days_per_month{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Pronounceable names
//
// Use names that are easy to pronounce.

// %%
int hw_crsr{};
int hardware_cursor{};

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Problem, not implementation
//
// - Avoid names that refer to implementation details
// 	- They don't reveal any information about why the code was written the way it is
// 	- Therefore they don't communicate your intentions

// %% slideshow={"slide_type": "subslide"}
#include <algorithm>

int add_array_elements(std::array<int, 12> vec) {
    return std::accumulate(cbegin(vec), cend(vec), 0);
}

// %%
// Seems fine...
add_array_elements(days_per_month)

// %% slideshow={"slide_type": "subslide"}
int compute_yearly_salary(std::array<int, 12> monthly_salaries) {
    return std::accumulate(cbegin(monthly_salaries), cend(monthly_salaries), 0);
}

// %%
// Hmmmm...
compute_yearly_salary(days_per_month)

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Avoid disinformation
//
// - Names mean something
// - Disinformation:
//     - The name's meaning implies something different than its program code:<br/>`int vector_of_cards`
//

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Avoid disinformation: rules
//
// - Avoid platform names `sco`, `aix`, `nt`
// - Don't include a type in a variable name if the variable is not of that type
//     - Mostly: Don't include a type in a variable name at all
// - Be careful with names that differ only slightly
// - Use names that mean something
// - Be consistent when naming

// %%
#include <iostream>
bool is_melee_defence_available{true};
bool is_melee_defense_available{false};
std::cout << (is_melee_defence_available == is_melee_defense_available);

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Meaningful distinction
//
// - Meaningful distinctions:
//     - Use names that express the meaning of concepts as clearly as possible
//     - Use the same name for the same concept
//     - Use clearly different names for different concepts
//

// %%
#include <string>
struct Dog { std::string name{}; };
struct Cat { std::string name{}; };

// %%
Dog a1{"Fluffy"};
Cat a2{"Garfield"};

// %%
Dog my_dog{"Fluffy"};
Cat jons_cat{"Garfield"};

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Avoid encodings such as Hungarian notation
//
// - Avoid Hungarian notation:<br/>``char* pc_text;``
// - Avoid member prefixes:<br/>``std::string m_name;``
// - Avoid C/I prefixes:<br/>``class CClass{};``

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Choose correct parts of speech
//
// - Classes and variales: nouns or noun phrases
// - Functions: verbs or verb phrases
// - Enums: often adjectives
// - Boolean variables and functions: often predicates: `is_foo`, `has_foo`
//
// Possibly:
// - Avoid noisy words, such as `foo_manager`, `foo_processor`, `_data`, `_info`
// - Use getters/setters for accessors

// %% [markdown] slideshow={"slide_type": "subslide"}
// ### Use scope length rules
//
// - Variables:
//     - Long scope = long name
//     - Short scope = short name
// - Classes and Methods
//     - Long scope = small name
//     - Short scope = long name
//     - (Perhaps restrict this to frequently used classes)
// - But see also rule N5 from the Code Smells chapter:
//     - Use long names for long scopes

// %%
#ifndef FIXED_SIZE_COLLECTION
#define FIXED_SIZE_COLLECTION
template <typename T, std::size_t Size>
class FixedSizeOrderedCollectionIndexedByInts{};
#endif

FixedSizeOrderedCollectionIndexedByInts<int, 12> monthly_salaries_1;
std::array<int, 12> monthly_salaries_2;

// %%
