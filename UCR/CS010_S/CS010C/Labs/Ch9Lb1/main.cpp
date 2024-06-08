#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::sort;

// Using clock() is pretty old school and does not take advantage
// of better precision timers.  But is fine for our purposes.  I'll
// show it both ways, but if one is causing problems, just use the other.
using std::clock_t;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

// This is the more modern way to do timings with the high resolution clock
// I'll provide an example
#include <chrono>
using std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration_cast;

// If using C++ 14, this is better as constexpr
const int NUMBERS_SIZE = 50000;

// Provided by zybooks
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

// Provided by zybooks
void fillArrays(int arr1[], int arr2[],int arr3[]) {
  for(int i = 0; i < NUMBERS_SIZE; ++i){
    arr1[i] = genRandInt(0,NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}

// CODETURD: You will want to write the QPartition -- See Section 5.10
// CODETURD: in your Zybook.  Use it for both versions of quicksort
// CODETURD: Note that quicksort will recursively call itself... that
// CODETURD: is the point!
int QPartition(int numbers[], int low, int high) {
  int pivot = numbers[high];                                          //set pivot value to the far most right,
  int lowIndex = low - 1;                                             //shift one to the left
  for (int highIndex = low; highIndex < high; highIndex++) {          //iterate though all the numbers between low and high indexes
      if (numbers[highIndex] <= pivot) {                              //if the value selected is bigger than the pivot value,
        lowIndex++;                                                   //move onto the next low index swap that value and the lowIndex value
        std::swap(numbers[lowIndex], numbers[highIndex]);
      }
    }
    std::swap(numbers[lowIndex + 1], numbers[high]);                  //then place back the pivot to its correct position
    return lowIndex + 1;                                              //returns the partitoined index value
}

void Quicksort_midpoint(int numbers[], int i, int k) {
  if(i >= k){                                                         //base case for if the low is greater than high, sorting is finished
    return;
  }
  int pivot = (i + k) / 2;                                            //set midpoint pivot index
  std::swap(numbers[pivot], numbers[k]);                              //place pivot value out of the way
  int partitionIndex = QPartition(numbers, i, k);                     //partition the array and get the partition index
  Quicksort_midpoint(numbers, i, partitionIndex-1);                   //recursively quicksorts both sides of the pivot over until finished sorting
  Quicksort_midpoint(numbers, partitionIndex+1, k);
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
  if(i >= k){                                                         //base case for if the low is greater than high, sorting is finished
    return;
  }

  int pivot = (i + k) / 2;                                            //set midpoint pivot index
  if (numbers[i] > numbers[pivot]) {                                  //swaps low value with pivot value if pivot value is less than low value
    std::swap(numbers[i], numbers[pivot]);
  }
  if (numbers[i] > numbers[k]) {                                      //swaps low and high value if high value is less than low value
    std::swap(numbers[i], numbers[k]);
  }
  if (numbers[pivot] > numbers[k]) {                                  //swaps high value with pivot value if pivot value is more than high value
    std::swap(numbers[pivot], numbers[k]);
  }
  std::swap(numbers[pivot], numbers[k - 1]);                          //then swaps the pivoting value with the value before highest

  int partitionIndex = QPartition(numbers, i, k - 1);                 //partition the array and get the partition index
  Quicksort_medianOfThree(numbers, i, partitionIndex-1);              //recursively quicksorts both sides of the pivot over until finished sorting
  Quicksort_medianOfThree(numbers, partitionIndex+1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
  for (int i  = 1; i < numbersSize; i++){                             //starting from the second index, compares each value
    for(int j = i; j > 0 && numbers[j-1] > numbers[j]; j--){          //if the value at index j is greater than the current i index, swap the 2 values
      std::swap(numbers[j-1], numbers[j]);                            //repeat for every value in the array and should be sorted at the end
    }
  }
}

// We can compare other sorts we've talked about
static void BubbleSort(int numbers[], int n);

static void MergeSort(int numbers[], int left, int right);

// A helper function that will let us know if we have sorted
// everything
static bool is_sorted(int numbers[], int numbersSize) {
  if (numbersSize <= 0) return true;
  int last = numbers[0];
  for(int i=0; i < numbersSize; ++i) {
    int curr = numbers[i];
    if (curr < last) return false;
    last = curr;
  }
  return true;
}

static void copy_vector_into_array(const std::vector<int>& source, int array[]) {
  for(int i=0;i<static_cast<int>(source.size()); ++i) {
    array[i] = source[i];
  }
}

static void RadixSort(int numbers[], int size);

int main() {
  // I'm going to use the same array every time for all the
  // functions.  This is different than the Zybooks suggestion
  // but will give us more consistent timings
  std::vector<int> sample;
  sample.reserve(NUMBERS_SIZE);
  for(int i=0; i<NUMBERS_SIZE; ++i) {
    sample.push_back(rand() % (NUMBERS_SIZE + 1));
  }
  
  // We'll run our tests across a bunch of sizes
  // CODETURD: While testing, I can do a break at the end of the
  // CODETURD: loop so I can make faster progress
  int test_sizes[4] = { 10, 100, 1000, 50000 };
  int test_array[NUMBERS_SIZE];
  for(int i=0; i<4; ++i) {
    int size = test_sizes[i];
    cout << endl;
    cout << "-------------------- size " << size << " --------------------" << endl;

    // BUBBLE SORT
    {
      copy_vector_into_array(sample, test_array);
      // CODETURD: Pick one timing scheme or the other and remove
      // CODETURD: the one you don't use
      time_point<steady_clock> start = steady_clock::now();
      // clock_t Start = clock();
      BubbleSort(test_array, size);
      // clock_t End = clock();
      // int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      // cout << elapsedTime << " ms" << endl;

      time_point<steady_clock> stop = steady_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for bubble sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // MERGE SORT
    {
      copy_vector_into_array(sample, test_array);
      // CODETURD: Pick one timing scheme or the other and remove
      // CODETURD: the one you don't use
      time_point<steady_clock> start = steady_clock::now();
      // clock_t Start = clock();
      MergeSort(test_array, 0, size-1);
      // clock_t End = clock();
      // int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      // cout << elapsedTime << " ms" << endl;

      time_point<steady_clock> stop = steady_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for merge sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // RADIX SORT
    {
      copy_vector_into_array(sample, test_array);
      // CODETURD: Pick one timing scheme or the other and remove
      // CODETURD: the one you don't use
      time_point<steady_clock> start = steady_clock::now();
      // clock_t Start = clock();
      RadixSort(test_array, size);
      // clock_t End = clock();
      // int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      // cout << elapsedTime << " ms" << endl;

      time_point<steady_clock> stop = steady_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for radix sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // CODETURD: break
  }
 
  return 0;
}

static void BubbleSort(int numbers[], int n) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (numbers[j] > numbers[j + 1]) {
	std::swap(numbers[j], numbers[j + 1]);
      }
    }
  }
}

static void merge(int numbers[], int start, int mid, int end) {
  int start2 = mid + 1;
 
  // If the direct merge is already sorted
  if (numbers[mid] <= numbers[start2]) {
    return;
  }
 
  // Two pointers to maintain start of both sub-arrays to merge
  while (start <= mid && start2 <= end) {
 
    // If element 1 is in right place
    if (numbers[start] <= numbers[start2]) {
      start++;
    } else {
      int value = numbers[start2];
      int index = start2;
 
      // Shift all the elements between element 1
      // element 2, right by 1.
      while (index != start) {
	numbers[index] = numbers[index - 1];
	index--;
      }
      numbers[start] = value;
 
      // Update all the pointers
      start++;
      mid++;
      start2++;
    }
  }
}

static void MergeSort(int numbers[], int left, int right) {
  if (left < right) {
    int mid = (left + right)/2;
    MergeSort(numbers, left, mid);
    MergeSort(numbers, mid+1, right);
    merge(numbers, left, mid, right);
  }
}

static void RadixSort(int numbers[], int size) {
  // LOTS of assumptions here.  I assume all data are
  // postive integers;
  
  // I have to do passes based on the digits.  I stop
  // when I extract the largest digit
  int divisor = 1;
  bool more = true;
  for(int pass=0; more ; pass++) {
    // I need 10 buckets with a lot of room in them
    std::vector< std::vector<int> > buckets(10);
    for(int i=0;i<10;++i) buckets[i].reserve(NUMBERS_SIZE);

    // I pull off the pass'th digit and use it to put a number
    // into a bucket.  To get it, I divide by 1, 10, 100, 1000
    // and then do a modulo
    more = false;
    for(int i=0; i<size; ++i) {
      int digit = (numbers[i]/divisor)%10;
      if (numbers[i]/divisor/10 > 0) more = true;
      buckets[digit].push_back(numbers[i]);
    }
    divisor *= 10;

    // Copy the buckets back into numbers
    int index = 0;
    for(int i=0; i<10; ++i) {
      const std::vector<int>& bucket = buckets[i];
      for(int j=0; j<static_cast<int>(bucket.size()); ++j) {
	numbers[index++] = bucket[j];
      }
    }
  }
}
