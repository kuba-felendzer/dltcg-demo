# dltcg-demo
A demo for a game I'm working on with a few friends.

## DISCLAIMER

**This demo is not at all indicative of the final product. This is more a proof-of-concept to get the programming department off their asses and working.**

## How to test

On Windows, run the provided `compfile.cmd` in your terminal
You need to have `raylib` and `gcc` installed, but I would just reccommend going to [the raylib website](https://raylib.com) and downloading it. Comes with a customized installation of Notepad++ (although switching to a different editor is very simple), gcc and all the header files needed. The script will run the provided `example.c`, but you can modify it to run your own custom code if you so choose.

*Modify `C:\raylib\mingw\bin\gcc -o out.exe <your C file here> C:\raylib\raylib\src\raylib.rc.data -s ...`*

On Linux, you'll just have to figure it out yourself like you do everything else about your computer. I might write a `compfile.sh` if there is any interest, although if you're programming in C with a relatively complex graphics lib you can probably figure out how to translate a 2 line script. The `gcc` command will probably just work, although no guarantees since I'm on Windows for the time being.

After you compile the code, there should just be an executable in the directory your script is in. I trust you know how to run an exe on your machine.
