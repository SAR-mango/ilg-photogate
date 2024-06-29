# Overview
A photogate is a timing device. It detects when an object crosses an infrared beam, and can do so with great accuracy. Such a tool is invaluable in a physics lab for obvious reasons. Some examples of use are:
- Measuring the period of a pendulum (and taking a rolling average)
- Measuring the speed of a projectile
- Counting the number of times a ball bounces before settling on the ground
This project aims to be a significantly cheaper – and equally functional – alternative to PASCO Scientific's photogates.

**NOTE: all documentation below is incomplete.**

# Modes and Usage

# Hardware
To answer this, let's look at the drawbacks of the alternatives.
**Radio:** Difficult to create a straight and narrow beam (it would require large directional antennas). Also passes through most objects.
**Visible Light:** Ambient light would make the photogate unusable unless in the dark.
**UV, X-ray:** Expensive and we don't want cancer.
We also note that while infrared or visible-spectrum lasers are suitable, their extremely narrow beamwidth makes it mechanically difficult to align the laser with the detector.

# Code Structure

# Remaining Tasks
- Finish all modes
- Return to mode-select screen after completing a measurement
- Implement data logging
- Set up RTC and include the time in logged files
- Test and characterize extensively (measure accuracy and precision)
- Write thorough documentation for usage (in LaTeX please!)
