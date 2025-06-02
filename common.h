#ifndef COMMON_H_
#define COMMON_H_
#pragma once
#pragma message("*** common.h 2025-06-02 | +M5StickC Plus2 & EVT_STOP ***")

#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

#define ESPNOW_CHANNEL 1

/* ─────────────── Struktura pakietu ─────────────── */
typedef struct __attribute__((packed)) {
    uint8_t   id;            // DeviceID nadawcy
    uint8_t   typ_zdarzenia; // EventType
    uint32_t  info;          // np. millis(), ADC, itp.
    uint8_t   mac[6];        // opcjonalnie: MAC źródła
} struct_message;

/* ─────────────── ID urządzeń ─────────────── */
enum DeviceID : uint8_t {
    ID_LITE1          = 3,
    ID_LITE2          = 4,
    ID_LITE3          = 5,
    ID_LITE5          = 7,
    ID_LITE8          = 8,
    ID_STICK1         = 9,   // ← NOWY • M5StickC Plus2
    ID_LILYGO_CENTRAL = 99
};

/* ─────────────── Typy zdarzeń ─────────────── */
enum EventType : uint8_t {
    EVT_ZAPOWIEDZ_1   = 1,   // AUSSEN
    EVT_ZAPOWIEDZ_2   = 2,   // INNEN
    EVT_ZAPOWIEDZ_3   = 3,   // CRIT
    EVT_CZUWAJ        = 30,  // reset / uzbrój
    EVT_CICHO         = 31,  // reset / silent
    EVT_SERWIS        = 32,  // tryb serwisowy
    EVT_STOP          = 33,  // rozbrojenie („stop”)  ← NOWE
    EVT_STATUS_REQ    = 40,
    EVT_STATUS_RESP   = 41
};

/* ─────────────── MAC adresy ─────────────── */
static const uint8_t mac_lilygo_centrala[6] = { 0xCC, 0x7B, 0x5C, 0x31, 0x01, 0x00 };

static const uint8_t mac_lite1 [6] = { 0x90, 0x15, 0x06, 0xFA, 0x7E, 0x48 };
static const uint8_t mac_lite2 [6] = { 0xF0, 0x24, 0xF9, 0xBC, 0x58, 0x24 };
static const uint8_t mac_lite3 [6] = { 0xF0, 0x24, 0xF9, 0xBA, 0xDC, 0x10 };
static const uint8_t mac_lite5 [6] = { 0xF0, 0x24, 0xF9, 0xBB, 0x43, 0xB8 };
static const uint8_t mac_lite8 [6] = { 0xF0, 0x24, 0xF9, 0xBB, 0x4E, 0xD0 };
static const uint8_t mac_stick1[6] = { 0xF0, 0x24, 0xF9, 0x98, 0xAD, 0xA8 };  

extern uint8_t myMacAddress[6];        // w razie potrzeby odczyt runtime

/* ─────────────── Auto-identyfikacja ─────────────── */
#ifdef THIS_IS_LITE1
  #define MY_DEVICE_ID ID_LITE1
  #define MY_MAC       mac_lite1
#endif

#ifdef THIS_IS_LITE2
  #define MY_DEVICE_ID ID_LITE2
  #define MY_MAC       mac_lite2
#endif

#ifdef THIS_IS_LITE3
  #define MY_DEVICE_ID ID_LITE3
  #define MY_MAC       mac_lite3
#endif

#ifdef THIS_IS_LITE5
  #define MY_DEVICE_ID ID_LITE5
  #define MY_MAC       mac_lite5
#endif

#ifdef THIS_IS_LITE8
  #define MY_DEVICE_ID ID_LITE8   // pełni funkcję CRIT
  #define MY_MAC       mac_lite8
#endif

#ifdef THIS_IS_STICK1           // ← dodaj flagę w projekcie Sticka
  #define MY_DEVICE_ID ID_STICK1
  #define MY_MAC       mac_stick1
#endif

#ifdef THIS_IS_LILYGO_CENTRAL
  #define MY_DEVICE_ID ID_LILYGO_CENTRAL
  #define MY_MAC       mac_lilygo_centrala
  #define TINY_GSM_MODEM_SIM800
  #include <TinyGsmClient.h>
#endif

#endif  // COMMON_H_
