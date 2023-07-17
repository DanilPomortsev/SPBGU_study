#include <fstream>
#include <cstring>
#include <climits>



class Heap {
    int* arr;
    int indexes[30002];
    int length;
    int capacity;

    void lifting_up(int index) {
        if (((index - 1) / 2) < 0) {
            return;
        }
        if (arr[(index - 1) / 2] > arr[index]) {
            std::swap(arr[(index - 1) / 2], arr[index]);
            indexes[arr[index] + 15000] = index;
            indexes[arr[(index - 1) / 2] + 15000] =  (index - 1) / 2;
            lifting_up((index - 1) / 2);
        }
    }

    void lifting_down(int index) {
        if ((2 * index + 1 > length - 1) && (2 * index + 2 > length - 1)) {
            return;
        }
        if (length - 1 < 2 * index + 2) {
            if (arr[2 * index + 1] < arr[index]) {
                std::swap(arr[index], arr[2 * index + 1]);
                indexes[arr[index] + 15000] = index;
                indexes[arr[2 * index + 1] + 15000] = 2 * index + 1;
            }
            return;
        }
        if (arr[2 * index + 1] <= arr[2 * index + 2]) {
            if (arr[2 * index + 1] < arr[index]) {
                std::swap(arr[index], arr[2 * index + 1]);
                indexes[arr[index] + 15000] = index;
                indexes[arr[2 * index + 1] + 15000] = 2 * index + 1;
                lifting_down(2 * index + 1);
            }
            else if (arr[2 * index + 2] < arr[index]) {
                std::swap(arr[index], arr[2 * index + 2]);
                indexes[arr[index] + 15000] = index;
                indexes[arr[2 * index + 2] + 15000] = 2 * index + 2;
                lifting_down(2 * index + 2);
            }
        }
        else {
            if (arr[2 * index + 2] < arr[index]) {
                std::swap(arr[index], arr[2 * index + 2]);
                indexes[arr[index] + 15000] = index;
                indexes[arr[2 * index + 2] + 15000] = 2 * index + 2;
                lifting_down(2 * index + 2);
            }
            else if (arr[2 * index + 1] < arr[index]) {
                std::swap(arr[index], arr[2 * index + 1]);
                indexes[arr[index] + 15000] = index;
                indexes[arr[2 * index + 1] + 15000] = 2 * index + 1;
                lifting_down(2 * index + 1);
            }
        }
    }


public:
    Heap() {
        length = 0;
        capacity = 10;
        arr = new int[capacity];
        for (int i = 0; i < 30002; ++i) {
            indexes[i] = INT_MIN;
        }
    }

    ~Heap() {
        delete[] arr;
    }

    int size() const {
        return length;
    }

    void insert(int element) {
        if (length == capacity) {
            capacity *= 2;
            int* new_arr = new int[capacity];
            int* past_arr = arr;
            for (int i = 0; i < length; ++i) {
                new_arr[i] = past_arr[i];
            }
            arr = new_arr;
            delete[] past_arr;
        }
        arr[length] = element;
        indexes[element + 15000] = length;
        lifting_up(length);
        ++length;
    }


    int Extract() {
        std::swap(arr[0], arr[length - 1]);
        int result = arr[length - 1];
        indexes[arr[length - 1] + 15000] = INT_MIN;
        --length;
        lifting_down(0);
        return result;
    }

    void changePriority(int element, int newPriority) {
        int index = indexes[element + 15000];
        indexes[element + 15000] = INT_MIN;
        arr[index] = newPriority;
        indexes[newPriority + 15000] =  index;
        lifting_up(index);
    }
};



char* int_to_str(int number, int& lenght) {
    if (number == 0) {
        char* result = new char[2];
        result[0] = '0';
        result[1] = '\n';
        lenght = 2;
        return result;
    }
    bool znak = true;
    int len = 0;
    if (number < 0) {
        number *= -1;
        znak = false;
        ++len;
    }
    int copy = number;
    while (copy > 0) {
        copy /= 10;
        ++len;
    }
    lenght = len + 1;
    char* result = new char[len + 1];
    if (!znak) {
        result[0] = '-';
    }
    while (number > 0) {
        result[len - 1] = (char)(number % 10 + 48);
        --len;
        number /= 10;
    }
    result[lenght - 1] = '\n';
    return result;
}

int main(int argc, char* argv[]) {
    std::ofstream out(argv[2]);
    std::ifstream in(argv[1]);
    Heap hs = Heap();
    int i = 0;
    int dictionary_of_operation[100000];
    char curr_op[100];
    while (in >> curr_op) {
        if (strcmp(curr_op, "push") == 0) {
            int number = 0;
            in >> number;
            hs.insert(number);
            dictionary_of_operation[i + 1] = number;
        }
        else if (strcmp(curr_op, "extract-min") == 0) {
            int number = 0;
            if (hs.size() == 0) {
                out.write("*\n", 2);
            }
            else {
                int min = hs.Extract();
                int len = 0;
                char* str = int_to_str(min, len);
                out.write(str, len);
                delete[] str;
            }

        }
        else if (strcmp(curr_op, "decrease-key") == 0) {
            int number = 0;
            in >> number;
            int el = dictionary_of_operation[number];
            int new_val = 0;
            in >> new_val;
            hs.changePriority(el, new_val);
        }
        ++i;
    }
    in.close();
    out.close();
    return 0;
}
