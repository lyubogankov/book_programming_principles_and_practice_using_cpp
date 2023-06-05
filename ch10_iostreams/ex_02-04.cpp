/*
2. Write a program that creates a file of data in the form of the temperature Reading type defined in §10.5.
    For testing, fill the file with at least 50 “temperature readings.

3. Write a program that reads the data from raw_temps.txt created in exercise 2 into a vector
    and then calculates the mean and median temperatures in your data set.

4. Modify the program from exercise 2 to include a temperature suffix c for Celsius or f for Fahrenheit temperatures.
    Then modify the program from exercise 3 to test each temperature, 
    converting the Celsius readings to Fahrenheit before putting them into the vector.
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

struct Reading {
    int hour;
    double temperature;
};
// for sorting
// q: why do folks define a separate struct in which to put the operator overloading function?
//      https://stackoverflow.com/a/1380496
bool operator<(const Reading& r1, const Reading& r2) { return r1.temperature < r2.temperature; }
bool operator>(const Reading& r1, const Reading& r2) { return r1.temperature > r2.temperature; }

const string DEFAULT_FILENAME = "readings.txt";

void create_temperature_reading_file(string filename = DEFAULT_FILENAME) {
    // https://en.cppreference.com/w/cpp/numeric/random
    default_random_engine e1(1); // seeding with a constant for repeatable generation
    uniform_int_distribution<int> uniform_dist_hours(0, 23);
    uniform_int_distribution<int> uniform_dist_temperature(200, 1200);  // will divide by 10 to get doubles
    uniform_int_distribution<int> uniform_dist_c_or_f(0, 1);

    ofstream ost {filename};
    if (!ost) throw runtime_error("Could not open file for output.");

    // changes for part 3: 
    // - instead of directly outputting hour / temperature, also generating random number for c vs f
    // - if 0, f = keep the temperature value as-is
    // - if 1, c = convert f -> c before writing to file
    for (int i = 0; i < 50; i++) {
        ost << uniform_dist_hours(e1) << " ";
        switch(uniform_dist_c_or_f(e1)) {
            case 0:
                ost << uniform_dist_temperature(e1) / 10.0 << "f ";
                break;
            case 1:
                ost << ((uniform_dist_temperature(e1) / 10.0) - 32) * 5/9 << "c "; // f -> c
                break;
        }
        ost << "\n";
    }
}

void obtain_temperature_readings_from_file(vector<Reading>& readings, string filename = DEFAULT_FILENAME) {
    ifstream ist {filename};
    if (!ist) throw runtime_error("Could not open file for input.");

    // changes for #3
    // - also obtaining a char from the file
    // - now, instead of directly putting into readings, need to convert c->f
    int hour;
    double temperature;
    char unit;
    while (ist >> hour >> temperature >> unit) {
        switch(unit) {
            case 'f':
                readings.push_back(Reading{hour, temperature});
                break;
            case 'c':
                readings.push_back(Reading{
                    hour, 
                    (temperature * 9 / 5) + 32 // c -> f
                });
                break;
        }
    }
}
void calculate_temperature_statistics(string filename = DEFAULT_FILENAME) {
    vector<Reading> readings;
    obtain_temperature_readings_from_file(readings, DEFAULT_FILENAME);

    // to get the mean, iterate over the temperatures!
    double sum = 0;
    for (Reading r : readings)
        sum += r.temperature;
    double mean = sum / readings.size();

    // to get the median, sort the readings!
    // (This worked!  I printed out the before/after readings)
    sort(readings.begin(), readings.end());

    // code from ch08 ex_11.cpp
    double median = 0;
    int mid = readings.size() / 2;
    if (readings.size() % 2 == 0) {
        median = double(readings[mid].temperature + readings[mid - 1].temperature) / 2;
    } else {
        median = readings[mid].temperature;
    }

    // since I used a uniform distribution, the mean/median are very similar!
    // ex03: mean 68.778, median 69.95
    // ex04: mean 67.664, median 68.8
    cout << "mean:   " << mean   << "\n"
         << "median: " << median << "\n";
}

int main() {
    create_temperature_reading_file();
    calculate_temperature_statistics();
    return 0;
}