from machine import Pin, Timer
import machine
from time import sleep, sleep_ms
import time

''' Use Case
led = Pin(13, Pin.OUT)
Blinky_Pin(period_ms=500, led=led)
'''
class Blinky_Pin(object):
    def __init__(self, period_ms, led):
        self.led = led
        self.tim = Timer(0)
        self.tim.init(period=period_ms, mode=Timer.PERIODIC, callback=self.cb)

    def cb(self, t):
        self.__toggle()

    def __toggle(self):
        self.led.off() if self.led.value() else self.led.on()

class Encoder(object):
    def __init__(self, dt, clk, sw, delay, enc_handler, sw_handler):
        
        self.dt = Pin(dt, Pin.IN)
        self.clk = Pin(clk, Pin.IN)
        self.sw = Pin(sw, Pin.IN)
        self.state = 0
        self.counter = 0
        self.delay = delay

        self.enc_handler = enc_handler
        self.sw_handler = sw_handler

        self.last_time_enc_irq = 0 
        self.last_time_sw_irq = 0 
        self.pos = 50
                                                                                                                                        
        self.dt.irq(handler=self.__enc_irq_handler, trigger=Pin.IRQ_FALLING)
        self.sw.irq(handler=self.__sw_irq_handler, trigger=Pin.IRQ_FALLING)

    def __enc_irq_handler(self, p):
        time_irq = time.ticks_ms()
  
        if (time_irq - self.last_time_enc_irq > 10):
            self.pos += 2 if self.clk.value() else -2
            self.pos = min(100, max(0, self.pos))
            self.last_time_enc_irq = time_irq
            self.counter += 1
            self.state = 1
        if self.counter >= self.delay:
            self.counter = 0
            self.enc_handler(self.pos)

    def __sw_irq_handler(self, p):
        time_irq = time.ticks_ms()
  
        if (time_irq - self.last_time_sw_irq > 200):
            self.state = 0 if self.state else 1
            self.sw_handler(self.state)
            self.last_time_sw_irq = time_irq
