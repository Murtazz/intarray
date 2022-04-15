#include <iostream>
#include <sstream>
using namespace std;

struct IntArray {
    int size;
    int capacity;
    int *contents;

};

void printContents(const IntArray& ia) {
    for (int i = 0; i < ia.size; ++i) {
        cout << ia.contents[i] << " ";
    }
    cout << endl;
}

IntArray CreateNew(int size, int capacity) {
    IntArray *a = new IntArray{size, capacity, new int[capacity]{}};
    return *a;
}

IntArray Copyover2(IntArray& oldarray) {
    IntArray newarray = CreateNew(oldarray.size, oldarray.capacity * 2);
    for (int x = 0; x <= (oldarray.size - 1); x++) {
      newarray.contents[x] = oldarray.contents[x];
    }
    delete[] oldarray.contents;
    return newarray;
}

IntArray readIntArray() {
  char c;
  IntArray ia = CreateNew(0, 0);
  while (cin >> c) {
    if (!isdigit(c) && c != '-') {
      if (cin.peek() < '0' || cin.peek() > '9') break;
    }
    if (ia.size == 0) {
        ia.capacity += 5;
    } else {
        if (ia.capacity == ia.size) {
          ia = Copyover2(ia);
        }
    }
    if (!isdigit(c)) {
      if (c == '-') {
        if (cin.peek() < '0' || cin.peek() > '9') break;
        cin >> c;
        int x = c - '0';
        ia.contents[ia.size] = -x;
        ia.size += 1;
      } else {

        //cin.ignore();
        break;
      }
    } else {
      ia.contents[ia.size] = c-'0';
      ia.size += 1;
    }
  }
  return ia;
}

void addToIntArray(IntArray& ia) {
  char c;
  while (true) {
    if (!isdigit(cin.peek())) break;
    if (!(cin >> c)) { // get another charecter
      if (cin.eof()) {
        break; // EOF
      } else if (!cin) {
        break; // not a number
      }
    }
    if (ia.size == 0) {
      ia.size += 1;
      ia.capacity += 5;
      ia.contents[ia.size - 1] = c-'0';
    } else {
      if (ia.capacity == ia.size) {
        ia = Copyover2(ia);
      }
      ia.contents[ia.size] = c-'0';
      ia.size += 1;
    }  
  }
  
}

void printIntArray(const IntArray& ia) {
  printContents(ia);
}

// Do not change this function!

int main() {  // Test harness for IntArray functions.
  bool done = false;
  IntArray a[4];
  a[0].contents = a[1].contents = a[2].contents = a[3].contents = 0;

  while(!done) {
    char c;
    char which;
    // Note:  prompt prints to stderr, so it should not occur in .out files
    cerr << "Command?" << endl;  // Valid commands:  ra, rb, rc, rd,
                                 //                  +a, +b, +c, +d,
                                 //                  pa, pb, pc, pd, q
    cin >> c;  // Reads r, +, p, or q
    if (cin.eof()) break;
    switch(c) {
      case 'r':
        cin >> which;  // Reads a, b, c, or d
        delete [] a[which-'a'].contents;
        a[which-'a'].contents = 0;
        a[which-'a'] = readIntArray();
        break;
      case '+':
        cin >> which;  // Reads a, b, c, or d
        addToIntArray(a[which-'a']);
        break;
      case 'p':
        cin >> which;  // Reads a, b, c, or d
        printIntArray(a[which-'a']);
        cout << "Capacity: " << a[which-'a'].capacity << endl;
        break;
      case 'q':
        done = true;
    }
  }

  for (int i = 0; i < 4; ++i) delete [] a[i].contents;
}

