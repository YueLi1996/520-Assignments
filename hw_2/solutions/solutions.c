#include "solutions.h"
int question_one_sum = 0; // global variable to store sum

int running_total (int num)
{
  question_one_sum += num;
  return question_one_sum;
}

int* reverse (int* array, int size)
{
  int * result = (int*)calloc (size, sizeof(int));

  int i;
  for(i = 0;i < size; i++)
  {
    result[i] = array[size-i-1];
  }

  return result;
}

void reverse_in_place (int* array, int size)
{
  int left = 0;
  int right = size - 1;

  while (left <= right)
  {
    int temp = array[left];
    array[left] = array[right];
    array[right] = temp;
    left++;
    right--;
  }

}

int num_occurences (int* array, int size, int value)
{
  int result = 0;
  
  int i;
  for (i = 0; i < size; i++)
  {
    if (array[i] == value) 
    {
      result += 1;
    }
  }
  return result;
}


