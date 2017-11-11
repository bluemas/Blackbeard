/*
 * RecognizerBase.h
 *
 *  Created on: 2017. 11. 10.
 *      Author: gtlove
 */

#ifndef COMMON_RECOGNIZERBASE_H_
#define COMMON_RECOGNIZERBASE_H_

class RecognizerBase {
public:
    RecognizerBase();
    virtual ~RecognizerBase();

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void run() = 0;
};

#endif /* COMMON_RECOGNIZERBASE_H_ */
