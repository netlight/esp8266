# curl \
# -v \
# 'http://nl_iot_1-webupdate.local/update' \
# -H 'Origin: http://nl_iot_1-webupdate.local' \
# -H 'Content-Type: multipart/form-data;' \
# --data-binary "@WebUpdater_1.ino.nodemcu.bin" \
# --compressed

UPDATE_BIN=".pioenvs/nodemcu/firmware.bin"
DEV_ARR=( "nl_iot_8-webupdate" )

for DEV in "${DEV_ARR[@]}"
do
   :
	curl "http://${DEV}.local/update" \
	-v \
	-H 'Origin: http://nl_iot_1-webupdate.local' \
	-H 'Accept-Encoding: gzip, deflate' \
	-H 'Accept-Language: sv-SE,sv;q=0.9,en-US;q=0.8,en;q=0.7,nb;q=0.6' \
	-H 'Upgrade-Insecure-Requests: 1' \
	-H 'User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36' \
	-H 'Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryBoomShackaLack' \
	-H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8' \
	-H 'Cache-Control: max-age=0' \
	-H "Referer: http://${DEV}.local/update" \
	-H 'Connection: keep-alive' \
	--data-binary $'------WebKitFormBoundaryBoomShackaLack\r\nContent-Disposition: form-data; name="update"; filename="'${UPDATE_BIN}$'"\r\nContent-Type: application/macbinary\r\n\r\n\r\n------WebKitFormBoundaryBoomShackaLack--\r\n' \
	--compressed
done
