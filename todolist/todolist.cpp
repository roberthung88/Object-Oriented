#include <stdexcept>
#include "todolist.h"
#include <iostream>
#include <new>
using namespace std;


DailyTodoList::DailyTodoList()
{
    data_ = new Item * [5];
    for(int i = 0; i < 5; ++i){
        data_[i] = NULL;
    }
    cap_ = 5;
    priorityHead_ = NULL;
    

    
}
DailyTodoList::~DailyTodoList(){
    for(int i = 0; i < int(cap_); ++i){
        if(data_[i] != NULL){
            Item* removeTerm = data_[i];
            while(removeTerm != NULL){
                Item* temp = removeTerm;
                removeTerm= removeTerm->nextItem;
                delete temp;
            }
        }
    }
    delete [] data_;
}


void DailyTodoList::push_back(size_t dayIndex, const std::string& val, bool highPriority)
{
    if (dayIndex < cap_)
    {
        this->insert(dayIndex, this->numItemsOnDay(dayIndex), val, highPriority);
    }
    else 
    {
        this->insert(dayIndex, 0, val, highPriority);
    }
    
}

void DailyTodoList::resize(size_t dayIndex){
    Item** temp = new Item * [dayIndex * 2];
    for(int i = 0; i < int(dayIndex) * 2; i++){
        temp[i] = NULL;
    }
    for(int i = 0; i < int(cap_); i++){
        temp[i] = data_[i];
    }
    delete [] data_;
    data_ = temp;
    cap_ = dayIndex * 2;
}
void DailyTodoList::insert(size_t dayIndex, size_t loc, const std::string& val, bool highPriority){
    int usage = 0;
    Item* temp = NULL;
    
    if(dayIndex > cap_ - 1){
        if(loc != 0){
            throw std::out_of_range("Invalid loc value");
        }
        //resize data_
        resize(dayIndex);
        if(loc == 0){
            data_[dayIndex] = new Item(val, NULL, NULL);
            temp = data_[dayIndex];
            usage = 0;
        }else{
            data_[dayIndex] = new Item("", NULL, NULL);
            temp = data_[dayIndex];
            for(int i = 0; i < int(loc) - 1; i++){
                Item* create_temp = new Item("", NULL, NULL);
                temp->nextItem = create_temp;
                temp = temp->nextItem;
            }
            temp->nextItem = new Item(val, NULL, NULL);
            usage = 1;
        }
    }else{
        if(loc > numItemsOnDay(dayIndex) || loc < 0){
            throw std::out_of_range("Invalid loc value");
        }
        temp = data_[dayIndex];
        if(loc == 0){
            if(temp != NULL){
                Item* toInsert = new Item(val, temp, NULL);
                data_[dayIndex] = toInsert;
                temp = data_[dayIndex];
            }else{
                data_[dayIndex] = new Item(val, NULL, NULL);
                temp = data_[dayIndex];
            }
            usage = 0;
        }else{
            if(temp == NULL){
                
                data_[dayIndex] = new Item("", NULL, NULL);
                temp = data_[dayIndex];
            }
            
            for(int i = 0; i < int(loc) - 1; i++){
                if(temp->nextItem == NULL){
                    Item* create_temp = new Item("", NULL, NULL);
                    temp->nextItem = create_temp;
                }
                temp = temp->nextItem;
            }
            if(temp->nextItem != NULL){
                Item* placeholder = temp->nextItem;
                Item* toInsert = new Item(val, placeholder, NULL);
                temp->nextItem = toInsert;
            }else{
                temp->nextItem = new Item(val, NULL, NULL);
            }
            usage = 1;
        }
       
    }
    if(highPriority){
        if(priorityHead_ == NULL){
            //no items
            if(usage == 0){
                priorityHead_ = temp;
            }else{
                priorityHead_ = temp->nextItem;
            }
                
            cap_priority = 1;
        }else{
            Item* tempprior = priorityHead_;
            cap_priority = 1;
            
            while(priorityHead_->nextPriorityItem != NULL){
                cap_priority++;
                priorityHead_ = priorityHead_->nextPriorityItem;
            }
            if(usage == 0){
                priorityHead_->nextPriorityItem  = temp;
            }else{
                priorityHead_->nextPriorityItem  = (temp->nextItem);
            }
            
            priorityHead_ = tempprior;
            cap_priority++;
        }
        
    }
}

void DailyTodoList::remove(size_t dayIndex, size_t loc){
    if(dayIndex > cap_ - 1 || dayIndex < 0){
         throw std::out_of_range("Invalid Location");
    }
    Item* temp = data_[dayIndex];
    if(numItemsOnDay(dayIndex) -1 < loc || loc < 0){
        throw std::out_of_range("Invalid Location");
    }
    if(loc == 0){
        if(data_[dayIndex] == NULL){
            return;
        }
        if(data_[dayIndex]->nextItem != NULL){
            Item* nextt = data_[dayIndex]->nextItem;
            data_[dayIndex] = nextt;
        }else{
            data_[dayIndex] = NULL;
        }
        
        Item* prioritycount = priorityHead_;
        if(priorityHead_ == temp){
            Item* nextPriority = prioritycount->nextPriorityItem;
            priorityHead_ = nextPriority;
            cap_priority--;
            delete temp;
        }else{
            if(prioritycount == NULL){
                return;
            }
            while(prioritycount->nextPriorityItem != NULL){
                if(prioritycount->nextPriorityItem == temp){
                    //found in prioritylist
                    Item* nextPriority = prioritycount->nextPriorityItem->nextPriorityItem;
                    if(nextPriority == NULL){
                        delete temp;
                        prioritycount->nextPriorityItem = NULL;
                        cap_priority--;
                    }else{
                        prioritycount->nextPriorityItem = nextPriority;
                        cap_priority--;
                        delete temp;
                        break;
                    }
                }
                prioritycount = prioritycount->nextPriorityItem;
                if(prioritycount == NULL){
                    return;
                }
            }
        }
        
        
    }else{
        for(int i = 0; i < int(loc) - 1; i++){
            temp = temp->nextItem;
        }
        Item* curr = temp->nextItem;
        Item* next_loc = curr->nextItem;
        temp->nextItem = next_loc;
        
        
        Item* prioritycount = priorityHead_;
        if(priorityHead_ == curr){
            Item* nextPriority = prioritycount->nextPriorityItem;
            priorityHead_ = nextPriority;
            cap_priority--;
            delete curr;
        }else{
            if(prioritycount == NULL){
                return;
            }
            while(prioritycount->nextPriorityItem != NULL){
                if(prioritycount->nextPriorityItem == curr){
                    //found in prioritylist
                    Item* nextPriority = prioritycount->nextPriorityItem->nextPriorityItem;
                    if(nextPriority == NULL){
                        delete curr;
                        prioritycount->nextPriorityItem = NULL;
                    }else{
                        prioritycount->nextPriorityItem = nextPriority;
                        cap_priority--;
                        delete temp;
                        break;
                    }
                }
                prioritycount = prioritycount->nextPriorityItem;
            }
        }
    }
}
size_t DailyTodoList::numDays() const{
    return cap_;
}

size_t DailyTodoList::numItemsOnDay(size_t dayIndex) const{
    if(dayIndex > cap_ - 1 || dayIndex < 0){
        throw std::out_of_range("DayIndex is Invalid");
    }
    size_t size = 0;
    Item* temp = data_[dayIndex];
    while(temp != NULL){
        size++;
        temp = temp->nextItem;
    }
    return size;
}

bool DailyTodoList::empty(size_t dayIndex) const{
    if(dayIndex > cap_ - 1 || dayIndex < 0){
        throw std::out_of_range("DayIndex is Invalid");
    }
    if(data_[dayIndex] == NULL){
        return true;
    }else{
        return false;
    }
}

const std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc) const{
    if(int(dayIndex) > int(cap_ - 1) || int(dayIndex) < 0){
        throw std::out_of_range("DayIndex is Invalid");
    }
    if(int(loc) > int(numItemsOnDay(dayIndex) - 1) || int(loc) < 0){
        throw std::out_of_range("Loc is Invalid");
    }
    Item* temp = data_[dayIndex];
    for(size_t i = 0; i < loc; i++){
        temp = temp->nextItem;
    }
    return temp->val;
}
std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc){
    if(int(dayIndex) > int(cap_ - 1) || int(dayIndex) < 0){
        throw std::out_of_range("DayIndex is Invalid");
    }
    if(int(loc) > int(numItemsOnDay(dayIndex) - 1) || int(loc) < 0){
        throw std::out_of_range("Loc is Invalid");
    }
    Item* temp = data_[dayIndex];
    for(size_t i = 0; i < loc; i++){
        temp = temp->nextItem;
    }
    return temp->val;
}

size_t DailyTodoList::numPriorityItems() const{
    return cap_priority;
}

const std::string& DailyTodoList::getPriorityVal(size_t priorityLoc) const{
    if(int(priorityLoc) > int(cap_priority - 1)){
        throw std::out_of_range("priorityLoc is Invalid");
    }
    Item* result = priorityHead_;
    for(int i = 0; i < int(priorityLoc); ++i){
        result = result->nextPriorityItem;
    }
    return result->val;
}
