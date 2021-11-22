#include <iostream>
#include <chrono>
#include "DocParser.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc == 1)
        cout << "Please provide a directory" << endl;
    else {
        int max = 0;
        cout << "How many files would you like to parse?: ";
        cin >> max;

        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

        DocParser d(argv[1], max);
        d.getFiles();

        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

        cout << "It took me " << time_span.count() << " seconds." << endl;
    }
    return 0;
}
