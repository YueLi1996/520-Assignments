#include <iostream>
#include "filter.h"

using namespace std;

void Filter::update() {
  if ( channel("link").nonempty() ) {
    // < 10th
    if (counter < 9) {
      ave_value = channel("link").latest();
      nums[counter] = ave_value;
      counter++;
      // for(int i = 0; i< 10; i++)
      //   {
      //       cout << nums[i] << " ";
      //   }
      // cout<<"current average value is "<<ave_value<<"\n";
    }
    else {
      // 10th
      if (counter == 9) {
        double sum = 0.0;
        nums[9] = channel("link").latest();
        for(int i = 0; i < 10; i++) {
          sum += nums[i];
        }
        ave_value = (double) (sum/10.0);
        counter++;
        // for(int i = 0; i< 10; i++)
        // {
        //     cout << nums[i] << " ";
        // }
        // cout<<"current average value is "<<ave_value<<"\n";
      }
      // 10+ th
      else {
        double sum = 0.0;
        double new_num = channel("link").latest();

        for(int i = 1; i < 10; i++) {
          double temp = nums[i];
          nums[i-1] = temp; 
        }
        nums[9] = new_num;

        for(int i = 0; i < 10; i++) {
          sum += nums[i];
        }
        // for(int i = 0; i< 10; i++)
        // {
        //     cout << nums[i] << " ";
        // }
        ave_value = (double) (sum/10.0);
        // cout<<"current average value is "<<ave_value<<"\n";
      }
    }
  }

}

double Filter::value()
{
  return ave_value;
}
