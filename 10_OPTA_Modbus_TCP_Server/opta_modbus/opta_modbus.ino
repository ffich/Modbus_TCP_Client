#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>

// Define the IP address for the Modbus TCP server
IPAddress ip(192, 168, 0, 2);

// Server will listen on Modbus TCP standard port 502
EthernetServer ethServer(502); 

// Create a Modbus TCP server instance
ModbusTCPServer modbusTCPServer;


void setup() {
  // Initialize serial communication at 9600 bauds,
  // wait for the serial port to connect,
  // initialize Ethernet connection with the specified IP address
  Serial.begin(9600);
  while (!Serial);
  Ethernet.begin(NULL, ip); 

  Serial.print("IP Opta: ");
  Serial.println(Ethernet.localIP());

  // Check Ethernet hardware and cable connections
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("- Ethernet interface not found!");
    while (true);
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("- Ethernet cable not connected!");
  }

  // Start the Modbus TCP server
  ethServer.begin();
  if (!modbusTCPServer.begin()) {
    Serial.println("- Failed to start Modbus TCP Server!");
    while (1);
  }

  // Configure the LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  // Configure the USER_BTN as an input
  pinMode(BTN_USER, INPUT);

  // Configure memory layout
  modbusTCPServer.configureCoils(0, 1);
  modbusTCPServer.configureDiscreteInputs(10, 1);
  modbusTCPServer.configureHoldingRegisters(20, 1);
  modbusTCPServer.configureInputRegisters(30, 1);
}

void loop() {
  // Handle incoming client connections and process Modbus requests
  EthernetClient client = ethServer.available();
  if (client) {
    Serial.println("Client connected!");

    // Accept and handle the client connection for Modbus communication
    modbusTCPServer.accept(client);

    // Main Communication Cycle
    while (client.connected()) {
      // Process Modbus requests
      modbusTCPServer.poll(); 

      // Handle specific Modbus Requests
      UpdateCoils();
      UpdateDiscreteInputs();
      UpdateHoldingRegisters();
      UpdateInputRegisters();
    }
  }
}

void UpdateCoils (void)
{
  // Read the current value of the coil at address 0x00
  int value = modbusTCPServer.coilRead(0);

  // Set the LED state; HIGH if coil value is 1, LOW if coil value is 0
  digitalWrite(LED_BUILTIN, value ? HIGH : LOW);

  // Write to the bus
  modbusTCPServer.coilWrite(0, value);
}

void UpdateDiscreteInputs (void)
{
  int value = 0;

  // Read the discrete input value
  value = digitalRead(BTN_USER);

  // Write to the bus
  modbusTCPServer.discreteInputWrite(10, value);
}

void UpdateHoldingRegisters (void)
{
  // Read the current value of the register at address 30
  int value = modbusTCPServer.holdingRegisterRead(20);

  // Write to the bus
  modbusTCPServer.holdingRegisterWrite(20, value);  
}

void UpdateInputRegisters (void)
{
  int value = random(0, 21);

  // Write to the bus
  modbusTCPServer.inputRegisterWrite(30, value);
}
