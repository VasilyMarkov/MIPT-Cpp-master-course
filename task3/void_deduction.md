# Void deduction

To support such a mechanism, it is necessary to specifically 
handle the case in the immediate context if the function call argument is missing.

Such a construct will be instantiated only if there are no errors 
in the function body on second phase, which means that `T` is not used in any way. 
In this case, the deducing for void makes no sense.

If the goal of this proposal is to gain the ability to not write a separate overload, 
then changing the type inference mechanism in the immediate context to do so seems questionable.