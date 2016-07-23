abCalc
======

The "Ass-Backward Calculator" for the Apple //GS - an RPN calculator NDA.

[Download a disk image](https://github.com/jeremysrand/abCalc/releases/download/v1.0.1/abCalc.2mg)
[Download a SHK file](https://github.com/jeremysrand/abCalc/releases/download/v1.0.1/abCalc.SHK)

The source can be built both from Mac OSX, resulting in a commandline binary which you can run on a Mac and from a //GS.
To build and execute on a Mac:

1. Make sure you have Xcode installed.  If not, grab it from the Mac App store.
2. Execute "make -f Make.mac"
3. Run "./abCalc"

In theory, it should work on any POSIX platform like Linux, Solaris, etc but I have not tested it on any other platforms.

To build this on a //GS, you need a number of prerequisites:

1. Orca/C v2.0.1
2. GNO/ME v2.x
3. occ - the Orca/C wrapper
4. dmake

To build this on a //GS, the steps are:

1. Somehow copy the files to your //GS.  Depending on whether you are using a real machine or an emulator, your
approach here may be different.
2. Find this line in your ORCACDefs/scrap.h file:
    extern pascal void PutScrap(unsigned Longint, Word, Pointer) inline(0x0C16,dispatcher);
and change it to
    extern pascal void PutScrap(LongWord, Word, Pointer) inline(0x0C16,dispatcher);
This is a bug in the headers which causes ORCA/C to generate the wrong output.
3. Once you have the files, you should first execute "dmake fixfiles".  This makes sure all files have the right
file types.
4. Execute "dmake"

When done, you will have two binaries.  The abCalc binary is a shell command you can use from GNO/ME:

![abCalc Shell Screenshot](/screenshots/abCalc.png "abCalc Shell Screenshot")

And abCalcNDA is a new desk accessory which you can use from within GS/OS applications:

![abCalc NDA Screenshot](/screenshots/abCalcNDA.png "abCalc NDA Screenshot")
