#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
//change names to more professional-sounding

using namespace emscripten;
using namespace std;

//A subset of Nathan Hites' CS3353 Lab 1 Project, written without file inclusion and multiple files
//these methods are also in "sorting_functions.cpp"
vector<int> myBubbleSort(vector<int>& myvec) {
    bool didswap = true;
    vector<int> newvec(myvec);
    while (didswap) {
        didswap = false; //reset idea from stackoverflow
        for (unsigned int i = 0; i < newvec.size()-1; i++) { //size-1 so we don't go out of bounds of the vector
            if (newvec[i]> newvec[i+1]) {
                didswap = true; //we found one that isn't in the right spot, so we have to pass through array again
                swap(newvec[i], newvec[i+1]);

            } //end if
        } //end for
    } //end while

    return newvec;
}


vector<int> myMerge(vector<int> leftside, vector<int> rightside) {
    vector<int> sorted;
    int left = 0;
    int mid = leftside.size();
    int right = 0;
    int end = rightside.size();
    //comparing left and right values
    while (left < mid && right < end) {
        if (leftside[left] < rightside[right]) {
            sorted.push_back(leftside[left]);
            left++;
        }
        else {
            sorted.push_back(rightside[right]);
            right++;
        }
    }

    //check to see which one went past its bound:
    if (left == mid) {
        //we have extra elements on the right
        while (right < end) {
            sorted.push_back(rightside[right]);
            right++;
        }
    }
    else {
        //we have extra elements on the left
        while (left < mid) {
            sorted.push_back(leftside[left]);
            left++;
        }
    }

    return sorted;
}

vector<int> myMergeSort(vector<int>& myvec2) {
    if (myvec2.size() <= 1) return myvec2; //the case where the array is already sorted
    int split = (myvec2.size() / 2);

    vector<int> left(myvec2.begin(), myvec2.begin() + split);
    vector <int> right(myvec2.begin()+ split, myvec2.end());

    return myMerge(myMergeSort(left),myMergeSort(right));
}

vector<int> myInsertionSort(vector<int>& myvec3) {
    //create vector to sort
    vector<int> vectosort(myvec3.begin(), myvec3.end());
    //perform insertion sort- adapted from Intro to Algorithms textbook
    for (unsigned int j = 1; j < vectosort.size(); j++) {
        int valuetocheck = vectosort[j];
        int i = j-1;
        //find spot to place the number
        while ((i >= 0) && (vectosort[i] > valuetocheck)) { //we need to be able to check vec[0] as well
            vectosort[i+1] = vectosort[i];
            i--;
        }
        //place in its proper spot
        vectosort[i+1] = valuetocheck;

    }
    //return
    return vectosort;

}


int main()
{
    chrono::duration<double> full_time = std::chrono::seconds(0);
    //create vectors of length 100000
    vector<int> myVector;
    for (int i = 0; i < 10; i++) {
        myVector.push_back(i);
    }
    vector<int> myVecReversed = myVector;
    std::reverse(myVecReversed.begin(), myVecReversed.end());

    vector<int> myVecRandom = myVector;
    std::random_shuffle(myVecRandom.begin(), myVecRandom.end());

    vector<int> myVecDupes = myVecRandom;
    for (unsigned int i = 1; i < myVecDupes.size()/5; i++) {
        myVecDupes[2*i] = myVecDupes[i];
        myVecDupes[3*i] = myVecDupes[i];
        myVecDupes[4*i] = myVecDupes[i];
        myVecDupes[5*i-1] = myVecDupes[i];
    }

    cout << "Bubble Sort: " << endl;
    //bubble on them
    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();
    vector<int> vecRevBubble = myBubbleSort(myVecReversed);
    chrono::high_resolution_clock::time_point end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end_time-start_time);
    cout << "Time for Reversed Array: " << time_span.count() << " seconds." << endl;
    full_time += time_span;

    start_time = chrono::high_resolution_clock::now();
    vector<int> vecRandBubble = myBubbleSort(myVecRandom);
    end_time = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(end_time-start_time);
    cout << "Time for Random Array: " << time_span.count() << " seconds." << endl;
    full_time += time_span;

    start_time = chrono::high_resolution_clock::now();
    vector<int> vecDupesBubble = myBubbleSort(myVecDupes);
    end_time = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(end_time-start_time);
    cout << "Time for 80% Duplicates Array: " << time_span.count() << " seconds." << endl;
    full_time += time_span;

    //merge on them
    cout << "Merge Sort: " << endl;
    start_time = chrono::high_resolution_clock::now();
    vector<int> vecRevMerge = myMergeSort(myVecReversed);
    end_time = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(end_time-start_time);
    cout << "Time for Reversed Array: " << time_span.count() << " seconds." << endl;
    full_time += time_span;

    start_time = chrono::high_resolution_clock::now();
    vector<int> vecRandMerge = myMergeSort(myVecRandom);
    end_time = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(end_time-start_time);
    cout << "Time for Random Array: " << time_span.count() << " seconds." << endl;
    full_time += time_span;

    start_time = chrono::high_resolution_clock::now();
    vector<int> vecDupesMerge = myMergeSort(myVecDupes);
    end_time = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(end_time-start_time);
    cout << "Time for 80% Duplicates Array: " << time_span.count() << " seconds." << endl;
    full_time += time_span;

    //insertion on them
    cout << "Insertion Sort: " << endl;
    start_time = chrono::high_resolution_clock::now();
    vector<int> vecRevInsertion = myInsertionSort(myVecReversed);
    end_time = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(end_time-start_time);
    cout << "Time for Reversed Array: " << time_span.count() << " seconds." << endl;
    full_time += time_span;

    start_time = chrono::high_resolution_clock::now();
    vector<int> vecRandInsertion = myInsertionSort(myVecRandom);
    end_time = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(end_time-start_time);
    cout << "Time for Random Array: " << time_span.count() << " seconds." << endl;
    full_time += time_span;

    start_time = chrono::high_resolution_clock::now();
    vector<int> vecDupesInsertion = myInsertionSort(myVecDupes);
    end_time = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(end_time-start_time);
    cout << "Time for 80% Duplicates Array: " << time_span.count() << " seconds." << endl;
    full_time += time_span;

    cout << "Total Time: " << (float) (full_time.count() )<< " seconds. " << endl;

    return 0;
}
