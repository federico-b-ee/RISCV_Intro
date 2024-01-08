import network
import ujson
import usocket as socket
import utime

WIFI_CRED_FILE = "wifi_config.json"

def create_hotspot():
    ap = network.WLAN(network.AP_IF)
    ap.active(True)
    ap.config(essid='ESP32_Hotspot', password='password')

def configure_webpage():
    html_content = """<!DOCTYPE html>
                    <html lang="en">
                    <head>
                        <meta charset="UTF-8">
                        <meta name="viewport" content="width=device-width, initial-scale=1.0">
                        <title>WiFi Configuration</title>
                        <style>
                            body {
                                font-family: Arial, sans-serif;
                                margin: 20px;
                            }
                            label {
                                display: block;
                                margin-bottom: 10px;
                            }
                            input {
                                width: 100%;
                                padding: 5px;
                                margin-bottom: 10px;
                            }
                            button {
                                padding: 10px;
                                background-color: #4CAF50;
                                color: white;
                                border: none;
                                border-radius: 4px;
                                cursor: pointer;
                            }
                        </style>
                    </head>
                    <body>
                        <h2>WiFi Configuration</h2>
                        <form action="/submitted" method="post">
                            <label for="ssid">WiFi SSID:</label>
                            <input type="text" id="ssid" name="ssid" required>
                            
                            <label for="password">WiFi Password:</label>
                            <input type="password" id="password" name="password" required>

                            <button type="submit">Submit</button>
                        </form>
                    </body>
                    </html>
                    """
    html_another = """<!DOCTYPE html>
                    <html lang="en">
                    <head>
                        <meta charset="UTF-8">
                        <meta name="viewport" content="width=device-width, initial-scale=1.0">
                        <title>WiFi Configuration</title>
                        <style>
                            body {
                                font-family: Arial, sans-serif;
                                margin: 20px;
                            }
                            label {
                                display: block;
                                margin-bottom: 10px;
                            }
                            input {
                                width: 100%;
                                padding: 5px;
                                margin-bottom: 10px;
                            }
                            button {
                                padding: 10px;
                                background-color: #4CAF50;
                                color: white;
                                border: none;
                                border-radius: 4px;
                                cursor: pointer;
                            }
                        </style>
                    </head>
                    <body>
                        <h2>Done!</h2>
                        <form action="/" method="post">
                            <button type="submit">Resubmit</button>
                        </form>
                    </body>
                    </html>
                    """

    # Set up server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('0.0.0.0', 80))
    server_socket.listen(1)

    print("Webpage server started. Open a web browser and navigate to http://esp32_ip_address/")

    # Serve the configuration webpage
    while True:
        conn, addr = server_socket.accept()
        request = conn.recv(1024)
        if request:
            request_str = request.decode('utf-8')
            print("Received request:")
            print(request_str)
            request_lines = request_str.split('\r\n')
            
            for line in request_lines:
                if line[0:4] == "ssid":
                    credentials = line.split('&')
                    ssid = credentials[0].split('=')[1]
                    
                    # This is an extra space at the end
                    if ssid[-1] == '+':
                        ssid = ssid[:-1]
                        
                    ssid = ssid.replace("+", " ")
                        
                    pwd = credentials[1].split('=')[1]
                    save_wifi_credentials(ssid, pwd)
                    print(f"///// SAVED")
                
            if (request_lines[0].split('H')[0] == "POST / ") or (request_lines[0].split('H')[0] == "GET / "):
                conn.send("HTTP/1.1 200 OK\r\n\r\n{}".format(html_content).encode('utf-8'))
            elif (request_lines[0].split('H')[0] == "POST /submitted ") or (request_lines[0].split('H')[0] == "GET /submitted "):
                conn.send("HTTP/1.1 200 OK\r\n\r\n{}".format(html_another).encode('utf-8'))
        conn.close()

def save_wifi_credentials(ssid, password):
    config = {
        "ssid": ssid,
        "password": password
    }
    with open(WIFI_CRED_FILE, 'w') as f:
        ujson.dump(config, f)

def load_wifi_credentials():
    try:
        with open(WIFI_CRED_FILE, 'r') as f:
            config = ujson.load(f)
            return config['ssid'], config['password']
    except (OSError, ValueError, KeyError):
        return None, None

def connect_to_wifi(ssid, password):
    sta = network.WLAN(network.STA_IF)
    sta.active(True)
    if not sta.isconnected():
        sta.connect(ssid, password)
        while not sta.isconnected():
            pass
    return sta
