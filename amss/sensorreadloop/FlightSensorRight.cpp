/*
MIT License

Copyright (c) 2017 John Bryan Moore

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//VL53L0X Flight Range Sensor Class Source File

#include "FlightSensorRight.h"

FlightSensorRight::FlightSensorRight()
{
    mpMyDevice = &mMyDevice;
    mpRangingMeasurementData = &mRangingMeasurementData;

    startRanging(VL53L0X_BETTER_ACCURACY_MODE, 0x29, 1, 0x70);

    if((mTiming = GetTiming()) == 0)
    {
        printf("Error Getting Timing Budget\n");
        stopRanging();
    }

    if(mTiming < 20000)	mTiming = 20000;
    printf("Timing %d ms\n", mTiming/1000);
}

void FlightSensorRight::read()
{
    int32_t distance;

    // Get distance from VL53L0X  on TCA9548A bus 1
    distance = getDistance();
    //if(distance > 0)
    //	printf("Right: %d mm, %d cm\n\n", distance, (distance/10));

    //Data Save
    if(distance > 0)
        putData(SensorType::right, (int)distance);

    usleep(mTiming);
}

/******************************************************************************
 * @brief   Start Ranging
 * @param   mode - ranging mode
 *              0 - Good Accuracy mode
 *              1 - Better Accuracy mode
 *              2 - Best Accuracy mode
 *              3 - Longe Range mode
 *              4 - High Speed mode
 * @note Mode Definitions
 *   Good Accuracy mode
 *       33 ms timing budget 1.2m range
 *   Better Accuracy mode
 *       66 ms timing budget 1.2m range
 *   Best Accuracy mode
 *       200 ms 1.2m range
 *   Long Range mode (indoor,darker conditions)
 *       33 ms timing budget 2m range
 *   High Speed Mode (decreased accuracy)
 *       20 ms timing budget 1.2m range
 *  @param  i2c_address - I2C Address to set for this device
 *  @param  TCA9548A_Device - Device number on TCA9548A I2C multiplexer if
 *              being used. If not being used, set to 255.
 *  @param  TCA9548A_Address - Address of TCA9548A I2C multiplexer if
 *              being used. If not being used, set to 0.
 *
 *****************************************************************************/
void FlightSensorRight::startRanging(int mode, uint8_t i2c_address, uint8_t TCA9548A_Device, uint8_t TCA9548A_Address)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;
    VL53L0X_Version_t Version;
    VL53L0X_Version_t * pVersion   = &Version;
    VL53L0X_DeviceInfo_t DeviceInfo;
    int32_t status_int;

    if (TCA9548A_Device < 8)
    {
        printf ("VL53L0X Start Ranging Object Address 0x%02X TCA9548A Device %d TCA9548A Address 0x%02X\n\n",
                    i2c_address, TCA9548A_Device, TCA9548A_Address);
    }
    else
    {
        printf ("VL53L0X Start Ranging Object Address 0x%02X\n\n", i2c_address);
    }

    if (mode >= VL53L0X_GOOD_ACCURACY_MODE && mode <= VL53L0X_HIGH_SPEED_MODE)
    {
        memset(mpMyDevice, 0, sizeof(VL53L0X_Dev_t));

        if (mpMyDevice != NULL)
        {
            // Initialize Comms to the default address to start
            mpMyDevice->I2cDevAddr      = VL53L0X_DEFAULT_ADDRESS;
            mpMyDevice->TCA9548A_Device = TCA9548A_Device;
            mpMyDevice->TCA9548A_Address = TCA9548A_Address;

            /*
             *  Get the version of the VL53L0X API running in the firmware
             */

            // If the requested address is not the default, change it in the device
            if (i2c_address != VL53L0X_DEFAULT_ADDRESS)
            {
                printf("Setting I2C Address to 0x%02X\n", i2c_address);
                // Address requested not default so set the address.
                // This assumes that the shutdown pin has been controlled
                // externally to this function.
                // TODO: Why does this function divide the address by 2? To get
                // the address we want we have to mutiply by 2 in the call so
                // it gets set right
                Status = VL53L0X_SetDeviceAddress(mpMyDevice, (i2c_address * 2));
                mpMyDevice->I2cDevAddr      = i2c_address;
            }

            if (Status == VL53L0X_ERROR_NONE)
            {
                status_int = VL53L0X_GetVersion(pVersion);
                if (status_int == 0)
                {
                    /*
                     *  Verify the version of the VL53L0X API running in the firmrware
                     */

                    // Check the Api version. If it is not correct, put out a warning
                    if( pVersion->major != VERSION_REQUIRED_MAJOR ||
                        pVersion->minor != VERSION_REQUIRED_MINOR ||
                        pVersion->build != VERSION_REQUIRED_BUILD )
                    {
                        printf("VL53L0X API Version Warning: Your firmware %d.%d.%d (revision %d). This requires %d.%d.%d.\n",
                            pVersion->major, pVersion->minor, pVersion->build, pVersion->revision,
                            VERSION_REQUIRED_MAJOR, VERSION_REQUIRED_MINOR, VERSION_REQUIRED_BUILD);
                    }
                    // End of implementation specific

                    Status = VL53L0X_DataInit(mpMyDevice); // Data initialization
                    if(Status == VL53L0X_ERROR_NONE)
                    {
                        Status = VL53L0X_GetDeviceInfo(mpMyDevice, &DeviceInfo);
                        if(Status == VL53L0X_ERROR_NONE)
                        {
                            printf("VL53L0X_GetDeviceInfo:\n");
                            printf("Device Name : %s\n", DeviceInfo.Name);
                            printf("Device Type : %s\n", DeviceInfo.Type);
                            printf("Device ID : %s\n", DeviceInfo.ProductId);
                            printf("ProductRevisionMajor : %d\n", DeviceInfo.ProductRevisionMajor);
                            printf("ProductRevisionMinor : %d\n", DeviceInfo.ProductRevisionMinor);

                            if ((DeviceInfo.ProductRevisionMajor != 1) && (DeviceInfo.ProductRevisionMinor != 1)) {
                                printf("Error expected cut 1.1 but found cut %d.%d\n",
                                        DeviceInfo.ProductRevisionMajor, DeviceInfo.ProductRevisionMinor);
                                Status = VL53L0X_ERROR_NOT_SUPPORTED;
                            }
                        }

                        if(Status == VL53L0X_ERROR_NONE)
                        {
                            Status = VL53L0X_StaticInit(mpMyDevice); // Device Initialization
                            // StaticInit will set interrupt by default

                            if(Status == VL53L0X_ERROR_NONE)
                            {
                                Status = VL53L0X_PerformRefCalibration(mpMyDevice,
                                        &VhvSettings, &PhaseCal); // Device Initialization

                                if(Status == VL53L0X_ERROR_NONE)
                                {
                                    Status = VL53L0X_PerformRefSpadManagement(mpMyDevice,
                                            &refSpadCount, &isApertureSpads); // Device Initialization

                                    if(Status == VL53L0X_ERROR_NONE)
                                    {
                                        // Setup in continuous ranging mode
                                        Status = VL53L0X_SetDeviceMode(mpMyDevice, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);

                                        if(Status == VL53L0X_ERROR_NONE)
                                        {
                                            // Set accuracy mode
                                            switch (mode)
                                            {
                                                case VL53L0X_BEST_ACCURACY_MODE:
                                                    printf("VL53L0X_BEST_ACCURACY_MODE\n");
                                                    if (Status == VL53L0X_ERROR_NONE)
                                                    {
                                                        Status = VL53L0X_SetLimitCheckValue(mpMyDevice,
                                                            VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
                                                            (FixPoint1616_t)(0.25*65536));

                                                        if (Status == VL53L0X_ERROR_NONE)
                                                        {
                                                            Status = VL53L0X_SetLimitCheckValue(mpMyDevice,
                                                                VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
                                                                (FixPoint1616_t)(18*65536));

                                                            if (Status == VL53L0X_ERROR_NONE)
                                                            {
                                                                Status =
                                                                    VL53L0X_SetMeasurementTimingBudgetMicroSeconds(mpMyDevice, 200000);
                                                            }
                                                        }
                                                    }
                                                    break;

                                                case VL53L0X_LONG_RANGE_MODE:
                                                    printf("VL53L0X_LONG_RANGE_MODE\n");
                                                    if (Status == VL53L0X_ERROR_NONE)
                                                    {
                                                        Status = VL53L0X_SetLimitCheckValue(mpMyDevice,
                                                                    VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
                                                                    (FixPoint1616_t)(0.1*65536));

                                                        if (Status == VL53L0X_ERROR_NONE)
                                                        {
                                                            Status = VL53L0X_SetLimitCheckValue(mpMyDevice,
                                                                        VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
                                                                        (FixPoint1616_t)(60*65536));

                                                            if (Status == VL53L0X_ERROR_NONE)
                                                            {
                                                                Status =
                                                                    VL53L0X_SetMeasurementTimingBudgetMicroSeconds(mpMyDevice, 33000);

                                                                if (Status == VL53L0X_ERROR_NONE)
                                                                {
                                                                    Status = VL53L0X_SetVcselPulsePeriod(mpMyDevice,
                                                                                VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);

                                                                    if (Status == VL53L0X_ERROR_NONE)
                                                                    {
                                                                        Status = VL53L0X_SetVcselPulsePeriod(mpMyDevice,
                                                                                    VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                    break;

                                                case VL53L0X_HIGH_SPEED_MODE:
                                                    printf("VL53L0X_HIGH_SPEED_MODE\n");
                                                    if (Status == VL53L0X_ERROR_NONE)
                                                    {
                                                        Status = VL53L0X_SetLimitCheckValue(mpMyDevice,
                                                                    VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
                                                                    (FixPoint1616_t)(0.25*65536));

                                                        if (Status == VL53L0X_ERROR_NONE)
                                                        {
                                                            Status = VL53L0X_SetLimitCheckValue(mpMyDevice,
                                                                        VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
                                                                        (FixPoint1616_t)(32*65536));

                                                            if (Status == VL53L0X_ERROR_NONE)
                                                            {
                                                                Status =
                                                                    VL53L0X_SetMeasurementTimingBudgetMicroSeconds(mpMyDevice, 20000);
                                                            }
                                                        }
                                                    }
                                                    break;

                                                case VL53L0X_BETTER_ACCURACY_MODE:
                                                    printf("VL53L0X_BETTER_ACCURACY_MODE\n");
                                                    if (Status == VL53L0X_ERROR_NONE)
                                                    {
                                                        Status =
                                                            VL53L0X_SetMeasurementTimingBudgetMicroSeconds(mpMyDevice, 66000);
                                                    }
                                                    break;

                                                case VL53L0X_GOOD_ACCURACY_MODE:
                                                default:
                                                    printf("VL53L0X_GOOD_ACCURACY_MODE\n");
                                                    if (Status == VL53L0X_ERROR_NONE)
                                                    {
                                                        Status =
                                                            VL53L0X_SetMeasurementTimingBudgetMicroSeconds(mpMyDevice, 33000);
                                                    }
                                                    break;
                                            }

                                            if(Status == VL53L0X_ERROR_NONE)
                                            {
                                                Status = VL53L0X_StartMeasurement(mpMyDevice);
                                            }
                                            else
                                            {
                                                printf("Set Accuracy\n");
                                            }
                                        }
                                        else
                                        {
                                            printf ("Call of VL53L0X_SetDeviceMode\n");
                                        }
                                    }
                                    else
                                    {
                                        printf ("Call of VL53L0X_PerformRefSpadManagement\n");
                                    }
                                }
                                else
                                {
                                    printf ("Call of VL53L0X_PerformRefCalibration\n");
                                }
                            }
                            else
                            {
                                printf ("Call of VL53L0X_StaticInit\n");
                            }
                        }
                        else
                        {
                            printf ("Invalid Device Info\n");
                        }
                    }
                    else
                    {
                        printf ("Call of VL53L0X_DataInit\n");
                    }
                }
                else
                {
                    Status = VL53L0X_ERROR_CONTROL_INTERFACE;
                    printf("Call of VL53L0X_GetVersion\n");
                }
            }
            else
            {
                printf("Call of VL53L0X_SetAddress\n");
            }

            print_pal_error(Status);
        }
        else
        {
            printf("Object not initialized\n");
        }
    }
    else
    {
        printf("Invalid mode %d specified\n", mode);
    }
}

/******************************************************************************
 * @brief   Get current distance in mm
 * @return  Current distance in mm or -1 on error
 *****************************************************************************/
int32_t FlightSensorRight::getDistance(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    int32_t current_distance = -1;

    if (mpMyDevice != NULL)
    {
        Status = WaitMeasurementDataReady(mpMyDevice);

        if(Status == VL53L0X_ERROR_NONE)
        {
            Status = VL53L0X_GetRangingMeasurementData(mpMyDevice,
                                mpRangingMeasurementData);
            if(Status == VL53L0X_ERROR_NONE)
            {
                current_distance = mpRangingMeasurementData->RangeMilliMeter;
            }

            // Clear the interrupt
            VL53L0X_ClearInterruptMask(mpMyDevice,
                                VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
            // VL53L0X_PollingDelay(mpMyDevice);
        }
    }
    else
    {
        printf("Object not initialized\n");
    }

    return current_distance;
}

/******************************************************************************
 * @brief   Stop Ranging
 *****************************************************************************/
void FlightSensorRight::stopRanging(void)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    printf ("Call of VL53L0X_StopMeasurement\n");

    if (mpMyDevice != NULL)
    {
        Status = VL53L0X_StopMeasurement(mpMyDevice);

        if(Status == VL53L0X_ERROR_NONE)
        {
            printf ("Wait Stop to be competed\n");
            Status = WaitStopCompleted(mpMyDevice);
        }

        if(Status == VL53L0X_ERROR_NONE)
        {
            Status = VL53L0X_ClearInterruptMask(mpMyDevice,
                VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
        }

        print_pal_error(Status);
    }
    else
    {
        printf("Object not initialized\n");
    }
}

void FlightSensorRight::print_pal_error(VL53L0X_Error Status)
{
    char buf[VL53L0X_MAX_STRING_LENGTH];
    VL53L0X_GetPalErrorString(Status, buf);
    printf("API Status: %i : %s\n", Status, buf);
}

VL53L0X_Error FlightSensorRight::WaitMeasurementDataReady(VL53L0X_DEV Dev)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint8_t NewDatReady=0;
    uint32_t LoopNb;

    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE)
    {
        LoopNb = 0;
        do
        {
            Status = VL53L0X_GetMeasurementDataReady(Dev, &NewDatReady);
            if ((NewDatReady == 0x01) || Status != VL53L0X_ERROR_NONE)
            {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP)
        {
            Status = VL53L0X_ERROR_TIME_OUT;
        }
    }

    return Status;
}

VL53L0X_Error FlightSensorRight::WaitStopCompleted(VL53L0X_DEV Dev)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint32_t StopCompleted=0;
    uint32_t LoopNb;

    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE)
    {
        LoopNb = 0;
        do
        {
            Status = VL53L0X_GetStopCompletedStatus(Dev, &StopCompleted);
            if ((StopCompleted == 0x00) || Status != VL53L0X_ERROR_NONE)
            {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP)
        {
            Status = VL53L0X_ERROR_TIME_OUT;
        }
    }

    return Status;
}

uint32_t FlightSensorRight::GetTiming()
{
    VL53L0X_Error status;
    uint32_t      budget;

    status=VL53L0X_GetMeasurementTimingBudgetMicroSeconds(mpMyDevice,&budget);
    if  (status==VL53L0X_ERROR_NONE)
    {
        printf("sleep time %d\n", budget);
        return(budget+1000);
    }
    else
        return (0);
}

