//need to include main.js file


var Algo = {
    Vector: {
        Init: function(size = 0){
            return Module.GetVector(size);
        },
        Shuffle: function(data) {
            return Module.ShuffleVector(data);
        },
        Reverse: function(data) {
            return Module.ReverseVector(data);
        },
        Dupe: function(data) {
            return Module.DupeVector(data);
        }
    },
    Sort: {
        Bubble: function(data) {
            return Module.BubbleSort(data);
        },
        Merge: function(data) {
            return Module.MergeSort(data);
        },
        Insertion: function(data) {
            return Module.InsertionSort(data);
        }

    }
}
