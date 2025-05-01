# UART-Based-Temperature-Monitoring-System-Using-LPC2129
📘 Project Overview
This project implements a temperature monitoring system using an LPC2129 (ARM7) microcontroller, an LM34 analog temperature sensor, and UART communication to display temperature data in real-time.

The system includes:
LM34 Temperature Sensor (analog voltage output)
LPC2129 Microcontroller (ADC + UART)
UART Terminal (Proteus or RealTerm) to display output


✅ Features (Explained Point-by-Point)
Temperature Acquisition via ADC
LM34 outputs voltage proportional to temperature (10mV/°F).
LPC2129 reads this analog signal via ADC channel 0 (P0.27).
ADC resolution is 10-bit (0–1023).
Conversion to °C and °F
ADC value is converted to voltage.

Voltage is mapped to °C:
Temp (°C) = (ADC * 3.3 / 1023.0) * 100

UART Communication
UART0 at 9600 baud rate is used.
Outputs temperature data every 500ms to a serial terminal.
Min and Max Temperature Tracking

Continuously stores and updates:
Current temperature
Minimum recorded temperature
Maximum recorded temperature
Overheat Warning
If temperature > 40°C, sends:
WARNING: High Temperature!
Command Interface via UART
Users can send RESET via UART to reset min/max values.
Delay Function
Custom delay used (based on loop counters).
Fault Tolerance
If ADC reading is unusually low or high, system can be extended to detect a disconnected sensor.

🛠️ How It Works
Module	Description
main.c	Contains system logic, ADC reads, UART display, and command parser.
uart.c	Handles initialization, sending, receiving characters and strings over UART.
uart.h	UART function declarations.
adc_init()	Sets up ADC channel and power settings.
read_adc()	Triggers and retrieves ADC conversion result.

🖼️ Simulation & Diagrams
✅ Full Proteus schematic (.pdsprj) provided.
✅ Block Diagram (.png and .docx) for documentation.
✅ UART output seen on Virtual Terminal.

🚀 Requirements
Microcontroller: LPC2129 (ARM7)
Sensor: LM34
Software:Keil µVision (for compiling)
Proteus 8 (for simulation)
RealTerm/TeraTerm (for UART debugging - optional)

🔁 Future Extensions
Set temperature thresholds via command (e.g., SET 45)
LCD integration for local display
EEPROM/SD card logging
PC plotting via Python serial communication

📣 Message for Recruiters
I’m an Embedded Systems Engineer with practical experience in microcontroller-based applications. This project shows my ability to interface analog sensors, implement serial communication protocols, and structure embedded code efficiently. I’m currently looking for roles in Embedded Firmware Development or IoT Firmware Engineering.

🏷️ Tags
#EmbeddedSystems #LPC2129 #ARM7 #UART #ADC #LM34 #TemperatureSensor
#CProgramming #MicrocontrollerProjects #Proteus #RealTimeSystems
#Keil #UARTCommunication


