# Modbus_TCP_Client
This repository contains a Modbus TCP Client control panel built with Node-RED, designed for experimenting, debugging, and learning Modbus communication.
The flow provides an interactive dashboard capable of reading and writing Modbus Coils, Discrete Inputs, Holding Registers, and Input Registers.
It is ideal for testing devices, lab experiments, automation demos, and industrial prototyping.

A dedicated Modbus TCP server for Arduino Opta is also available and was used to test the dashboard, making this project a complete Modbus testing environment (client + embedded server).

🚀 **Features**

🔧 **Dynamic Modbus Server Configuration**
- Dashboard text input to set the Modbus TCP server IP.
- A Function node generates the configuration object:
  - tcpHost
  - tcpPort
  - unitId
- A modbus-flex-connector applies the configuration without restarting the flow.

🟢 **Coil Write**
- A dashboard ui_switch toggles Coil 0.
- Uses a modbus-write node to send boolean values.

🔴 **Coil Read**
- Periodic read (every 1 second) using modbus-read.
- Extracts payload[0] and displays it via a colored LED indicator.

🟡 **Discrete Input Read**
- Reads a discrete input from address 0.
- Displays the state in real time through a LED widget.

🔵 **Holding Register Write**
- Dashboard numeric input (0–100).
- Writes the value to Holding Register 20.

🔵 **Holding Register Read**
- Reads the same Holding Register every second.
- Real-time gauge visualization on the dashboard.

🟣 **Input Register Read**
- Reads Input Register 30.
- Shows the value on a dashboard gauge.

🧪 **Optional Modbus Server Simulator**
The flow includes a disabled Modbus Server node that can act as a local simulator for testing without physical hardware.

🔌 **Arduino Opta as Modbus TCP Server**

<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/84615eb3-92fb-47d5-af66-aca46672a5a7" />

This dashboard can be tested using a custom Modbus TCP server implementation running on Arduino Opta.
The Opta exposes coils and registers mapped exactly for this client flow, allowing you to:
- simulate real industrial I/O,
- test Modbus reads/writes end-to-end,
- validate timing and communication reliability,
- use Opta as an embedded PLC-class Modbus server.

This makes the project a complete setup:
Node-RED Modbus Client ↔ Arduino Opta Modbus Server

🖥️ **Dashboard Layout**

The UI is organized into the following groups:
- Coil Test
- Discrete Input Test
- Holding Register Test
- Input Register Test
- Configuration

<img width="1418" height="660" alt="image" src="https://github.com/user-attachments/assets/d59b9648-56d4-4576-b0df-aed6f2dea267" />

Each group provides intuitive controls such as switches, numeric inputs, LED indicators, and gauges.

▶️ **How to Use**

1. Import Modbus_TCP_Client_Panel.json into Node-RED.
2. Open the dashboard (typically at http://localhost:1880/ui).
3. Set the Modbus TCP server IP from the Configuration panel.
4. Interact with coils and registers using the provided switches, indicators, and gauges.

🤝 Contributing

Contributions, improvements and feature extensions are welcome!
Feel free to open issues or submit pull requests.
