# Arduino book displayer

Reads file from microSD card -> displays text on MAX7219 4-in-1 display.

![scrolling text video](readme_files/scrolling_text_video.webp)
### Hardware used

- Arduino Leonardo
- MAX7219 4-in-1 display
- 1GB SD card
- Micro SD Card Mini TF Card Reader Module


### Wiring

| Component      | Pin Name | Leonardo Pin |
| -------------- | -------- | ------------ |
| SD Card Module | VCC      | 5V           |
| SD Card Module | GND      | GND          |
| SD Card Module | MISO     | ICSP-1       |
| SD Card Module | SCK      | ICSP-3       |
| SD Card Module | MOSI     | ICSP-4       |
| SD Card Module | CS       | D4           |
| MAX7219 Matrix | VCC      | 5V           |
| MAX7219 Matrix | GND      | GND          |
| MAX7219 Matrix | DIN      | D11          |
| MAX7219 Matrix | CS       | D10          |
| MAX7219 Matrix | CLK      | D13          |
