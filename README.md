# aimbot
a working wireless aimbot which shoots a nerf gun at targets detected by face recognition

python code works by detecting faces via fd.xml trained AI algorithm, which is taken from live RSTP feed from any wireless RSTP camera mounted on camera.
It sends movement data to the ESP32, which wirelessly sends it to the ESP32 on the turret, which controls 2 stepper motors, one left-right, one up-down, capable of moving the gun in all 360 degrees.
The 3 parts work together to provide a seamless experience of a bluetooth, handheld, wireless aimbot turret.

demo: https://media.discordapp.net/attachments/937601702608125963/966136262585118820/IMG_2219.mp4
(It is connected to the computer for power, no instructions are being run though the USB cable)
