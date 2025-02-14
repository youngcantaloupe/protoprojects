#include <bitset>
#include <iostream>
using namespace std;

int main() {
    cout << "Enter the integer that holds the bits: ";
    unsigned int n;
    cin >> n;

    cout << "Enter the rightmost bit position: ";
    unsigned int k;
    cin >> k;

    cout << "Enter the leftmost bit position: ";
    unsigned int m;
    cin >> m;

    cout << "Extracting bits " << k << " through " << m << " from " << n << " = " << bitset<32>(n)
         << endl;

    unsigned int mask = (1 << m) - 1;
    mask <<= k - 1;
    auto temp = n & mask;
    auto result = temp >> k;

    cout << result << " = " << bitset<32>(result) << endl;
}

/*unsigned int mask = (n << (m - k + 1)) - 1;*/
/*mask = (1 >> m) - 1;*/
/*auto temp = n & mask;*/
/*auto result = temp >> k;*/

/*mask <<= k;
/*int result;*/
/*result = n & mask;*/
/*result >>= k;*/
/*cout << k << endl;*/

/*(n & (((1 << (m - k + 1)) - 1) << k)) >> k;*/
/*cout << k << endl;*/
/*cout << n << endl;*/
/*cout << m << endl;*/

/*unsigned int mask = (1 << (m - k + 1)) - 1;*/
/*mask <<= m;*/
/*int temp = n & mask;*/
/*mask >>= k;*/
/*cout << (n & mask) << endl;*/
/*cout << n << endl;*/
/*cout << k << endl;*/
/*cout << m << endl;*/
/*cout << temp << endl;*/
/*cout << mask << endl;*/
