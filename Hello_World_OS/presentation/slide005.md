            ___                             __    __         ______          __   ___     ____  __       _   ______ _
           /   |  _____________  ____ ___  / /_  / /_  __   / ____/___  ____/ /__/__ \   / __ \/ /_     / | / / __ ( )____
          / /| | / ___/ ___/ _ \/ __ `__ \/ __ \/ / / / /  / /   / __ \/ __  / _ \/ _/  / / / / __ \   /  |/ / / / // ___/
         / ___ |(__  )__  )  __/ / / / / / /_/ / / /_/ /  / /___/ /_/ / /_/ /  __/_/   / /_/ / / / /  / /|  / /_/ / (__  )
        /_/  |_/____/____/\___/_/ /_/ /_/_.___/_/\__, /   \____/\____/\__,_/\___(_)    \____/_/ /_/  /_/ |_/\____/ /____/
                                                /____/
        Next, we need to write an assembly code layer that sets up some data required
        by grub or other multiboot complient bootloaders so that they can recognize our
        kernel as a multiboot complient kernel.

        This assembly code also setups a stack so that we can write the rest of our kernel in C.

        We will be using the NetWide Assembler (Nasm) Because I like intel syntax.

















































































slide 005
