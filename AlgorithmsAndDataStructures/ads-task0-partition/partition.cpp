#include <iostream>

long long partition(int n, int k);

int main() {
	int n = 0;
	int k = 0;
	std::cin >> n >> k;
	std::cout << partition(n, k);
	return 0;
}

long long partition(int n, int k) {
	long long* arr_first = new long long[n + 1];
	long long* arr_second = new long long[n + 1];
	bool flag_first = true;
	for (int i = 1; i < n + 1; ++i) {
		arr_first[i] = 1;
	}
	int count_of_row = 2;
	long long result;
	while (count_of_row <= k) {
		if (flag_first) {
			for (int i = 1; i < n + 1; ++i) {
				if (i < count_of_row) {
					arr_second[i] = 0;
				}
				else if (i == count_of_row) {
					arr_second[i] = 1;
				}
				else {
					arr_second[i] = arr_first[i - 1] + arr_second[i - count_of_row];
				}
			}
			flag_first = false;
		}
		else
		{
			for (int i = 1; i < n + 1; ++i) {
				if (i < count_of_row) {
					arr_first[i] = 0;
				}
				else if (i == count_of_row) {
					arr_first[i] = 1;
				}
				else {
					arr_first[i] = arr_second[i - 1] + arr_first[i - count_of_row];
				}
			}
			flag_first = true;
		}
		++count_of_row;
	}
	if (flag_first) {
		result = arr_first[n];
	}
	else {
		result = arr_second[n];
	}
	delete[] arr_first;
	delete[] arr_second;
	return result;
}
