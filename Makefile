build:
	platformio run -e nodemcu

upload:
	curl -F "image=@.pioenvs/nodemcu/firmware.bin" http://nl_iot_8-webupdate.local/update
serial:
	pio device monitor --port /dev/cu.wchusbserial1410 --baud 115200
