# 1-UP
Live coding environment, built harboring simplicity and portability. Built with the beginner in mind - to break out of standard frameworks and notational systems of music.

## Usage
1. Download the latest release
2. Open terminal and navigate to the directory where you downloaded the release (e.g. `cd ~/Downloads/1up`)
3. `./1up {port_number}` 

## Functions
#### Mono Note
> m!/{note}/{velocity}/{duration}/
#### Poly Note
> p!/{notes seperated by commas}/{velocities seperates by commas, or just one value if all notes are the same}/{duration}/

## Commands
- Navigate between editors `ctrl+h` and `ctrl+l`
- Navigate text, `arrow key`
- `K` - play line (for testing)
- `k` - play sequence
- `t` - send current line over OSC protocol (for testing)
- `i` - insert line
- `esc` - exit insert mode
- `ctrl + g` - open up global params

## Parameters
- `bpm` - beats per minute
- `ip address` - ip address of the machine you want to send OSC messages to.
- `port` - port number of the machine you want to send OSC messages to.