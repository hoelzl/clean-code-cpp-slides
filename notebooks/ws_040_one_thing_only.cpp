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

#import <iostream>
#import <string>
#import <vector>

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

std::vector<double> all_salaries{};
double tax_1{handle_money_stuff(3, 240.0, "Joe", all_salaries)};
double tax_2{handle_money_stuff(5, 240.0, "Jack", all_salaries)};
double tax_3{handle_money_stuff(6, 260.0, "Jill", all_salaries)};
double tax_4{handle_money_stuff(6, 800.0, "Jane", all_salaries)};
