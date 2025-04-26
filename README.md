# Sidewalk-Following Robot

<img src="https://ollama.com/public/blog/nexttime.png" alt="Until next time"/>![image](https://github.com/user-attachments/assets/0228fca0-f0e4-4fbb-8b02-eff8857a47e4)

This project features an autonomous robot designed to follow sidewalks using **OpenCV** for path detection and an **Arduino** for motor control. The robot uses a webcam for visual input, which is processed on a Windows PC to detect and follow paths, then sends movement commands to the Arduino via USB serial. The motors are controlled to steer and drive the robot along the sidewalk.

## Features:
- **Open-source C++ code** for path detection using OpenCV.
- **Arduino-controlled movement** via serial communication.
- **Easy-to-upload INO file** to Arduino for motor control.
- Designed for **autonomous operation** with continuous movement.
- Utilizes **webcam video input** to follow sidewalks in real time.

## 📋 Setup Instructions:

1. **Install OpenCV** for C++ on your Windows PC. [Follow this guide](https://docs.opencv.org/4.x/d3/d52/tutorial_windows_install.html) to install OpenCV.
   
2. Clone the repository and navigate to the project folder:
   ```bash
   git clone https://github.com/yourusername/sidewalk-following-robot.git
   cd sidewalk-following-robot
   
Then compile and run the C++ code:
`bash g++ -o sidewalk_follower main.cpp pkg-config --cflags --libs opencv4 ./sidewalk_follower`

## 📋 Arduino Instructions:
Requirements: Arduino UNO R3, obv a cable


1. **Install IDE** https://docs.arduino.cc/software/ preferrably the GUI client

2. **Upload .ino file** click the upload button dumahh

3. **Start UNO** start your arduino and run the code.

## License 📜

This project is licensed under the [BSD-3-Clause License](LICENSE) - see the [LICENSE](LICENSE) file for details. 📄

## Support 💬

If you have any questions, suggestions, or need assistance, please open an issue to connect! 🤝

