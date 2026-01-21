## The electrical circuit
Here is the complete electrical diagram of our system. It consists of a gas-type switch, a variable resistor using an MCP41100 digital potentiometer, another variable resistor using an MCP41100 digital potentiometer, an Arduino Uno, a gas sensor, and a LoRa module.

<img width="1069" height="761" alt="Capture d’écran 2026-01-21 à 14 50 42" src="https://github.com/user-attachments/assets/f9749b54-5b4b-4f5f-adf4-a1123967b55f" />


The fabricated gas sensor exhibits a very high resistance that varies depending on the type and presence of gas. Its resistance is on the order of gigohms, resulting in an extremely low current of the order of nanoamperes flowing into the ADC. Since an Arduino uses a 10-bit ADC, the sensor output signal must be amplified. To address this, we designed an amplification circuit based on an operational amplifier and validated it through LTSpice simulations.
Below is the LTSpice circuit:

<img width="1205" height="579" alt="Capture d’écran 2026-01-21 à 14 50 59" src="https://github.com/user-attachments/assets/da387e7a-4670-471a-a106-f1b9d512d2ef" />

The circuit includes three filters with different cutoff frequencies to reduce noise and shape the signal:
- A low-frequency filter to suppress sensor noise,
- A notch filter to attenuate 50 Hz power-line interference,
- An anti-aliasing filter to prevent distortion during ADC sampling.

Transient simulations confirmed correct amplifier operation, with a gain of 101, matching theoretical calculations. Frequency analysis using Bode diagrams showed an overall gain of 140 dB, consistent with the expected transfer function. FFT analysis further demonstrated effective noise reduction, particularly at 50 Hz, while highlighting the trade-off between noise suppression and signal distortion when filter capacitance is increased excessively.
Overall, the simulations validate the amplifier design and confirm its suitability for accurately measuring low-current gas sensor signals using low-cost data acquisition systems.

## PCB Design
To bring all the components of our sensor system together, we designed a dedicated Printed Circuit Board (PCB). This board combines all stages of the system into a unified and compact design, providing an optimized layout, enhanced reliability, and efficient operation. The detailed PCB design is shown in the figure below.

<img width="821" height="632" alt="Capture d’écran 2026-01-21 à 14 51 16" src="https://github.com/user-attachments/assets/aff53977-cc37-4a82-8851-a0ac24ff60ac" />



Below, there is a 3D view of the PCB after conception.

- Front view:


<img width="553" height="449" alt="Capture d’écran 2026-01-21 à 14 51 26" src="https://github.com/user-attachments/assets/fcee5305-a097-4b84-93d8-64f9f1c78505" />




- Back view:


<img width="553" height="449" alt="Capture d’écran 2026-01-21 à 14 51 32" src="https://github.com/user-attachments/assets/0dcf478f-0281-4cf1-b078-9a62e4b0c805" />



## MIT App Inventor



The MIT App Inventor application is designed to interface with the Arduino, allowing users to control the system and monitor sensor data in real time.


  <img width="498" height="805" alt="Capture d’écran 2026-01-21 à 14 52 11" src="https://github.com/user-attachments/assets/2b66d18e-0d05-4d7a-bd6e-26b859578ae6" />

  


This MIT App Inventor application functions as a Bluetooth remote control for an Arduino system. It allows the user to first connect to a Bluetooth module (such as HC-05) through a list of available devices, and then send commands either by pressing buttons or using voice commands. The "LED ON" button sends the number 1 to turn on the LED, the "LED OFF" button sends 2 to turn it off, and if the voice recognition detects the word "blink," the app sends 3 to make the LED blink. At the same time, the application can receive and display messages sent by the Arduino via Bluetooth.
