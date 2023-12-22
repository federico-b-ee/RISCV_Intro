* [ESP32-C3-DevKitM-1 - ESP32-C3 - — ESP-IDF Programming Guide latest documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/hw-reference/esp32c3/user-guide-devkitm-1.html)

# Micropython

## Installation

Install esptool.py:

```sh
python3 -m pip isntall esptool
```

Erase flash:

```sh
esptool.py --port /dev/ttyXXX erase_flash
```

Write Micropython firmware:

```sh
esptool.py --port /dev/ttyXXX write flash -z 0x0 XXXX.bin
```

Now Thonny, or any IDE can be used to interact with micropython REPL prompt.

## Simple Web Server

This is a simple web server which IP is printed by `print(wlan.ifconfig())`. 
The mcu detects and IRQ and appends it to a buffer, then the buffer is appended to the html. Time sync is also implemented, ntptime is used for this purpose.

```python
from time import sleep
import time
from machine import PWM, Pin
import utime

import socket

SSID = 'ssid'
PASS = 'pwd'

interruptionCount = 0
buff_int = []

def irq_callback(x):
    global interruptionCount
    global buff_int

    interruptionCount += 1
    
    t = utime.mktime(utime.localtime()) - 3*3600
    tm = utime.localtime(t)
    
    buff_int.append(f'<p><strong>ints: {interruptionCount} // New {tm[0]}/{tm[1]}/{tm[2]}@{tm[3]}:{tm[4]}:{tm[5]}</strong></p>')

def connect():
    import network
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        wlan.connect(SSID, PASS)
        while not wlan.isconnected():
            pass
    print(wlan.ifconfig())
    
def server():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind(('', 80))
    sock.listen(5)
    
    while True:
        client, addr = sock.accept()
        request = client.recv(1024)
        request = str(request)
        response = html()
        client.send('HTTPS/1.1 200 OK\n')
        client.send('Content-Type: text/html\n')
        client.send('Connection: close\n\n')
        client.sendall(response)
        client.close()

def html():
    s = "<h1>Interrupts</h1>"
    
    for x in buff_int:
        s += x
        
    html_str="""<html>
                 <head>
                     <title>ESP32</title>
                     <meta http-equiv="refresh" content="2">
                 </head>
                 <body>
                 """ + s + """
                 </body>
                 <style>html{text-align:center}</style>
                 </html>"""
    return html_str

def set_time():
    import ntptime
    ntptime.settime()
     
def main():
    connect()
    set_time()
    
    irq_pin = Pin(0, Pin.IN, Pin.PULL_UP)
    irq_pin.irq(handler=irq_callback, trigger=Pin.IRQ_FALLING)

    led = PWM(8, freq=5)
    led.duty_u16(32768)
    
    server()

if __name__ == "__main__":
    main()
```

## Resources

* [MicroPython - Python for microcontrollers](https://micropython.org/download/ESP32_GENERIC_C3/)
* [Quick reference for the ESP32 — MicroPython latest documentation](https://docs.micropython.org/en/latest/esp32/quickref.html#)


# Rust

`esp-rs` repo has all the info related to esp32+Rust projects.

## Instalation

From esp-rs repo:

```sh
cargo install cargo-generate
cargo install ldproxy
cargo install espup
cargo install espflash
```
```sh
apt-get install libuv-dev
```
```sh
espup install
. $HOME/export-esp.sh
```

Copy the template:

```sh
cargo generate esp-rs/esp-idf-template cargo
```
Build:

```sh
cd <project>
cargo build
```

Flash:

```sh
espflash flash target/riscv32imc-esp-espidf/debug/<project>
```

Monitor ( for println!() ):

```sh
espflash monitor
```

## PWM quick demo:

`main.rs`:

```rust
#[allow(unused_imports)]
use esp_idf_hal::{delay::FreeRtos, gpio::PinDriver, peripherals::Peripherals};
#[allow(unused_imports)]
use esp_idf_hal::ledc::{config::TimerConfig, LedcDriver, LedcTimerDriver, Resolution};
#[allow(unused_imports)]
use esp_idf_hal::adc;
#[allow(unused_imports)]
use esp_idf_hal::prelude::*;
use anyhow;


fn main() -> anyhow::Result<()>  {
    // It is necessary to call this function once. Otherwise some patches to the runtime
    // implemented by esp-idf-sys might not link properly. See https://github.com/esp-rs/esp-idf-template/issues/71
    esp_idf_svc::sys::link_patches();

    println!("Starting");

    let p = Peripherals::take()?;
    // PWM is set
    //let mut led = PinDriver::output(p.pins.gpio8).unwrap();

    let t_driver = LedcTimerDriver::new(p.ledc.timer0, &TimerConfig::new().frequency(24.kHz().into()))?;
    let mut pwm_driver = LedcDriver::new(p.ledc.channel0, t_driver, p.pins.gpio8)?;
    let max_duty = pwm_driver.get_max_duty();
    
    
    for n in (1..=100).cycle() {
        pwm_driver.set_duty(max_duty * n / 100)?;
        FreeRtos::delay_ms(50);
    };

    loop {
        // Never reaches this loop
        FreeRtos::delay_ms(1000);
    }
}
```

`Cargo.toml`:

```sh
#[...]
esp-idf-hal = "0.42"
anyhow = "1"
#[...]
```
Copy those lines into `Cargo.toml`, or inside the project folder:

```sh
cargo add esp-idf-hal
cargo add anyhow
```

## PWM + ADC

Using a trimmer from Bourns:

- 3V &rarr; pin1 of trimmer
- GPIO0(of esp32) &rarr; pin2 of trimmer
- GND &rarr; pin3 of trimmer

```rust
#[allow(unused_imports)]
use esp_idf_hal::{delay::FreeRtos, gpio::PinDriver, peripherals::Peripherals};
#[allow(unused_imports)]
use esp_idf_hal::ledc::{config::TimerConfig, LedcDriver, LedcTimerDriver, Resolution};
#[allow(unused_imports)]
use esp_idf_hal::adc::*;
use esp_idf_hal::adc::config::Config;
#[allow(unused_imports)]
use esp_idf_hal::prelude::*;
use anyhow;

fn main() -> anyhow::Result<()> {
    // It is necessary to call this function once. Otherwise some patches to the runtime
    // implemented by esp-idf-sys might not link properly. See https://github.com/esp-rs/esp-idf-template/issues/71
    esp_idf_svc::sys::link_patches();

    let p = Peripherals::take()?;

    let mut adc = AdcDriver::new(p.adc1, &Config::new().calibration(true))?;

    // att11DB -> ADC reads from 0-3.6V 
    let mut adc_pin: AdcChannelDriver<{ attenuation::DB_11 }, _> = AdcChannelDriver::new(p.pins.gpio0)?;

    let t_driver = LedcTimerDriver::new(p.ledc.timer0, &TimerConfig::new().frequency(200.into()))?;
    let mut pwm_driver = LedcDriver::new(p.ledc.channel0, t_driver, p.pins.gpio8)?;
    
    let mut read = adc.read(&mut adc_pin)?;
    loop {
        FreeRtos::delay_ms(500);
        read = adc.read(&mut adc_pin)?;
        pwm_driver.set_duty((read * 3).into())?;
        println!("ADC count: {read}");
    }
}
```

`espflash monitor` output when the trimmer is "rotated":

```sh
ADC count: 76
ADC count: 74
ADC count: 76
ADC count: 74
ADC count: 76
ADC count: 79
ADC count: 85
```

## Resources

* [esp-rs · GitHub](https://github.com/esp-rs)
* [GitHub - esp-rs/esp-idf-hal: embedded-hal implementation for Rust on ESP32 and ESP-IDF](https://github.com/esp-rs/esp-idf-hal)
* [GitHub - esp-rs/esp-idf-template: A "Hello, world!" template of a Rust binary crate for the ESP-IDF framework.](https://github.com/esp-rs/esp-idf-template)
* [esp-idf-hal/examples at master · esp-rs/esp-idf-hal · GitHub](https://github.com/esp-rs/esp-idf-hal/tree/master/examples)

### Tutorials
* [P3 - ADC with Rust on ESP32-C3 - YouTube](https://www.youtube.com/watch?v=07SVj6R_AhA)
* [Hutscape | Tutorials - Blinky with Rust on ESP32-C3](https://hutscape.com/tutorials/blinky-rust-esp32c3)

# Zephyr Project

## Instalation

Following Zephyr's docs: [Getting Started Guide — Zephyr Project Documentation](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)

To make it work with an specific board, a board dir has to be made.

The path used is:

```sh
~/zephyrproject/zephyr/boards/riscv
```
A simple blinky is already given in the examples folder, but if the boards used has the led mapped to another gpio or even no led it won't compile.

A workaround is to change the `esp32c3_luatos_core` dir, and more specifically, the `esp32c3_luatos_core.dtsi` file:

In `~/zephyrproject/zephyr/boards/riscv/esp32c3_luatos_core/esp32c3_luatos_core.dtsi`

```dtsi
	[...]
    aliases {
		sw0 = &user_button1;
		i2c-0 = &i2c0;
		watchdog0 = &wdt0;
		led0 = &led_d4;
		led1 = &led_d5;
	};
    [...]
	leds {
		compatible = "gpio-leds";

		led_d4: led_1 {
			label = "D4";
			gpios = <&gpio0 8 GPIO_ACTIVE_HIGH>;
		};
    [...]
```
led0 is being used by the blinky example. 

Now:

```sh
cd ~/zephyrproject/zephyr
west build -p always -b esp32c3_luatos_core samples/basic/blinky
```

And to automatically detect the board and flash it:

```sh
west flash
```

## Resources 

* [Getting Started Guide — Zephyr Project Documentation](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)
* [Supported Boards — Zephyr Project Documentation](https://docs.zephyrproject.org/latest/boards/index.html#boards)

# Inline Assembly

```c
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
void app_main() 
{
  int result;
  while(1)
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);  
    asm("csrr %0, 0x7E2" : "=r"(result) : );
    printf("0x%x\n", result);
  } 
} 
```

Reading MPCCR(Located at `0x7E2`) status register.

## Resources

*  [inline assembly - How to interact with RISC-V CSRs by using GCC C code? - Stack Overflow](https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code)
* [riscv-spec-v2.2.pdf_Page111](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)
* [esp32-c3_manual_Page29-MPCCR](https://www.espressif.com/sites/default/files/documentation/esp32-c3_technical_reference_manual_en.pdf)
* [ESP32-C3 RDCYCLE - ESP32 Forum](https://esp32.com/viewtopic.php?t=26295)
* [RISC-V Assembly Language Programming using ESP32-C3 and QEMU (+ FREE ESP32 RISC-V Board) | Elektor](https://www.elektor.com/risc-v-assembly-language-programming-using-esp32-c3-and-qemu)
* 
# espidf(C/C++) - PlatformIO - FreeRTOS

Using PlatformIO:

## FreeRTOS demo

```c
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO GPIO_NUM_8
#define GPIO GPIO_NUM_0
#define STACK_SIZE 4000

void task1(void *pvParams)
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    while (1)
    {
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void task2(void *pvParams)
{
    gpio_reset_pin(GPIO);
    gpio_set_direction(GPIO, GPIO_MODE_OUTPUT);
    while (1)
    {
        gpio_set_level(GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main() 
{
  xTaskCreatePinnedToCore(&task1, "LED", STACK_SIZE, NULL, 0, NULL, 1);
  xTaskCreatePinnedToCore(&task2, "GPIO", STACK_SIZE, NULL, 0, NULL, 0);
} 
```

If `STACK_SIZE` has a low value, it may not run. Each operation is run in a different core.

## Resources

* [xTaskCreatePinnedToCore doesn't work for Core 1 - ESP32 Forum](https://www.esp32.com/viewtopic.php?t=12121)

# Resources

* [Docs ESP32-C3](https://cdn-shop.adafruit.com/product-files/5405/ESP32-C3FN4-Espressif-Systems-datasheet-156944166.pdf)
* [ESP32-C3 SuperMini Board](https://es.aliexpress.com/item/1005005834887898.html?spm=a2g0o.productlist.main.99.22586f30OuAYf4&algo_pvid=e05ca647-1a86-4897-a997-07e7f5b24d22&algo_exp_id=e05ca647-1a86-4897-a997-07e7f5b24d22-49&pdp_npi=4%40dis%21USD%212.96%212.4%21%21%212.96%21%21%40210324c816977571880007280e4e69%2112000035725542252%21sea%21AR%210%21AB&curPageLogUid=komK4uE2clqj)

