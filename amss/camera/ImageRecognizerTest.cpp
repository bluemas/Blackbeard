//ImageRecognizer Test

#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include "ImageRecognizer.h"
//#include <thread>


using namespace std;

static void Control_C_Handler(int s);

static bool gRun = false;

int main() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = Control_C_Handler; // Setup control-c callback 
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);    

    ImageRecognizer imgRecognizer;
    imgRecognizer.setLineRecognizeMode(true);
    gRun = true;
    printf("start test\n");
    imgRecognizer.start();
    while(gRun)
    {
        sleep(1);
    }
    printf("end test\n");
    


    return 0;
}

static void Control_C_Handler(int s)
{
    printf("Caught signal %d\n",s);
    gRun = false;
    printf("exiting\n");
    //exit(1);
}