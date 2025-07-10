![remote control top view](controller_top_view.jpg)


## Summary


- A rudimentary RC controller used to read movements of joysticks and write them wirelessly to a RC Car.


### Backstory


- In order to prepare for more advanced RF projects in the future, it was necessary to understand the basics of the NRF24 module, how it works, and where it falls short. For the code, designs, and circuit listed in this project, the RC controller is writing joystick movement data to drive an RC car project that's still in development (for now ;D).


### Reading Joystick Movements


- With 2 joysticks there are 4 different channels of movement we can read in to pass over radio communication:
  - Left vertical (left to right), left horizontal (up and down), right vertical (left to right), and right horizontal (up and down)
  - The Arduino nano's [analog to digital converter (ADC)](https://en.wikipedia.org/wiki/Analog-to-digital_converter) has a 10-bit resolution, we can take in a analog reading between 0 - 1024 for each channel listed above.


- Values for each channel are mapped from 0 - 1024 to 0 - 255 for ease of use by the RC receiver on the end of the serial connection (in this example, PWM values to drive an RC car).


- Given the orientation of the joysticks are being flipped to simplify wiring and space, when the values are being mapped, we invert the values for left horizontal and right vertical.
 - This is done by subtracting the max 'ceiling' value for said channel by the channel value mapped from the analog reading (255 - channel mapped value).


### NRF24 Communication


- The NRF24 module uses a 2.4 GHz frequency to communicate with other NRF24 module(s). This is represented in code where two devices would form a connection by opening either a read or write pipe that matches the other modules byte address.


- The NRF24 uses the SPI protocol to transmit and receive data between the arduino nano, where in this example, the arduino drives the NRF24 module to transmit packets to the configured address. The packets here being the struct `data` where the 4 joysticks channels are represented and sent to the configured address.
  - See [Serial Peripheral Interface](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface) for more details on this protocol.


### Output To Display




  OLED display uses I2C protocol and serial communication is handled via the `Adafruit_SSD1306` library to write relevant data to display.




  Display data key:


  LV: *Left vertical joystick value*


  LH: *Left horizontal joystick value*


  RV: *Right vertical joystick value*


  RH: *Right horizontal joystick value*




## Material List




- 1x 50mm x 70mm PCB Prototype Board
- 22 AWG Jumper Wires
- 1x Arduino Nano (ATmega328P)
- 1x NRF24 Transceiver Module 2.4G
- 1x NRF24 Socket Adapter Board
- 2x dual-axis joysticks
- DC switch (250V 10A switch is what I'm using)
- 1x small OLED display (I2C)
- Soldering setup (iron, solder, etc.)
- 9 volt battery + battery connector




#### Optional Materials




- Heat shrink tubing
- 3d printer and PLA filament (for printing the housing)
- Solder flux paste to make better contacts




## Future Enhancements


- Setting up reading pipe on RC controller
  - NRF24 transceiver is capable of both reading and writing data to a multitude of addresses.
  - Setting up a reading data pipeline, it would be possible to interpret payloads from the devices that are being written to, such as the end device's cameras, sensors, etc.


- Read and write to multiple devices
  - Writing to multiple address allows to control two devices with the same or potentially different payloads
  - In tandem with reading and writing, the RC controller could be used as a central hub in the RF network to relay and interpret information from one node to another, simplifying computation / logic required at each end node device.


- Bluetooth and wifi connectivity
  - The RC controller could pass information off to other devices over another local network not associated with the NRF24 2.4 Ghz band.
  - The RC controller could be used as a go between the RF devices and cloud infrastructure, which could host communication to or from a private web api hosted in the cloud.