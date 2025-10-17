#include "AnalogIn.h"
#include "ThisThread.h"
#include "mbed.h"


#define brakeSensor PA_3
#define conSwitch A6
#define sensor1 PA_3
#define sensor2 PA_4
#define buzzer PA_7
#define sensor1Low 0.25
#define sensor1High 2.25
#define sensor2Low 0.3
#define sensor2High 2.7
#define brakeSensorLow 0.25
#define brakeSensorHigh 2.25
#define sensorTimeout 100


AnalogIn s1{sensor1}; // first throttle position sensor
AnalogIn s2{sensor2}; // second throttle position sensor
AnalogIn bS{brakeSensor}; // brake position sensor
DigitalIn cS{conSwitch}; // cockpit control switch
DigitalOut bz{buzzer}; // buzzer
bool devianceDetected = false;
bool brakeSet = false;
bool switchSet = false;

float pedalPos(AnalogIn&, float, float);

float calcAveragePos(float, float);


int main()
{
    int64_t timeOfDeviance = 0;
    float s1Reading;
    float s2Reading;
    float realReading;
    float difference;
    Timer t;
    float brakeSensorRead = 0;
/* Wait for ready to drive sequence:
  first hit the brake then hit the cockpit control switch
*/
    printf("Waiting for Init sequence:\n");
    while (!brakeSet){
      brakeSensorRead = pedalPos(bS, brakeSensorLow, brakeSensorHigh);
      if(brakeSensorRead > 80){
        brakeSet = true;
        printf("BrakeSet\n");
        break;
      }

    }
    while (!switchSet){
      if(cS){
        switchSet = true;
        printf("SwitchSet\n");
        bz = 1;
        ThisThread::sleep_for(1s);
        bz = 0;
        break;
      }
    }


    //Main loop executing after the ready to drive sequence:

    while (true) {
        s1Reading = pedalPos(s1, sensor1Low, sensor1High);
        s2Reading = pedalPos(s2, sensor2Low, sensor2High);

        difference = (s1Reading - s2Reading);

        realReading = calcAveragePos(s1Reading, s2Reading); //read the 2 sensors and find the average between them
        timeOfDeviance = t.elapsed_time().count() /1000; // convert the time to milliseconds
        if((-10 > difference || difference > 10)){ // start the timer if a deviance of more than 10% detected
            t.start();
        }else if((-10 < difference && difference < 10)){
            t.reset(); // stop the timer when the deviance stops
            timeOfDeviance = 0;
        }


        if(timeOfDeviance < sensorTimeout){ //output the throttle position to the serial output
            printf("%f", realReading);
            printf("\n");
        }else{
            printf("%f", 0);
        }
    }
}


float pedalPos(AnalogIn &givenSensor, float LowEnd, float HighEnd){ //calculate pedal position based off of voltage range and read voltage
    float measuredV = givenSensor.read()*3.3;
    if(measuredV < LowEnd || measuredV > HighEnd){
      return 0;
    }else{
      float percent = (measuredV-LowEnd) / (HighEnd-LowEnd);
      return percent*100;
    }
}

float calcAveragePos(float reading1, float reading2){ // calculate the average between two values
    return (reading1+reading2)/2;
}
