/*
 * MapRepo.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAPREPO_H_
#define SAM_MAPREPO_H_

#include "../common/SharedMemory.h"

class MapRepo : public SharedMemory {

public:
    void map();
    void unMap();
};

#endif /* SAM_MAPREPO_H_ */
