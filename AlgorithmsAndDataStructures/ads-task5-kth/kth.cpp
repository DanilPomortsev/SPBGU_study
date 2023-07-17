#include <iostream>
#include <fstream>


template <typename T>
int partition(T* arr, int start, int end, T sortedBy) {
	while (true) {
		while (arr[start] < sortedBy) {
			++start;
		}

		while (arr[end] > sortedBy) {
			--end;
		}

		if (start >= end) {
			return end;
		}

		T tmp = arr[start];
		arr[start] = arr[end];
		arr[end] = tmp;
		++start;
		--end;
	}
	return end;
}


template <typename T>
void quickSelectAll(T* arr, int start, int end, int k1, int k2) {
	if (start >= end) {
		return;
	}

	T sortedBy = arr[start + (end - start) / 2];
	int partition_idx = partition(arr, start, end, sortedBy);


	if (partition_idx < k1) {
		quickSelectAll(arr, partition_idx + 1, end, k1, k2);
	}
	else if (partition_idx >= k2) {
		quickSelectAll(arr, start, partition_idx, k1, k2);
	}
	else {
		quickSelectAll(arr, start, partition_idx, k1, k2);
		quickSelectAll(arr, partition_idx + 1, end, k1, k2);
	}
}

int main(int argc, char* argv[]) {
	std::ofstream out(argv[2]);
	std::ifstream in(argv[1]);

	int n;
	int k1;
	int k2;
	int A;
	int B;
	int C;
	int x_0;
	int x_1;
	in >> n;
	in >> k1;
	in >> k2;
	in >> A;
	in >> B;
	in >> C;
	in >> x_0;
	in >> x_1;

	int* arr = new int[n];
	arr[0] = x_0;
	arr[1] = x_1;

	for (int i = 2; i < n; ++i) {
		arr[i] = arr[i - 2] * A + arr[i - 1] * B + C;
	}

	quickSelectAll(arr, 0, n - 1, k1 - 1, k2 - 1);

	for (int i = k1 - 1; i < k2; ++i) {
		if (i == k2 - 1) {
			out << arr[i];
		}
		else {
			out << arr[i] << " ";
		}
	}

	in.close();
	out.close();
	delete[] arr;
	return 0;
}
