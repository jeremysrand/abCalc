abCalc
======

The "Ass-Backward Calculator" for the Apple //GS - an RPN calculator NDA

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
2. Once you have the files, you should first execute "dmake fixfiles".  This makes sure all files have the right
file types.
3. Execute "dmake"

When done, you will have two binaries.  The abCalc binary is a shell command you can use from GNO/ME.  And abCalcNDA
is a new desk accessory which you can use from within GS/OS applications.
