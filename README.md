# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
## Files
- _PID.cpp_: PID controller implementation and tracking of the MSE for Twiddle
- _main.cpp_: steering & throttle control, and Twiddle implementation

## Demo Video
https://youtu.be/GXjdCbwiTCk

## Final Hyperparameters
- Kp = .14 (_main.cpp line 44_)
- Kd = 3.4
- Ki = 0.001

## Reflection

**Throttle Control**
I started out by implementing a throttle PID controller to maintain constant speed.  The throttle controller uses simple setting (1,0,0), which appears to work just fine.  Later, I came up with the idea of using the throttle controller to brake when the car encounters a curve and is moving too fast.  I do this by setting the desired maximum speed inversely proportional to the CTE.  In the final configuration, the maximum speed is set to 60 when CTE=0 and lowers to 30 when CTE>=1.25 (_main.cpp line 121_).

**Twiddle Implementation**
I implemented Twiddle using a state machine (_main.cpp line 45 and 81_).  I use the code from the discussion forum to automatically reset the simulator each time the CTE gets bigger than 2.5m, i.e. the car goes off the road.  The Twiddle implementation works to find local maximum; however, it takes a long time to converge.  It appears it may "wander" off if the delta values are set too large; though it may come back after a while.  Even with good initial settings, finding optimal values are very slow because the car will drive a very long time before it goes off track.  I remedied this by using a lower max-CTE of 1 meter, to force a reset sooner each iteration.  In the end, however, most of the work was through manual tuning.  I used Twiddle only to tune the Kd parameter, after I have chosen a good value for Kp.

**Manual Tuning**
Through many hours of manual tuning, I slowly understood the effects of the PID coefficients.

- The Kp parameter controls how quickly (or strongly) the car responds to a curve.  The Kp parameter alone is not enough to cause CTE to converge to 0.  The car keeps overcompensating and ends up swerving forever.  A large Kp causes more over-steer, resulting in bigger swerving.

- The Kd differential parameter dampens the effect of first parameter and allows the CTE to converge to 0.  When CTE is increasing, the Kd component is negative, adding to the effect of Kp, resulting in stronger corrective steering when entering a curve.  When CTE is decreasing, the Kd component is positive, reducing the effect of Kp, resulting in graceful convergence to the reference track.  The tricky part is if Kd is set too high, its positive effect will trump the effect of Kp, resulting in more swerving, a behavior I couldn't completely understand and need further investigation.

- The Ki integral parameter is supposed to correct any system bias such as steering drift (e.g. wheel misalignment).  I could not really see the effect of this parameter during my manual tuning process.  In the end, I set it to a small non-zero value.  In theory, over time the steering drift makes itself known through the accumulative CTE; and the Ki component then accounts for this in the steering calculation.

In the end, my method for choosing parameter is basically as follows.  First I pick a big enough Kp value that results in good response to curves.  Then I find a good Kd value that results in quick and graceful dampening of CTE.  With a lot of trial and errors, good values for Kd and Kp were found that allows the car to pass the lake track at an average speed of 40-50.

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`.
