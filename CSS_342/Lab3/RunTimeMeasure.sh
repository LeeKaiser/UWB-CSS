#!/bin/bash

sortTypeArray=("BubbleSort" "InsertionSort" "MergeSort" "QuickSort" "ShellSort")
listSizeArray=(100 1000 5000 10000 50000 100000)
listTypeArray=("Random" "Ordered" "Partial" "Reversed")

#cover every sort type (BubbleSort InsertionSort MergeSort QuickSort ShellSort)
for i in ${sortTypeArray[@]}
do
    #cover every list type (Random Sorted Ordered Reversed)
    for j in ${listTypeArray[@]}
    do 
        #run through 100 to 100000
        for k in ${listSizeArray[@]}
        do 
        
            echo -e "Sort Type: \t $i \t List Type: \t $j \t List Size: \t $k"
            ./Sorter.out $i $k NO $j 3
            
            
        done
        #run through 50000 to 100000 in certain conditions
        if ( [ "$i" = "BubbleSort" ] && ( [ "$j" = "Random" ] || [ "$j" = "Reversed" ] ) ) || ( [ "$i" = "InsertionSort" ] && ( [ "$j" = "Random" ] || [ "$j" = "Reversed" ] ) ) || [ "$i" = "MergeSort" ]; 
        then
            echo -e "Sort Type: \t $i \t List Type: \t $j \t List Size: \t 500000"
            echo -e "command would take too long \n" 
            echo -e "Sort Type: \t $i \t List Type: \t $j \t List Size: \t 1000000"
            echo -e "command would take too long \n" 
        else
            echo -e "Sort Type: \t $i \t List Type: \t $j \t List Size: \t 500000"
            ./Sorter.out $i 500000 NO $j 3

            echo -e "Sort Type: \t $i \t List Type: \t $j \t List Size: \t 1000000"
            ./Sorter.out $i 1000000 NO $j 3
            

            
        fi
    done
done
