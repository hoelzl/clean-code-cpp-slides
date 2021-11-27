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

// %%
