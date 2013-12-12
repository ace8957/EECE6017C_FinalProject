======================
EECE6017C_FinalProject
======================

Battleship

======================

Equipment Required:
    Single Player:
        1 - Altera DE-1 Board
    Two Player:
        2 - Atera DE-1 Boards
        1 - RS232 Serial Cable
Setup:
    Load the project file (application/battleship.ncf) onto the DE-1 board
    and connect a display to the VGA port and a keyboard to the PS/2 port. 
    If playing a two player game, also connect the RS232 cable to the 
    serial ports on each board.      

Project Files:
    .//application:
    AI.c            a.out           game.c          graphics.c      keyboard.c      nios2_ctrl_reg_macros.h setup.h
    AI.h            battleship.ncf      game.h          graphics.h      keyboard.h      serial.c        ui.c
    AI.o            color.c         globals.c       graphics_testing    main.c          serial.h        ui.h
    PS2_ISR.c       exception_handler.c globals.h       interval_timer_ISR.c    media_interrupt.c   setup.c         ui.o

    .//application/graphics_testing:
    Makefile    graphics.h  keyboard.c  keyboard.o  main.o      ui.c        ui.o
    graphics.c  graphics.o  keyboard.h  main.c      testUI      ui.h

    .//hardware:
    DE1_Media_Computer.jdi  DE1_Media_Computer.sof  nios_system.sopcinfo

    .//lab7_files:
    PS2_ISR.c       globals.c       globals.h       media_interrupt.c

    .//python:
    serialCommRS232.py

