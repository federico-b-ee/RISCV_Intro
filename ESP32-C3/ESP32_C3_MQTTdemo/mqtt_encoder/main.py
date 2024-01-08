import driver_encoder
import driver_wifi
import driver_mqtt
from machine import Pin
import time, machine

def enc_handler(pos, mqtt, topic):
    mqtt.publish(topic, str(pos))

def main():
    # Check if WiFi credentials are already stored
    # Reads credentials from '*.json'
    ssid, password = driver_wifi.load_wifi_credentials()

    if ssid and password:
        sta = driver_wifi.connect_to_wifi(ssid, password)
        print("Connected to WiFi: SSID={}, Password={}".format(ssid, '*' * len(password)))
        
        mqtt = driver_mqtt.MQTT_client(user="testing2", client_id="encoder")
        mqtt.connect()
        encoder = driver_encoder.Encoder(dt=3, clk=2, sw=4, delay=2, enc_handler=lambda p: enc_handler(p, mqtt, driver_mqtt.MQTT_T_BRIGHTNESS), sw_handler=lambda s: enc_handler(s, mqtt, driver_mqtt.MQTT_T_STATUS))
        
        print(f"Connected to WiFi:{sta.isconnected()}")
        while True:
            mqtt.client.ping()
            mqtt.client.check_msg()
            if not sta.isconnected():
                print(f"Connected to WiFi:{sta.isconnected()}")
            time.sleep(1)
    else:
        # ap.config(essid='ESP32_Hotspot', password='password')
        driver_wifi.create_hotspot()
        driver_wifi.configure_webpage()

if __name__ == "__main__":
    while True:
        try:
            main()
        except OSError as e:
            machine.reset()
