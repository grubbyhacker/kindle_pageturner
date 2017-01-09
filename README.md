# kindle_pageturner
This is the code I used to implement a remote control "page-turner" for my Kindle-4. I love to read on e-ink - but I hate the shape, size and controls of my Kindle. My dream was to be able to read my kindle without holding it, with pageturning done from a handheld device. I implemented this using an esp8266 microcontroller mounted inside of an old two-button flight stick. When I squeeze the trigger the esp8266 sends a "forward" command - pressing the "hat" button sends a "back" command. The kindle receives these commands with a little UDP server.

# Acknowledgements
TBD - I read somebody else's project that did something very similar that inspired me. Need to find a link - its been over a year.

# On the Kindle
## Get out of jail
First of all you have to jailbreak your kindle. You can read all about how to do that [here](). I'm sure this voids your warranty and that there are lots of ways to brick you device. So you have been warned and I'm not responsible for what happens to you or your property.
## Install Python
Second you need to install a version of python that can run on your Kindle. I chose to use python to implement the UDP server because it was the fastest way to develop one for me. [Here]() is the link that I used.
## ssh
If you configure an ssh service debugging and testing will be much easier.
## Launcher
It would be very inconvienent if you had to ssh in to your kindle every time you want to start the UDP service. After a small amount of research I stumbled upon KUAL, the Kindle Unified Application Launcher. KUAL has a manu system and has been reliable for me for over one year. Install KUAL by following this [link](https://www.mobileread.com/forums/showthread.php?t=203326).
## Copy KUAL Menu
The last thing you need to do on the Kindle is copy the extensions directory in this repo to your Kindle documents directory.

# On the ESP8266
The short Arduino sketch is pretty self explanatory. There are two inputs, one for each button. This one is built for a SparkFun Thing. 
## Configuration
This version of the ESP8266 code uses a Wifi Manager that puts the chip into base station mode if it cannot connect to a known WIFI. This is about 50% useful, since you need to also know the IP address of the Kindle. At some point I will implement a way to store the Kindle's address - or support pure-base station mode between the kindle and page turner device.

# History
I first implemented this using a RaspberryPi and a tiny bluetooth shutter key. This worked, but was a bit overbuilt. Bluetooth in general is rather poorly documented and challenging to build around. Over time the complexity of managing three devices sank this project - I never quite covered all of the ways that the shutterkey might disconnect then reconnect. In this solution the RaspberryPi made ssh exec calls to the kindle. Unfortunately Arduino does not have SSH client libraries implemented (or didn't) so that is why I came up with the UDP server based solution on the Kindle.

