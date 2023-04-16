# Logging
This is a simple Logging System using [fmt](https://github.com/fmtlib/fmt)



## Features
Current capabilities are:
- fmt Formatting
- Log 2 levels to Console

## Future
- Add the rest of the levels as needed
- Add write to file with more info in the CRITICAL and DEBUG modes.

## Usage

Call the Macros:

```c++
LINFO("Some string to print and a literal to show: {}", 1);

LINFO("Some other string to print and a variable to show: {}", foo);
```

## Results

![image](https://user-images.githubusercontent.com/16245845/232340553-bc30abe5-27bf-4615-bcc9-c943faf62cfb.png)
