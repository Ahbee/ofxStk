#ofxStk
ofxStk lets you use [The Synthesis Tool Kit](https://ccrma.stanford.edu/software/stk/index.html) inside openFrameworks. The offical repo for stk is here at https://github.com/thestk/stk. For features and issues you are better off posting there. I sync ofxStk with the offical Stk repo about once a month, or on demand 


##Installation 
***

Step 1 - Do what you normally do for an add-on (project generator works well)
 
Step 2 - Copy the 'rawwaves' folder from bin/data of the example project, into bin/data of your project.

##### Note on Linux
if your are on linux and your system is little endian you have to complie with the following option

```
-D__LITTLE_ENDIAN__
```


##How to use
***

Stk already works well with openFrameworks so there is no need to wrap it onto a separate api. Your best resource would be [the stk documentation](https://ccrma.stanford.edu/software/stk/classes.html). You can also ask me questions on the [forum](http://forum.openframeworks.cc/t/ofxstk-synthesis-toolkit-addon/15989/3)

####steps to create a custom instrument

1. Subclass stk::Instrument
2. Override all the pure virtual functions in stk::Instrmnt
3. When overriding `virtual StkFloat tick( unsigned int channel = 0 ) = 0` make sure you set `lastFrame_` which is the last computed frame of audio, and return the output for the channel specified by the argument. Remember a frame is different than a sample- `a Frame a set of samples that contains one sample from each channel in an audio data stream.`
4. When overriding `StkFrames& tick( StkFrames& frames, unsigned int channel = 0 ) = 0`,your job is to fill the specified frames starting at the specific channel. For example if your instrument is mono and tick(frames,1) is called, you fill the second channel of frames with your output. If your instrument is stereo and tick(frames,1) is called. you fill the second and third channel of frames with your output. Remember that lastFrame_ also has to be set in the function 
5. If your instrument is stereo, you will have to override the constructor of stk:Instrmnt to resize the lastFrame_. so in your constructor you should have the line `lastFrame_.resize( 1, 2, 0.0 );` 


##Notes
***
 
I've tested on Mac OSX, IOS ,and linux so far. But getting it to work for other platforms should be just a matter of configuring the macros in the file "Stk.h"
