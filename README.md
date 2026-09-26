# Water Level Monitor System

In many applications such as water storage tanks, monitoring and managing water levels is crucial for efficient operation and prevention of overflow or depletion. This project implements a water level indicator using an Arduino Uno, an analog water level sensor, a set of LEDs and a buzzer to provide both visual and audible representation of water level.

## Features

- Realtime water level reading via analog sensor
- Serial Monitor output for raw sensor value and calculated percentage
- Threetier LED indication (low / rising / critical)
- Buzzer alerts that escalate as water level increases
- Continuous alert loop when water level reaches 100% or above until it drops back down

## System Components

- **Arduino Uno Board** — serves as the main controller, processing the sensor input and driving the output devices.
- **Water Level Sensor** — an analog sensor connected to the Arduino's A5 pin. 
- **LED Indicators** — three LEDs (red, yellow, blue) that visually indicate the current water level status.
- **Buzzer** — provides an audible alert once the water level crosses certain thresholds.
- **Resistors** — limit current to the LEDs to protect them from damage.
- **Jumper Wires** — connect the components on the breadboard (available in male-to-male, male-to-female, and female-to-female types).
- **Breadboard** — used to connect the sensor and other components to the microcontroller.

## Wiring / Pin Layout

| Component           | Arduino Pin | Notes                      |
|---------------------|:-----------:|----------------------------|
| Water level sensor  | A5          | Analog input               |
| Red LED             | 7           | Digital output             |
| Yellow LED          | 11          | Digital output             |
| Blue LED            | 12          | Digital output             |
| Buzzer              | 13          | Digital output             |

## System Functionality

The Arduino continuously reads the analog input from the water level sensor and converts it into a percentage value representing the water level. Based on this percentage, the system sets the state of the LEDs and buzzer as follows:

- **Below 25%** — all LEDs are turned off and the buzzer is silent, followed by a 500 ms delay before the next check.
- **25%–49%** — the red LED turns on, the buzzer stays silent, followed by a 500 ms delay before the next check.
- **50%–99%** — the yellow LED turns on and the buzzer emits a 600 Hz tone for 0.1 seconds, followed by a 500 ms delay before the next check.
- **100% or above** — the blue LED turns on and the buzzer emits an 800 Hz tone for 0.1 seconds, followed by a 100 ms delay, then continuous beeping until the water level drops back below 100%.

This monitoring cycle repeats continuously, updating the LED and buzzer outputs in response to changing water levels. Sensor readings and calculated percentages are also printed to the Serial Monitor (9600 baud) for debugging and monitoring.

| Water Level | LED       | Buzzer                                                    |
|-------------|-----------|--------------------------------------------------         |
| < 25%       | None      | Off                                                       |
| 25–49%      | Red       | Off                                                       |
| 50–99%      | Yellow    | Beeps at 600 Hz                                           |
| ≥ 100%      | Blue      | Beeps at 800 Hz continuously until level drops below 100% |

## Getting Started

1. Wire the components according to the pin layout above.
2. Open `water_level_monitor.ino` in the Arduino IDE.
3. Select your board (Arduino Uno) and the correct COM port.


## Calibration Note

The `map(sensorValue, 0, 700, 0, 100)` call assumes a maximum raw sensor reading of 700 corresponds to a "full" water level. This value may need to be adjusted depending on your specific sensor and container setup — test with your sensor fully submerged and adjust the upper bound accordingly.

## Possible Improvements

- Use `millis()` for non-blocking buzzer timing instead of the blocking `while` loop at 100%+
- Add a button or reset mechanism to silence the alarm manually
- Log readings to an SD card or send data over WiFi/Bluetooth for remote monitoring


