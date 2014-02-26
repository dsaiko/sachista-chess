sachista-chess
==============

Simple and effective chess move generator and possible future chess engine implementation in C

Sachista-chess is a simple and (hopefully) effective implementation of chess move generator.

It may grow into UCI chess engine in a near future, but so far I just wanted to focus 
on implementing move-generator in a way which would satisfy me with both performance and code quality.

This is my probably fourth or fifth rewrite of move generation engine.

What I remember, my first try was quite a long ago, when I implemented chess-moves generation in Java from scratch, 
then rewriting that into C++. Without reading any chess-programming articles, this code worked well, 
but the first move generation produced only around 20.000 legal moves per a second 
(on common hardware relevant to let's say year 2006). 
Later on, I experimented with rewriting this generator to Scala, which ... well ... was not really any faster ;-). 
Just an experiment. I also created a simple Java Swing GUI for my chess programming that time, 
I think it looked quite OK. But well, Swing is dead.

In year 2013, I created a "proper" version of a generator and basic UCI chess-engine in Java, 
implementing magic-chessboard mechanism. As I really did not like the engine part, 
I rather deleted it and tried to make just the generator as good as possible. 
My code is generating pseudo-legal moves which needs a makemoverification for perft, in Java version, 
this was generating around 12.000.000 legal combinations per second in one thread and around 72.000.000 
when running in multithreaded version on my current notebook using Java7 fork-and-join framework.

After being upset with Java (will not list the reasons here, but as a long time Java developer 
I have my own opinion), I decided to rewrite the engine again, this time into C and hunt performance. 
I was able to achieve 35.000.000 of legal moves per a second with my perft(3x faster than almost (90%) the same 
solution in Java) (still the same notebook), but comparing those results to stockfish chess engine, I was not happy. 
Stockfish perft runs around 120.000.000 positions per seconds, but that's only because it generates legal moves 
(vs my pseudo-legal generator) and does not make the move for the last generated ply (no need to make-unmake).
Forcing stockfish to generate even the leaves moves, my performance was better, as stockfish was generating around 
25.000.000 legal positions /s.

Adding OpenMP Multithreading and perft caching boosted my perft results to the sky ... see peft results

Generator in a nutshell:

- C language, C99 standard, CMake
- tested on x64 and x86 Linux and Windows platforms, compiled by GCC and ICC
- OpenMP multi threading
- CppUTest unit testing suite
- valid perft with multithreading and position cache
- no unmake-move, using board-copy for perft
- posible future paths: chess gui or chess engine


Would like to give a credit to following sources which were my (technical or motivation) inspiration:

- Mediocre Chess blog
- Chess programming wiki
- Stockfish
- Phalanx

*note on unmake move: I have implemented unmake move, but that code is not very clear and it still required 
additional arrays where non-recoverable info would be stored. 
Then I deleted unmake move and replaced it simply with currentBoard=*boardBackup; board backuping. 
Code is cleaner, performance the same in my case.
