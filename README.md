# 1-UP
Live coding environment, built harboring simplicity and portability. Built with the beginner in mind - to break out of standard frameworks and notational systems of music.

## Usage
1. Download the latest release
2. Open terminal and navigate to the directory where you downloaded the release (e.g. `cd ~/Downloads/1up`)
3. `./1up {port_number} {no. of channels}` 

## Functions
#### Mono Note
> m!/{note}/{velocity}/{duration}/
#### Poly Note
> p!/{notes seperated by commas}/{velocities seperates by commas, or just one value if all notes are the same}/{duration}/
#### Wait
> w!{duration} 

## Loops
1-UP is designed around a fascination for the euclidean sequence. This allows for immediate musicality amongst the user's journey into the world of live coding.

> Encapsulate a sequence of functions between `(` and `)` (on their own lines) to create the loop, directly following the closing bracket of the loop, add a `.` and then the subdivision of the euclidean sequence (must be over the number of functions in the loop).

Example:
```
(
m!/C3/127/1000/
m!/E3/127/1000/
m!/F3/127/1000/
).7
```

## Commands
- Navigate between editors `ctrl+h` and `ctrl+l`
- Navigate text, `arrow key`
- `K` - play line (for testing)
- `k` - play sequence
- `t` - send current line over OSC protocol (for testing)
- `i` - insert line
- `b{bpm}` - set bpm (without curly braces)
- `esc` - exit insert mode