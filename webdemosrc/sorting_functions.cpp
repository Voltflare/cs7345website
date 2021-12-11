#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <emscripten/bind.h>
//change names to more professional-sounding

using namespace emscripten;
using namespace std;

// ---------- Helper Functions for Emscripten Binding ------------
vector<int> getAVector(int size = 0) {
    if (size == 0) {
        vector<int> newVector;
        return newVector;
    }
    else {
        vector<int> newVector(size);
        std::iota(newVector.begin(), newVector.end(), 1);
        return newVector;
        }
}

//shuffle done via fisher-yates
vector<int> shuffleVector(vector<int> vecToShuffle) {
    vector<int> newVec = vecToShuffle;
    int n = vecToShuffle.size();
    for (int i = 0; i < n -1; i++) {
        int j = i + rand() % (n-1);
        std::swap(vecToShuffle[i], vecToShuffle[j]);
    }
    return newVec;
}

vector<int> reverseVector(vector<int> vecToReverse) {
    vector<int> newVec;
    for (int i = vecToReverse.size()-1; i >= 0; i--) {
        newVec.push_back(vecToReverse[i]);
    }
    return newVec;
}

vector<int> dupeVector(vector<int> vecToDupe) {
    vector<int> newVec = vecToDupe;
    for (unsigned int i = 1; i < newVec.size()/5; i++) {
        newVec[2*i] = newVec[i];
        newVec[3*i] = newVec[i];
        newVec[4*i] = newVec[i];
        newVec[5*i-1] = newVec[i];
    }
    return newVec;
}

// ---------------------------------------------------------

//A subset of Nathan Hites' CS3353 Lab 1 Project, written without file inclusion and multiple files
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

//binding code

//exported out --> Module.BubbleSort in JS file, etc
EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("GetVector", &getAVector);
    emscripten::function("DupeVector", &dupeVector);
    emscripten::function("ReverseVector", &reverseVector);
    emscripten::function("ShuffleVector", &shuffleVector);
    emscripten::function("BubbleSort", &myBubbleSort);
    emscripten::function("Merge", &myMerge);
    emscripten::function("MergeSort", &myMergeSort);
    emscripten::function("InsertionSort", &myInsertionSort);
}

EMSCRIPTEN_BINDINGS(stl_wrappers) {
    register_vector<int>("VectorInt");
}