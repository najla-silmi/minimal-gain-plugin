# Minimal Gain Plugin 

## An introduction to input and output gain control in JUCE.

### First off, what is gain?
I remember struggling with the difference between "volume" and "gain" when I took my first audio engineering class, so I'll try to explain it as simply as possible. Volume can essentially be reduced to human perception of loudness. Gain, on the other hand, is a technical concept, with two main types: input and output gain. 

#### Input gain 
Input gain controls how much of a signal is affected by the processor, shaping tone and potentially introducing distortion.

#### Output gain
Output gain is sometimes used synomymously with "make-up gain." This controls the level of a signal after processing, especially since processing can affect the perceived loudness of a signal.

### Linear gain versus decibel gain sliders
Linear gain is the common option for audio plugins. Each sample is multipled by the same value, regardless of its amplitude. <br>

$$
\text{Amplified Signal = Input Signal x Gain}
$$

Where a gain factor less than 1 lowers the level and a gain factor greater than 1 increases the level.

However, gain knobs rarely use direct linear gain values for their UI, instead presenting dB values. The dB values are converted to linear gain factors using the following formula: <br>

$$
\text{Linear Gain} = 10^{\frac{dB}{20}}
$$

### Justifying the use of dB in plugins using human perception
While linear gain factors can work for gain sliders in JUCE, decibel values can make a bit more sense. When working with hearing aids and studying human loudness perception, I learned three rules that helped me understand the relationships between gain and perceived loudness (and make sure I wasn't going crazy with gain adjustments): <br>
1. A 3dB increase in a signal is a doubling in sound intensity, and is a clearly noticeable difference for most people.
2. A 6dB increase in a signal is a doubling in sound pressure. Doubling distance from a sound source decreases the sound pressure by 6dB, while halving distance from a sound source increases the sound pressure by 6dB.
3. A 10dB increase in a signal is perceived as a doubling in loudness.

After learning these relationships, the reasoning behind having sliders with dB values seemed more intuitive to me. 

### How to manage gain in JUCE
In JUCE, the class juce::dsp::gain can be used to convert dB values obtained from a slider into linear gain factors, and vice versa. To convert dB values into linear gain factors, the following function can be used in place of the previosuly provided formula: <br>
```
linearGain = juce::Decibels::decibelsToGain(dbGain);
```

### Using the Minimal Gain Plugin
The Minimal Gain Plugin is meant as a playground for understanding input and output gain. Since input and output gain are not differentiable without some sort of processing in between, a basic soft clipper has been added to demonstrate gain-dependent effects (though this can ultimately be replaced with other types of processing).
