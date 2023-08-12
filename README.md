# Pomoljus Interval Timer

Pomoljus is a programmable sequential interval timer with a light based alert method. In other words, its a clock aimed to function in a way inspired by the Pomodoro technique using only RGB LEDs.

## Milestones

The development of the Pomoljus is slow and is lead by a single slow person. To keep the development pointing in the correct direction a series of more achievable milestones have are listed below. This can also give an idea of where the development of this project is.

[Insert PBI]

Here is a rough estimation of the three major areas of the Pomoljus development.

- Firmware
  - ▰▰▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱ *[10%]*
- Electrical
  - ▰▰▰▰▰▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱ *[25%]*
- Housing
  - ▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱▱ *[00%]*

## Support

If you wish to shout encouraging words at me then you can find me at [@bpall@mstdn.social](https://mstdn.social/@bpall). You can also find my blog/project hub over at [bPall.se ](bPall.se).

## More

[My blog post about the initial concept generation.](https://bpall.se/blog/Pomljus%20Ch%200/)

---

## Getting it running

The Pomoljus is designed to run on an RP2040 using the [Raspberry Pi Pico C/C++ SDK](https://github.com/raspberrypi/pico-sdk). The LEDs are SK6812Minis. It's all mounted on custom designed PCBs created using KiCad. The housing is designed in [TBD].

Firmware files are found in `/firmware/`. Electrical diagrams and PCB design files are found in `/pcb/`. Housing and mechanical designs will live in `/cad/`.

### Building firmware from source

[Insert instructions on how to build...]