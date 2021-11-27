// ---
// jupyter:
//   jupytext:
//     formats: cpp:light
//     text_representation:
//       extension: .cpp
//       format_name: light
//       format_version: '1.5'
//       jupytext_version: 1.13.1
//   kernelspec:
//     display_name: C++17
//     language: C++17
//     name: xcpp17
// ---

// # Workshops for Functions

// ## Do one thing only
//
// The following function does more than one thing. 
//
// Split it into several functions so that each does one thing only. 
// Ensure that
// - each function does its job well, 
// - all names are appropriate, and
// - the code is easy to understand.

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

double handle_money_stuff(int i_dow, double d_spd, const char* pc_n, std::vector<double>& dv_slrs) {
    static std::string sa_dns[] {"Mon", "Tue", "Wed", "Thu", "Fri"};
    // We count Sunday as 1, Monday as 2, etc. but the work week starts on Monday
    std::string& sr_d{sa_dns[i_dow-2]};
    // Compute the salary so far, based on the day of week and the salary per day
    double d_ssf{(i_dow-1) * d_spd};
    // Compute the tax
    double d_t{0.0};
    if (d_ssf > 500.0 && d_ssf <= 1000.0) {
        d_t = d_ssf * 0.05;
    } 
    else if (d_ssf > 500.0 && d_ssf <= 2000.0) {
        d_t = d_ssf * 0.1;
    }
    else if (d_ssf > 500.0) {
        d_t = d_ssf * 0.15;
    }
    // Update the salary based on the tax to pay
    d_ssf = d_ssf - d_t;
    // Add the salary to the vector of all salaries paid
    dv_slrs.push_back(d_ssf);
    std::cout << pc_n << " worked till " << sr_d << " and earned $" << d_ssf << " this week.\n";
    std::cout << "  " << "Their taxes were $" << d_t << "." << std::endl;
    return d_t;
}

#ifdef __CLING__
std::vector<double> all_salaries{};
double tax_1{handle_money_stuff(3, 240.0, "Joe", all_salaries)};
double tax_2{handle_money_stuff(5, 240.0, "Jack", all_salaries)};
double tax_3{handle_money_stuff(6, 260.0, "Jill", all_salaries)};
double tax_4{handle_money_stuff(6, 800.0, "Jane", all_salaries)};
#endif

#ifdef __CLING__
std::cout << tax_1 << ", " << tax_2 << ", " << tax_3 << ", " << tax_4 << "\n";
#endif

// ## Proposal for Solution

void assert_valid_day_number(int day_number) {
    if (day_number < 1 || day_number > 7) {
        throw std::domain_error("The value of day_number must be between 1 and 7.");
    }
}

const std::string& compute_day_of_week_name(int day_number) {
    const static std::array<const std::string, 7> day_names{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    assert_valid_day_number(day_number);
    return day_names.at(day_number - 1);
}

double compute_tax_rate(int salary) {
    if (salary <= 500.0) {
        return 0.0;
    } else if (salary <= 1000.0) {
        return 0.05;
    } else if (salary <= 2000.0) {
        return 0.1;
    } else {
        return 0.15;
    }
}

double compute_salary_before_taxes(int day_number, double salary_per_day) {
    assert_valid_day_number(day_number);
    return (day_number - 1) * salary_per_day;
}

double compute_taxes(double salary_before_taxes) {
    return salary_before_taxes * compute_tax_rate(salary_before_taxes);
}

double compute_taxes(int day_number, double salary_per_day) {
    auto salary_before_taxes = compute_salary_before_taxes(day_number, salary_per_day);
    return compute_taxes(salary_before_taxes);
}

double compute_salary_after_taxes(int day_number, double salary_per_day) {
    auto salary_before_taxes = compute_salary_before_taxes(day_number, salary_per_day);
    auto taxes = compute_taxes(salary_before_taxes);
    return salary_before_taxes - taxes;
}

void store_salary(double salary, std::vector<double>& all_salaries) {
    all_salaries.push_back(salary);
}

void print_salary(int day_number, double salary_per_day, const char* employee_name) {
    std::cout << employee_name << " worked till " << compute_day_of_week_name(day_number)
              << " and earned $" << compute_salary_after_taxes(day_number, salary_per_day)
              << " this week.\n";
    std::cout << "  " << "Their taxes were $" << compute_taxes(day_number, salary_per_day) << ".";
    std::cout << std::endl;
}

double process_salary(int day_number, double salary_per_day, const char* employee_name,
                      std::vector<double>& all_salaries) {
    auto salary_after_taxes = compute_salary_after_taxes(day_number, salary_per_day);
    store_salary(salary_after_taxes, all_salaries);
    print_salary(day_number, salary_per_day, employee_name);
    return compute_taxes(day_number, salary_per_day);
}

#ifdef __CLING__
std::vector<double> all_salaries{};
double tax_1{process_salary(3, 240.0, "Joe", all_salaries)};
double tax_2{process_salary(5, 240.0, "Jack", all_salaries)};
double tax_3{process_salary(6, 260.0, "Jill", all_salaries)};
double tax_4{process_salary(6, 800.0, "Jane", all_salaries)};
#endif

#ifdef __CLING__
std::cout << tax_1 << ", " << tax_2 << ", " << tax_3 << ", " << tax_4 << "\n";
#endif

void show_compute_day_of_week_name() {
    std::array<int, 7> valid_day_numbers{};
    std::iota(begin(valid_day_numbers), end(valid_day_numbers), 1);
    std::for_each(begin(valid_day_numbers), end(valid_day_numbers),
                  [](int day) {std::cout << "Day " << day << ": " << compute_day_of_week_name(day) << "\n"; });
    try {
        compute_day_of_week_name(0);
    }
    catch (std::domain_error err) {
        std::cout << "Caught expected error for day 0: " << err.what() << std::endl;
    }
    try {
        compute_day_of_week_name(8);
    }
    catch (std::domain_error err) {
        std::cout << "Caught expected error for day 8: " << err.what() << std::endl;
    }
}

#ifdef __CLING__
show_compute_day_of_week_name();
#endif

void show_compute_tax_rate() {
    for (double salary : {400.0, 500.0, 600.0, 1000.0, 1500.0, 2000.0, 3000.0}) {
        std::cout << "Salary: " << salary << ", tax rate: " << compute_tax_rate(salary) << "\n";
    }
}

#ifdef __CLING__
show_compute_tax_rate();
#endif

// ## Machine code for simplified versions
//
// It may seem the repeatedly performing the `compute_salary_before_taxes()` and `compute_taxes()` might have a huge impact on performance. However, this is not necessarily the case, since C++ compilers are often very good at optimizing code and removing redundant computations. Here is the assembly generated for simplified versions of these functions (without storing the value and outputting the result and omitting the range check for `process_salary()`). The work performed by the two functions seems to be comparable.
//
// (However, for more complex functions the compiler may not be able to optimize away multiple calls, so it pays to profile the result.)

// ```
// handle_money_stuff(int, double, char const*):
//         movapd  xmm1, xmm0
//         sub     edi, 1
//         pxor    xmm0, xmm0
//         cvtsi2sd        xmm0, edi
//         mulsd   xmm0, xmm1
//         comisd  xmm0, QWORD PTR .LC1[rip]
//         jbe     .L12
//         movsd   xmm1, QWORD PTR .LC2[rip]
//         comisd  xmm1, xmm0
//         jb      .L13
//         mulsd   xmm0, QWORD PTR .LC3[rip]
//         ret
// .L12:
//         pxor    xmm0, xmm0
//         ret
// .L13:
//         movsd   xmm1, QWORD PTR .LC4[rip]
//         comisd  xmm1, xmm0
//         jb      .L14
//         mulsd   xmm0, QWORD PTR .LC5[rip]
//         ret
// .L14:
//         mulsd   xmm0, QWORD PTR .LC6[rip]
//         ret
// ```

// ```
// process_salary(int, double, char const*):
//         movapd  xmm1, xmm0
//         sub     edi, 1
//         pxor    xmm0, xmm0
//         cvtsi2sd        xmm0, edi
//         mulsd   xmm0, xmm1
//         pxor    xmm1, xmm1
//         cvttsd2si       eax, xmm0
//         cmp     eax, 500
//         jle     .L39
//         movsd   xmm1, QWORD PTR .LC3[rip]
//         cmp     eax, 1000
//         jle     .L39
//         movsd   xmm1, QWORD PTR .LC5[rip]
//         cmp     eax, 2000
//         jle     .L39
//         movsd   xmm1, QWORD PTR .LC6[rip]
// .L39:
//         mulsd   xmm0, xmm1
//         ret
// ```


