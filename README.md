# Chip8
Chip8 Emulator written in C with SDL2

This was a very fun project to make, and a great learning experience.

# What is the CHIP 8?

the CHIP 8  is an interpreted programming language. what that basically means is that the CHIP8 is not a physical system but is a language that runs on systems. The original systems it was made for include the COSMAC VIP and the Telmac 1800. The language has seen changes over time, but this emulator is focused on the vanilla CHIP 8 as it ran on the cosmac vip. in the future I may return and add configurations to make it work with these different systems

# Background

I have always been interested in retro games and emulation, and I've been feeling the need to flesh out my resume with some personal projects. 

the idea to create this came to me I think when I was going to the mall with my mom. I was on my phone and went down a bit of a rabbit hole on emulation when I realized I should make my own! People say a good place to start is either emulating CHIP-8 or an old space invaders cabinet. There are some really great resources on CHIP-8 emulation and not as much on space invaders. I think moving forward I would like to try some projects around networking, like making this emulator 2 player for the games that support it, like pong. I'd also like to Emulate some mroe advanced systems like the NES, SNES etc.

I would highly recommend this project to anyone interested, Here are some of the resources I used:

https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#google_vignette 

https://www.youtube.com/playlist?list=PLT7NbkyNWaqbyBMzdySdqjnfUFxt8rnU_ 

http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.0 


# Running
to run this program you type this into your terminal:
./bin/chip8 'roms/FILENAME.ch8'

in the rom folder there are a bunch of different games to play, like breakout, brix, pong, and space invaders.

there are more of CHIP-8 games available online, but they may not work because they were developed for system other than the COSMAC-500 and will not work with the instructions of this emulator.

from game to game the keys used are different so you'll have to experiment to see what does what.

there are still some quirks to workout, particularly with space invaders. I am busy with schoolwork so this may not be fixed for a while.

# input
the original Chip 8 used input on a 16 digit keypad, like this.

 ----- ----- ----- -----
|  7  |  8  |  9  |  F  |
 ----- ----- ----- -----
|  4  |  5  |  6  |  E  |
 ----- ----- ----- -----
|  7  |  8  |  9  |  D  |
 ----- ----- ----- -----
|  A  |  0  |  B  |  C  |
 ----- ----- ----- -----

This is mapped onto your keyboard like this:

 ----- ----- ----- -----
|  1  |  2  |  3  |  4  |
 ----- ----- ----- -----
|  Q  |  W  |  E  |  R  |
 ----- ----- ----- -----
|  A  |  S  |  D  |  F  |
 ----- ----- ----- -----
|  Z  |  X  |  C  |  V  |
 ----- ----- ----- -----

# Debugging

Although it is disabled, you can go through my code and turn on some of the debugging features that I used to help me figure out some quirks.

# Future plans

I think I may return sometime and add much more customizable configurations like:
-making it work with some of the different quirks the different systems required
-letting the user change the display size and colours
-changing the keypad, as some other systems expected a different layout.
-speed
-a java based GUI?
-online multiplayer features?!
-other fun stuff!

# Thanks!

Thanks for checking out this project! If you find bugs or have any questions or recommendations shoot me an email at:
blaine.edgar07@gmail.com