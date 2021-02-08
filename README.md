# NotepadAnimator

Play your videos in a notepad using beautiful ASCII art!

### **MSVC and Windows only, sadly, because this project uses Windows' native notepad.exe application and WinAPI to control it.**

## Does it even work?

Well, almost. When recording, or just usually, the audio can desync for a second or two which breaks the whole thing, but rather than that, it's fully working!
Here's a video showing the result on a Bad Apple!! music video:
https://www.youtube.com/watch?v=juFDSQkpOQY

## Ok, but how do I build it?

I'm not sure what CLion does, but you can follow the same steps my Github Actions do.
So basically:
1. Generate MSVC makefiles with CMake
2. Compile ALL_BUILD.vcxproj from the CMake output

## But.. why??

I don't know, I just had fun and learnt a bit what suffering with C++ looks like.

## OK, I found your code is 💩.

That's good to hear! Please, submit an issue or a pull request and I will accept it! I would love any kind of contributing.

## Made with love, CLion and code from StackOverflow ❤️