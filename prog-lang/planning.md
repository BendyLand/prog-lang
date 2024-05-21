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

} // Okay
```
```
if condition 
{

}
else 
{

} // Also okay 
```
```
if {

}
else {

} // Also okay
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

## Special Considerations

Source code files should end in `.pr`.

Programs are executed line-by-line, but definitions should be available throughout the file, unlike Python and Ruby (Two pass parsing? JIT compilation?).
___

## Annoying bits:

**Semicolons**... The more time I spend on this project, the less I think I will end up needing them! The bad news is that the solution looks like it will end up being kind of complex, and at first may come with some performance penalties. My thought is that I should be able to determine the end of each token by what the expected end token could/should be. However, this means that each expression will need a custom parsing strategy, likely adding some overhead.  

**Reserved words** will obviously be necessary. I'll be including several, from various other languages serving as sources of inspiration. They will all be lowercase, and while they may be familiar from existing languages, they may not always behave the same. I make no claim for trying to limit the scope of these, though I will try to only include ones that I feel are beneficial in some way. The proposed benefit could be anything from readability, to the location of the keys on the keyboard necessary for typing the word.  

**Performance** will be a priority of mine, although there is only so much that can be done for an interpreted language. Especially coming from someone with my level of experience (i.e. none), it could be a bit before any major optimizations happen.


