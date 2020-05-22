#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include "streetgrid.h"
#include "derived_events.h"

using namespace std;
StreetGrid::StreetGrid(
    const std::vector<unsigned int> rowCapacities,
    const std::vector<unsigned int> colCapacities)
    : rowCapacities_(rowCapacities), colCapacities_(colCapacities)
{
    n = rowCapacities.size();
    m = colCapacities.size();
    expectedVehicles_ = 0;

    for(int i = 0; i < int(n); ++i){
        rowSeg[i] = new int[m];
        colSeg[i] = new int[m];
        sameTime[i] = new int[m];
        for(int j = 0; j < int(m); ++j){
            rowSeg[i][j] = 0;
            colSeg[i][j] = 0;
            sameTime[i][j] = 0;
        }
    }

    for (int i = 0; i < int(n); ++i){
        blocked[i] = new bool*[m];
        for (int j = 0; j < int(m); ++j){
            blocked[i][j] = new bool[2];
            for(int k = 0; k < 2; ++k){
                if(j == int(m - 1)){
                    blocked[i][j][1] = true;
                }else if(i == int(n - 1)){
                    blocked[i][j][0] = true;
                }else{
                    blocked[i][j][k] = false;
                }
            }
        }
    }
    // Call monitor state to output starting state
    monitorState();
}

StreetGrid::~StreetGrid(){
    for(int i = 0; i < int(n); ++i){
        delete [] rowSeg[i];
        delete [] colSeg[i];
        delete [] sameTime[i];
    }
    delete [] rowSeg;
    delete [] colSeg;
    delete [] sameTime;

    for (int i = 0; i < int(n); ++i){
        for (int j = 0; j < int(m); ++j){
            delete [] blocked[i][j];
        }
         delete [] blocked[i];
    }

    delete [] blocked;

    
}
size_t StreetGrid::numRows() const
{
    return n;
}
size_t StreetGrid::numCols() const
{
    return m;
}
void StreetGrid::setExpected(size_t expectedVehicles)
{
    expectedVehicles_ = expectedVehicles;
}

void StreetGrid::outputCompletedVehicles(std::ostream& ostr) const
{
    for(auto v : completed_) {
        ostr << v.end << " " << v.id << std::endl;
    }
}

bool StreetGrid::allVehiclesArrived() const
{
    return completed_.size() == expectedVehicles_;
}

void StreetGrid::monitorState()
{
    std::cout << "State: " << std::endl;
    std::cout << std::setw(4) << " ";

    // Print header row with column capacities
    for(size_t cidx = 0; cidx < m; ++cidx) {
        std::cout <<  std::setw(4) << colCapacities_[cidx] << " " <<  std::setw(4) << " ";
    }
    std::cout << std::endl;
    std::cout << "    ";
    for(size_t cidx = 0; cidx < m; ++cidx) {
        std::cout <<  std::setw(4) << "====="  << "=====";
    }
    std::cout << std::endl;

    // Start printing grid data
    for(size_t ridx = 0; ridx < n; ++ridx) {
        // Print row capacity
        std::cout << std::setw(2) << rowCapacities_[ridx] << " |";
        // Print row occupancies
        for(size_t cidx = 0; cidx < m; ++cidx) {
            std::cout << std::setw(4) << "+" << " ";
            if(cidx < m-1) {
                if(isBlocked(ridx,cidx,true)) {
                    std::cout << std::setw(3) << getRowOccupancy(ridx,cidx);
                    std::cout << "B";
                }
                else {
                    std::cout << std::setw(4) << getRowOccupancy(ridx,cidx);
                }
            }
        }
        std::cout << std::endl;
        std::cout <<  "   |";
        // Print column occupancies
        if(ridx < n-1) {
            for(size_t cidx = 0; cidx < m; ++cidx) {
                if(isBlocked(ridx,cidx,false)) {
                    std::cout << std::setw(3) << getColOccupancy(ridx,cidx);
                    std::cout << "B";
                }
                else {
                    std::cout << std::setw(4) << getColOccupancy(ridx,cidx);
                }
                std::cout << std::setw(4) << " " << " " ;
            }
        }
        std::cout << std::endl;

    }
}

size_t StreetGrid::getRowOccupancy(size_t row, size_t col) const
{
    return rowSeg[row][col];
}

size_t StreetGrid::getColOccupancy(size_t row, size_t col) const
{
    return colSeg[row][col];
}

bool StreetGrid::isBlocked(size_t row, size_t col, bool rowDir) const
{
    return blocked[row][col][rowDir];
}

size_t StreetGrid::calcCrossTime(size_t row, size_t col, bool rowDir){
    if(rowDir == 1){
        //rowTime
        return std::max(1.0, (1.0+double(getRowOccupancy(row, col))) /( double(rowCapacities_[row])*1.0)) * SCALE_FACTOR;
    }else if(rowDir == 0){
        //colTime
        return std::max(1.0, (1.0+double(getColOccupancy(row, col))) /( double(colCapacities_[col]))*1.0) * SCALE_FACTOR;
    }
    return 1;
}
// @returns true if the vehicle should travel in the current row and
// false if the vehicle should travel down the current column
bool StreetGrid::shouldChooseRow(size_t row, size_t col)
{
    if(blocked[row][col][0] == true){
        return true;
    }else if(blocked[row][col][1] == true){
        return false;
    }else{
        double rowTime = calcCrossTime(row, col, 1);
        double colTime = calcCrossTime(row, col, 0);
        if(rowTime == colTime){
            //vehicles should choose the opposite direction as the last vehicle
            // in that intersection that encountered equal times in both directions,
            // starting with the choice of row for the first vehicle in that situation.
            if(sameTime[row][col] == 1){
                sameTime[row][col] = 2;
                return 0;
            }else if(sameTime[row][col] == 2){
                sameTime[row][col] = 1;
                return 1;
            }else{
                //first car to have same intersection time
                sameTime[row][col] = 1;
                return 1;
            }
            
        }else{
            return rowTime < colTime;
        }
    }
    return 1;
}

void StreetGrid::setBlockage(size_t row, size_t col, bool rowDir, bool val)
{
    blocked[row][col][rowDir] = val;
}

EventList StreetGrid::processArrival(const std::string& vehicleID, const TimeStamp& ts)
{
    EventList newEvents;
    std::map<std::string, Vehicle>::iterator it = vehicles_.find(vehicleID);
       if(it == vehicles_.end()){
           throw std::logic_error("vehicle with that ID doesn't exist");
       }else{
           if(it->second.rowDir){
               rowSeg[it->second.rowIndex][it->second.colIndex]--;
               it->second.colIndex++;
           }else{
               colSeg[it->second.rowIndex][it->second.colIndex]--;
               it->second.rowIndex++;
           }
           if(it->second.rowIndex == (n - 1) && it->second.colIndex == (m - 1)){
               //at terminal location
               it->second.end = ts;
               completed_.push_back(it->second);
               vehicles_.erase(it);
           }else{
               bool row_or_col = shouldChooseRow(it->second.rowIndex, it->second.colIndex);
               int arrivalTime;
               if(row_or_col == 1){
                   //should cross row
                   arrivalTime = calcCrossTime(it->second.rowIndex, it->second.colIndex, 1);
                   it->second.rowDir = 1;
                   rowSeg[it->second.rowIndex][it->second.colIndex]++;
                   newEvents.push_back(new ArrivalEvent(ts + arrivalTime, *this, vehicleID));
               }else if(row_or_col == 0){
                   //should cross col
                   arrivalTime = calcCrossTime(it->second.rowIndex, it->second.colIndex, 0);
                   it->second.rowDir = 0;
                   colSeg[it->second.rowIndex][it->second.colIndex]++;
                   newEvents.push_back(new ArrivalEvent(ts + arrivalTime, *this, vehicleID));
               }
           }
       }
    return newEvents;
}

EventList StreetGrid::addVehicle(const Vehicle& v)
{
    EventList newEvents;
    std::map<std::string, Vehicle>::iterator it = vehicles_.find(v.id);
    if(it != vehicles_.end()){
        throw std::logic_error("vehicle with that ID has already been added");
    }else{
        if(v.rowIndex == (n - 1) && v.colIndex == (m - 1)){
            //already at terminal location
            completed_.push_back(v);
            return newEvents;
        }
        vehicles_.insert(make_pair(v.id, v));
        it = vehicles_.find(v.id);
        bool row_or_col = shouldChooseRow(v.rowIndex, v.colIndex);
        int arrivalTime;
        if(row_or_col == 1){
            //should cross row
            arrivalTime = calcCrossTime(it->second.rowIndex, it->second.colIndex, 1);
            it->second.rowDir = 1;
            rowSeg[it->second.rowIndex][it->second.colIndex]++;
            newEvents.push_back(new ArrivalEvent(it->second.start + arrivalTime, *this, it->second.id));
        }else if(row_or_col == 0){
            //should cross col
            arrivalTime = calcCrossTime(it->second.rowIndex, it->second.colIndex, 0);
            it->second.rowDir = 0;
            colSeg[it->second.rowIndex][it->second.colIndex]++;
            newEvents.push_back(new ArrivalEvent(it->second.start + arrivalTime, *this, it->second.id));
        }
        return newEvents;
    }
}


