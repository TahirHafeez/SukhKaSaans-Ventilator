# Sukh Ka Saans
Open Source Mechanical Ventilator using Ambu Bag &amp; Arduino to help people struggling for medical aid in pandemic situations like COVID-19. It's low cost ($60-80) easy to make and use.\
It is strap based design which squeezes the bag with servo motor rotation and measures tidal volume with servo motor position.  
There are three knobs which control  
1. Tidal Volume  
2. BPM (Breath per minute) rate
3. LCD brightness and Visuals


# Schematics

![](schematics.png)

# Components
1. Arduino 1(Use any available like UNO, Mega, Nano, esp8266 etc,)  
2. Servo Motor (Metal Geared High torque) 1  
**DO NOT use mg996r/946.. Atleast use 40kg/cm torque motor. I am using 60kg motor.**  
**You can use nema 17/23 stepper motors as well with H-bridge L298, drv8825 or a4988 etc., drivers**  
**Note: Stepper Motor perform better than servo**  
3. Servo Driver 1 (Optional)  
4. Ambu Bag 1 (Any Available, preferable medium or adult size)  
5. 16-2 LCD (Optional) 1  
6. Potentiometers 3 (10k or any other available)  
7. Voltage Regulator / Power Supply (To power Arduino, Servo and other components)  
8. Breadboard / Veroboard / PCB  

# Prototype

![](1st.jpg)

\
**Feel free for suggestions and modifications.**
