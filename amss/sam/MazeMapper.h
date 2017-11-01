/*
 * MazeMapper.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAZEMAPPER_H_
#define SAM_MAZEMAPPER_H_

#include "../common/SensingEvent.h"
#include "../common/Constants.h"

class MazeMapper {

public:
    MazeMapper();
    virtual ~MazeMapper();

    void notify(SensingEvent e);
    void setNextDirection(Direction dir);
};

#endif /* SAM_MAZEMAPPER_H_ */
