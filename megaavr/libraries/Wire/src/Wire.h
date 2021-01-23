/*
  TwoWire.h - TWI/I2C library for Arduino & Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

#ifndef TwoWire_h
#define TwoWire_h

#include <Arduino.h>

#ifndef BUFFER_LENGTH
#if ((RAMEND - RAMSTART) < 1023)
  #define BUFFER_LENGTH 16
#elif ((RAMEND - RAMSTART) < 4095)
  #define BUFFER_LENGTH 32
#elif ((RAMEND - RAMSTART) < 8191)
  #define BUFFER_LENGTH 64
#else
  #define BUFFER_LENGTH 128
#endif
#endif

// WIRE_HAS_END means Wire has end()
#ifndef WIRE_HAS_END
#define WIRE_HAS_END 1
#endif
class TwoWire : public Stream
{
  private:
    static uint8_t rxBuffer[];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;

    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;

    static uint8_t transmitting;
    static void (*user_onRequest)(void);
    static void (*user_onReceive)(int);
    static uint8_t onRequestService(void);
    static void onReceiveService(int);
  public:
    TwoWire();
    bool pins(uint8_t sda_pin, uint8_t scl_pin);
    bool swap(uint8_t state = 1);
    void usePullups();
    void begin();
    void begin(uint8_t);
    void begin(int);
    void begin(uint8_t, bool, uint8_t);
    void begin(int, bool, uint8_t);
    void begin(uint8_t, bool);
    void begin(int, bool);
    void end();
    void setClock(uint32_t);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(void);
    uint8_t endTransmission(bool);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, size_t);
    uint8_t requestFrom(uint8_t, size_t, bool);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void onReceive(void (*)(int));
    void onRequest(void (*)(void));

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;
};

extern TwoWire Wire;

#endif
