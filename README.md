# Load this project in MPLABX

1. Download required software
    a. Download the latest MPLABX IDE from official site
       - https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide
    b. Also download the `xc-dsc` compiler, which can target _dsPIC30F_:
       - https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers/xc-dsc
    c. In case you don't yet have it, download a git client appropriate for your operative system
       - Mac OS - install it via https://brew.sh/
       - Linux - install it via your package manager.
       - Windows - download it via https://git-scm.com/downloads/win

2. Clone the repository (see https://git-scm.com/docs/git-clone)

3. Open the project in MPLABX
   a. Open MPLABX
   b. On main menu, click on _File_ -> _Open project_
   c. Select the folder you just cloned.

# Check the project
1. Verify that it has two configurations:
   - TEST - To execute unit tests.
   - DEFAULT - To execute the program.
2. Verify DEFAULT configuration:
   - Select DEFAULT configuration.
   - Check that the project compiles without errors.
     It may have warnings about unused variables, as the program is
     not complete.
3. Verify TEST configuration:
   - Select TEST configuration.
   - Check that the project compiles without errors or warnings.
   - Run the program, and verify that there is content in UART 1 Output.
   - Most or all tests should be failing, as the program is not complete.

# Complete the program
Your job is completing the program, so all automated tests pass

It is possible to complete the program changing only the following two files:

1. In `peripheral-pwm.`, calculate the constants marked with `TODO`, so as
   to match the requirements for indexable LED of type PL9823
2. In `leds.c`, complete the methods marked as `TODO`. 
   
You're free to change anything you see fit.
