# *Think* Language Development

## Background/Idea

This project was born out of the desire to have a very simple way to express logical ideas in a programming language.

I don't necessarily dislike the existing logic programming languages, such as Prolog and CLIPS, but I found myself getting more frustrated with them than I wanted to be. So what's the obvious solution? To create my own, of course!

## About

*Think* is a general-purpose logic programming language built by someone who is (still) not a very experienced programmer, but who has always had a certain affinity for understanding and expressing logical concepts in the real world. Unlike my other language development project, *[Prog](../../prog-lang/README.md)*, this is **not** a learning project. Instead, I am viewing it as more of a chance for me to implement a tool that I don't see available in the current software landscape (which will happen to help me learn as I work on it... big difference).  

## Name

I am calling this project *Think*. In my eyes, a general-purpose logic programming language should be able to offload some of the brainpower in decision-making from you onto your machine. Of course, they have their more "academic" uses, but my primary objective is to make a language that anyone can learn in less than a day, which will help them reason about, and *think* through their problems. 

## Design

My goal is for this language to have a minimalist syntax which resembles a blend of high-level languages, like Python and Ruby, with a set of declarative terms which more closely resemble something like a SQL or LINQ query. 

My other goal is for the language to be executable in the same way as an interpreted, general-purpose programming language. One of my biggest frustrations with Prolog is the need to either interact with your rules through REPL queries or by writing a main entry point and loading it into the shell. I just wanted to be able to write something that looks like a nice, simple script (Bash/Python/Ruby/etc.), run the language interpreter, and have it spit out a result at the end. Apparently, this was too much to ask for, so now I'm doing it myself.