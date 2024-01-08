import driver_wifi
import driver_mqtt
from machine import Pin
import time, machine

pwm_state = False
def ledstrip():
    pwm = machine.PWM(Pin(0), freq=1000, duty=1023)
        
    def irq_mqtt(topic, msg):
        global pwm_state
        if topic == driver_mqtt.MQTT_T_BRIGHTNESS:
            print("brightness")
            x = min(100,max(int(msg),0))
            if pwm_state:
                pwm.duty(int(x/100 * 1023))
            else:
                pwm.init(duty=int(x/100 * 1023), freq=1000)
        elif topic == driver_mqtt.MQTT_T_STATUS:
            if msg == b"0":
                pwm_state = False
                pwm.deinit()
            elif msg == b"1":
                pwm_state = True
                pwm.init(duty=0, freq=1000)

            
    ssid, password = driver_wifi.load_wifi_credentials()
    if ssid and password:
        driver_wifi.connect_to_wifi(ssid, password)
        mqtt = driver_mqtt.MQTT_client()
        mqtt.connect()
        mqtt.client.set_callback(irq_mqtt)
        mqtt.client.subscribe(driver_mqtt.MQTT_T_STATUS)
        mqtt.client.subscribe(driver_mqtt.MQTT_T_BRIGHTNESS)
        
        print("Connected to WiFi: SSID={}, Password={}".format(ssid, '*' * len(password)))

        
    
    while True:
        mqtt.client.check_msg()
        mqtt.client.ping()
        mqtt.client.check_msg()
        time.sleep_ms(50)
    
        
if __name__ == "__main__":
    while True:
        try:
            ledstrip()
        except OSError as e:
            machine.reset()