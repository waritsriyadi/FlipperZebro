# DISCLAIMER
THIS PROJECT IS LEARNING AND RESEARCH PURPOSES ONLY. ANY ILLEGAL ACTIVITES USING THIS PROJECT ARE NOT AUTHOR'S RESPONSIBLE. 
FlipperZebro is intended solely for educational and research purposes. Any use of this product for unauthorized or malicious activities is strictly prohibited. The developers and manufacturers of FlipperZebro disclaim any responsibility for the misuse of this device. Users are encouraged to adhere to ethical standards and legal regulations governing cybersecurity testing and research activities. Use FlipperZebro responsibly, respecting privacy, and obtaining proper authorization before conducting any testing on networks or devices not owned by the user.

# ABOUT PROJECT
Developed for educational and research purposes, FlipperZebro is an innovative device that seamlessly integrates RFID cloning, Captive Portal, WiFi Beacon Spam, BLE Spamming, and Deauth SSID attack functionalities. This advanced security toolkit offers unparalleled capabilities, providing a comprehensive solution for in-depth testing and analysis in the realms of RFID, WiFi, and Bluetooth security.

**Key Features:**

**RFID Cloning Mastery:**
FlipperZebro has perfected RFID cloning, allowing users to replicate RFID signals effortlessly. This feature empowers security experts to recreate real-world scenarios for thorough testing and evaluation.

**Captive Portal Integration:**
Navigating security landscapes is made seamless with FlipperZebro's Captive Portal integration. Users can assess and secure networks by implementing customizable authentication processes, ensuring a robust defense against unauthorized access.

**WiFi Beacon Spam Dominance:**
Take control of WiFi environments using FlipperZebro's WiFi Beacon Spam functionality. Flood networks with simulated beacon signals for comprehensive testing and analysis, uncovering potential vulnerabilities and weaknesses.

**BLE Spamming Prowess:**
Explore the intricacies of Bluetooth Low Energy (BLE) with FlipperZebro's BLE Spamming feature. Uncover security gaps in Bluetooth-enabled devices by inundating them with controlled signals, facilitating thorough penetration testing.

**Deauth SSID Attack Expertise:**
FlipperZebro's Deauth SSID Attack capability enhances your security toolkit by allowing you to simulate and evaluate the impact of deauthentication attacks on WiFi networks. Identify and address vulnerabilities efficiently.


# THINGS YOU NEED
1. RFID MFRC522
2. ESP32 DEVKIT V1 (2 pcs, why? cuz 1 memory not enough for BLE function)
3. DC Adapter or Battery
4. Button Tactile Input-PullUP (3 pcs)
5. LCD_I2C 16x2 (You can use another display such as OLED/TTGO by changin display PIN)
6. Relay for activate the other ESP32



Say HI!~

Instagram  :  instagram.com/ryd.warits
Linkedin   :  linkedin.com/in/waritsriyadi/

⠀⠀⠀⠀⠈⠉⠒⠦⣄⣀⣀⡤⢾⢏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢯⠃⠀⠀⠀⠀⠀⠀⢠⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢀⣠⠞⠁⠀⠘⣟⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣞⣿⠀⠀⠀⣀⣀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣞⠁⠀⠀⠀⠀⠸⡽⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣯⣇⠶⣾⣭⢷⣶⢇⠀⣾⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠹⣄⠀⠀⠀⠀⠀⠹⣿⡀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣠⠤⠤⠴⠶⠶⠶⠶⠤⠤⣄⣰⣷⠙⣧⠸⣽⣻⣞⣮⢿⣿⣿⣷⡄⣀⣀⣀⢀⣀⣤⡴⠶⣦⣄⡀⠀⠀⠀
⠑⢄⠀⠀⠀⠀⠀⠀⠹⣆⠀⠀⠀⠀⠀⠳⣷⡀⠀⣀⠤⠖⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⢿⣇⢹⡷⢾⡽⣞⣿⠿⠓⣛⢩⣠⢻⣟⠁⠀⠀⠀⠀⠀⠙⢷⡀⠀
⠀⠀⠙⠢⣄⡀⠀⠀⠀⠘⢧⠀⠀⠀⠀⠀⢹⠷⠊⠁⠀⠀⠀⠀⠀⠀⠈⠒⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡽⠆⣿⡻⣼⡹⢳⠖⣏⢎⡳⡌⡅⢿⡀⠀⠀⠀⠀⠀⠀⠀⠹⣄
⠀⠀⠀⠀⠀⠉⠒⠦⣀⣠⠞⢳⡀⠀⢀⡴⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠢⣀⠀⠀⠀⠀⠀⣠⢴⣫⣵⢶⣻⢳⡝⡶⡹⢭⢞⣱⣮⣵⣾⣿⡿⢧⠀⠀⠀⠀⠀⠀⠀⠀⠹
⠢⢤⣀⠀⠀⠀⠀⢀⡼⠁⠀⢀⡽⢦⠞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⣄⠀⠀⠀⣇⢿⡽⣞⢯⡞⢧⢯⣱⢏⡳⢚⣏⢿⡟⠭⣷⢩⢻⡀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠘⠣⢄⡀⠀⢸⠃⠀⠀⡼⢠⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢇⡀⠀⠸⡜⢿⣜⣧⠿⣛⣿⠸⣜⠣⢇⠸⡜⣿⢣⢻⡟⡼⡀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠙⢲⡏⠀⠀⡼⢡⠏⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠱⣄⠀⢻⣤⣴⠾⠟⠛⠉⢷⡸⡇⠌⣀⣻⠹⣇⡏⣷⠭⡇⠀⠀⠀⠀⠀⠀⠀⠀
⠦⢀⠀⠀⠀⠀⢸⠃⠀⣸⢃⠏⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⣧⠀⠀⠀⠀⠀⠀⠀⠀⠈⢦⠈⣏⡇⠀⠀⠀⠀⠈⢷⣽⣟⣭⣿⣾⡿⣘⢽⡞⣧⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⣷⡴⢶⠀⣼⠀⢰⠃⡞⠀⠀⠀⠀⠀⠀⠀⣧⠀⠀⠀⠀⠀⠀⠀⠀⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠈⢣⡰⢻⡄⠀⠀⠀⠀⠀⠛⢻⡫⣕⢻⣧⡙⣎⣷⣹⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⡞⡇⢸⡆⣟⠀⡾⢸⠁⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀⠀⠀⠀⠀⠀⠀⢻⠘⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡥⢻⠀⠀⠀⠀⠀⠀⠀⠱⣎⡝⣷⣩⢒⣽⣾⠀⠀⠀⠀⠀⠀⠀⠀
⢤⡾⢥⣃⠜⢀⡯⢰⠇⠇⡀⠀⠀⠀⠀⠀⢀⣾⠹⡄⠀⠀⠀⠀⠀⠀⠀⢸⠀⠈⢳⡀⠀⠀⠀⠀⠀⠀⠀⠈⢳⡹⣇⢀⠀⠀⠀⠀⠀⠀⡷⣘⢻⣦⢋⡜⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠙⠢⢤⡀⢸⡇⢸⢠⠀⠀⠀⠀⠀⠀⠀⡞⡇⠀⢳⠀⠀⠀⠀⠀⠀⠀⠸⡇⠀⠀⠙⣄⠀⠀⠀⠀⠀⠁⠀⠈⣇⢿⠀⠀⠀⠀⠀⠀⠀⢹⣌⢳⣿⠱⢎⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠈⢹⡇⠹⢸⠀⠀⠀⠀⠀⠀⠀⣻⠁⠆⠀⢣⠀⠀⠀⠀⠀⠀⠘⣇⠀⠇⠀⠈⢣⡀⠀⠀⠀⠀⠀⢘⣿⢸⡆⠀⠀⠀⠀⠀⠀⢸⡎⡿⣾⣟⠲⣼⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⡇⢘⠀⠀⠀⠀⠀⠀⠀⡴⡏⠀⠀⠀⠀⢧⡀⠀⠀⠀⠀⠀⢿⠀⠀⠀⠀⢀⣙⣦⣀⣠⢤⠤⠴⣻⡘⣧⠀⠀⠀⠀⠀⠀⠐⣿⢳⣏⢽⡇⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣇⢸⠀⠀⠀⠀⠀⠀⢀⠷⡇⠀⠀⠀⠀⠀⠳⡀⠀⠀⠀⠙⠻⡏⠉⠉⠉⠁⣀⣄⣙⣶⣤⣄⣈⣧⡙⣿⠀⠀⠀⠀⠀⠀⢘⣏⡿⡸⣌⢿⣾⠀⠀⠀⠀⢀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⡧⢸⠀⠀⠀⠀⠀⠀⢘⣺⠅⠀⣀⠠⠔⠲⣁⠙⣦⢀⡀⠀⢘⣳⠀⡄⣴⣿⣿⢿⣿⣛⠛⠿⠿⣿⣷⣿⡀⠀⠀⠀⠀⠀⢸⠛⢷⡱⢎⠾⠛⣀⣀⣀⣄⣌⣐⠂⢀
⡄⠀⠀⠀⠀⠀⣱⢸⠀⠀⠀⠀⠀⠀⠞⣼⠉⣡⣶⣶⣶⣶⣶⣍⠊⢻⣜⢲⡀⣚⣇⠐⡿⠋⣾⢿⣽⣻⣿⣄⠀⠈⠙⣿⣇⠀⠀⠀⠀⢀⣾⡀⠘⣧⠋⣴⡿⠽⠟⠛⠚⠛⠛⠻⢾
⡿⣥⡀⠀⠀⠀⢸⠀⡄⠀⠀⠀⠀⠀⣛⣼⢠⡿⠋⣠⣶⣦⣭⡙⠳⠄⠙⢿⠳⢵⣺⡄⠀⢸⡿⡿⣿⣷⡹⣿⡆⠀⠀⣿⡏⠀⠀⠀⠀⣜⣿⡇⢀⣇⠸⣏⡀⠀⠀⠀⠀⠀⠀⠀⠀
⣿⣽⣳⣄⠀⠀⢸⡀⢇⠀⠀⠀⠀⠀⢧⢾⢸⡗⠀⣿⡟⣿⣟⣿⡄⠀⠀⠀⠀⠀⠈⠙⠀⠀⢿⣿⡻⠾⣡⢿⡇⠀⠀⣯⣓⠀⠀⢀⣼⣯⡟⣠⣾⡿⠁⠀⣙⠓⢤⡀⠀⠀⠀⠀⠀
⢷⢯⣷⣻⡄⠀⢸⡇⠸⡄⠀⠀⠀⢈⢮⣹⣆⠃⠀⢿⣿⣿⣟⣯⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⠙⠫⠱⠊⠁⡔⠀⣷⡍⠆⢠⠞⡽⣿⣴⣿⠏⠀⠀⠀⣿⠀⠀⠍⡓⠦⣀⠀⠀
⠀⠉⠘⠉⠃⠀⠸⡇⠀⣧⠀⠀⠀⠨⣖⣹⣿⡆⠀⠈⠻⠛⠊⡝⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠸⣧⣙⢦⡙⣾⣟⡿⠛⠁⠀⠀⠀⠀⣹⠀⠀⢠⠋⠀⠨⠑⠢
⠀⠀⠀⠀⠀⠀⠈⣧⠀⠘⡇⢰⡄⠐⢣⣾⣿⣿⣼⠁⠀⡜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣵⡏⣮⣽⡟⠋⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⢸⠀⠀⠀⠀⠐
⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠿⡜⡿⣰⢋⡼⣿⣿⣷⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣾⢏⣜⡾⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⣸⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠘⡥⡇⠙⢧⣚⣿⣿⣿⣧⣀⠀⠀⠀⠀⠀⢀⠀⠴⠦⣍⣈⡭⠭⠭⠕⠀⠀⣀⣤⡾⠛⣟⣮⣾⣷⣶⠶⢿⠛⠛⠲⢤⡀⠀⠀⢸⡃⠀⡞⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢸⡄⠀⠀⡃⠁⠀⠀⠙⣿⣿⣿⣿⣿⡓⠶⣶⣤⣤⠁⠀⡠⠦⣈⡇⠀⢀⣀⣤⣶⣿⠟⡽⠁⢸⡿⠁⡞⠀⠄⡰⠁⠀⠀⠀⠀⢳⡀⠀⢸⡇⠀⡇⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠇⠀⠀⠀⠀⢻⣻⣿⣿⡿⠁⠀⠀⢠⡏⢀⣸⠁⢀⡼⠛⣿⠿⣿⣿⠿⢋⡾⠁⠀⠃⠀⠀⡇⠀⡐⡁⠀⠀⠀⠀⠀⠈⢷⠀⠸⡅⢠⡇⠀⠀⠀⠀⠀
⠀⠀⠀⣀⠀⠀⠀⢸⡇⠀⠀⡃⠀⠀⠀⠀⠈⣷⢪⠿⣧⠀⠀⣴⢿⠁⢠⠃⠀⡟⠀⢀⡧⢽⢞⡆⣰⠟⠀⠀⠀⠀⠀⢰⠀⡜⡍⠀⠀⠀⠀⠀⠀⠀⠸⡄⢈⡇⢸⠀⠀⠀⠀⠀⠀
⠀⠀⢿⠱⡦⣔⣢⢸⡇⠀⠀⡅⠀⠀⠀⠀⠀⢹⣎⠵⣻⠀⢨⡟⠸⡄⡀⠀⢠⠀⠠⠊⠀⣸⡼⣿⣧⠖⠒⣄⠀⠀⠀⡎⡰⡝⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠠⡇⣸⠀⠀⠀⠀⠀⠀
⡴⠖⠚⣀⢩⡤⠼⠜⡇⠀⠀⡇⠀⠀⠀⠀⠀⠀⢿⢪⢽⡂⢸⡇⠀⢳⠀⠀⠀⠀⠀⠀⠸⡟⠁⠀⠇⠀⠂⠀⠙⡖⠚⢀⣱⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⠀⣧⡿⠀⠀⠀⠀⠀⠀
⡓⢊⣉⣙⡄⢳⠜⢛⠳⣗⠄⡇⠀⠀⠀⠀⠀⠀⢸⡏⢾⡅⢺⡇⠀⠈⡆⠀⠀⠀⠀⠀⠀⣇⡀⠀⠀⠀⠀⣿⠆⠃⠀⢠⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⠀⣿⡇⠀⠀⠀⠀⠀⠀
