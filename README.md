# Drone 
Starting a drone/quadcopter project. 
Will proceed as follows:
1.  Start out with reading and plotting a gyroscope and interpreting that information. May add another gyroscope and then have arduino poll those gyroscopes. What follows would be some accelerometer data, again maybe followed by some polling from the controller. These two gyro/accelerometers could actually be split into different resolutions (ie one accelerometer handles <2g maneuvers, the other <16).
2.  Create a feedback loop where an LED will blink with a higher frequency as the gyro is tilted away from its neutral "home" plane. This would mimic an auto levelling function where the computer controls the quadcopter motors' rpm to level itself using differential thrust.
3. Add some forward motion functions and GPS. Tilt until within a certain range angle and move laterally using differential thrust based on angle at that time. 
If successful may save up to buy some quadcopter motors and blades and implement. Ideally would use a teensy 4.0 and a shift register if I need more pins.
4. If succesful will buy the parts for drone. Will keep it as economical as possible.