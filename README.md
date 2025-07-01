# WCalc  
__A Calculator that can load modules at Runtime__  
__Compatible with macOS & Linux & Windows (Maybe)__  
## Usage

>[!IMPORTANT]  
>To Compile standard libs & App  
>LibDyn is needed - See [LibDyn on GitHub](https://github.com/Wdboyes14/libdyn) - FLAGS var in Makefile will need to be adjusted to you install path  
>Run `make PLATFORM=osx` on macOS  
>Run `make PLATFORM=linux` on Linux  
>__On Windows you will need to learn the art of dynamic linking yourslef :3__  

To start, run `./calc` it will automatically load `stdmath.dylib` (Standard Math Plugin)  
From the current directory  

To load a library do `ldplug [Path To Library]`  
To exit type `exit`  
For help type `help`  
  
To do an operation it is `opname Num1 Num2` With `opname` being the Operation Name (See `help`)  
and Num1/Num2 being the numbers to do that operation on, in order  

For example  

```
In: ldplug ./stdbit.dylib
Out: Bitwise ops are distinguished with b-
     Loaded plugin: Standard Bitwise Operations Plugin (6 ops)

In: boc 5 x
Out: Ignoring Num2
     boc Returned -6

In: random 0 10
Out: random Returned 5

In: exit
```  

## Notes  
- Typing `help` at any time will give you a list of ops, and what each does  
- Plugins are just `.dylib` files (Or `.so` or `.dll` but by default compilation outputs `.dylib`)  
- Easy to understand codebase, the standard modules are so easy to understand that we dont even need plugin dev docs  