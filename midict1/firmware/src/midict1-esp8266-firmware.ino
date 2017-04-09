#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include "ESP8266WiFiGeneric.h"
#include "ESP8266WiFiSTA.h"

extern "C" {
  #include "ets_sys.h"
  #include "user_interface.h"
}

#include "AppleMidi.h"

#include "Bus.h"
#include "Knobs.h"

#include "secrets.h"

APPLEMIDI_CREATE_INSTANCE(WiFiUDP, AppleMIDI); // see definition in AppleMidi_Defs.h

bool isConnected = false;

void setup_wifi() {
  Serial.println("Getting IP address ...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(":");
  }
  Serial.println();
  Serial.print("IP address is ");
  Serial.println(WiFi.localIP());
}

void setup_midi() {
  // Create a session and wait for a remote host to connect to us
  AppleMIDI.begin("midict1");

  AppleMIDI.OnConnected(OnAppleMidiConnected);
  AppleMIDI.OnDisconnected(OnAppleMidiDisconnected);
}

void send_levels() {
  for (uint8_t i = 0; i < KNOBS_COUNT; i++) {
    bus.send_level(i, scanner.valueAt(i));
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing ...");
  Serial.println("-> Knobs ...");
  knobs.setup();
  Serial.println("-> Knobs scanner ...");
  scanner.setup();
  Serial.println("-> WIFI ...");
  setup_wifi();
  Serial.println("-> MIDI ...");
  setup_midi();
  Serial.println("Ready");
  send_levels();
}

void loop() {

  // WiFi.mode(WIFI_OFF);

  for (uint8_t i = 0; i < KNOBS_COUNT; i++) {
    uint16_t start = millis();
    // bool changed = scanner.valueChanged();
    // yield();
    // scanner.next();
    // if (changed) {
    //   uint8_t index = scanner.valueIndex();
    //   uint16_t value = scanner.value();
    //   yield();
    //   bus.send_level(index, value);
    //   yield();
    //   if (isConnected) {
    //     AppleMIDI.controlChange(7, value, 0);
    //   }
    // }

    if (isConnected) {
       AppleMIDI.controlChange(7, 64, 0);
     }

    yield();
    AppleMIDI.run();
    yield();

    while ((millis() - start) < 100) {
      delay(10);
      yield();
    }
  }

  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, pass);
  // while (WiFi.status() != WL_CONNECTED) delay(5);

  // WiFi.mode(WIFI_STA);
  // ETS_UART_INTR_DISABLE();
  // wifi_station_connect();
  // ETS_UART_INTR_ENABLE();
}

// ====================================================================================
// Event handlers for incoming MIDI messages
// ====================================================================================

// -----------------------------------------------------------------------------
// rtpMIDI session. Device connected
// -----------------------------------------------------------------------------
void OnAppleMidiConnected(uint32_t ssrc, char* name) {
  isConnected  = true;
  Serial.print("Connected to session ");
  Serial.println(name);
}

// -----------------------------------------------------------------------------
// rtpMIDI session. Device disconnected
// -----------------------------------------------------------------------------
void OnAppleMidiDisconnected(uint32_t ssrc) {
  isConnected  = false;
  Serial.println("Disconnected");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void OnAppleMidiNoteOn(byte channel, byte note, byte velocity) {
  Serial.print("Incoming NoteOn from channel:");
  Serial.print(channel);
  Serial.print(" note:");
  Serial.print(note);
  Serial.print(" velocity:");
  Serial.print(velocity);
  Serial.println();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void OnAppleMidiNoteOff(byte channel, byte note, byte velocity) {
  Serial.print("Incoming NoteOff from channel:");
  Serial.print(channel);
  Serial.print(" note:");
  Serial.print(note);
  Serial.print(" velocity:");
  Serial.print(velocity);
  Serial.println();
}
