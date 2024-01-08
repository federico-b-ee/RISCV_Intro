from umqtt.simple import MQTTClient
import ujson


MQTT_CRED_FILE = "mqtt_config.json"

def load_mqtt_credentials():
    try:
        with open(MQTT_CRED_FILE, 'r') as f:
            config = ujson.load(f)
            return config['pwd'], config['server']
    except (OSError, ValueError, KeyError):
        return None, None
    
# MQTT Server Parameters
MQTT_CLIENT_ID = "esp32"
MQTT_USER      = "testing"
(MQTT_PASSWORD, MQTT_SERVER)  = load_mqtt_credentials()
MQTT_T_STATUS  = b"ledstrip/status"
MQTT_T_BRIGHTNESS  = b"ledstrip/brightness"
MQTT_PORT      = 8883

class MQTT_client(object):
    def __init__(self,
             client_id=MQTT_CLIENT_ID,
             server=MQTT_SERVER,
             user=MQTT_USER,
             password=MQTT_PASSWORD,
             port=MQTT_PORT,
             ssl=True,
             ssl_params={'server_hostname': MQTT_SERVER},
             keepalive=50):
        
        self.client_id = client_id
        self.server = server
        self.user = user
        self.password = password
        self.port = port
        self.ssl = ssl
        self.ssl_params = ssl_params
        self.keepalive = keepalive
        self.client =  MQTTClient(
                                client_id = self.client_id,
                                server = self.server,
                                user = self.user,
                                password = self.password,
                                port = self.port,
                                ssl = self.ssl,
                                ssl_params = self.ssl_params,
                                keepalive = self.keepalive
                                )
    def connect(self):
        self.client.connect()
    def publish(self, topic, string):
        self.client.publish(topic, string)