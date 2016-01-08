# arduino-yun-lockitron
Simple Arduino Yún door access application usin Lockitron

<img src="http://behuns.com/media/arduino-yun-lockitron/icon.png" alt="Lockitron Icon">

## Features
- Remotely open or closes a regular door lock.
- Shows the actual state using AJAX (and zepto.js)
- Simple and with a little bit of design.
- Lock protected through password but **IT IS NOT SECURE** (yet).

## Installation

Get the packacge
```
git clone https://github.com/devalfrz/arduino-yun-lockitron
```
Or simply download the package from github: <a href="https://github.com/devalfrz/arduino-yun-lockitron/archive/master.zip">https://github.com/devalfrz/arduino-yun-lockitron/archive/master.zip</a>.

Inside the "Lockitron" directory you can find the ```lockitron.ino``` arduino sketch. Load it to the Arduino. The password is hard-coded into the scketch so change it if you want to. The default password is "arduino".

For the next step you need to know the IP address of your Arduino Yún or use the default DNS arduino.local. Yoy can do this by following this guide: https://www.arduino.cc/en/Guide/ArduinoYun

Using a ftp file browser connect to your arduino and copy the contents of ```www``` inside of the ```/www``` directory. It should look like this: ```/www/lockitron```

Finally connect to your Arduino on a web page using the ip:
(In my case)
```
http://192.168.1.67/lockitron
```
Or use the DNS
```
http://arduino.local/lockitron
```
