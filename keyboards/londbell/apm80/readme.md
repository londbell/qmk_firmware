# apm80

![apm80](imgur.com image replace me!)

A 80% multi-layout keyboard with no nkoo for mac.
This keyboard use 16mhz HSE and APM32F103CBT6(STM32F103CBT6) as MCU.

* Keyboard Maintainer: [londbell](https://github.com/londbell)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make apm80:default

    or

    qmk compile -kb londbell/apm80 -km via

Flashing example for this keyboard:

    make apm80:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset pad**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
