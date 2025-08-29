# R26_test

<p align="center">
  <img src="https://github.com/teamrudra/r26_test/blob/main/misc/rover.webp" width="480" height="480"/>

#### Some Instructions
1. You may use any online resources, datasheets, or documentation needed, but be mindful of your time and stay focused on the task.
2. The duration of the test is 90 mins from 5:15pm to 6:45 pm.
3. There will be a MCQ test conducted [here](https://rudra26test.vercel.app/)
4. There are 4 tasks in the tests. Complete all of them.
5. In case you are not able to complete all the tasks, do upload whatever you are able to.
6. In the `README.md` of your repository include your thought process, places where you got stuck, where you used the help of AI, google or other online resources.
7. Even if you are not able to solve anything, do fill the readme and what your thought process would have been.
8. Carefully read the instructions to implement the required functionality.
9. Install [mingw(c compiler)](https://www.mingw-w64.org/downloads/#w64devkit) and [git](https://git-scm.com/downloads) if you haven't already done it.
10. After finishing your test, provide the link to your forked repository in the google form provided at the end.

### Aim/Objective: To decode GPS data of start and goal position, and create a path planning algorithm which computes an optimal path over a predefined gridmap

## Description
You are implementing code to decode GPS position data, received from a u-blox GNSS module on-board a rover (check out the [datasheet](https://drive.google.com/file/d/1rOcPxpP-3JE8l39kBMiQV6KKe8B6zlDf/view)). You are given the current/start position of the rover and the goal position where the rover has to reach, your goal is to develop a path planning algorithm to traverse over a pre-defined gridmap and generate necessary odometry commands (total time & angle traversed) to guide the rover along the generated path. 

### Task 0: Fork the provided repository and ensure it is set to PUBLIC so we can access and assess your work.
### Task 1: Decoding gps data (in ubx format) from u-blox reciever.
Working with UBX format and extracted relevant navigation data for use in the planner.
### Task 2: Develop a path planning algorithm to traverse over a gridmap.
Implemented a grid-based path planner that computes an optimal route from start to goal.
### Task 3: Generate odometry commands to guide the rover along the generated path.
Converted the path into motion commands (direction and timing) based on wheel parameters.
### Task 4: Compile and run the code.
Verified the workflow on sample inputs and ensured the project compiles successfully with g++.

#### Code
1. [src/main.cpp](src/main.cpp): Code for running the test.
2. [src/ublox_reader.cpp](src/ublox_reader.cpp): Recitfy errors in this code to compute correct lat & lon coordinates.
3. [src/planning.cpp](src/planning.cpp): Complete the defined `Planner::pathplanning` function 
4. [src/odometry.cpp](src/odometry.cpp): Complete the defined `Odometry::computeCommands` function 

#### How to Compile & Check your code
(make sure you are in the root directory)   
1. Compile your code by running: `make build`
2. To check if your code is implemented correctly run: `make check`
   
If you are able to compile your code successfully you should see something like this on your screen:

```
*** Success: ***
--------------------------------------------
```

4. If your make check was unsuccesfull, you can clean your attempt by running `make clean`, review your implementation and repeat the previous steps.

# Solution
## Understanding
The problem was to develop a complete rover navigation system that involves three main components:
1. GPS Data Decoding
2. Path Planning
3. Odometry Command Generation
so,it handled real gps coordinates,convert them to grid coordinates, plan around obstacles, and generate practical movement commands for a physical rover.

## Thought Process
I approached this systematically by breaking down the problem into small tasks:

First, fix the GPS decoding: I analyzed the UBX message format and identified that the buffer offset errors in the NAV_POSLLH function were causing incorrect latitude/longitude extraction. The original code was reading from the same buffer position for both longitude and latitude.

Then implement path planning: I chose the A* algorithm because it's optimal for grid-based pathfinding and finds the shortest path while being computationally efficient. I considered both 4-directional and 8-directional movement, choosing 8-directional for more robot movement.

Finally, calculate odometry: I analyzed what motion commands meant in the context of rover navigation - the total time represents linear movement duration, and the total angle represents total rotations needed.

Ensure compatibility: I set up the Windows build environment with MinGW since the original makefile was designed for Unix-like systems.

## Implementation
How did you decide to implement your solution.
GPS Decoding (ublox_reader.cpp)
Issue: Buffer offsets in NAV_POSLLH were incorrect - longitude and latitude were both reading from the same memory position
Solution: Fixed memory offsets to read longitude from buffer + 4 and latitude from buffer + 8 according to UBX NAV-POSLLH message format
Path Planning (planning.cpp)
Algorithm Choice: Implemented A* pathfinding algorithm for optimal route finding
Implementation Details:
Used g-cost (actual distance from start) and f-cost
Implemented 8-directional movement with higher cost for diagonal moves (√2 vs 1.0)
Used Euclidean distance
Odometry Commands (odometry.cpp)
Time Calculation:
Calculated segment distances using Euclidean distance formula
Converted distance to time using: time = distance / velocity
Linear velocity derived from wheel parameters: v = 2πr × (rpm/60)
Angle Calculation:
Calculated absolute angle for each path segment using atan2()
Summed all segment angles to get total rotation
Converted from radians to degrees
 ## Places Where I Got Stuck & Used Resources
 I used 

# Google Form
[Link to Repo Submission](https://docs.google.com/forms/d/e/1FAIpQLSdlVJ2LzP8wUOATRD804zDVL611rwwGMO1y_ecYu5aoV5YQfw/viewform)


<p align="center">
  <img src="https://github.com/teamrudra/r25-test/blob/main/datasheets/feynman-simple.jpg" width="600" height="600"/>
</p>
     
