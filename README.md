# DMP-PROJECT
# Push-Up Counter

An Arduino-based push-up counter that uses an OLED display, a button, and a proximity sensor (simulated using a potentiometer) to count push-ups.

1- Features
- **Push-Up Detection**:
  - Uses a proximity sensor to detect both the downward and upward motion of a push-up.
  - Smooths sensor readings to avoid noise.
- **Button Controls**:
  - **Single Press**: Start/Stop counting.
  - **Double Press**: Reset the push-up counter.
  - **Hold (2+ seconds)**: Displays a message to release the button to continue.
- **OLED Display**:
  - Displays the current push-up count and status messages.

2- Components
1. **Arduino Uno/Nano** 
2. **OLED Display** (SSD1306, I2C connection)
3. **Button** (for user interaction)
4. **Proximity Sensor** (simulated using a potentiometer)
5. **Breadboard and Wires**

3- Circuit Diagram
Connect the components as follows:
- **OLED Display**:
  - `VCC` → `5V`
  - `GND` → `GND`
  - `SCL` → `A5`
  - `SDA` → `A4`
- **Proximity Sensor (Potentiometer)**:
  - Middle pin → `A0`
  - Side pins → `5V` and `GND`
- **Button**:
  - One terminal → `D2`
  - Other terminal → `GND`

4- How It Works
1. When the device is powered on, the OLED displays "Push-Up Counter."
2. Use the button for the following controls:
   - **Single Press**: Toggles counting mode.
   - **Double Press**: Resets the push-up counter to 0.
   - **Hold for 2+ Seconds**: Displays a message asking you to release the button to continue.
3. Perform push-ups, and the counter will increase for every full downward and upward motion detected by the proximity sensor.

5- Code Overview
The Arduino sketch implements:
- **Push-Up Detection**: Monitors the proximity sensor and counts a push-up when the user moves up and down past predefined thresholds.
- **Button Handling**: Implements single, double, and long-press detection using timers.
- **OLED Updates**: Updates the OLED with push-up count and status messages.
