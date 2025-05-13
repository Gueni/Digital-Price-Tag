import asyncio
from bleak import BleClient, BleakScanner
import paho.mqtt.client as mqtt

DEVICE_NAME = "PRICE_TAG"
PRICE_CHAR_UUID = "00002a56-0000-1000-8000-00805f9b34fb"

price_tag = None

def on_message(client, userdata, msg):
    payload = msg.payload.decode()
    print(f"MQTT Received: {payload}")
    asyncio.run(write_price(payload))

async def write_price(price):
    global price_tag
    if price_tag is None:
        devices = await BleakScanner.discover()
        for d in devices:
            if DEVICE_NAME in d.name:
                price_tag = d
                break
    if price_tag:
        async with BleClient(price_tag.address) as client:
            await client.write_gatt_char(PRICE_CHAR_UUID, bytes(price, 'utf-8'))

mqtt_client = mqtt.Client()
mqtt_client.on_message = on_message
mqtt_client.connect("localhost", 1883)
mqtt_client.subscribe("shelf/price")
mqtt_client.loop_forever()
