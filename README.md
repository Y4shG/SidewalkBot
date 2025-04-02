🤖 Sidewalk-Following Robot 🚶‍♀️
This project features an autonomous robot designed to follow sidewalks using OpenCV for path detection and an Arduino for motor control. The robot uses a webcam for visual input, which is processed on a Windows PC to detect and follow paths, then sends movement commands to the Arduino via USB serial. The motors are controlled to steer and drive the robot along the sidewalk.

🚀 Features:
🌟 Open-source C++ code for path detection using OpenCV.

🎮 Arduino-controlled movement via serial communication.

🛠️ Easy-to-upload INO file to Arduino for motor control.

🏃‍♂️ Designed for autonomous operation with continuous movement.

📹 Utilizes webcam video input to follow sidewalks in real time.

📋 Setup Instructions:
Install OpenCV for C++ on your Windows PC. Follow this guide to install OpenCV.

Clone the repository and navigate to the project folder:

bash
Copy
Edit
git clone https://github.com/yourusername/sidewalk-following-robot.git
cd sidewalk-following-robot
Compile and run the C++ code:

bash
Copy
Edit
g++ -o sidewalk_follower main.cpp `pkg-config --cflags --libs opencv4`
./sidewalk_follower
Upload the INO file to your Arduino using the Arduino IDE.

Open robot_control.ino in the Arduino IDE.

Select your Arduino board and port.

Click Upload to transfer the code to the Arduino.

🚗 Commands Sent to Arduino:
L: Turn Left

R: Turn Right

F: Move Forward

The robot will follow the sidewalk autonomously for up to 30 minutes or more without interruptions, adjusting its path as necessary.

Feel free to fork the project, contribute, and modify the code to fit your specific needs! The project is fully open-source and welcomes improvements from the community. 🚀
