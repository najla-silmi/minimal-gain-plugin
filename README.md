<img width="790" height="312" alt="Screenshot 2026-04-28 at 10 51 03 PM" src="https://github.com/user-attachments/assets/5d53b6e2-01ec-4073-805b-1820521cf9c3" />

# Using the Minimal Gain Plugin 

## What it is 
The Minimal Gain Plugin provides an introduction to the effects of gain, specifically on soft clip saturation. As the name suggests, it includes a basic UI with three controls: 
1. Input gain
2. Normalized soft clip saturation, a common type of gradual saturation.
3. Output gain <br>
As well as basic parameter smoothing and decibel to linear gain factor conversion using the Decibels class in JUCE. <br>
This plugin is geared towards those just geting started with JUCE/DSP, and those who want to gain an understanding of gain from a perceptual and hands-on perspective.

## How to use 
### Required software: <br>
JUCE: https://juce.com/download/ <br>
Digital Audio Workstation (DAW) (I use REAPER for plugin testing, but other DAWs should work just fine): https://www.reaper.fm <br>

This tutorial, however, will focus on using the plugin in Reaper.

### Downloading the Minimal Gain Plugin
1. Download the source code.
   - In the project repository, click the green "Code" button.
   - Select "Download ZIP" and save to your device.
2. Open the project in JUCE
   - Launch the Projucer.
   - Open the file Minimal Gain Plugin.jucer from the .zip folder.
3. Export the project
   - In Projucer, select your IDE (Xcode, Visual Studio, etc., depending on your device).
   - Click the button to the right of the IDE selection to open the project in your chosen IDE.

### Building the plugin
1. Locate and select your plugin target (VST/VST3, AU, etc.).
2. Compile and run.
3. Save the built plugin (although in Xcode, this happens automatically for me).

### Using the plugin (in REAPER)
1. Open REAPER and create a track (either record one or import an audio file).
2. Click on "FX."
3. Filter the plugins to your selected plugin target.
4. Select "Minimal Gain Plugin."
   - The plugin should show up in its own window.

### Testing the plugin
Adjust ->
- Input gain: increases level into the soft clip saturation.
- Soft clip: adds harmonic distortion.
- Output gain: controls final volume.

### Questions, concerns, or room for improvement?
Let me know! :)
