#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    // Sections in the supermarket
    vector<string> sections = {"Clothing", "Gaming", "Grocery", "Stationery"};
    int num_sections = sections.size();

    // To store prices of items in each section
    vector<vector<int>> prices(num_sections);

    // Taking user input for each section
    for (int i = 0; i < num_sections; ++i) {
        int num_items;
        cout << "Enter the number of items in " << sections[i] << " section: ";
        cin >> num_items;

        prices[i].resize(num_items);
        cout << "Enter the prices of the items in " << sections[i] << ":\n";
        for (int j = 0; j < num_items; ++j) {
            cin >> prices[i][j];
        }
    }

    vector<int> section_totals_serial(num_sections, 0);  // Serial section totals
    vector<int> section_totals_parallel(num_sections, 0);  // Parallel section totals
    int final_total_serial = 0;                           // Serial total bill
    int final_total_parallel = 0;                         // Parallel total bill

    // Serial computation of section totals
    double start_serial = omp_get_wtime();
    for (int i = 0; i < num_sections; ++i) {
        for (int price : prices[i]) {
            section_totals_serial[i] += price;
        }
        final_total_serial += section_totals_serial[i];
    }
    double end_serial = omp_get_wtime();

    // Parallel computation of section totals
    double start_parallel = omp_get_wtime();
    #pragma omp parallel for reduction(+:final_total_parallel)
    for (int i = 0; i < num_sections; ++i) {
        int section_sum = 0;
        for (int price : prices[i]) {
            section_sum += price;
        }
        section_totals_parallel[i] = section_sum;
        final_total_parallel += section_sum;  // Accumulate to final total
    }
    double end_parallel = omp_get_wtime();

    // Output section-wise totals (serial)
    cout << "\nSerial bill details per section:\n";
    for (int i = 0; i < num_sections; ++i) {
        cout << sections[i] << " total: " << section_totals_serial[i] << endl;
    }

    // Output section-wise totals (parallel)
    cout << "\nParallel bill details per section:\n";
    for (int i = 0; i < num_sections; ++i) {
        cout << sections[i] << " total: " << section_totals_parallel[i] << endl;
    }

    // Output final totals
    cout << "\nFinal total amount to be paid (Serial): " << final_total_serial << endl;
    cout << "Final total amount to be paid (Parallel): " << final_total_parallel << endl;
    cout << "Parallel Time: " << end_parallel - start_parallel << " seconds\n";
    	cout << "Serial Time: " << end_serial - start_serial << " seconds\n";


    return 0;
}
