# Prog syntax

## Organization
I'm considering either a:
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
if condition {

}
else {

} # Also okay
```

### or a non {} language without () for conditions, with required opening and closing statements e.g.
```
if condition then 

elif condition then

end 
```
```
for condition do

end 
```
most likely the former. 

___

## Special Considerations (aka "Before I Forget")

Source code files should end in `.pr`.

Programs are executed line-by-line, but definitions should be available throughout the file, unlike Python and Ruby (Two pass parsing? JIT compilation?).

It might be neat to implement a REPL style execution environment, but that would be a non-priority to start.
___

