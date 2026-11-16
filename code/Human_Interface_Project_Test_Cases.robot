*** Settings ***
Documentation     Arduino HMI project test plan (manual hardware verification).
...               Covers Arduino UNO / ATmega328P, LM35, DHT11, LDR, LCD,
...               two push buttons, upper/lower limits, LED, and UART.
...               Code excerpts are illustrative examples from the prior discussion,
...               NOT verified extracts from the final source files.
...               Each case is skipped until its hardware behavior is checked.

*** Test Cases ***
TC01 System Startup
    [Documentation]    Scenario: Power on Arduino.
    ...    Expected: LCD shows "System Starting" for about 1 second.
    ...    File: Arduino_HMI_Modular_final.ino
    ...    Code: LCD_Init(); ADC_Init(); Sensors_Init(); LED_Init(); UART_Init(); Buttons_Init();
    ...    Code: LCD_Clear(); LCD_String("System Starting"); _delay_ms(1000);
    Skip    Manual hardware test: verify startup message.

TC02 Normal Temperature Reading
    [Documentation]    Scenario: LM35 at A0 measures ambient temperature.
    ...    Expected: LCD shows a valid temperature with C unit.
    ...    Files: ADC.ino, Sensors.ino, Arduino_HMI_Modular_final.ino
    ...    Code: Sensors_UpdateAnalog();
    ...    Code: LCD_Number(readings[sensor]); LCD_Char('C');
    Skip    Manual hardware test: compare displayed temperature with reference.

TC03 Normal Humidity Reading
    [Documentation]    Scenario: DHT11 on D3 reads humidity.
    ...    Expected: LCD displays humidity with % unit.
    ...    Files: DHT11.ino, Sensors.ino, Arduino_HMI_Modular_final.ino
    ...    Code: Sensors_UpdateHumidity();
    ...    Code: LCD_Number(readings[sensor]); LCD_Char('%');
    Skip    Manual hardware test: verify valid humidity reading.

TC04 LDR Responds To Light
    [Documentation]    Scenario: Cover and uncover LDR at A1.
    ...    Expected: Displayed light reading changes.
    ...    Files: ADC.ino, Sensors.ino
    ...    Code: Sensors_UpdateAnalog();
    Skip    Manual hardware test: compare light and dark readings.

TC05 Automatic Sensor Switching
    [Documentation]    Scenario: Wait while system operates normally.
    ...    Expected: LCD cycles temperature, humidity, LDR about every 3 seconds.
    ...    File: Arduino_HMI_Modular_final.ino
    ...    Code: if (elapsed_ms >= 3000) { elapsed_ms = 0; current_sensor++;
    ...    Code: if (current_sensor >= 3) { current_sensor = 0; } }
    Skip    Manual hardware test: time the display cycle.

TC06 Reading Within Limits
    [Documentation]    Scenario: Sensor reading is between LL and LH.
    ...    Expected: LCD shows OK and warning LED is OFF.
    ...    Files: Sensors.ino, LED.ino, Arduino_HMI_Modular_final.ino
    ...    Code: if (Sensors_Alarm(sensor)) { LCD_String("NOK"); }
    ...    Code: else { LCD_String("OK"); }
    Skip    Manual hardware test: verify OK and LED OFF.

TC07 Reading Above Upper Limit
    [Documentation]    Scenario: Reading becomes greater than LH.
    ...    Expected: LCD shows NOK and warning LED turns ON.
    ...    Files: Sensors.ino, LED.ino
    ...    Code: readings[sensor] > high_limit[sensor]
    ...    Code: LED_Update();
    Skip    Manual hardware test: exceed LH and verify warning.

TC08 Reading Below Lower Limit
    [Documentation]    Scenario: Reading becomes less than LL.
    ...    Expected: LCD shows NOK and warning LED turns ON.
    ...    Files: Sensors.ino, LED.ino
    ...    Code: readings[sensor] < low_limit[sensor]
    ...    Code: LED_Update();
    Skip    Manual hardware test: fall below LL and verify warning.

TC09 Invalid Sensor Reading
    [Documentation]    Scenario: Sensor reading is invalid or unavailable.
    ...    Expected: LCD shows ERR; behavior of LED should match final implementation.
    ...    Files: Sensors.ino, Arduino_HMI_Modular_final.ino
    ...    Code: if (!valid[sensor]) { LCD_String("ERR"); }
    Skip    Manual hardware test: simulate or disconnect sensor safely.

TC10 Button 1 Increases Selected Limit
    [Documentation]    Scenario: Press D8 button once.
    ...    Expected: Selected LH or LL increases by one if within allowed range.
    ...    File: Buttons.ino
    ...    Code: if (current1) { high_limit[selected_sensor]++; }
    ...    Note: Illustrative only; final implementation must check selected_limit and bounds.
    Skip    Manual hardware test: verify increase.

TC11 Button 2 Decreases Selected Limit
    [Documentation]    Scenario: Press D9 button once.
    ...    Expected: Selected LH or LL decreases by one if within allowed range.
    ...    File: Buttons.ino
    ...    Code: if (current2) { high_limit[selected_sensor]--; }
    ...    Note: Illustrative only; final implementation must check selected_limit and bounds.
    Skip    Manual hardware test: verify decrease.

TC12 Both Buttons Switch Limit Selection
    [Documentation]    Scenario: Press D8 and D9 together.
    ...    Expected: Selection toggles LH to LL, then LL to LH on next simultaneous press.
    ...    File: Buttons.ino
    ...    Code: if (current1 && current2) {
    ...    Code: if (selected_limit == 0) { selected_limit = 1; }
    ...    Code: else { selected_limit = 0; } }
    Skip    Manual hardware test: verify toggle and release between presses.

TC13 Upper Limit Maximum Boundary
    [Documentation]    Scenario: Attempt to increase LH beyond 1023.
    ...    Expected: LH does not exceed 1023.
    ...    File: Buttons.ino
    ...    Code: if (high_limit[selected_sensor] < 1023) { high_limit[selected_sensor]++; }
    Skip    Manual hardware test: check upper boundary.

TC14 Lower Limit Minimum Boundary
    [Documentation]    Scenario: Attempt to decrease LL below zero.
    ...    Expected: LL remains at zero.
    ...    File: Buttons.ino
    ...    Code: if (low_limit[selected_sensor] > 0) { low_limit[selected_sensor]--; }
    Skip    Manual hardware test: check lower boundary.

TC15 Prevent Limit Crossing
    [Documentation]    Scenario: Attempt to decrease LH too close to LL or increase LL too close to LH.
    ...    Expected: Limits maintain the separation required by the implemented checks.
    ...    File: Buttons.ino
    ...    Code: if (high_limit[selected_sensor] > low_limit[selected_sensor] + 1)
    ...    Code: { high_limit[selected_sensor]--; }
    ...    Code: if (low_limit[selected_sensor] + 1 < high_limit[selected_sensor])
    ...    Code: { low_limit[selected_sensor]++; }
    Skip    Manual hardware test: verify boundary behavior.

TC16 Button Held Down
    [Documentation]    Scenario: Hold one button continuously.
    ...    Expected: One adjustment per press, not continuous changes, if edge detection is active.
    ...    File: Buttons.ino
    ...    Code: if ((current1 || current2) && !button1 && !button2) { _delay_ms(50); }
    ...    Note: State tracking is also needed for this behavior.
    Skip    Manual hardware test: verify one change per hold.

TC17 Limits Are Sensor Specific
    [Documentation]    Scenario: Adjust limits on one sensor, then switch to another sensor.
    ...    Expected: Other sensor limits remain unchanged.
    ...    Files: Buttons.ino, Sensors.ino
    ...    Code: low_limit[selected_sensor]++;
    ...    Code: high_limit[selected_sensor]++;
    ...    Note: Examples show indexed storage, not unconditional simultaneous updates.
    Skip    Manual hardware test: compare limits across sensors.

TC18 UART Button Press And Release Messages
    [Documentation]    Scenario: Open Serial Monitor at 9600 baud, press and release D8 and D9 individually.
    ...    Expected: Button 1: PRESSED, Button 1: NOT PRESSED, Button 2: PRESSED, and Button 2: NOT PRESSED appear on their respective state transitions.
    ...    Files: UART.ino, Buttons.ino
    ...    Code: if (current1 && !button1) { UART_String("Button 1: PRESSED\\r\\n"); }
    ...    Code: else if (!current1 && button1) { UART_String("Button 1: NOT PRESSED\\r\\n"); }
    ...    Code: if (current2 && !button2) { UART_String("Button 2: PRESSED\\r\\n"); }
    ...    Code: else if (!current2 && button2) { UART_String("Button 2: NOT PRESSED\\r\\n"); }
    ...    Note: UART messages report button states, not LH/LL adjustments.
    Skip    Manual hardware test: verify press and release messages at 9600 baud.

TC19 Warning Clears After Return To Normal
    [Documentation]    Scenario: Bring an out-of-range sensor reading back within limits.
    ...    Expected: LCD returns to OK and LED switches OFF.
    ...    Files: Sensors.ino, LED.ino, Arduino_HMI_Modular_final.ino
    ...    Code: if (Sensors_Alarm(sensor)) { LCD_String("NOK"); }
    ...    Code: else { LCD_String("OK"); }
    ...    Code: LED_Update();
    Skip    Manual hardware test: verify alarm recovery.

TC20 LCD Displays LL And LH
    [Documentation]    Scenario: View each sensor on LCD.
    ...    Expected: Second LCD line displays current LL and LH values.
    ...    File: Arduino_HMI_Modular_final.ino
    ...    Code: LCD_ClearLine(1); LCD_String("LL:"); LCD_Number(low_limit[sensor]);
    ...    Code: LCD_Position(1, 9); LCD_String("LH:"); LCD_Number(high_limit[sensor]);
    Skip    Manual hardware test: verify both values and updates.
