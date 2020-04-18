#include <stdio.h>
#include <stdlib.h>
#define VERTEX_COUNT 10
#define false 0
#define true 1


// Initialize the first graph according to the material given
int graph1[VERTEX_COUNT][VERTEX_COUNT] = {
//       v0     v1     v2     v3     v4     v5     v6     v7     v8     v9
/*v0*/  {false, true,  false, false, false, true,  false, false, false, false},
/*v1*/  {false, false, false, false, false, false, false, true,  false, false},
/*v2*/  {false, false, false, false, false, false, false, false, false, false},
/*v3*/  {false, false, true,  false, true,  false, false, true,  true,  false},
/*v4*/  {false, false, false, false, false, false, false, false, true,  false},
/*v5*/  {false, false, false, false, false, false, false, false, false, false},
/*v6*/  {true,  true,  true,  false, false, false, false, false, false, false},
/*v7*/  {false, false, false, false, false, false, false, false, false, false},
/*v8*/  {false, false, true,  false, false, false, false, true,  false, false},
/*v9*/  {false, false, false, false, true,  false, false, false, false, false}
};

// Initialize the second graph according to the material given
int graph2[VERTEX_COUNT][VERTEX_COUNT] = {
//       v0     v1     v2     v3     v4     v5     v6     v7     v8     v9
/*v0*/  {false, true,  false, false, false, true,  false, false, false, false},
/*v1*/  {false, false, false, false, false, false, false, true,  false, false},
/*v2*/  {false, false, false, false, false, false, false, false, false, false},
/*v3*/  {false, false, true,  false, true,  false, false, true,  true,  false},
/*v4*/  {false, false, false, false, false, false, false, false, true,  false},
/*v5*/  {false, false, false, false, false, false, false, false, false, false},
/*v6*/  {true,  true,  true,  false, false, false, false, false, false, false},
/*v7*/  {false, false, false, false, false, false, false, false, false, false},
/*v8*/  {false, false, false, false, false, false, false, true,  false, false},
/*v9*/  {false, false, false, false, true,  false, false, false, false, false}
};

// In order to see if a value is in an array I created a separate function
int isInArray(int value, int array[], int arraySize)
{
    int i;
    for(i = 0; i < arraySize; i++)
    {
        if(array[i] == value)
            return 1;
    }
    return 0;
}

// Append to the end of array
int appendToArray(int value, int array[], int freePos){
    array[freePos] = value;
    freePos += 1;
    return freePos;
}

// Sometimes the array has to be reset and if we reset it using memset() or other methods "0" will be seen in the array, to get the correct result every index has to be made -1.
int nullifyArray(int array[], int arrayLength){
    for(int i=0;i<arrayLength;i++){
        array[i] = -1;
    }
    return 0;
}

// Given the graph this function will return an array with the in-degrees of every vertex
int * findIndegree(int graphArray[VERTEX_COUNT][VERTEX_COUNT]){
    // Allocate memory for the array which will store the in-degree values
    int * indegreeArray = malloc(sizeof(int)*VERTEX_COUNT);
    // For every column
    for(int i=0;i<VERTEX_COUNT;i++){
            // Reset counter
            int tempCounter = 0;
        // Start checking the rows
        for(int t=0;t<VERTEX_COUNT;t++){
            // If the value at the t.nth row and i.th column is true increase counter
            if(graphArray[t][i] == true){
                tempCounter += 1;
            }
        }
        // Insert value in to the array
        indegreeArray[i] = tempCounter;
    }
    // Return the array
    return indegreeArray;
};

// This function calculates the topological order from the given graph
int * findOrder(int graphArray[VERTEX_COUNT][VERTEX_COUNT]){
    // Calculate in-degree of given graph
    int * indegreeArray = findIndegree(graphArray);
    // Allocate memory for the array where we will store the order of vertices
    int * orderArray = malloc(sizeof(int)*VERTEX_COUNT);
    // Initialize the temporary array and other variables
    int vertexToBeAdded;
    int tempArray[VERTEX_COUNT];
    // In order to append to the order array and temporary array, the free position must also be known
    int freePosOrderArray, freePosTempArray = 0;
    // The array has to be initialized with values that are not in the graph, otherwise 0 will show up as an existing member of the array when checking
    freePosOrderArray = nullifyArray(orderArray, VERTEX_COUNT);
    // Start putting the vertices in order
    for(int i=0;i<VERTEX_COUNT;i++){
        // Reset the temporary array
        freePosTempArray = nullifyArray(tempArray, VERTEX_COUNT);
        // Find which vertex will be added to the temporary array next
        for(int t=0;t<VERTEX_COUNT;t++){
            // If this vertex is already in topological order, then skip it.
            if(isInArray(t, orderArray, VERTEX_COUNT)){
                continue;
            }
            // If the in-degree is equal to 0, add this vertex to the temporary array
            if(indegreeArray[t] == 0){
                freePosTempArray = appendToArray(t, tempArray, freePosTempArray);
            }
        };

        // For every member of the temporary array
        for(int l=0;l<freePosTempArray;l++){
            // Append the vertex to the topological order array from the temporary array
            freePosOrderArray = appendToArray(tempArray[l], orderArray, freePosOrderArray);
            // Look for vertices this vertex points to and reduce their in-degree by 1
            vertexToBeAdded = tempArray[l];
            for(int k=0;k<VERTEX_COUNT;k++){
                // If the vertex that will be removed points to another vertex
                if(graphArray[vertexToBeAdded][k] == true){
                    // Reduce the in-degree value of that vertex
                    indegreeArray[k]--;
                }
            }
        };
    }
    // return pointer of the order array
    return orderArray;
};

int main()
{
    // Initialize the pointers where the address of the outputs will be stored
    int * order1, * order2;
    int i;

    // Calculate orders
    order1 = findOrder(graph1);
    order2 = findOrder(graph2);
    // Print the outputs
    printf("\n");
    printf("The topological order for graph1 is:\n");
    for(i=0;i<10;i++){
        printf("%d ",order1[i]);
    }

    printf("\nThe topological order for graph2 is:\n");
    for(i=0;i<10;i++){
        printf("%d ",order2[i]);
    }
    printf("\n");
    return 0;
}
