## Formula Slug Firmware Onboarding Project

The following is my submission of the firmware onboarding project in order to join the formula slug club at UCSC

Clone with:
```
git clone https://github.com/EthanM417/FormulaSlug-Firmware-Onboarding-Project.git --recursive  
```


# Description:

This project is an implementation of an electronic throttle control algorithm, consistent with the rules for the Formula SAE competition, outlined [here](https://www.fsaeonline.com/cdsweb/gen/DownloadDocument.aspx?DocumentID=278fd4d7-aa27-4e33-bc4a-090148e662a0).

The algorithm averages the calculated throttle position between two sensors. It will also detect a deviation of more than 10% between the two sensors, and in such a case cut power to the motor.

It furthermore implements the ready to drive function, outlined in the rules.

Note: The algorithm is supposed to serve as a simulation, thus it outputs the throttle position over serial instead of over CAN. 


# Build

The project depends on mbed-os community edition, ninja build, and the arm gnu toolchain.
A setup guide is provided [here](https://mbed-ce.dev/getting-started/toolchain-install/).


To Build:
creat a directory called build. Enter the build directory and execute

```
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Develop -DMBED_TARGET=NUCLEO_L432KC
```

change the -DMBED_TARGET to whatever board you would like to flash


then to compile:

```
ninja
```

and finally to flash 
```
ninja flash-firmwareOnboard
```
where firmwareOnBoard is just the project name defined in CMakeLists.txt
