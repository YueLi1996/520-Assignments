#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <float.h>
#include <math.h>


/* private functions *********************************************************/
/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

double DynamicArray_min ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    int i;
    double min_value = DBL_MAX;
    for(i=0;i < DynamicArray_size(da);i++)
    {
        if (DynamicArray_get(da, i) < min_value) {
            min_value = DynamicArray_get(da, i);
        }
    }
    return min_value;
}

double DynamicArray_max ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    int i;
    double max_value = -DBL_MAX;
    for(i=0;i < DynamicArray_size(da); i++)
    {
        if (DynamicArray_get(da, i) > max_value)
        {
            max_value = DynamicArray_get(da, i);
        }
    }
    return max_value;
}

double DynamicArray_sum ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    double sum_value = 0;
    
    if (da->capacity == 0) {
        return sum_value;
    }
        
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum_value += DynamicArray_get(da, i);
    }
    return sum_value;
}


double DynamicArray_mean ( const DynamicArray * da )
{
    assert(da->capacity != 0);
    assert(da->buffer != NULL);
    double mean_value = DynamicArray_sum(da) / DynamicArray_size(da);
    return mean_value;
}

double DynamicArray_median ( const DynamicArray * da )
{   
    DynamicArray * helperArray = DynamicArray_new();
    int arraySize = DynamicArray_size(da);
    // printf("%d and %d\n arraySize: %d", da->origin, da->end, arraySize);
    for (int i= 0; i < arraySize; i++) 
    {
        DynamicArray_push(helperArray,DynamicArray_get(da, i));
    }
    // bubble sort :(
    for (int i= 0; i < arraySize; i++) {
        for (int j = i+1; j < arraySize; j++) {
            if(DynamicArray_get(helperArray, i) > DynamicArray_get(helperArray, j)) {
                double temp = DynamicArray_get(helperArray, j);
                DynamicArray_set(helperArray, j, DynamicArray_get(helperArray, i));
                DynamicArray_set(helperArray, i, temp);
            }
        }
    }
    // char* s = DynamicArray_to_string(helperArray);
    // printf("%s", s);
    if ( arraySize % 2 != 0) {
        return DynamicArray_get(helperArray, arraySize/2);
    }
    else {
        return (DynamicArray_get(helperArray, arraySize/2 - 1) + DynamicArray_get(helperArray, arraySize/2) ) / 2;
    } 
    DynamicArray_destroy(helperArray);
}

double DynamicArray_last ( const DynamicArray * da ) 
{       
    assert(da->capacity != 0);
    assert(da->buffer != NULL);
    return DynamicArray_get(da, DynamicArray_size(da)-1);
}

double DynamicArray_first ( const DynamicArray * da ) 
{
    assert(da->capacity != 0);
    assert(da->buffer != NULL);
    return DynamicArray_get(da, 0);
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da )
{
    DynamicArray* newArr = DynamicArray_new();
    int arraySize = DynamicArray_size(da);
    for (int i= 0; i < arraySize; i++) 
    {
        DynamicArray_push(newArr,DynamicArray_get(da, i));
    }

    return newArr;
}

DynamicArray * DynamicArray_range ( double a, double b, double step)
{
    assert(b >= a);
    DynamicArray* newArr = DynamicArray_new();
    int arraySize =  (int) ceil((b - a)/step); 
    for (int i= 0; i <= arraySize; i++) 
    {
        DynamicArray_push(newArr, a + i * step);
    }
    // char* s = DynamicArray_to_string(newArr);
    // printf("%s", s);
    return newArr;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b )
{

    DynamicArray* newArr = DynamicArray_new();
    
    for (int i= 0; i < DynamicArray_size(a); i++) 
    {
        DynamicArray_push(newArr, DynamicArray_get(a, i));
    }

    for (int i= 0; i < DynamicArray_size(b); i++) 
    {
        DynamicArray_push(newArr, DynamicArray_get(b, i));
    }

    return newArr;
}

DynamicArray * DynamicArray_take ( const DynamicArray * da, int n )
{
    assert(da->capacity != 0);
    assert(da->buffer != NULL);
    DynamicArray* newArr = DynamicArray_new();
    if (n == 0){
        return newArr;
    }
    else if (n > 0) {
        int counter1 = 0;
        while (counter1 < n) {
            if (counter1 >= DynamicArray_size(da)) {
                DynamicArray_push(newArr, 0);
                counter1++;
                continue;
            }
            DynamicArray_push(newArr, DynamicArray_get(da, counter1));
            counter1++;
        }
    }
    else if (n < 0) {
        int counter2 = -n; //7
        while (counter2 > 0) {
            if (counter2 > DynamicArray_size(da)) { 
                DynamicArray_push(newArr, 0);
                counter2--;
                continue;
            }
            DynamicArray_push(newArr, DynamicArray_get(da, DynamicArray_size(da) - counter2));
            counter2--;
        }
    }

    return newArr;
}

int DynamicArray_is_valid(const DynamicArray * da)
{
    if(da->buffer != NULL){
        return 1;
    }
    return 0;
}