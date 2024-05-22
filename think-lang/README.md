# *Think* Language Development

*This project is in its early stages of development as of 5/22/24. It is currently non-functional and will not be for quite some time.*

## Background/Idea

This project was born out of the desire to have a very simple way to express logical ideas in a programming language.

I don't necessarily dislike the existing logic programming languages, such as Prolog and CLIPS, but I found myself getting more frustrated using them than I wanted to be. There were times when I just wanted a nice, easy way to quickly check a logical problem I had. Every single one of those times, I always found my way back to Python or Ruby and just wrote some imperative code to handle it. This is a fine workaround for most people and situations, and for the ones it isn't fine for, Prolog usually does the trick; but I wasn't satisfied with that.

So what's the remaining solution? To create my own, of course!

## About

*Think* is a general-purpose logic programming language with a focus on simplicity, built by someone who is (still) not a very experienced programmer, but who has always had a certain affinity for understanding and expressing logical concepts in the real world. Unlike my other language development project, *[Prog](../prog-lang/README.md)*, this is **not** a project made for the purpose of learning. Instead, I am viewing it as more of a chance for me to implement a tool that I don't see available in the current software landscape (which will happen to help me learn as I work on it... big difference).

## Name

I am calling this project *Think*. In my eyes, a general-purpose logic programming language should be able to offload some of the brainpower in decision-making from you onto your machine. Of course, they have their more "academic" uses, but my primary objective is to make a language that anyone can learn in less than a day, which will help them reason about, and *think* through their problems.

## Design

My goal is for this language to have a minimalist syntax which resembles a blend of high-level languages, like Python and Ruby, with a set of declarative terms which more closely resemble something like a SQL or LINQ query.

My other goal is for the language to be executable in the same way as an interpreted, general-purpose programming language. One of my biggest frustrations with Prolog is the need to either interact with your rules through REPL queries or by writing a main entry point and loading it into the shell. I was always looking for a nice, simple, script-looking file that I could run like an executable, so that is the design that I will be aiming for.

<!-- TODO: Add examples here to illustrate points."Providing a small code snippet or a before/after comparison with existing languages might help illustrate your points better." - Prof. GPT -->

## Types

As a logic language, the primary mechanism by which evaluation occurs is symbolic reasoning. This means that there are **no primitive data types in this language**.

Instead, the basic (and only) type that will comprise the data itself will be made up of plain text. This "type" has gone by many names in various settings: atoms, tokens, literals, etc.

*I* will be calling it the "data" type (*you* can call it whatever you like). While this is a mildly confusing design choice, there is a reason for it:

I find that too many technologies introduce (what I think is) unnecessary vernacular to their ecosystem. However, over time I've found that the justification for these design choices are frequently sound as well, *just not to the beginner programmer*. This resulted in a surprising amount of cognitive dissonance for me.
- The highly logical and technical side of me appreciates the attention to detail and correctness.
- However, the highly curious part of me, who loves trying various technologies (old, new, popular, niche, etc.) hates how much higher that places the barrier to entry for said technologies.

By eliminating **all** primitive types, the language will be able to condense all of the developer's input into a single type that represents the raw *data* to be examined at execution time. Left on its own, this is not very useful.

In addition to the "data" type, `Think` will include a variety of collection types. It is  the combination of these collections, as well as the operations provided by the keywords, which allow logical operations to be evaluated.

<!-- TODO: "Consider providing more examples of how this single "data" type would be used in practice. This will help readers visualize its application better." - Prof. GPT -->

## Keywords

While `Think` may not have a variety of data types, it will include several reserved keywords and symbols, which provide a significant amount of the functionality of the language. They will typically be used as a way to provide context to the data. For example:
```
person                           # Create data
parent = person                  # Create a fact for `parent`
child = person                   # Create a fact for `child`
child = parent + distinct parent # Create rule for `child`
```
 - In the code above, we create some data `person` on line 1. This is basically just a constant that represents arbitrary data.
 - On the next line, we assign that data to a variable called `parent`. If you are familiar with logic programming, this is the equivalent of a "fact".
 - We assign the same data to a variable called `child` on line 3. **This does not change anything we have previously done**.
     - You can think of lines 2 and 3 similarly to inheritance. However, unlike in OOP, this doesn't create any objects. It would be more accurate to say that this assigns the label "person" onto the variable "parent" and onto the variable "child".
 - Finally, we define that `child` is made up of `parent + parent`, using the keyword `distinct` to ensure that both parents are not the same person.
