#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
			// create window for w
			unsigned long long w[5] = {0, 0, 0, 0, 0};
			unsigned long long curr_val = 0;
			int w_index= 4;
			int k_index = 0;
			unsigned long long curr_power = 1;

        // Add your code here
				for (int i = k.size() - 1; i >= 0; i--) {
					curr_val += letterDigitToNumber(k[i]) * curr_power;
					curr_power *= 36;
					k_index++;

					if (k_index == 6 || i == 0) {
						if (w_index >= 0) {
							w[w_index--] = curr_val;
							k_index = 0;
							curr_val = 0;
							curr_power = 1;
						}
					}
				}

			// calculate the hash
			unsigned long long hash = 0;
			for (int j = 0; j <= 4; j++) {
				hash += static_cast<unsigned long long>(rValues[j]) * w[j];
			}

			return static_cast<HASH_INDEX_T>(hash);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

				// just return the value of each letter given the mapping
				if (std::isalpha(letter)) {
					char l = std::tolower(letter);
					return static_cast<HASH_INDEX_T>(l - 'a');
				}
				
				else if (std::isdigit(letter)) {
					return static_cast<HASH_INDEX_T>(letter - '0') + 26;
				}

				return 0;
		}

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
