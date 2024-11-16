# Seagate-Error-Calc
Seagate Error Calculator, win32 app of s.i.wtf

# Purpose
If you read the SMART values of your Seagate HDDs, you probably would ask why the error rate is so high.<br>
Well, it's because the way they calculate it are so different to other brands.<br>
https://s.i.wtf has the calculator but it's online and I don't want to go online to check the error.<br>
So I made this app.<br>

# How to compile
Compilable on Codeblocks and Visual Studio 2005 to 2022.<br>
Console app only.<br>
Make a new console c++ project on Codeblocks if to compile on that and copy paste the .cpp file.
The following compilation options have to be turned on if using MinGW<br>
- Static libgcc
- Static libstc++
- Static Linking<br>

Or else the compiled app will only execute in Codeblocks but not outside of it.
