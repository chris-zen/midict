# MIDIct2

## Modules

### Knobs
This is a board with 8 rotary encoders to allow controlling several parameters simultaneously.

### Screen

A TFT HVGA 480x320 3.2" screen to show status to the user.
It will be controlled from software through some protocol MIDI SysEx / OSC.

### Control

This is a board with 2 rotary encoders and 6 buttons.
For controlling pages, devices, parameters, transport, ...

## Roadmap

**Knobs**

- [x] PCB design, assembly and verification
- [ ] Firmware development for the RPi
- [ ] RPi setup: mDNS, AppleMIDI driver, USB-OTG MIDI, ...

**Screen**

- [ ] MIDI/OSC Protocol to control the screen content
- [ ] Firmware to draw the screen from the RPi

**Control**

- [ ] PCB design, assembly and verification
- [ ] Firmware development for the RPi

## Images

* [First try for the rotary encoders with a photosensible dry film that was full of scratches](https://goo.gl/photos/vFz5QZcYP5DqDy86A)
* [Second try with tonner transfer using sheets from a magazinne](https://goo.gl/photos/Drio2UvwJJE7scSj7)
* [My own UV insolator](https://goo.gl/photos/k7TKoiVqc2WFZSGJ9)
