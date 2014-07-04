#ofxStk
ofxStk lets you use [The Synthesis Tool Kit](https://ccrma.stanford.edu/software/stk/index.html) inside openFrameworks. 


##Installation 
***

Step 1 - Do what you normally do for an add-on
 
Step 2 - Copy the 'rawwaves' folder from bin/data of the example project, into bin/data of your project.

##### Note on Linux
if your are on linux and your system is little endian you have to complie with the following option

```
-D__LITTLE_ENDIAN__
```


##How to use
***

Stk already works well with openFrameworks so there is no need to wrap it onto a separate api. Your best resource would be [the stk documentation](https://ccrma.stanford.edu/software/stk/classes.html). You can also ask me questions on the [forum](http://forum.openframeworks.cc/t/ofxstk-synthesis-toolkit-addon/15989/3)

##Notes
***
 
I've only tested on Mac OSX so far. But getting it to work for other platforms should be just a matter of configuring the macros in the file "Stk.h"
