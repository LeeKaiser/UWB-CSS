#!/bin/bash

sortTypeArray=("BubbleSort" "InsertionSort" "MergeSort" "QuickSort" "ShellSort")
listSizeArray=(100 1000 5000 10000 50000 100000 500000 1000000)
listTypeArray=("Random" "Ordered" "Partial" "Reversed")

#cover every sort type (BubbleSort InsertionSort MergeSort QuickSort ShellSort)
for i in ${sortTypeArray[@]}
do
    #cover every list type (Random Sorted Ordered Reversed)
    for j in ${listTypeArray[@]}
    do 
        #run through 100 to 1000000
        for k in ${listSizeArray[@]}
        do 
        
            echo -e "Sort Type: \t $i \t List Type: \t $j \t List Size: \t $k"
            ./Sorter.out $i $k NO $j
            
            
        done
        
    done
done
