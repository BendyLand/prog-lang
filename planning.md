# Prog syntax

## Organization
My plan is to implement a:
### {} language without () for the condition, e.g.
```
if condition {

}
for condition {

}
```
etc.

as well as flexible placement:
```
if condition {

} else {

} # Okay
```
```
if condition 
{

}
else 
{

} # Also okay 
```
```
if {

}
else {

} # Also okay
```
___

Variables will be immutable by default:
```
let a = 10
a += 5
^------ Error: attempted change to immutable variable.
puts a # won't make it here
```
But can be declared as mutable at their definition:
```
let mut b = 15
b -= 5 # Okay
puts b # 10
```
___

## Extra Considerations (aka "Before I Forget")

 - Source code files should end in `.pr`.
 - Programs are executed line-by-line, but definitions should be available throughout the file, unlike Python and Ruby (Two pass parsing? JIT compilation?).
 - It might be neat to implement a REPL style execution environment, but that would be a non-priority to start.
 - Unclear error messages are the bane of my existence. My goal is to implement *painfully* clear error messages, even at the expense of what some people might call "professionalism". I personally don't see the point of making things as cryptic as possible, just so they are "academically" correct. It doesn't matter how correct something is if nobody knows how to handle it when it happens. 
   - An inevitable consequence of this is that the error messages will be very strongly tied to the behavior of the primitive building blocks of the language. This means that they may not offer much insight into why a more complex program is not working properly. You'll have to solve the logic yourself using those basic building blocks. That's the theme of this language; basic building blocks and that's it. 
___

