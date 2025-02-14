#include <iostream>
using namespace std;

void determineHighway(int highway) {
    if (highway % 100 == 0) {
        cout << highway << " is not a valid interstate highway number." << endl;
        exit(0);
    }
    if (highway > 0 && highway < 100) {
        if (highway % 2 == 0) {
            cout << "I-" << highway << " is primary, going east/west." << endl;
        } else {
            cout << "I-" << highway << " is primary, going north/south." << endl;
        }
    } else if (highway > 100 && highway < 1000) {
        int service = highway % 100;
        if (highway % 2 == 0) {
            cout << "I-" << highway << " is auxiliary, serving I-" << service
                 << ", going east/west." << endl;

        } else {
            cout << "I-" << highway << " is auxiliary, serving I-" << service
                 << ", going north/south." << endl;
        }
    } else {
        cout << "Invalid number entered" << endl;
        exit(0);
    }
}

int main() {
    int highwayNumber;

    cin >> highwayNumber;

    determineHighway(highwayNumber);

    return 0;
}
