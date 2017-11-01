/*
 * WallRecognizer.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_WALLRECOGNIZER_H_
#define SAM_WALLRECOGNIZER_H_

#include "../common/SensorDataRepo.h"


class WallRecognizer {
public:
    WallRecognizer();
    virtual ~WallRecognizer();

    void init();

private:
    const int MIN_FRONT_DISTANCE = 50;
    const int MIN_SIDE_DISTANCE  = 50;

    SensorDataRepo *m_SensorDataRepo;
};

#endif /* RECOGNIZER_WALLRECOGNIZER_H_ */
