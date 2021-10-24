#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <typeinfo>

void replace_input_string(std::string& base) {
	constexpr char opening = '(';
	constexpr char closed = ')';

	std::unordered_map<char, int16_t, std::hash<char>> char_map;
	std::transform(base.begin(), base.end(), base.begin(),
		[](unsigned char c) { return std::tolower(c); });
	int counter{ 0 };
	for (auto& x : base) {
		if (char_map.count(x) == 0) {
			char_map.insert(std::make_pair(x, counter));
			x = opening;
		}
		else {
			auto search = char_map.find(x);
			if (search != char_map.end()) {
				x = closed;
				if (search->second != -1) {
					base[search->second] = closed;
					search->second = -1;
				}
			}
		}
		counter++;
	}
}



int main()
{
	
	std::string test;
	std::cin >> test;
	replace_input_string(test);
	std::cout << test;
}

