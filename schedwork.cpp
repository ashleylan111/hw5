#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int) - 1;


// Add prototypes for any helper functions here

bool schedHelper(const AvailabilityMatrix& avail, 
size_t dailyNeed, size_t maxShifts, 
DailySchedule& sched, vector<size_t>& shiftCount, 
size_t day, size_t slot){

  size_t n = avail.size();
  size_t k = avail[0].size();

  if (day == n){
    return true;
  }

  if (slot == dailyNeed){
    return schedHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day + 1, 0);
  }

  for (size_t w = 0; w < k; w++){
    if (!avail[day][w]){
      continue;
    }

    if (shiftCount[w] >= maxShifts){
      continue;
    }

    if (find(sched[day].begin(), sched[day].begin() + slot, w) != sched[day].begin() + slot){
      continue;
    }

    sched[day][slot] = w;
    shiftCount[w]++;

    if (schedHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day, slot + 1)){
      return true;
    }

    shiftCount[w]--;

    
  }

  return false; 

  
}


// Add your implementation of schedule() and other helper functions here
/**
 * @brief Produces a work schedule given worker availability,
 *        the number of needed workers per day, and the maximum 
 *        shifts any single worker is allowed. Returns true
 *        and the valid schedule if a solution exists, and false
 *        otherwise. 
 * 
 * @param [in]  avail n x k vector of vectors (i.e. matrix) of the availability
 *                    of the k workers for each of the n days
 * @param [in]  dailyNeed Number of workers needed per day (aka d)
 * @param [in]  maxShifts Maximum shifts any worker is allowed over 
 *                        the n day period (aka m)
 * @param [out] sched n x d vector of vectors indicating the d workers
 *                    who are scheduled to work on each of the n days
 * @return true if a solution exists; sched contains the solution
 * @return false if no solution exists; sched is undefined (can be anything)
 */
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below 

    size_t n = avail.size();
    size_t k = avail[0].size();

    sched = DailySchedule(n, vector<Worker_T>(dailyNeed));

    vector<size_t> shiftCount(k, 0);

    return schedHelper(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);

}

