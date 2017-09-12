abCalc
======

The "Ass-Backward Calculator" for the Apple //GS - an RPN calculator NDA

[Download a disk image](https://github.com/jeremysrand/abCalc/releases/download/v1.0.1/abCalc.2mg) or [download a SHK file](https://github.com/jeremysrand/abCalc/releases/download/v1.0.1/abCalc.SHK)

The source code is built using my [Apple //GS Build Pipeline](https://github.com/jeremysrand/Apple2GSBuildPipeline).
If you setup all of the prerequisites on that project, you should be able to build this on a Mac
using Xcode.  Failing that, put the source onto a real or emulated GS and build it using ORCA/C.
However, I no longer have a GS compatible Makefile.  If you look in the git history, you will see that
in the past, the build could be done using dmake under GNO/ME on a GS.

The abCalc binary is a shell command you can use from GNO/ME:

![abCalc Shell Screenshot](/abCalc/screenshots/abCalc.png "abCalc Shell Screenshot")

And abCalcNDA is a new desk accessory which you can use from within GS/OS applications:

![abCalc NDA Screenshot](/abCalc/screenshots/abCalcNDA.png "abCalc NDA Screenshot")
