#include <iostream>
#include <fstream>


char* LSD(char** arr_str, int number_string, int len_string, int quantity_of_sort) {
    int* arr_permutation_out = new int[number_string];
    for (int i = 0; i < number_string; ++i) {
        arr_permutation_out[i] = i;
    }

    int* arr_permutation_in = new int[number_string];
    for (int i = 0; i < number_string; ++i) {
        arr_permutation_in[i] = i;
    }

    int* arr_counting = new int[256];
    for (int i = 0; i < 256; ++i) {
        arr_counting[i] = 0;
    }
    int* tmp;

    for (int i = 0; i < quantity_of_sort; ++i) {
        for (int j = 0; j < number_string; ++j) {
            ++arr_counting[(int)arr_str[len_string - 1 - i][j]];
        }

        for (int i = 1; i < 256; ++i) {
            arr_counting[i] += arr_counting[i - 1];
        }

        bool start = true;
        arr_counting[0] = 0;
        int fill_val = 0;
        int curr_val = 0;
        for (int i = 0; i < 256; ++i) {
            if (arr_counting[i] == 0) {
                continue;
            }
            else if (start) {
                curr_val = arr_counting[i];
                arr_counting[i] = 0;
                start = false;
            }
            else {
                if (curr_val != arr_counting[i]) {
                    fill_val = curr_val;
                    curr_val = arr_counting[i];
                }
                arr_counting[i] = fill_val;
            }
        }

        for (int j = 0; j < number_string; ++j) {
            arr_permutation_out[arr_counting[(int)arr_str[len_string - 1 - i][arr_permutation_in[j]]]] = arr_permutation_in[j];
            ++arr_counting[(int)arr_str[len_string - 1 - i][arr_permutation_in[j]]];
        }


        for (int i = 0; i < 256; ++i) {
            arr_counting[i] = 0;
        }
        tmp = arr_permutation_in;
        arr_permutation_in = arr_permutation_out;
        arr_permutation_out = tmp;
    }
    char* result = new char[number_string];
    for (int i = 0; i < number_string; ++i)
        result[i] = arr_str[0][arr_permutation_in[i]];
    delete[] arr_permutation_out;
    delete[] arr_permutation_in;
    delete[] arr_counting;
    return result;
}

int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]);
    int number_string;
    int len_string;
    int quantity_of_sort;
    in >> number_string;
    in >> len_string;
    in >> quantity_of_sort;
    char** arr_str = new char* [len_string];
    char bin[10];
    in.getline(bin, number_string + 1);
    for (int i = 0; i < len_string; ++i) {
        arr_str[i] = new char[number_string+1];
        in.getline(arr_str[i], number_string+1);
    }
    in.close();
    char* result = LSD(arr_str, number_string, len_string, quantity_of_sort);
    std::ofstream out("output.txt");
    for (int i = 0; i < number_string; ++i) {
        out << result[i];
    }
    out.close();
    delete[] result;
    
    for (int i = 0; i < len_string; ++i) {
        delete[] arr_str[i];
    }
    delete[] arr_str;
}

