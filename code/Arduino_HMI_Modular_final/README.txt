Arduino Uno / ATmega328P modular HMI sketch

Open Arduino_HMI_Modular.ino in Arduino IDE. Keep all .h and .ino files in the same folder.

Connections (separate 16x2 LCD, NOT LCD keypad shield):
LCD RS D12 (PB4), E D11 (PB3), LCD D4-D7 to Arduino D4-D7.
LM35 output A0; LDR voltage-divider output A1.
DHT11 data D3, with suitable data pull-up if the module lacks one.
LED D10 through current-limiting resistor, cathode to GND.
Button 1 (lower limit) D8/PB0 and Button 2 (upper limit) D9/PB1.
Both buttons are active HIGH: pressed = 5V/HIGH, released = 0V/LOW.
Use external pull-down resistors (e.g. 10k ohms to GND) unless the button modules already provide a defined LOW when released.
Internal pull-ups are disabled. Never leave these inputs floating.

The LCD rotates Temp, Hum, LDR approximately every 3 seconds.
Press D8 to increment the lower limit for the currently displayed sensor.
Press D9 to increment the upper limit for the currently displayed sensor.
Each press changes temperature/humidity by 1 unit, LDR by 10 ADC counts.
At the limit, values wrap while maintaining lower limit < upper limit.
Button presses are debounced and only count once until released.
Limits are held in RAM and reset to defaults on power cycle.
The LED turns on if any valid sensor reading is outside its limits.

LM35: ADC channel A0 is read using the AVcc reference, nominally 5.00 V.
The LM35 outputs 10 mV per degree Celsius. Conversion is ADC -> mV -> C.
Change LM35_ADC_REFERENCE_MV in Sensors.ino to your measured AVcc in millivolts
if it differs from 5000. Temperatures above 150 C are shown as ERR rather
than accepted as a valid LM35 reading. This does NOT correct wiring errors.
If the LCD previously showed 100+ C at room temperature, check LM35 pinout
for your exact package, common GND, A0 wiring, and actual AVcc voltage.
A disconnected/floating input or miswired LM35 can produce incorrect values.

DHT11 reading uses Timer1 and assumes a 16 MHz ATmega328P.
This is source-code updated for the requested features, not physically verified.

UART debugging: 9600 baud, 8N1, via Arduino USB Serial Monitor.
Open Serial Monitor at 9600 baud. The initial states and each debounced
button press/release are reported as Button 1/2: PRESSED or NOT PRESSED.
UART uses the ATmega328P hardware TX pin D1; do not connect it to other
peripherals while using USB Serial.
