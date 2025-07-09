# Heated Bed Controller for 3d Printer

![remote control top view](controller_top_view.jpg)

## Summary

### Backstory

- TBD

### Reading Joystick Movements

- TBD

### NRF24 Communication

- TBD

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

- TBD