#include <iostream>
#include <fstream>

class Piece {
private:
    int start;
    int end;
public:
    ~Piece() {};
    Piece() {};
    Piece(int start_, int end_) : start(start_), end(end_) {}
    int getEnd() const{
        return end;
    }
    int getStart() const{
        return start;
    }
    friend bool operator <=(Piece const& c1, Piece const& c2) {
        return c1.start <= c2.start;
    }
};

template<typename T>
unsigned long long merge_sort_with_count(int len, T* arr) {
    T* copy = new T[len];
    int size_of_arrs = 1;
    bool curr_arr = true;
    T* filled_in_arr = copy;
    T* sorting_arr = arr;
    unsigned long long result = 0;
    while (size_of_arrs < len) {
        if (curr_arr) {
            filled_in_arr = copy;
            sorting_arr = arr;
            curr_arr = false;
        }
        else {
            filled_in_arr = arr;
            sorting_arr = copy;
            curr_arr = true;
        }

        int curr_pos = 0;
        int curr_pos_left = 0;
        int curr_pos_right = 0;
        int right_plus = 0;
        bool installed = false;
        for (int i = 0; i < len; ++i) {
            if (len - curr_pos - size_of_arrs <= 0) {
                while (i != len) {
                    filled_in_arr[i] = sorting_arr[i];
                    ++i;
                }
                break;
            }
            if ((len - curr_pos - 2*size_of_arrs < 0)&&(!installed)) {
                right_plus = size_of_arrs - (len - curr_pos - size_of_arrs);
                installed = true;
            }
            if (curr_pos_left != size_of_arrs && curr_pos_right + right_plus != size_of_arrs) {
                if (sorting_arr[curr_pos + curr_pos_left] <= sorting_arr[curr_pos + size_of_arrs + curr_pos_right]) {
                    filled_in_arr[i] = sorting_arr[curr_pos + curr_pos_left];
                    ++curr_pos_left;
                }
                else {
                    filled_in_arr[i] = sorting_arr[curr_pos + size_of_arrs + curr_pos_right];
                    ++curr_pos_right;
                    result += size_of_arrs - curr_pos_left;
                }
            }
            else if (curr_pos_left == size_of_arrs) {
                filled_in_arr[i] = sorting_arr[curr_pos + size_of_arrs + curr_pos_right];
                ++curr_pos_right;
            }
            else if (curr_pos_right + right_plus == size_of_arrs) {
                filled_in_arr[i] = sorting_arr[curr_pos + curr_pos_left];
                ++curr_pos_left;
            }
            if (curr_pos_right == size_of_arrs && curr_pos_left == size_of_arrs) {
                curr_pos += 2 * size_of_arrs;
                curr_pos_left = 0;
                curr_pos_right = 0;
            }
        }
        size_of_arrs *= 2;
        result = result;
    }

    for (int i = 0; i < len; ++i) {
        arr[i] = filled_in_arr[i];
    }

    delete[] copy;
    return result;
}

unsigned long long counting_of_inter(int len, Piece* arr) {
    unsigned long long result = 0;
    merge_sort_with_count(len, arr);
    int* arr_of_end = new int[len];
    int len_of_inter = 1;
    for (int i = 0; i < len; ++i) {
        arr_of_end[i] = arr[i].getEnd();
        if ((i > 0) && (arr[i].getStart() == arr[i - 1].getStart())) {
            result += len_of_inter;
            ++len_of_inter;
        }
        else {
            len_of_inter = 1;
        }

    }
    result += merge_sort_with_count(len, arr_of_end);
    for (int i = 1; i < len; ++i) {
        if (arr_of_end[i] == arr_of_end[i - 1]) {
            result += len_of_inter;
            ++len_of_inter;
        }
        else {
            len_of_inter = 1;
        }
    }
    delete[] arr_of_end;
    return result;
}

int main(int argc, char* argv[]){
    std::ifstream in(argv[1]);
    int quantity_piece = 1;
    in >> quantity_piece;
    Piece* arr = new Piece[quantity_piece];
    for (int i = 0; i < quantity_piece; ++i) {
        int start;
        int end;
        in >> start;
        in >> end;
        arr[i] = Piece(start, end);
    }
    unsigned long long result = counting_of_inter(quantity_piece, arr);
    std::cout << result;
    delete[] arr;
}
