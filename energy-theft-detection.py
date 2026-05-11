‘import time
import machine
import network
import urequests
import math

WIFI_SSID     = " "
WIFI_PASSWORD = " "

API_KEY = " "
THINGSPEAK_URL = " "

FIELD_CURRENT = 1
FIELD_STATUS  = 2

SAMPLES     = 800
SENSITIVITY = 0.185

adc    = machine.ADC(machine.Pin(26))
green  = machine.Pin(15, machine.Pin.OUT)
red    = machine.Pin(16, machine.Pin.OUT)
buzzer = machine.Pin(17, machine.Pin.OUT)

green.off()
red.off()
buzzer.value(1)

def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(WIFI_SSID, WIFI_PASSWORD)
    print("Connecting WiFi", end="")
    for _ in range(20):
        if wlan.isconnected():
            print("\nConnected:", wlan.ifconfig()[0])
            return True
        print(".", end="")
        time.sleep(1)
    print("\nWiFi FAILED")
    return False

def send_to_cloud(amps, status_code):
    try:
        url = "{}?api_key={}&field{}={}&field{}={}".format(
            THINGSPEAK_URL,
            API_KEY,
            FIELD_CURRENT,
            round(amps, 3),
            FIELD_STATUS,
            status_code
        )
        r = urequests.get(url)
        print("Upload:", r.text)
        r.close()
    except Exception as e:
        print("Upload error:", e)

def read_current_rms(zero_point):
    sum_sq = 0
    for _ in range(SAMPLES):
        raw = adc.read_u16()
        voltage = (raw / 65535) * 3.3
        current = (voltage - zero_point) / SENSITIVITY
        sum_sq += current * current
        time.sleep_us(50)
    return math.sqrt(sum_sq / SAMPLES)

def buzzer_off():
    buzzer.value(1)

def buzzer_beep(n):
    for _ in range(n):
        buzzer.value(0); time.sleep(0.15)
        buzzer.value(1); time.sleep(0.15)

def set_normal():
    green.on(); red.off(); buzzer_off()

def set_warning():
    green.off(); red.on(); buzzer_beep(1)

def set_theft():
    green.off(); red.on(); buzzer_beep(3)

def main():
    print("ThingSpeak System Start")

    for _ in range(3):
        green.on(); red.on(); buzzer.value(0)
        time.sleep(0.2)
        green.off(); red.off(); buzzer.value(1)
        time.sleep(0.2)

    connected = connect_wifi()

    print("Remove load...")
    time.sleep(5)

    zero_sum = 0
    for _ in range(SAMPLES):
        zero_sum += adc.read_u16()
        time.sleep_us(50)
    ZERO_POINT = (zero_sum / SAMPLES) * 3.3 / 65535

    print("Zero:", ZERO_POINT)

    print("Connect load...")
    time.sleep(5)

    baseline_vals = []
    for i in range(5):
        val = read_current_rms(ZERO_POINT)
        baseline_vals.append(val)
        print("Sample", i+1, ":", val)
        time.sleep(1)

    BASELINE = sum(baseline_vals) / len(baseline_vals)

    THRESH_WARNING = BASELINE + max(BASELINE * 0.4, 0.05)
    THRESH_THEFT   = BASELINE + max(BASELINE * 1.0, 0.10)

    print("Monitoring...")

    stable_count = 0
    last_status = -1
    consecutive_warn = 0
    last_upload = time.time()

    while True:
        amps = read_current_rms(ZERO_POINT)

        if amps <= THRESH_WARNING:
            status_code = 0
        elif amps <= THRESH_THEFT:
            status_code = 1
        else:
            status_code = 2

        labels = ["NORMAL", "WARNING", "THEFT"]
        print("Current:", round(amps,3), "|", labels[status_code])

        if status_code == last_status:
            stable_count += 1
        else:
            stable_count = 0
            last_status = status_code

        if stable_count >= 2:
            if status_code == 0:
                set_normal()
                consecutive_warn = 0
            elif status_code == 1:
                set_warning()
                consecutive_warn += 1
                if consecutive_warn >= 3:
                    set_theft()
            else:
                set_theft()
                consecutive_warn = 0

            if connected and (time.time() - last_upload) >= 3:
                send_to_cloud(amps, status_code)
                last_upload = time.time()

        time.sleep(1)

main()