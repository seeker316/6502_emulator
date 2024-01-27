so currently i have made all the architecture...from the documentation and okay i don't think there is any need to mention it as you can see from my code...i think it'll be fair enough to say thast this is m first cpp project so apologies,.....
okay then back to it from what i understand i have a rpugh idea of how the rough workflow will go on it'll be

my memory will contain opcode of instructions i'll fetch instruction opcodes from memory with help of program counter then with the opcode as my index for the defined instructionset table i'll some how find a way to execute the instruction that the opcode instructs to....currently i don't have a proper plan of doing it ...let's see if i can get my brain around it ....;)


it is jan 20 8:13 am and i am done with all the declarations and i've defined the instruction table which contains the op codes now iam going to start with the function definitions..............


so it is jan 20 and 17:24 after seeing the above entry ....bruh i've wasted my full day is how i feel....that's way to slow....the progress is i've developed helper functions to load code in the memory, to fetch the instructions and execute them....now I think i am finally ready to start with function declarations :() 

it was jan 23 midnight 1.30 and i am done with writing all adressing modes functions now i will be starting with 
the instruction functions

note 
In a real 6502 machine, the interpretation of a value as signed or unsigned is entirely dependent on the context in which the value is used by the program. The 6502 processor itself does not inherently assign signedness to values stored in memory. It treats all values as binary numbers and executes instructions accordingly.
For example, if you load the value 255 into a register using the LDA (Load Accumulator) instruction, the 6502 processor doesn't know whether you intend to interpret that value as an unsigned integer (255) or as a signed integer.
So, if you load the value 255 (11111111 in binary) into the accumulator, the Negative (N) flag will indeed be set because the MSB is 1.

It's JAN 27 10 PM I have finally finished the code.... done with all the functions including illegal opcodes
the thing is not been tested yet...but I'll see about it later...I've been coding since morning...that was a lot of hardwork....actually i planned on completing the thing by last weekend but managed to do it a week later.
that's all. The next things I plan on doing is testing it with some online scripts fix if any errors...and then plan on using it in any further implementatiosn like NES or actually I haven't looked into it but I was planning on running Wozman / apple I software.   