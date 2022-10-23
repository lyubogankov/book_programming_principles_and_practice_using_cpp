#include<iostream>
#include<limits>
#include<vector>
using namespace std;

int main() {

    vector<double> routes_between_two_cities;

    // Read in the "distance between the two cities along a given route".
    for(double route_distance; cin >> route_distance;)
        routes_between_two_cities.push_back(route_distance);

    // now, compute summary statistics
    double sum=0.0;
    double shortest_route = numeric_limits<double>::max();  // init to  largest possible val
    double longest_route  = numeric_limits<double>::min();  // init to smallest possible val

    for (double d : routes_between_two_cities) {
        // Compute the total distance of all the routes
        sum += d;
        // Shortest route
        if (d < shortest_route)
            shortest_route = d;
        // Longest route
        if (d > longest_route)
            longest_route = d;
    }
    // Mean route
    double mean_distance = sum / routes_between_two_cities.size();

    cout << "Shortest route: " << shortest_route << "\n"
         << " Longest route: " << longest_route  << "\n"
         << "           Sum: " << sum            << "\n"
         << "          Mean: " << mean_distance  << "\n\n";

    return 0;
}
